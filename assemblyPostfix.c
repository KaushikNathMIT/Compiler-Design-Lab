#include <iostream>
#include <ctype.h>
#include <stack>
using namespace std;

int main() {
        int i=0;
        char postfix[] = "123*+4-";
        stack<int> s;
        int first, second, temp;
        char ch = postfix[i];
        while(postfix[i]!='\0') {
                ch = postfix[i];
                if(isdigit(ch)) {
                        s.push(ch-48);
                        cout<<"\nMove r"<<s.size()-1<<","<<ch;
                }
                else {
                        switch(ch) {
                                case '+' : {
                                        second = s.top();
                                        s.pop();
                                        first = s.top();
                                        s.pop();
                                        cout<<"\nadd r"<<s.size()<<",r"<<s.size()+1;
                                        temp = first+second;
                                        s.push(temp);
                                        break;
                                }
                                case '-' : {
                                        second = s.top();
                                        s.pop();
                                        first = s.top();
                                        s.pop();
                                        cout<<"\nsub r"<<s.size()<<",r"<<s.size()+1;
                                        temp = first-second;
                                        s.push(temp);
                                        break;
                                }
                                case '*' : {
                                        second = s.top();
                                        s.pop();
                                        first = s.top();
                                        s.pop();
                                        cout<<"\nmul r"<<s.size()<<",r"<<s.size()+1;
                                        temp = first*second;
                                        s.push(temp);
                                        break;
                                }
                                case '/' : {
                                        second = s.top();
                                        s.pop();
                                        first = s.top();
                                        s.pop();
                                        cout<<"\ndiv r"<<s.size()<<",r"<<s.size()+1;
                                        temp = first/second;
                                        s.push(temp);
                                        break;
                                }
                        }
                }
                i++;
        }
        while(s.size()>0) {
                cout<<"\n"<<s.top()<<"\n";
                s.pop();
        }
}
