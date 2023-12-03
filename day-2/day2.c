#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int MAX_RED = 12;
int MAX_GREEN = 13;
int MAX_BLUE = 14;

int charToInt(char c) {
    return c - '0';
}

int processGame(char *line, int lineLength, int lineNumber) {
    int readIndex = 0;
    int num1 = 0, num2 = 0;
    int combinedNum = 0;
    int maxRed = 0, maxGreen = 0, maxBlue = 0;
    int power = 0;

    for(int i = 0; i < lineLength; i++) {
        if(line[i] == ':') {
            readIndex = 1;
            continue;
        }

        if(readIndex && isdigit(line[i])) {
            num1 = charToInt(line[i]);
            if(isdigit(line[i+1])) { //two digit number
                num2 = charToInt(line[i+1]);
                combinedNum = (num1 * 10) + num2;

                if(line[i+3] == 'r') {
                    if(combinedNum > maxRed) {
                        maxRed = combinedNum;
                    }
                } else if(line[i+3] == 'g') {
                    if(combinedNum > maxGreen) {
                        maxGreen = combinedNum;
                    }
                } else if(line[i+3] == 'b') {
                    if(combinedNum > maxBlue) {
                        maxBlue = combinedNum;
                    }
                }

                i += 4;
            } else if (line[i+1] == ' ') {
                combinedNum = num1;

                if(line[i+2] == 'r') {
                    if(combinedNum > maxRed) {
                        maxRed = combinedNum;
                    }
                } else if(line[i+2] == 'g') {
                    if(combinedNum > maxGreen) {
                        maxGreen = combinedNum;
                    }
                } else if(line[i+2] == 'b') {
                    if(combinedNum > maxBlue) {
                        maxBlue = combinedNum;
                    }
                }

                i += 3;
            }
        }
    }

    printf("Line %d: r: %d g: %d b: %d\n", lineNumber+1, maxRed, maxGreen, maxBlue);

    // if(maxRed > MAX_RED || maxGreen > MAX_GREEN || maxBlue > MAX_BLUE) {
    //     return 1;
    // } else {
    //     return 0;
    // }

    power = maxRed * maxGreen * maxBlue;
    return power;
}

int main (int argc, char **argv) {
    FILE *file;
    int fileLength;
    int iLine = 0;
    int lineCounter = 0;
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
        // if(processGame(lines[i], lineLengths[i], i)) {
        //     printf("Game %d is invalid\n", i+1);
        // } else {
        //     sum += i+1;
        // }
        // printf("\n");
        sum += processGame(lines[i], lineLengths[i], i);
    }

    printf("Answer: %d\n", sum);

    free(inputBuf);
    for(int i = 0; i < lineCounter; i++) {
        free(lines[i]);
    }
    free(lines);
    free(lineLengths);
}