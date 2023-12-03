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

int isNumString(char c, char* line, int startIndex) {
    switch(c) {
        case 'o':
            if(line[startIndex + 1] == 'n') {
                if(line[startIndex + 2] == 'e') {
                    return 1;
                }
            }
            return -1;
        case 't':
            if(line[startIndex + 1] == 'w') {
                if(line[startIndex + 2] == 'o') {
                    return 2;
                }
            } else if(line[startIndex + 1] == 'h') {
                if(line[startIndex + 2] == 'r') {
                    if(line[startIndex + 3] == 'e') {
                        if(line[startIndex + 4] == 'e') {
                            return 3;
                        }
                    }
                }
            }
            return -1;
        case 'f':
            if(line[startIndex + 1] == 'o') {
                if(line[startIndex + 2] == 'u') {
                    if(line[startIndex + 3] == 'r') {
                        return 4;
                    }
                }
            } else if(line[startIndex + 1] == 'i') {
                if(line[startIndex + 2] == 'v') {
                    if(line[startIndex + 3] == 'e') {
                        return 5;
                    }
                }
            }
            return -1;
        case 's':
            if(line[startIndex + 1] == 'i') {
                if(line[startIndex + 2] == 'x') {
                    return 6;
                }
            } else if(line[startIndex + 1] == 'e') {
                if(line[startIndex + 2] == 'v') {
                    if(line[startIndex + 3] == 'e') {
                        if(line[startIndex + 4] == 'n') {
                            return 7;
                        }
                    }
                }
            }
            return -1;
        case 'e':
            if(line[startIndex + 1] == 'i') {
                if(line[startIndex + 2] == 'g') {
                    if(line[startIndex + 3] == 'h') {
                        if(line[startIndex + 4] == 't') {
                            return 8;
                        }
                    }
                }
            }
            return -1;
        case 'n':
            if(line[startIndex + 1] == 'i') {
                if(line[startIndex + 2] == 'n') {
                    if(line[startIndex + 3] == 'e') {
                        return 9;
                    }
                }
            }
            return -1;
    }
}

int findWord(char c, char *line, int startIndex) {
    if(c != 'o' && c != 't' && c != 'f' && c != 's' && c != 'e' && c != 'n') {
        return -1;
    }

    return isNumString(c, line, startIndex);
    
    return -1;
}

int processLine(int firstNum, int secondNum, int firstNumPos, int secondNumPos, char *line, int lineLength, int lineNumber) {
    int combinedNum;
    int firstStringFound = 0, secondStringFound = 0, firstString = 0, secondString = 0, firstStringPos = 100, secondStringPos = -1;
    int num = -1;

    for(int i = 0; i < lineLength; i++) {
        num = findWord(line[i], line, i);
        if(firstStringFound && num != -1) {
            secondString = num;
            secondStringPos = i;
        } else if(firstStringFound == 0 && num != -1) {
            firstString = num;
            secondString = num;
            firstStringPos = i;
            secondStringPos = i;
            firstStringFound = 1;
        }
    }

    if(firstStringPos < firstNumPos) { //string comes first
        firstNum = firstString;
    }
    if(secondStringPos > secondNumPos) { //string comes last
        secondNum = secondString;
    }

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
    int firstNum, secondNum, firstNumPos = -1, secondNumPos = -1, lineSum, totalSum = 0;
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

            lineSum = processLine(firstNum, secondNum, firstNumPos, secondNumPos, line, iLine, lineCounter);
            printf("Line %d: %d\n", lineCounter, lineSum);

            totalSum += lineSum;
            firstNumSet = 0;
            // printf("Line %d: %d characters long\n",lineCounter,iLine);
            iLine = 0;
            free(line);
            continue;
        } else if(isNum(inputBuf[i])) { //is a number
            if(firstNumSet) {
                secondNum = processChar(inputBuf[i]);
                secondNumPos = iLine;
            } else {
                firstNum = processChar(inputBuf[i]);
                secondNum = processChar(inputBuf[i]);
                firstNumPos = iLine;
                secondNumPos = iLine;
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