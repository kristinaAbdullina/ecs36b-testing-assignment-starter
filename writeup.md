# Writeup

## Things I Thought To Test

When writing my tests, I focused on verifying correctness, edge cases, and making sure functions did not unintentionally modify data.

For the `swap` function, I tested swapping two individual values and swapping elements inside an array. I also made sure that only the intended values changed and the rest of the array stayed the same.

For `copy_array`, I tested that the copied array had the same values as the original, that the original array was not modified, and that a true copy was created (meaning the memory addresses were different).

For `min_index_of_array`, I tested cases where the minimum value appears at the beginning, middle, and end of the array. I also tested arrays with duplicate minimum values to ensure the function returns the first occurrence. Additionally, I verified that calling the function does not change the array.

For `make_sorted`, I tested arrays that were already sorted, reverse sorted, randomly ordered, and containing duplicate values. I also used property-based tests to confirm that the output is always in ascending order.

For `get_sorted`, I tested that the returned array is sorted correctly, that the original array remains unchanged, and that the returned array is a separate copy in memory.

For `parse_args`, I tested parsing normal integer inputs from command-line arguments and the case where no arguments are provided. I also used property-based testing to ensure correct parsing for multiple random inputs.

---

## Bug 1

**Where the bug is:**
`sorting.cpp` → `swap`

**How I found the bug:**
The swap tests failed because the values did not change after calling the function.

**Description of the bug:**
The function swapped the pointer variables instead of the values they pointed to, so the actual data remained unchanged.

**How I fixed the bug:**

```c
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
```

---

## Bug 2

**Where the bug is:**
`sorting.cpp` → `copy_array`

**How I found the bug:**
Tests checking whether a copy was created failed because the returned pointer was the same as the original array.

**Description of the bug:**
The function returned the original pointer instead of allocating new memory and copying values.

**How I fixed the bug:**

```c
int* copy_array(int* ar, int len) {
    int* copy = (int*)malloc(sizeof(int) * len);
    for (int i = 0; i < len; ++i) {
        copy[i] = ar[i];
    }
    return copy;
}
```

---

## Bug 3

**Where the bug is:**
`sorting.cpp` → `min_index_of_array`

**How I found the bug:**
Tests failed when the minimum value was not at the first position.

**Description of the bug:**
The function used the wrong comparison operator and returned the value instead of the index.

**How I fixed the bug:**

```c
int min_index_of_array(int* ar, int len) {
    int min_index = 0;
    for (int i = 1; i < len; ++i) {
        if (ar[i] < ar[min_index]) {
            min_index = i;
        }
    }
    return min_index;
}
```

---

## Bug 4

**Where the bug is:**
`sorting.cpp` → `make_sorted`

**How I found the bug:**
Sorting tests failed for unsorted and reverse-sorted arrays.

**Description of the bug:**
The function used the wrong length when searching for the minimum and did not correctly offset the index for swapping.

**How I fixed the bug:**

```c
void make_sorted(int* ar, int len) {
    for (int i = 0; i < len; ++i) {
        int min_index = min_index_of_array(ar + i, len - i);
        swap(ar + i, ar + i + min_index);
    }
}
```

---

## Bug 5

**Where the bug is:**
`sorting.cpp` → `get_sorted`

**How I found the bug:**
Tests showed that the original array was being modified.

**Description of the bug:**
The function sorted the original array instead of the copied array.

**How I fixed the bug:**

```c
int* get_sorted(int* ar, int len) {
    int* sorted_ar = copy_array(ar, len);
    make_sorted(sorted_ar, len);
    return sorted_ar;
}
```

---

## Bug 6

**Where the bug is:**
`formatting.cpp` → `print_ar`

**How I found the bug:**
The program did not correctly print array values.

**Description of the bug:**
The loop decremented instead of incrementing, causing incorrect iteration.

**How I fixed the bug:**

```c
for (int i = 0; i < len; ++i)
```

---

## Bug 7

**Where the bug is:**
`formatting.cpp` → `parse_args`

**How I found the bug:**
Parsing tests failed and sometimes caused incorrect results.

**Description of the bug:**
The function had multiple issues: incorrect pointer type, wrong memory allocation size, incorrect argument indexing, and incorrect `sscanf` usage.

**How I fixed the bug:**

```c
void parse_args(int argc, char** argv, int** ar_out, int* len_out) {
    *len_out = argc - 1;

    if (*len_out <= 0) {
        *ar_out = NULL;
        return;
    }

    *ar_out = (int*)malloc(sizeof(int) * (*len_out));

    for (int i = 0; i < *len_out; ++i) {
        sscanf(argv[i + 1], "%d", &((*ar_out)[i]));
    }
}
```

---

## Conclusion

Through writing tests and debugging the code, I was able to identify multiple issues related to pointer usage, memory allocation, and incorrect logic. Writing both unit tests and property-based tests helped ensure that the program works correctly across many different cases.
