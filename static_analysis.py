import re
from graphviz import Digraph
import pandas as pd
from collections import defaultdict
import argparse

class CFGBuilder:
    def __init__(self, code):
        # Split code into lines if it's a single string
        if isinstance(code, str):
            code = code.splitlines()
        # Remove empty lines
        self.code = [line.strip() for line in code if line.strip()]
        self.leaders = set()
        self.basic_blocks = []
        self.edges = []
        self.block_map = {}

        # For Reaching Definitions
        self.definitions = {}
        self.line_to_def = {}
        self.gen = {}
        self.kill = {}
        self.in_sets = defaultdict(set)
        self.out_sets = defaultdict(set)

    def find_leaders(self):
        self.leaders.add(0)  # First line is always a leader

        for i, line in enumerate(self.code):
            if re.match(r'^(if|while|for)\s*\(.*\)', line):
                self.leaders.add(i)
                if i + 1 < len(self.code):
                    self.leaders.add(i + 1)
            elif re.match(r'^else', line):
                # if re.match(r'^else if', line):
                #     self.leaders.add(i)
                if i + 1 < len(self.code):
                    self.leaders.add(i + 1)

        # Lines after control blocks
        for i, line in enumerate(self.code):
            if re.match(r'^(if|while|for)\s*\(.*\)', line):
                brace_count = 0
                for j in range(i, len(self.code)):
                    brace_count += self.code[j].count('{')
                    brace_count -= self.code[j].count('}')
                    if brace_count == 0:
                        if j + 1 < len(self.code):
                            self.leaders.add(j + 1)
                        break

        self.leaders = sorted(list(self.leaders))
        self.basic_blocks = self.build_basic_blocks()
        # print(self.basic_blocks)

    def build_basic_blocks(self):
        blocks = []
        for i, leader in enumerate(self.leaders):
            start = leader
            end = self.leaders[i + 1] if i + 1 < len(self.leaders) else len(self.code)
            block = self.code[start:end]
            self.block_map[start] = len(blocks)
            blocks.append(block)
        return blocks

    def create_edges(self):
        for i, block in enumerate(self.basic_blocks):
            last = block[-1]
            # Sequential edge
            if not re.match(r'^(if|else|while|for|return|goto)', last):
                if i + 1 < len(self.basic_blocks):
                    self.edges.append((i, i + 1, ""))

            # Conditional if
            if re.match(r'^if\s*\(.*\)', last):
                if i + 1 < len(self.basic_blocks):
                    self.edges.append((i, i + 1, "T"))

                brace_count = 0
                for j in range(self.leaders[i], len(self.code)):
                    brace_count += self.code[j].count('{')
                    brace_count -= self.code[j].count('}')
                    if brace_count == 0:
                        next_leader = self.block_map.get(j + 1)
                        if next_leader is not None and next_leader != i + 1:
                            self.edges.append((i, next_leader, "F"))
                        break

            # Else
            if re.match(r'^else', last):
                if i + 1 < len(self.basic_blocks):
                    self.edges.append((i, i + 1, ""))

            # Loops
            if re.match(r'^(while|for)\s*\(.*\)', last):
                if i + 1 < len(self.basic_blocks):
                    self.edges.append((i, i + 1, "T"))

                brace_count = 0
                for j in range(self.leaders[i], len(self.code)):
                    brace_count += self.code[j].count('{')
                    brace_count -= self.code[j].count('}')
                    if brace_count == 0:
                        next_leader = self.block_map.get(j + 1)
                        if next_leader is not None:
                            self.edges.append((i, next_leader, ""))
                            self.edges.append((next_leader, i, ""))
                        break

        # Remove duplicates
        self.edges = list(dict.fromkeys(self.edges))

    def calculate_cyclomatic_complexity(self):
        N = len(self.basic_blocks)
        E = len(self.edges)
        CC = E - N + 2
        print("\n===== CFG METRICS =====")
        print(f"Number of Nodes (N): {N}")
        print(f"Number of Edges (E): {E}")
        print(f"Cyclomatic Complexity (CC): {CC}")
        print("========================\n")
        return N, E, CC

    def build_cfg(self):
        self.find_leaders()
        self.create_edges()
        self.calculate_cyclomatic_complexity()
        return self.basic_blocks, self.edges

    def to_dot(self, filename="cfg.dot"):
        dot = Digraph(name="CFG", format="png")
        dot.attr("node", shape="box", fontsize="10", width="3", height="0.5", fixedsize="false")

        for i, block in enumerate(self.basic_blocks):
            label = "\n".join(block)
            dot.node(f"B{i}", label=label)

        for src, dst, label in self.edges:
            dot.edge(f"B{src}", f"B{dst}", label=label if label else "")

        output_path = dot.render(filename, view=False)
        print(f"CFG graph generated: {output_path}")

    def find_definitions(self):
        count = 1
        assign_re = re.compile(r"(?:\b(?:int|float|double|char|long|short|bool)\b\s+)?([a-zA-Z_]\w*)\s*=")
        for i, block in enumerate(self.basic_blocks):
            for line in block:
                match = assign_re.match(line)
                # print("Line:", line, "Match:", match)
                if match:
                    var = match.group(1)
                    # print("Var", var)
                    def_id = f"D{count}"
                    self.definitions[def_id] = var
                    self.line_to_def[line] = def_id
                    count += 1

    def compute_gen_kill(self):
        for i, block in enumerate(self.basic_blocks):
            gen_set = set()
            kill_set = set()
            for line in block:
                if line in self.line_to_def:
                    def_id = self.line_to_def[line]
                    var = self.definitions[def_id]
                    for d, v in self.definitions.items():
                        if v == var and d != def_id:
                            kill_set.add(d)
                    gen_set.add(def_id)
            self.gen[i] = gen_set
            self.kill[i] = kill_set

    def compute_predecessors(self):
        preds = defaultdict(list)
        for src, dst, _ in self.edges:
            preds[dst].append(src)
        return preds

    def reaching_definition_analysis(self, program_name="program"):
        print(program_name)
        self.find_definitions()
        self.compute_gen_kill()
        preds = self.compute_predecessors()
        changed = True
        iteration = 1
        while changed:
            changed = False

            for i in range(len(self.basic_blocks)):
                in_set = set()
                for p in preds.get(i, []):
                    in_set |= self.out_sets[p]

                out_set = self.gen[i] | (in_set - self.kill[i])

                if in_set != self.in_sets[i] or out_set != self.out_sets[i]:
                    changed = True
                    self.in_sets[i] = in_set
                    self.out_sets[i] = out_set

            iteration += 1
        
        data = []
        for i in range(len(self.basic_blocks)):
            data.append({
                'Block': f'B{i}',
                'gen[B]': self.gen[i] if self.gen[i] else {},
                'kill[B]': self.kill[i] if self.kill[i] else {},
                'in[B]': self.in_sets[i] if self.in_sets[i] else {},
                'out[B]': self.out_sets[i] if self.out_sets[i] else {},
            })
        # print(data)
        df = pd.DataFrame(data)
        df.to_csv(f"reaching_definitions_output_{program_name}.csv", index=False)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Build CFG and perform Reaching Definitions Analysis on a given C program."
    )
    parser.add_argument(
        "filename",
        help="Path to the target C source file (e.g., code2.c)"
    )
    args = parser.parse_args()

    with open(args.filename) as f:
        code = f.read()

    cfg = CFGBuilder(code)
    cfg.build_cfg()

    output_name = args.filename.rsplit(".", 1)[0]
    cfg.to_dot(filename=f"{output_name}_cfg")
    cfg.reaching_definition_analysis(program_name=output_name)
