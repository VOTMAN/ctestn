#include <stdio.h>
#include <string.h>

int main() {
    int i, j, c = 0;
    char input[50], output[50];
    printf("Enter the frame: \n");
    scanf("%s", input);
    int n = strlen(input);
    strcpy(output, "flag");
    j = strlen(output);

    for (int i = 0; i < n; i++) {
        if (input[i] == 'f' && input[i+1] == 'l' && input[i+2] == 'a' && input[i + 3] == 'g') {
            output[j++] = 'e';
            output[j++] = 's';
            output[j++] = 'c';
        } else if (input[i] == 'e' && input[i+1] == 's' && input[i+2] == 'c') {
            output[j++] = 'e';
            output[j++] = 's';
            output[j++] = 'c';
        }
        output[j++] = input[i];
    }

    strcpy(output+j, "flag");
    printf("After char stuffing the output is: ");
    puts(output);
}
