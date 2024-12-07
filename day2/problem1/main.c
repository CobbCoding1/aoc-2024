#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE "input.txt"

int compare(const void *a_v, const void *b_v) {
    return *(int*)a_v > *(int*)b_v;
}

typedef enum {
    NONE,
    INCREASE,
    DECREASE
} Status;

int main() {
    FILE *f = fopen(INPUT_FILE, "r");
    int prev_num = 0;
    int num = 0;
    Status stat = NONE;
    int safe = 1;
    size_t total = 0;
    while(fscanf(f, "%d", &num) != EOF) {
        printf("%d ", num);
        Status new_stat = NONE;
        if(prev_num != 0) {
            int dif = num - prev_num;
            if(dif > 0 && abs(dif) <= 3 && abs(dif) >= 1) {
                new_stat = INCREASE;
            } else if(dif < 0 && abs(dif) <= 3 && abs(dif) >= 1) {
                new_stat = DECREASE;
            } else
                safe = 0;

            if(new_stat != stat && stat != NONE)
                safe = 0;
            printf("%d %d\n", stat, new_stat);
            stat = new_stat;
        }        
        prev_num = num;
        char ch = '\0';
        if(fscanf(f, "%c", &ch) && ch == '\n') {
            printf("NEWLINE: %d\n", safe);
            total += safe;
            safe = 1;
            stat = NONE;
            prev_num = 0;
            continue;
        }
        fscanf(f, " ");
    }
    printf("%zu\n", total);
    return 0;
}
