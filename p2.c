#include <stdio.h>
#include <stdlib.h>

 int main() {
    int count=0;
    char ch, fileName[25];
    FILE *fp;
    printf("Enter the file name \n");
    scanf("%s", fileName);
    fp = fopen(fileName, "r");

    if (fp == NULL) {
        printf("Error Occured: Error while opening the file.\n");
        exit(0);
    }

    fp = fopen(fileName, "r");
    char* s = malloc(1000*sizeof(char));

    while(fgets(s,1000,fp)) {
        printf("\n%s", s);
        count++;
        if(count==5){
            count=0;
            scanf(" %c", &ch);
            if(ch == 'Q'){
                printf("\nYou chose to stop printing");
                break;
            }
            else if(ch != 'C'){
                printf("\nValid choice not entered");
                exit(0);
            }
        }
    }
    printf("\nProgram ended");
    fclose(fp);
    return 0;
 }
