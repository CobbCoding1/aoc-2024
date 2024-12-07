#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE "testinput.txt"
typedef enum {
    NONE,
    INCREASE,
    DECREASE,
    INVALID
} Status;

Status compare(int *line, size_t index, int removed) {
    Status ret = NONE;
    size_t first = index;
    size_t second = index-1;
    if(first == removed)
        first++;
    else if(second == removed) {
        second--;
    }
    int dif = line[first] - line[second];
    if(dif > 0 && abs(dif) >= 1 && abs(dif) <= 3)
        ret = INCREASE;
    else if(dif < 0 && abs(dif) >= 1 && abs(dif) <= 3)
        ret = DECREASE;
    else
        ret = INVALID;
    return ret;
}

int main() {
    FILE *f = fopen(INPUT_FILE, "r");
    int line[20000] = {0};
    size_t line_s = 0;
    char symb = '\0';
    size_t total = 0;
    int out = 1;
    while(1) {
        do {
            out = fscanf(f, "%d%c", &line[line_s++], &symb);
        } while(symb != '\n');
        if(out == EOF) break;
        Status stat = NONE;
        Status new_stat = NONE;
        int invalid = 1;
        for(size_t i = 1; i < line_s; i++) {
            for(int removed = -1; removed < line_s; removed++) {
                printf("%d %d\n", removed, line_s);
                if(removed == 0) continue;
                new_stat = compare(line, i, removed);
                printf("stat: %d, new_stat: %d ", stat, new_stat);
                if(stat != NONE && new_stat != stat) {
                    new_stat = INVALID;
                    invalid = 0;
                }
                stat = new_stat;
            }
        }
        printf("\n %d\n", invalid);
        total += invalid;
        line_s = 0;
    }
    printf("%zu\n", total);
    return 0;
}
