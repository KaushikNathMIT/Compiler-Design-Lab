#include <stdio.h>
#include <stdlib.h>

 int main() {
    int count=3;
    char ch, fileName[25];
    FILE *fp;
    printf("Enter the file name \n");
    scanf("%s", fileName);
    fp = fopen(fileName, "r");
    fseek(fp,0,SEEK_END);
    printf("\nFile Size %d\n", ftell(fp));
    return 0;
 }
