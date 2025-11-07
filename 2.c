#include <stdio.h>
#include <string.h>

int main() {
    char data[100], temp[100], div[100], div1[100], quot[100], rem[100];
    printf("Enter data: ");
    scanf("%s", data);
    printf("\nEnter divosor: ");
    scanf("%s", div);

    int datalen = strlen(data);
    int divlen = strlen(div);

    for (int i = 0; i < divlen - 1; i++) {
        data[datalen+i] = '0';
    }
    data[datalen+divlen - 1] = '\0';

    strcpy(temp, data);
    strcpy(div1, div);

    for (int i = 0; i < datalen; i++) {
        quot[i] = temp[0];
        if (quot[i] == '0') {
            for (int j = 0; j < divlen; j++) {
                div[j] = '0';
            }
        } else {
            strcpy(div, div1);
        }

        for (int j = 1; j < divlen; j++) {
            rem[j-1] = (temp[j] == div[j]) ? '0': '1';
        }

        rem[divlen-1] = data[i+divlen];
        rem[divlen] = '\0';
        strcpy(temp, rem);
    }

    quot[datalen] = '\0';
    strcpy(rem, temp);

    printf("Quotient: %s\n", quot);
    printf("Remainder: %s\n", rem);

    for (int i = 0; i < divlen; i++) {
        data[datalen+i] = rem[i];
    }

    data[datalen+divlen-1] = '\0';
    printf("Final Data is: %s\n", data);
    return 0;
}
