#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// #define LEN 30000

bool is_digit(char c) {
    return (c >= '0' && c <= '9'); 
}

int sum(int arr[], int n) {
    if (n == 0) {
        return 0;
    } else {
        return arr[0] + sum(arr + 1, n - 1);
    }
}

int main() {
    char *filename = "input.txt";
    FILE *fp = fopen(filename, "r");
	int LEN = 30000;
    char input_str[LEN]; // Have to allocate memory, why?

    int task_answer[LEN] = {};
    int i = 0;
    while (fgets(input_str, LEN, fp)) {

        size_t length = strlen(input_str);
        // printf("%d %s", length, input_str);
        for (size_t j = 0; j < length; j++){
            if (is_digit(input_str[j]) == true) {
                // printf("%d\n", (input_str[j] - '0')*10);
                task_answer[i] = (input_str[j] - '0')*10;
                break;
            }
        }
        for (size_t j = length; j > 0; j--){
            if (is_digit(input_str[j]) == true) {
                // printf("%d\n", (input_str[j] - '0'));
                task_answer[i] = task_answer[i] + (input_str[j] - '0');
                // printf("%d\n", task_answer[i]);
                break;
            }
        }
        i++;
    }
    printf("Answ sum: %d\n", sum(task_answer, sizeof(task_answer)/sizeof(task_answer[0])));

    fclose(fp);

    return 0;
}
