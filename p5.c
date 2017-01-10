#include <stdio.h>
#include <stdlib.h>

 int main() {
    int flag=1;
    char ch, fileName1[25], fileName2[25];
    FILE *fp1, *fp2;
    printf("Enter the file name 1\n");
    scanf("%s", fileName1);
    printf("Enter the file name 2\n");
    scanf("%s", fileName2);
    fp1 = fopen(fileName1, "r");
    fp2 = fopen(fileName2, "r");
    while (1){
        ch = fgetc(fp1);
        if(ch==EOF) break;
        if (ch != fgetc(fp2)) {
            printf("\nFiles not same");
            exit(0);
        }
    }
    printf("\nFiles are same");
    return 0;
 }
