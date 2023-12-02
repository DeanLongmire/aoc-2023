#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
    FILE *file;
    int fileLength;
    char *inputBuf;

    file = fopen("input.txt", "r");

    fseek(file, 0, SEEK_END);
    fileLength = ftell(file);
    fseek(file, 0, SEEK_SET);
    printf("File is %d bytes long.\n", fileLength);

    inputBuf = malloc(fileLength);

    fread(inputBuf, 1, fileLength, file);

    fclose(file);
}