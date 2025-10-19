int main() {
    int data[100];
    int n = 30;
    int choice, i, j, temp;
    double mean = 0.0, variance = 0.0, stddev = 0.0;
    int minVal, maxVal;
    int key, found;
    srand(10);

    for (i = 0; i < n; i++) {
        data[i] = rand() % 100;
    }

    while (1) {
        printf("\n=== DATA ANALYSIS TOOL ===\n");
        printf("1. Display Data\n");
        printf("2. Compute Mean, Variance, Std Dev\n");
        printf("3. Find Min and Max\n");
        printf("4. Sort Data (Bubble Sort)\n");
        printf("5. Sort Data (Insertion Sort)\n");
        printf("6. Linear Search\n");
        printf("7. Binary Search (on sorted data)\n");
        printf("8. Filter Values (Above Threshold)\n");
        printf("9. Replace Negative Values\n");
        printf("10. Shuffle Data\n");
        printf("11. Generate New Data\n");
        printf("12. Check if Data is Increasing/Decreasing\n");
        printf("13. Check if Data is Constant\n");
        printf("14. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Data: ");
            for (i = 0; i < n; i++) {
                printf("%d ", data[i]);
            }
            printf("\n");
        } 
        else if (choice == 2) {
            mean = 0.0;
            for (i = 0; i < n; i++) {
                mean += data[i];
            }
            mean /= n;

            variance = 0.0;
            for (i = 0; i < n; i++) {
                variance += (data[i] - mean) * (data[i] - mean);
            }
            variance /= n;
            stddev = sqrt(variance);

            printf("Mean: %.2f, Variance: %.2f, Std Dev: %.2f\n", mean, variance, stddev);
        } 
        else if (choice == 3) {
            minVal = data[0];
            maxVal = data[0];
            for (i = 1; i < n; i++) {
                if (data[i] < minVal)
                    minVal = data[i];
                else if (data[i] > maxVal)
                    maxVal = data[i];
            }
            printf("Min: %d, Max: %d\n", minVal, maxVal);
        } 
        else if (choice == 4) {
            for (i = 0; i < n - 1; i++) {
                for (j = 0; j < n - i - 1; j++) {
                    if (data[j] > data[j + 1]) {
                        temp = data[j];
                        data[j] = data[j + 1];
                        data[j + 1] = temp;
                    }
                }
            }
            printf("Data sorted using Bubble Sort.\n");
        } 
        else if (choice == 5) {
            for (i = 1; i < n; i++) {
                temp = data[i];
                j = i - 1;
                while (j >= 0 && data[j] > temp) {
                    data[j + 1] = data[j];
                    j--;
                }
                data[j + 1] = temp;
            }
            printf("Data sorted using Insertion Sort.\n");
        } 
        else if (choice == 6) {
            printf("Enter value to search: ");
            scanf("%d", &key);
            found = 0;
            for (i = 0; i < n; i++) {
                if (data[i] == key) {
                    printf("Value found at index %d\n", i);
                    found = 1;
                    break;
                }
            }
            if (!found)
                printf("Value not found.\n");
        } 
        else if (choice == 7) {
            printf("Enter value to search: ");
            scanf("%d", &key);
            int low = 0, high = n - 1, mid;
            found = 0;
            while (low <= high) {
                mid = (low + high) / 2;
                if (data[mid] == key) {
                    printf("Value found at index %d\n", mid);
                    found = 1;
                    break;
                } else if (data[mid] < key) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
            if (!found)
                printf("Value not found.\n");
        } 
        else if (choice == 8) {
            int threshold;
            printf("Enter threshold: ");
            scanf("%d", &threshold);
            printf("Values above %d: ", threshold);
            for (i = 0; i < n; i++) {
                if (data[i] > threshold)
                    printf("%d ", data[i]);
            }
            printf("\n");
        } 
        else if (choice == 9) {
            int replaced = 0;
            for (i = 0; i < n; i++) {
                if (data[i] < 0) {
                    data[i] = abs(data[i]);
                    replaced++;
                }
            }
            printf("Replaced %d negative values.\n", replaced);
        } 
        else if (choice == 10) {
            for (i = 0; i < n; i++) {
                int r = rand() % n;
                temp = data[i];
                data[i] = data[r];
                data[r] = temp;
            }
            printf("Data shuffled.\n");
        } 
        else if (choice == 11) {
            printf("Enter new size (<=100): ");
            scanf("%d", &n);
            if (n <= 0 || n > 100) {
                printf("Invalid size.\n");
                n = 30;
            }
            for (i = 0; i < n; i++) {
                data[i] = rand() % 200 - 100;
            }
            printf("New data generated.\n");
        } 
        else if (choice == 12) {
            int increasing = 1, decreasing = 1;
            for (i = 1; i < n; i++) {
                if (data[i] > data[i - 1])
                    decreasing = 0;
                else if (data[i] < data[i - 1])
                    increasing = 0;
            }
            if (increasing)
                printf("Data is sorted in increasing order.\n");
            else if (decreasing)
                printf("Data is sorted in decreasing order.\n");
            else
                printf("Data is unsorted.\n");
        }
        else if (choice == 13) {
            int constant = 1;
            for (i = 1; i < n; i++) {
                if (data[i] != data[i - 1]) {
                    constant = 0;
                    break;
                }
            }
            if (constant)
                printf("All data values are constant.\n");
            else
                printf("Data values are not constant.\n");
        } 
        else if (choice == 14) {
            printf("Exiting program.\n");
            break;
        } 
        else {
            printf("Invalid choice! Try again.\n");
        }

        if (n > 50) {
            printf("Warning: Large dataset, computations may slow down.\n");
        } else if (n < 10) {
            printf("Dataset is too small for statistical analysis.\n");
        }

        int sanity = 1;
        for (i = 0; i < n; i++) {
            if (data[i] > 1000 || data[i] < -1000) {
                sanity = 0;
                break;
            }
        }
        if (!sanity)
            printf("Sanity check failed: extreme values found!\n");
    }

    printf("Final dataset:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", data[i]);
        if ((i + 1) % 10 == 0)
            printf("\n");
    }

    printf("\nProgram terminated successfully.\n");
    return 0;
}
