#include <stdio.h>
#include <string.h>
#include "LexicalAnalyzer.h"

FILE *fp;
char* token;
int Program();
int declarations();
int dataType();
int identifierList();
int assignStat();

int Program() {
        token = getNextWord(fp);
        if(strcmp(token, "main")==0) {
                printf("\nParsed main");
                token = getNextWord(fp);
                if(token[0]=='(') {
                        printf("\nParsed (");
                        token = getNextWord(fp);
                        if(token[0]==')') {
                                printf("\nParsed )");
                                token = getNextWord(fp);
                                if(token[0] == '{') {
                                        printf("\nParsed {");
                                        if(declarations()==1 && assignStat()==1) {
                                                token = getNextWord(fp);
                                                if(token[0] == '}') {
                                                        printf("\nParsed }");
                                                        return 1;
                                                }
                                        }
                                }
                        }
                }
        }
        return 0;
}

int declarations() {
        if(dataType() == 1) {
                if(identifierList() == 1) {
                        token = getNextWord(fp);
                        //printf("Token now is %s", token);
                        if(token[0]==';') {
                                printf("\nParsed ;");
                                return declarations();
                        }
                        else fseek(fp,-strlen(token),SEEK_CUR);
                }
                return 0;
        }
        return 1;
}


int dataType() {
        token = getNextWord(fp);
        if(strcmp(token, "int")==0 || strcmp(token, "char")==0) {
                printf("\nParsed %s", token);
                return 1;
        }
        else {
                fseek(fp,-strlen(token), SEEK_CUR);
                return 0;
        }
}

int identifierList() {
        token = getNextWord(fp);
        char* temp = token;
        if(strcmp(token, "id") == 0) {
                printf("\nParsed id");
                token = getNextWord(fp);
                if(strcmp(token, ",")==0) {
                        printf("\nParsed ,");
                        return identifierList();
                }
                fseek(fp,-strlen(token),SEEK_CUR);
                return 1;
        }
        fseek(fp,-strlen(temp),SEEK_CUR);
        return 0;
}

int assignStat() {
        token = getNextWord(fp);
        char* temp = token;
        if(strcmp(token, "id")==0) {
                printf("\nParsed %s", token);
                token = getNextWord(fp);
                if(strcmp(token, "=")==0) {
                        printf("\nParsed %s", token);
                        token = getNextWord(fp);
                        if(strcmp(token,"id") == 0 || strcmp(token, "num")==0) {
                                printf("\nParsed %s", token);
                                return 1;
                        }
                }
        }
        fseek(fp,-strlen(temp),SEEK_CUR);
        return 0;
}

int main() {
        char fileName[100];
        printf("Enter the file Name\n");
        scanf("%s", fileName);
        fp = fopen(fileName, "r");
        if(Program() == 1) printf("\nString possible by grammar");
        else printf("\nString not present in grammar");

}
