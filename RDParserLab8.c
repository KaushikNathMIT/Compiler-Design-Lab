#include <stdio.h>
#include <string.h>
#include "LexicalAnalyzer2.h"

FILE *fp;
char* token;
int Program();
int declarations();
int dataType();
int identifierList();
int statementList();
int statement();
int assignStat();
int expn();
int eprime();
int simpleExpn();
int seprime();
int term();
int tprime();
int factor();
int relop();
int addop();
int mulop();

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
                                        if(declarations()==1 && statementList()==1) {
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


int statement() {
        return assignStat();
}


int statementList() {
        int tpos = ftell(fp);
        if(statement() == 1) {
                if(statementList() == 1) {
                        return 1;
                }

                return 0;
        }
        fseek(fp,tpos, SEEK_SET);
        return 1;
}

int identifierList() {
        token = getNextWord(fp);
        char* temp = token;
        if(isIdentifier(token)==1) {
                printf("\nParsed %s", token);
                token = getNextWord(fp);
                if(strcmp(token, ",")==0) {
                        printf("\nParsed ,");
                        return identifierList();
                }
                else if(strcmp(token, "[")==0) {
                        printf("\nParsed [");
                        char* temp = getNextWord(fp);
                        if(isSNum(temp) == 1) {
                                printf("\nParsed %s", temp);
                                char* temp3 = getNextWord(fp);
                                if(strcmp(temp3, "]")==0) {
                                        printf("\nParsed ]");
                                        char* temp2 = getNextWord(fp);
                                        if(strcmp(temp2, ",")==0) {
                                                printf("\nParsed ,");
                                                return identifierList();
                                        }
                                        fseek(fp, -strlen(temp2), SEEK_CUR);
                                        return 1;
                                }
                                fseek(fp, -strlen(temp3), SEEK_CUR);
                                return 0;
                        }
                        else {
                                fseek(fp, -strlen(temp), SEEK_CUR);
                                return 0;
                        }
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
        if(isIdentifier(token)==1) {
                printf("\nParsed %s", token);
                char* temp1 = getNextWord(fp);
                if(strcmp(temp1, "=")==0) {
                        printf("\nParsed %s", temp1);
                        return expn();
                }
                fseek(fp,-strlen(temp1),SEEK_CUR);
        }
        fseek(fp,-strlen(temp),SEEK_CUR);
        return 0;
}

int expn() {
        if(simpleExpn() && eprime()) {
                return 1;
        }
        return 0;
}

int eprime() {
        int tpos = ftell(fp);
        if(relop()==1) {
                if(simpleExpn()==1) return 1;
                return 0;
        }
        fseek(fp,tpos, SEEK_SET);
        return 1;
}

int simpleExpn() {
        if(term() && seprime()) {
                return 1;
        }
        return 0;
}

int seprime() {
        int tpos = ftell(fp);
        if(addop()) {
                if(term() && seprime()) return 1;
                return 0;
        }
        fseek(fp,tpos, SEEK_SET);
        return 1;
}

int term() {
        if(factor() && tprime()) {
                return 1;
        }
        return 0;
}

int tprime() {
        int tpos = ftell(fp);
        if(mulop()) {
                if(factor() && tprime()) return 1;
                return 0;
        }
        fseek(fp,tpos, SEEK_SET);
        return 1;
}

int factor() {
        char* temp = getNextWord(fp);
        if(isIdentifier(temp)==1 || isSNum(temp)==1) {
                printf("\nParsed %s", temp);
                return 1;
        }
        fseek(fp,-strlen(temp), SEEK_CUR);
        return 0;
}

int relop() {
        char* temp = getNextWord(fp);
        if(strcmp(temp, "==")==0) {
                printf("\nParsed %s", temp);
                char* temp1 = getNextWord(fp);
                if(strcmp(temp1,"=")==0) {
                        printf("\nParsed %s", temp1);
                        return 1;
                }
                fseek(fp, -strlen(temp1), SEEK_CUR);
                return 0;
        }
        if(strcmp(temp, "!")==0) {
                printf("\nParsed %s", temp);
                char* temp1 = getNextWord(fp);
                if(strcmp(temp1,"=")==0) {
                        printf("\nParsed %s", temp1);
                        return 1;
                }
                fseek(fp, -strlen(temp1), SEEK_CUR);
                return 0;
        }
        if(strcmp(temp, "<")==0) {
                printf("\nParsed %s", temp);
                char* temp1 = getNextWord(fp);
                if(strcmp(temp1,"=")==0) {
                        printf("\nParsed %s", temp1);
                        return 1;
                }
                fseek(fp, -strlen(temp1), SEEK_CUR);
                return 1;
        }
        if(strcmp(temp, ">")==0) {
                printf("\nParsed %s", temp);
                char* temp1 = getNextWord(fp);
                if(strcmp(temp1,"=")==0) {
                        printf("\nParsed %s", temp1);
                        return 1;
                }
                fseek(fp, -strlen(temp1), SEEK_CUR);
                return 1;
        }
        fseek(fp,-strlen(temp), SEEK_CUR);
        return 0;
}

int addop() {
        char* temp1 = getNextWord(fp);
        if((strcmp(temp1,"+")==0) || (strcmp(temp1,"-")==0)) {
                printf("\nParsed %s", temp1);
                return 1;
        }
        fseek(fp, -strlen(temp1), SEEK_CUR);
        return 0;
}

int mulop() {
        char* temp1 = getNextWord(fp);
        if((strcmp(temp1,"*")==0) || (strcmp(temp1,"/")==0) || (strcmp(temp1,"%")==0)) {
                printf("\nParsed %s", temp1);
                return 1;
        }
        fseek(fp, -strlen(temp1), SEEK_CUR);
        return 0;
}

int main() {
        char fileName[100];
        printf("Enter the file Name\n");
        //scanf("%s", fileName);
        fp = fopen("test", "r");
        LexicalAnalyzer(fp);
        fp = fopen("test", "r");
        if(Program() == 1) printf("\nString possible by grammar");
        else printf("\nString not present in grammar");
        return 0;
}
