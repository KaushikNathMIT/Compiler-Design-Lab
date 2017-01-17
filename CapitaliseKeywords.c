#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(){
    char fileName[20], fileName2[20];
    FILE *fp, *fp2;
    printf("Enter the input file name \n");
    scanf("%s", fileName);
    fp = fopen(fileName, "r");
    //fp2 = fopen(fileName2, "w");

    if (fp == NULL) {
        printf("Error Occured: Error while opening the input file.\n");
        exit(0);
    }
    if (fp2 == NULL) {
        printf("Error Occured: Error while opening the output file.\n");
        exit(0);
    }
    char keyWords[32][10] = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};
    while (1) {
        char temp[100];
        if(!fgets(temp, 100, fp)) break;
        if(!temp) break;
        int i=0;
        //printf("\nhere\n");
        while(temp[i]!='\0') {
        	//printf("\nhere2 %d\n", i);
        	if(temp[i]==' ' || temp[i]=='{' || temp[i]=='}' || temp[i]==',' || temp[i]==';' || temp[i]=='(' || temp[i]==')'){
            	i++;
            	while(temp[i]==' ' || temp[i]=='{' || temp[i]=='}' || temp[i]==',' || temp[i]==';' || temp[i]=='(' || temp[i]==')') i++;
            	int j=0;
            	char word[15];
            	while(temp[i]!=' ' && temp[i]!='{' && temp[i]!='}' && temp[i]!=',' && temp[i]!=';' && temp[i]!='(' && temp[i]!=')' && temp[i]!='\0') {
            		word[j] = temp[i];
            		i++;
            		j++;
            	}
            	if(temp[i] == '\0') break;
            	word[j] = '\0';
            	for(j=0; j<32; j++) {
            		if(strcmp(word, keyWords[j]) == 0) {
            			for(int k=0;word[k]!='\0';k++) printf("%c", toupper(word[k]));
            			printf("\n");
            		}
            	}
        	}
        	else i++;
        }
    }
    fclose(fp);
    //fclose(fp2);
    return 0;
}


/*
"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
*/
