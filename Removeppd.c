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
        printf("Error Occured: Error while opening the input file.\n");
        exit(0);
    }
    if (fp2 == NULL) {
        printf("Error Occured: Error while opening the output file.\n");
        exit(0);
    }
    while (1) {
        char temp[50];
        if(!fgets(temp, 50, fp)) break;
        if(!temp) break;
        if(temp[0] != '#'){
            fputs(temp, fp2);
        }
    }
    fclose(fp);
    fclose(fp2);
    return 0;
}
