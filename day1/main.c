#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE "input.txt"

int compare(const void *a_v, const void *b_v) {
    return *(int*)a_v > *(int*)b_v;
}

int main() {
    FILE *f = fopen(INPUT_FILE, "r");
    int left[1024] = {0};
    int right[1024] = {0};
    size_t left_s = 0;
    size_t right_s = 0;
    int lhs = 0;
    int rhs = 0;
    while(fscanf(f, "%d %d\n", &lhs, &rhs) != EOF) {
        left[left_s++] = lhs;
        right[right_s++] = rhs;
    }
    qsort(left, left_s, sizeof(*left), compare);
    qsort(right, right_s, sizeof(*left), compare);
    size_t dif = 0;
    for(size_t i = 0; i < left_s; i++) {
        dif += abs(left[i] - right[i]);
    }
    printf("%zu\n", dif);
    return 0;
}
