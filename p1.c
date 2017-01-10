#include <stdio.h>
#include <stdlib.h>

 int main() {
    int characterCount, lineCount;
    characterCount=lineCount=0;
    char ch, fileName[25];
    FILE *fp;
    printf("Enter the file name \n");
    scanf("%s", fileName);
    fp = fopen(fileName, "r");

    if (fp == NULL) {
        printf("Error Occured: Error while opening the file.\n");
        exit(0);
    }
    while (fgetc(fp) != EOF) {
        characterCount++;
    }
    fclose(fp);
    fp = fopen(fileName, "r");
    char* s = malloc(100*sizeof(char));
    while(fgets(s,100,fp)) {
        lineCount++;
    }
    fclose(fp);
    printf("\nThe number of characters are %d.\n", characterCount);
    printf("\nThe number of lines are %d.\n", lineCount);
    return 0;
 }
