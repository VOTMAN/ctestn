#include <stdio.h>
#include <string.h>

int main() {
    int i, j, c = 0;
    char input[1000], output[1000];
    printf("Enter the frames(0s & 1s): \n");
    scanf("%s", &input);
    int n = strlen(input);
    strcpy(output, "01111110");
    j = strlen(output);

    for (int i = 0; i < n; i++) {
        output[j++] = input[i];
        if (input[i] == '1') {
            c++;
            if (c==5) {
                output[j++] = 0;
                c=0;
            }
        } else {
            c = 0;
        }
    }

    strcpy(output+j, "01111110");
    printf("After Bit Stuffin the output is: ");
    puts(output);
    return 0;
}
