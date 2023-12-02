#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int processChar(char hexNum) {
    int intNum;
    char *stringNum = malloc(1);

    stringNum[0] = hexNum;
    intNum = atoi(stringNum);
    free(stringNum);

    return intNum;
}

int processLine(int firstNum, int secondNum) {
    int combinedNum;

    combinedNum = firstNum * 10;
    combinedNum += secondNum;

    return combinedNum;
}

int isNum(char num) {
    switch (num) {
        case 0x31:
            return 1;
        case 0x32:
            return 1;
        case 0x33:
            return 1;
        case 0x34:
            return 1;
        case 0x35:
            return 1;
        case 0x36:
            return 1;
        case 0x37:
            return 1;
        case 0x38:
            return 1;
        case 0x39:
            return 1;
    }

    return 0;
}

int main(int argc, char **argv) {
    FILE *file;
    int fileLength;
    int firstNum, secondNum, lineSum, totalSum = 0;
    int lineCounter = 0;
    int firstNumSet = 0;
    char *inputBuf;

    file = fopen("input.txt", "r");

    fseek(file, 0, SEEK_END);
    fileLength = ftell(file);
    fseek(file, 0, SEEK_SET);
    printf("File is %d bytes long.\n", fileLength);

    inputBuf = malloc(fileLength);

    fread(inputBuf, 1, fileLength, file);

    for(int i = 0; i < fileLength; i++) {
        if(inputBuf[i] == 0x0A) { //new line character
            lineCounter++;

            lineSum = processLine(firstNum, secondNum);
            printf("Line %d: %d\n", lineCounter, lineSum);

            totalSum += lineSum;
            firstNumSet = 0;
        } else if(isNum(inputBuf[i])) { //is a number
            if(firstNumSet) {
                secondNum = processChar(inputBuf[i]);
            } else {
                firstNum = processChar(inputBuf[i]);
                secondNum = processChar(inputBuf[i]);
                firstNumSet = 1;
            }
        }
    }

    printf("%d number of lines in file.\n", lineCounter);
    printf("Total sum: %d\n", totalSum);

    fclose(file);
}