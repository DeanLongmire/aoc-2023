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

int isSymbol(char c) {
    if(c == '.') {
        return 0;
    } else if(ispunct(c)) {
        return 1;
    } else {
        return 0;
    }
}

int checkAboveOrBelow(char *lineToCheck, int startIndex, int endIndex, int lineLength) {
    if(startIndex - 1 < 0) {
        for(int i = startIndex; i <= endIndex + 1; i++) {
            if(isSymbol(lineToCheck[i])) {
                return 1;
            }
        }
    } else if(startIndex + 1 > lineLength) {
        for(int i = startIndex - 1; i <= endIndex; i++) {
            if(isSymbol(lineToCheck[i])) {
                return 1;
            }
        }
    } else {
        for(int i = startIndex - 1; i <= endIndex + 1; i++) {
            if(isSymbol(lineToCheck[i])) {
                return 1;
            }
        }
    }

    return 0;
}

int checkAdjacent(char *line, int startIndex, int endIndex, int lineLength) {
    if(startIndex - 1 < 0) {
        if(isSymbol(line[endIndex + 1])) {
            return 1;
        } else {
            return 0;
        }
    } else if(endIndex + 1 > lineLength) {
        if(isSymbol(line[startIndex - 1])) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if(isSymbol(line[startIndex - 1]) || isSymbol(line[endIndex + 1])) {
            return 1;
        } else {
            return 0;
        }
    }
}

int processLine(char *line, char *aboveLine, char *belowLine, int lineLength, int aLength, int bLength, int lineNumber, int flag) {
    int j = 1;
    int startNumIndex = 0;
    int endNumIndex = 0;
    int num;
    int above = 0, below = 0, adjacent = 0;
    int sum = 0;

    for(int i = 0; i < lineLength; i++) {
        if(isdigit(line[i])) {
            startNumIndex = i;

            while(isdigit(line[i+j])) {
                j++;
            }

            endNumIndex = i += j - 1;
            num = getNumRead(line, startNumIndex, endNumIndex);
            printf("Read number %d\n", num);

            adjacent = checkAdjacent(line, startNumIndex, endNumIndex, lineLength);
            if(flag == FIRST_LINE) {
                below = checkAboveOrBelow(belowLine, startNumIndex, endNumIndex, bLength);
            } else if(flag == LAST_LINE) {
                above = checkAboveOrBelow(aboveLine, startNumIndex, endNumIndex, aLength);
            } else {
                below = checkAboveOrBelow(belowLine, startNumIndex, endNumIndex, bLength);
                above = checkAboveOrBelow(aboveLine, startNumIndex, endNumIndex, aLength);
            }

            if(adjacent == 1) {
                printf("Symbol is adjacent to this number\n");
            }
            if(below == 1) {
                printf("Symbol is below this number\n");
            }
            if(above == 1) {
                printf("Symbol is above this number\n");
            }

            if(adjacent || below || above) {
                sum += num;
            }

            j = 1;
        }
    }

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