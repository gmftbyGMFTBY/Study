import the libaray
```c
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
```

void qsort(void *ptr, size_t count, size_t size, int(*comp)(const void*, const void *));
    * ptr: pointer to the array
    * count: number of the element in the array
    * size: size of each element
    * comp: comparison function
        ```c
        int compare_ints(const void* a, const void* b)
        {
            int arg1 = *(const int*)a;
            int arg2 = *(const int*)b;
            
            // add sort
            if (arg1 < arg2) return -1;
            if (arg1 > arg2) return 1;
            return 0;

            // return (arg1 > arg2) - (arg1 < arg2); // possible shortcut
            // return arg1 - arg2; // erroneous shortcut (fails if INT_MIN is present)
        }
        ```
