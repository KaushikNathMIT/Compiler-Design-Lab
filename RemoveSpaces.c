#include<stdio.h>

int main(){
    char fileName[20], fileName2[20];
    FILE *fp, *fp2;
    printf("Enter the input file name \n");
    scanf("%s", fileName);
    printf("Enter the output file name \n");
    scanf("%s", fileName2);
    fp = fopen(fileName, "r");
    fp2 = fopen(fileName2, "w");

    if (fp == NULL) {
        printf("Error Occured: Error while opening the file.\n");
        exit(0);
    }
    while (1) {
        char temp = fgetc(fp);
        if(temp == EOF) break;
        if(temp != ' '){
            fputc(temp,fp2);
        }
    }
    fclose(fp);
    fclose(fp2);
    return 0;
}
