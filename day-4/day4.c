#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

typedef struct {
    int originalCard;
    int *winningNumbers;
    int *cardNumbers;
} Card;

int cmpfunc(const void *a, const void *b) {
    return ( *(int*)a > *(int*)b );
}

int binarySearch(int arr[], int l, int r, int x)
{
    while (l <= r) {
        int m = l + (r - l) / 2;
 
        if (arr[m] == x) {
            return m;
        } 
        if (arr[m] < x) {
            l = m + 1;
        } 
        else {
            r = m - 1;
        }
    }
 
    return -1;
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

void initCard(Card **card, int cardNumber) {
    *card = malloc(sizeof(Card));

    (*card)->originalCard = cardNumber;
    (*card)->winningNumbers = malloc(sizeof(int) * 10);
    (*card)->cardNumbers = malloc(sizeof(int) * 25);
}

void freeCard(Card **card) {
    free((*card)->winningNumbers);
    free((*card)->cardNumbers);
    free((*card));
    *card = NULL;
}

int checkCard(char *line, int lineLength, int lineNumber) {
    int readingNumbers = 0;
    int numLength = 0;
    int winningIndex = 0;
    int cardIndex = 0;
    int numbersMatched = 0;
    int sum = 0;

    Card *card;
    initCard(&card, lineNumber + 1);

    card->winningNumbers[0] = 1;

    printf("Card %d: ", card->originalCard);

    for(int i = 0; i < lineLength; i++) {
        if(line[i] == ':') {
            readingNumbers = 1;
        } else if(isdigit(line[i]) && readingNumbers) {
            if(isdigit(line[i+1])) {
                numLength = 2;
                i++;
            } else {
                numLength = 1;
            }

            if(winningIndex < 10) {
                card->winningNumbers[winningIndex] = getNumRead(line, i - 1, i + numLength);
                printf("%2d ", card->winningNumbers[winningIndex]);
                winningIndex++;
            } else {
                card->cardNumbers[cardIndex] = getNumRead(line, i - 1, i + numLength);
                printf("%2d ", card->cardNumbers[cardIndex]);
                cardIndex++;
            }
        }
    }

    qsort(card->cardNumbers, cardIndex, sizeof(int), cmpfunc);

    for(int i = 0; i < winningIndex; i++) {
        if(binarySearch(card->cardNumbers, 0, cardIndex, card->winningNumbers[i]) != -1) {
            numbersMatched++;
        }
    }

    if(numbersMatched > 0) {
        sum = pow(2,numbersMatched - 1);
    }

    printf("Matched %d numbers: %d\n", numbersMatched, sum);

    freeCard(&card);

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
        lineSum = checkCard(lines[i], lineLengths[i], i);

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