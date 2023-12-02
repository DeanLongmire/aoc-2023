#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int processChar(char hexNum) {
    int intNum;
    char *stringNum = malloc(2);

    stringNum[0] = hexNum;
    stringNum[1] = '\0';
    intNum = atoi(stringNum);
    free(stringNum);

    return intNum;
}

int processLine(int firstNum, int secondNum, char *line, int lineNumber) {
    int combinedNum;

    combinedNum = firstNum * 10;
    combinedNum += secondNum;

    return combinedNum;
}

int isNum(char num) {
    return num > '0' && num <= '9';
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

    int iLine = 0;
    int j;

    for(int i = 0; i < fileLength; i++) {
        if(inputBuf[i] == 0x0A) { //new line character
            lineCounter++;
            char *line = malloc(iLine + 1);

            for(j = 0; j <= iLine - 1; j++) {
                line[j] = inputBuf[i - (iLine - j)];
            }
            line[j] = '\0';

            // printf("Line %d: %s\n", lineCounter, line);

            lineSum = processLine(firstNum, secondNum, line, lineCounter);
            //printf("Line %d: %d\n", lineCounter, lineSum);

            totalSum += lineSum;
            firstNumSet = 0;
            // printf("Line %d: %d characters long\n",lineCounter,iLine);
            iLine = 0;
            free(line);
            continue;
        } else if(isNum(inputBuf[i])) { //is a number
            if(firstNumSet) {
                secondNum = processChar(inputBuf[i]);
            } else {
                firstNum = processChar(inputBuf[i]);
                secondNum = processChar(inputBuf[i]);
                firstNumSet = 1;
            }
        }
        iLine++;
    }

    printf("%d number of lines in file.\n", lineCounter);
    printf("Total sum: %d\n", totalSum);

    fclose(file);
    free(inputBuf);
}