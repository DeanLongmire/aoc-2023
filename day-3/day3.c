#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int FIRST_LINE = 1;
int LAST_LINE = 2;

int charToInt(char c) {
    return c - '0';
}

int getNumRead(char *line, int startIndex, int endIndex) {
    int charsToRead = endIndex - startIndex + 1;
    int numInt;
    char *numString = malloc(charsToRead + 1);

    int i;
    for(i = 0; i < charsToRead; i++) {
        numString[i] = line[startIndex+i];
    }
    numString[i] = '\0';

    numInt = atoi(numString);
    free(numString);
    return numInt;
}

int isGear(char c) {
    if(c == '*') {
        return 1;
    } else {
        return 0;
    }
}

int getNumAboveOrBelow(char *line, int gearIndex, int lineLength) {
    int i = 1;
    int num;
    int numLength = 0;
    int startIndex = gearIndex, endIndex;

    while(gearIndex - i >= 0 && isdigit(line[gearIndex - i])) {
        startIndex--;
        i++;
    }

    i = 1;
    while(startIndex + i < lineLength && isdigit(line[startIndex+i])) {
        numLength++;
        i++;
    }
    
    endIndex = startIndex + numLength;

    num = getNumRead(line, startIndex, endIndex);
    // printf("Found %d above or below gear\n", num);
    return num;
}   

int getNumLeft(char *line, int gearIndex, int lineLength) {
    int i = 1;
    int num;
    int numLength = 0;
    int startIndex, endIndex;

    while(gearIndex - i >= 0 && isdigit(line[gearIndex - i])) {
        numLength++;
        i++;
    }

    startIndex = gearIndex - numLength;
    endIndex = gearIndex - 1;

    num = getNumRead(line, startIndex, endIndex);
    // printf("Found %d to the left of gear\n", num);
    return num;
}

int getNumRight(char *line, int gearIndex, int lineLength) {
    int i = 1;
    int num;
    int numLength = 0;
    int startIndex, endIndex;

    while(gearIndex + i < lineLength && isdigit(line[gearIndex + i])) {
        numLength++;
        i++;
    }

    startIndex = gearIndex + 1;
    endIndex = gearIndex + numLength;

    num = getNumRead(line, startIndex, endIndex);
    // printf("Found %d to the right of gear\n", num);
    return num;
}

int checkTouching(char *line, char *aboveLine, char *belowLine, int gearIndex, int lineLength, int flag) {
    int numTouching = 0;
    int num1 = 0;
    int num2 = 0;
    int num1Set = 0;

    if(gearIndex - 1 < 0) {
        if(isdigit(line[gearIndex + 1])) { //to the right
            numTouching++;
            if(num1Set == 0) {
                num1 = getNumRight(line, gearIndex, lineLength);
                num1Set = 1;
            } else {
                num2 = getNumRight(line, gearIndex, lineLength);
            }
        }
        if(flag != FIRST_LINE) {
            if(isdigit(aboveLine[gearIndex])) { //directly above
                numTouching++;
                if(num1Set == 0) {
                    num1 = getNumAboveOrBelow(aboveLine, gearIndex, lineLength);
                    num1Set = 1;
                } else {
                    num2 = getNumAboveOrBelow(aboveLine, gearIndex, lineLength);
                }
            } else if(isdigit(aboveLine[gearIndex + 1])) { //diagonal above right
                numTouching++;
                if(num1Set == 0) {
                    num1 = getNumRight(aboveLine, gearIndex, lineLength);
                    num1Set = 1;
                } else {
                    num2 = getNumRight(aboveLine, gearIndex, lineLength);
                }
            }
        }
        if(flag != LAST_LINE) {
            if(isdigit(belowLine[gearIndex])) { //directly below
                numTouching++;
                if(num1Set == 0) {
                    num1 = getNumAboveOrBelow(belowLine, gearIndex, lineLength);
                    num1Set = 1;
                } else {
                    num2 = getNumAboveOrBelow(belowLine, gearIndex, lineLength);
                }
            } else if(isdigit(belowLine[gearIndex + 1])) { //diagonal below right
                numTouching++;
                if(num1Set == 0) {
                    num1 = getNumRight(belowLine, gearIndex, lineLength);
                    num1Set = 1;
                } else {
                    num2 = getNumRight(belowLine, gearIndex, lineLength);
                }
            }
        }
    } else if(gearIndex + 1 > lineLength) {
        if(isdigit(line[gearIndex - 1])) { //to the left
            numTouching++;
            if(num1Set == 0) {
                num1 = getNumLeft(line, gearIndex, lineLength);
                num1Set = 1;
            } else {
                num2 = getNumLeft(line, gearIndex, lineLength);
            }
        } 
        if(flag != FIRST_LINE) {
            if(isdigit(aboveLine[gearIndex])) { //directly above
                numTouching++;
                if(num1Set == 0) {
                    num1 = getNumAboveOrBelow(aboveLine, gearIndex, lineLength);
                    num1Set = 1;
                } else {
                    num2 = getNumAboveOrBelow(aboveLine, gearIndex, lineLength);
                }
            } else if(isdigit(aboveLine[gearIndex - 1])) { //diagonal above left
                numTouching++;
                if(num1Set == 0) {
                    num1 = getNumLeft(aboveLine, gearIndex, lineLength);
                    num1Set = 1;
                } else {
                    num2 = getNumLeft(aboveLine, gearIndex, lineLength);
                }
            }
        }
        if(flag != LAST_LINE) {
            if(isdigit(belowLine[gearIndex])) { //directly below
                numTouching++;
                if(num1Set == 0) {
                    num1 = getNumAboveOrBelow(belowLine, gearIndex, lineLength);
                    num1Set = 1;
                } else {
                    num2 = getNumAboveOrBelow(belowLine, gearIndex, lineLength);
                }
            } else if(isdigit(belowLine[gearIndex - 1])) { //diagonal below left
                numTouching++;
                if(num1Set == 0) {
                    num1 = getNumLeft(belowLine, gearIndex, lineLength);
                    num1Set = 1;
                } else {
                    num2 = getNumLeft(belowLine, gearIndex, lineLength);
                }
            }
        }
    } else {
        if(isdigit(line[gearIndex - 1])) { //to the left
            numTouching++;
            if(num1Set == 0) {
                num1 = getNumLeft(line, gearIndex, lineLength);
                num1Set = 1;
            } else {
                num2 = getNumLeft(line, gearIndex, lineLength);
            }
        }
        if(isdigit(line[gearIndex + 1])) { //to the right
            numTouching++;
            if(num1Set == 0) {
                num1 = getNumRight(line, gearIndex, lineLength);
                num1Set = 1;
            } else {
                num2 = getNumRight(line, gearIndex, lineLength);
            }
        }
        if(flag != FIRST_LINE) {
            if(isdigit(aboveLine[gearIndex])) { //directly above
                numTouching++;
                if(num1Set == 0) {
                    num1 = getNumAboveOrBelow(aboveLine, gearIndex, lineLength);
                    num1Set = 1;
                } else {
                    num2 = getNumAboveOrBelow(aboveLine, gearIndex, lineLength);
                }
            } else {
                if(isdigit(aboveLine[gearIndex - 1])) { //diagonal above left
                    numTouching++;
                    if(num1Set == 0) {
                        num1 = getNumLeft(aboveLine, gearIndex, lineLength);
                        num1Set = 1;
                    } else {
                        num2 = getNumLeft(aboveLine, gearIndex, lineLength);
                    }
                }
                if(isdigit(aboveLine[gearIndex + 1])) { //diagonal above right
                    numTouching++;
                    if(num1Set == 0) {
                        num1 = getNumRight(aboveLine, gearIndex, lineLength);
                        num1Set = 1;
                    } else {
                        num2 = getNumRight(aboveLine, gearIndex, lineLength);
                    }
                }
            }
        }
        if(flag != LAST_LINE) {
            if(isdigit(belowLine[gearIndex])) { //directly below
                numTouching++;
                if(num1Set == 0) {
                    num1 = getNumAboveOrBelow(belowLine, gearIndex, lineLength);
                    num1Set = 1;
                } else {
                    num2 = getNumAboveOrBelow(belowLine, gearIndex, lineLength);
                }
            } else {
                if(isdigit(belowLine[gearIndex - 1])) { //diagonal below left
                    numTouching++;
                    if(num1Set == 0) {
                        num1 = getNumLeft(belowLine, gearIndex, lineLength);
                        num1Set = 1;
                    } else {
                        num2 = getNumLeft(belowLine, gearIndex, lineLength);
                    }
                }
                if(isdigit(belowLine[gearIndex + 1])) { //diagonal below right
                    numTouching++;
                    if(num1Set == 0) {
                        num1 = getNumRight(belowLine, gearIndex, lineLength);
                        num1Set = 1;
                    } else {
                        num2 = getNumRight(belowLine, gearIndex, lineLength);
                    }
                }
            }
        }
    }

    printf("Gear is touching %d nums\n", numTouching);

    if(numTouching == 2) {
        return num1 * num2;
    } else {
        return -1;
    }
}

int processLine(char *line, char *aboveLine, char *belowLine, int lineLength, int aLength, int bLength, int lineNumber, int flag) {
    int j = 1;
    int startNumIndex = 0;
    int endNumIndex = 0;
    int gearIndex = 0;
    int num;
    int gearRatio = 0;
    int sum = 0;

    for(int i = 0; i < lineLength; i++) {
        if(isGear(line[i])) {
            gearIndex = i;
            printf("Found a gear at %d\n", i);

            gearRatio = checkTouching(line, aboveLine, belowLine, gearIndex, lineLength, flag);

            if(gearRatio > 0) {
                sum += gearRatio;
            }
        }
    }

    printf("Line Sum: %d\n", sum);
    return sum;
}

int main (int argc, char **argv) {
    FILE *file;
    int fileLength;
    int iLine = 0;
    int lineCounter = 0;
    int lineSum = 0;
    int sum = 0;
    int *lineLengths;
    char *inputBuf;
    char **lines;

    file = fopen("input.txt", "r");

    fseek(file, 0, SEEK_END);
    fileLength = ftell(file);
    fseek(file, 0, SEEK_SET);
    printf("File is %d bytes long.\n", fileLength);

    inputBuf = malloc(fileLength);

    fread(inputBuf, 1, fileLength, file);

    fclose(file);

    for(int i = 0; i < fileLength; i++) {
        if(inputBuf[i] == 0x0A) { //new line character
            lineCounter++;
        }
    }

    printf("%d total lines\n", lineCounter);

    lines = malloc(lineCounter * sizeof(char *));
    lineLengths = malloc(lineCounter * sizeof(int));

    int j = 0;
    int k;
    for(int i = 0; i < fileLength; i++) {
        if(inputBuf[i] == 0x0A) { //new line character
            lines[j] = malloc(iLine + 1);

            for(k = 0; k <= iLine - 1; k++) {
                lines[j][k] = inputBuf[i - (iLine - k)];
            }
            lines[j][k] = '\0';
            lineLengths[j] = iLine + 1;

            iLine = 0;
            j++;
            continue;
        }
        iLine++;
    }

    for(int i = 0; i < lineCounter; i++) {
        if(i == 0) { //edge case, first line, no line above it
            lineSum = processLine(lines[i], NULL, lines[i+1], lineLengths[i], 0, lineLengths[i+1], i, FIRST_LINE);
        } else if(i == lineCounter - 1) { //edge case, last line, no line below it
            lineSum = processLine(lines[i], lines[i-1], NULL, lineLengths[i], lineLengths[i-1], 0, i, LAST_LINE);
        } else { //normal case, line above and below it
            lineSum = processLine(lines[i], lines[i-1], lines[i+1], lineLengths[i], lineLengths[i-1], lineLengths[i+1], i, 0);
        }

        sum += lineSum;
    }

    printf("Answer: %d\n", sum);

    free(inputBuf);
    for(int i = 0; i < lineCounter; i++) {
        free(lines[i]);
    }
    free(lines);
    free(lineLengths);
}