#include<stdio.h>
#include<string.h>
#include<stdlib.h>


typedef struct SymbolTableEntry{
	char name[50], type[10], scope, arg[10][10], returnType[10];
	int size, nArg;
} STE;

STE ste[100];
char lastKeyWord[10];
int steSize =0;
int nopb=0;
int nopb2=0;
int nowArg = 0;

char keyWords[33][10] = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while", "FILE"};
char specialCharacters[5] = {';', '{', '(', ')', '}'};
char operators[9] = {'=', '!', '>', '<', '+', '-', '%', '/', '^'};
char types[8][10] = {"int", "char", "double", "float", "long", "void", "struct", "FILE"};

int isNum(char c) {
    if(c>='0' && c<='9') {
        return 1;
    }
    return 0;
}

int isAlpha(char c) {
    if((c>='a' && c<='z') || (c>='A' && c<='Z')) return 1;
    else return 0;
}

int isKeyword(char* word){
	for(int i=0;i<33;i++){
		if(strcmp(word, keyWords[i])==0){
			strcpy(lastKeyWord, word);
			return 1;
		}
	}
	return 0;
}

void addArg(int i, char* word) {
	strcpy(ste[i].arg[ste[i].nArg-1], word);
}

void checkSymbolTable(char* word) {
    //printf("Got word %s", word);
	for(int i=0; i<steSize; i++){
		if(strcmp(ste[i].name, word) == 0){
			printf("<id,%d>", i+1);
			return;
		}
	}
	if(nowArg == 1 && !isKeyword(word)) {
		//printf("hello");
		for(int i=steSize-1;i>=0;i--){
			if(strcmp(ste[i].type,"FUNC")==0){
				ste[i].nArg++;
				addArg(i, word);
				break;
			} 
		}
	}
	for(int i=0;i<8;i++){
        if(strcmp(lastKeyWord, types[i]) == 0) {
            strcpy(ste[steSize].name, word);
            ste[steSize].nArg = 0;
            printf("<id,%d>",steSize+1);
            if(nopb>0 || nopb2>0) {
            	ste[steSize].scope = 'L';
            }
            else ste[steSize].scope = 'G';
            //printf("\nnopb here %d\n", nopb);
            //if(nopb2 == 0 && ((nopb > 0 ) || (strcmp(lastKeyWord,"struct")==0)))
            strcpy(ste[steSize].type, lastKeyWord);
            //else strcpy(ste[steSize].type, "FUNC");
            steSize++;
            break;
        }
	}
}

void printSymbolTable() {
    for(int i=0; i<steSize; i++) {
    	if(strcmp(ste[i].type, "int")==0) ste[i].size=sizeof(int);
    	if(strcmp(ste[i].type, "char")==0) ste[i].size=sizeof(char);
    	if(strcmp(ste[i].type, "long")==0) ste[i].size=sizeof(long);
    	if(strcmp(ste[i].type, "double")==0) ste[i].size=sizeof(double);
    	if(strcmp(ste[i].type, "FUNC")==0) ste[i].scope=' ';
        printf("\n%d\t%s\t%s\t%c\t%d\t%s\t%d\t", i+1, ste[i].name, ste[i].type, ste[i].scope, ste[i].nArg, ste[i].returnType, ste[i].size);
    	for(int j=0;j<ste[i].nArg; j++) {
    		printf("%s <id,%d> ", ste[i].arg[j], i+j+2);
    	}
    }
}

int isSpecialOrOperator(char c){
	for(int i=0; i<5; i++){
		if(specialCharacters[i] == c){
			return 1;
		}
	}
	for(int i=0; i<9; i++){
		if(operators[i] == c){
			return 1;
		}
	}
	return 0;
}





char* getNextWord(FILE *fp){
	//printf("Here now\n");
	char c = fgetc(fp);
	if(c == EOF) return "EOF!";
	//printf("\nHere here %c\n", c);
	if(c == '"') {
		printf("%c", c);
        c=fgetc(fp);
        while(c!='"') {
            printf("%c", c);
            c = fgetc(fp);
        }
        printf("%c", c);
        c = fgetc(fp);
	}
	if(c == '\'') {
		printf("%c", c);
        c=fgetc(fp);
        while(c!='\'') {
            printf("%c", c);
            c = fgetc(fp);
        }
        printf("%c", c);
        c = fgetc(fp);
	}
	while(isSpecialOrOperator(c) && c!=EOF){
        if(c == '{') nopb++;
        else if(c=='}') nopb--;
		if(c == '(') {
			nopb2++;
			
			if(nowArg==0) {
				if(!strcmp(lastKeyWord,"while")==0 && !strcmp(lastKeyWord,"for")==0 && !strcmp(lastKeyWord,"do")==0 && strcmp(lastKeyWord,"return")!=0) {
					strcpy(ste[steSize-1].returnType, ste[steSize-1].type);
					strcpy(ste[steSize-1].type, "FUNC");
				}
				
				nowArg=1;
			}
		}
        else if(c==')') {
        	nopb2--;
        	nowArg=0;
        }
		printf("<%c>", c);
		c=fgetc(fp);
	}
	//printf("\nHere here\n");
	if(c == EOF) return "EOF!";
	char* word = malloc(30*sizeof(char));
	if(isAlpha(c)) {
        int i=0;
        while(isAlpha(c) || isNum(c)){
            word[i++] = c;
            c=fgetc(fp);
        }
        word[i] = '\0';
        if(isKeyword(word)) {
            printf("<%s>", word);
        }
        else {
            //printf("%s", word);
            checkSymbolTable(word);
        }
	}
	if(c == '"') {
		printf("%c", c);
        c=fgetc(fp);
        while(c!='"') {
            printf("%c", c);
            c = fgetc(fp);
        }
        printf("%c", c);
        c = fgetc(fp);
	}
	if(c == '\'') {
		printf("%c", c);
        c=fgetc(fp);
        while(c!='\'') {
            printf("%c", c);
            c = fgetc(fp);
        }
        printf("%c", c);
        c = fgetc(fp);
	}
	if(isSpecialOrOperator(c) && c!=EOF){
	    if(c == '{') nopb++;
        else if(c=='}') nopb--;
		if(c == '(') {
			nopb2++;
			if(nowArg==0) {
				if(!strcmp(lastKeyWord,"while")==0 && !strcmp(lastKeyWord,"for")==0 && !strcmp(lastKeyWord,"do")==0 && strcmp(lastKeyWord,"return")!=0) {
					strcpy(ste[steSize-1].returnType, ste[steSize-1].type);
					strcpy(ste[steSize-1].type, "FUNC");
				}
				
				nowArg=1;
			}
		}
        else if(c==')') {
        	nopb2--;
        	nowArg=0;
        }
		printf("<%c>", c);
	}
    else if(!isSpecialOrOperator(c)) printf("%c", c);
    else return "EOF!";
    return word;
}

int main(){
    char fileName[20], fileName2[20];
    FILE *fp, *fp2;
    printf("Enter the input file name \n");
    scanf("%s", fileName);
    //printf("Enter the output file name");
    //scanf("%s", fileName2);
    fp = fopen(fileName, "r");
    //fp2 = fopen(fileName2, "w");

    if (fp == NULL) {
        printf("Error Occured: Error while opening the input file.\n");
        exit(0);
    }


    while (1) {
        char* word = malloc(30*sizeof(char));
        word = getNextWord(fp);
        if(strcmp(word, "EOF!") == 0){
        	break;
        }
    }
    fclose(fp);
    //fclose(fp2);
    printf("Index\tName\tType\tScope\tnArg\tRetType\tSize\tArguments");
    printSymbolTable();
    return 0;
}


/*
"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
*/
