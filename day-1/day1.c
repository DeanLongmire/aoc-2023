#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int processChar(char hexNum) {
    int intNum;
    char *stringNum = malloc(2);

    stringNum[0] = hexNum;
    stringNum[1] = '\0';
    intNum = atoi(stringNum);
    free(stringNum);

    return intNum;
}

int processLine(int firstNum, int secondNum, char *line, regex_t *regexes, int lineNumber) {
    int combinedNum;
    int regexMatch;
    regoff_t firstNumPosition = 100;
    regoff_t secondNumPosition = -1;
    int firstNumMatch = 0, secondNumMatch = 0;
    size_t numMatches = 18;
    regmatch_t *matchInfo = malloc(numMatches * sizeof(regmatch_t));

    for(int i = 0; i < 18; i++) {
        if(regexec(&regexes[i], line, numMatches, matchInfo, 0) == 0) {
            printf("Line %d had match for regex %d at position %d\n", lineNumber, i, matchInfo->rm_so);
            if(matchInfo->rm_so < firstNumPosition) {
                firstNumPosition = matchInfo->rm_so;
                firstNumMatch = i;
            }

            if(matchInfo->rm_so > secondNumPosition) {
                secondNumPosition = matchInfo->rm_so;
                secondNumMatch = i;
            }
        }
    }

    if(firstNumPosition == secondNumPosition) {
        printf("Line %d has two nums back to back %d:%d\n", lineNumber, firstNumPosition, secondNumPosition);
    }

    printf("Taking match %d and %d for line %d\n", firstNumMatch, secondNumMatch, lineNumber);

    combinedNum = firstNum * 10;
    combinedNum += secondNum;

    free(matchInfo);

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
    int offset;
    char *inputBuf;

    regex_t *regexes = malloc(sizeof(regex_t) * 18);

    regcomp(&regexes[0], "^[^0-9]*one", 0); //first 'number' is a string
    regcomp(&regexes[1], "one[^0-9]*$", 0); //last 'number' is a string
    regcomp(&regexes[2], "^[^0-9]*two", 0);
    regcomp(&regexes[3], "two[^0-9]*$", 0);
    regcomp(&regexes[4], "^[^0-9]*three", 0);
    regcomp(&regexes[5], "three[^0-9]*$", 0);
    regcomp(&regexes[6], "^[^0-9]*four", 0);
    regcomp(&regexes[7], "four[^0-9]*$", 0);
    regcomp(&regexes[8], "^[^0-9]*five", 0);
    regcomp(&regexes[9], "five[^0-9]*$", 0);
    regcomp(&regexes[10], "^[^0-9]*six", 0);
    regcomp(&regexes[11], "six[^0-9]*$", 0);
    regcomp(&regexes[12], "^[^0-9]*seven", 0);
    regcomp(&regexes[13], "seven[^0-9]*$", 0);
    regcomp(&regexes[14], "^[^0-9]*eight", 0);
    regcomp(&regexes[15], "eight[^0-9]*$", 0);
    regcomp(&regexes[16], "^[^0-9]*nine", 0);
    regcomp(&regexes[17], "nine[^0-9]*$", 0);

    // file = fopen("input.txt", "r");

    // fseek(file, 0, SEEK_END);
    // fileLength = ftell(file);
    // fseek(file, 0, SEEK_SET);
    // printf("File is %d bytes long.\n", fileLength);

    // inputBuf = malloc(fileLength);

    // fread(inputBuf, 1, fileLength, file);

    // int iLine = 0;
    // int j;

    // for(int i = 0; i < fileLength; i++) {
    //     if(inputBuf[i] == 0x0A) { //new line character
    //         lineCounter++;
    //         char *line = malloc(iLine + 1);

    //         for(j = 0; j <= iLine - 1; j++) {
    //             line[j] = inputBuf[i - (iLine - j)];
    //         }
    //         line[j] = '\0';

    //         // printf("Line %d: %s\n", lineCounter, line);

    //         lineSum = processLine(firstNum, secondNum, line, regexes, lineCounter);
    //         //printf("Line %d: %d\n", lineCounter, lineSum);

    //         totalSum += lineSum;
    //         firstNumSet = 0;
    //         // printf("Line %d: %d characters long\n",lineCounter,iLine);
    //         iLine = 0;
    //         free(line);
    //         continue;
    //     } else if(isNum(inputBuf[i])) { //is a number
    //         if(firstNumSet) {
    //             secondNum = processChar(inputBuf[i]);
    //         } else {
    //             firstNum = processChar(inputBuf[i]);
    //             secondNum = processChar(inputBuf[i]);
    //             firstNumSet = 1;
    //         }
    //     }
    //     iLine++;
    // }

    // printf("%d number of lines in file.\n", lineCounter);
    // printf("Total sum: %d\n", totalSum);

    // fclose(file);
    // free(inputBuf);

    char *line = strdup("asdftwoonethree223asd");

    processLine(1, 1, line, regexes, 1);

    for(int i = 0; i < 18; i++) {
        regfree(&regexes[i]);
    }
    free(regexes);
}