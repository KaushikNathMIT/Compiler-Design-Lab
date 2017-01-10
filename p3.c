#include <stdio.h>
#include <stdlib.h>

 int main() {
    int count=3;
    char ch, fileName[25];
    FILE *fp;
    while(count--) {
        printf("Enter the file name \n");
        scanf("%s", fileName);
        fp = fopen(fileName, "r");
        if (fp == NULL) {
            printf("Error Occured: Error while opening the file.\nChances remaining %d\n", count);
        }
        else{
            printf("\nVaid file.");
            fclose(fp);
            break;
        }
    }


    return 0;
 }
