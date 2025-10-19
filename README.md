# Software Tools and Techniques for CSE
## Assignment - 7

Shah Harshil Hardik (Roll No. 23110132), Sonawane Samarth Awinash (23110317)

---

This assignment was meant to create a static analyzer for `C` programs which can be used to create Control Flow Graphs (CFGs), analyze Cyclomatic Complexity (CC) and perform Reaching Defintion Analysis (RDA).
To use the static analyzer created in this assignment, use the below snippet to test you `C` program with this static analyzer.

```console
python static_analyzer.py <path-to-C-file>
```

This would generate the `.dot` files for the graphs, rendered control flow graph in `.png` format and the results of reaching defintion analysis. 
