//
//  main.cpp
//  mycalculate
//
//  Created by 黎景 on 5/24/16.
//  Copyright © 2016 黎景. All rights reserved.
//

//注意注意注意！这段代码在mac上可以运行，windows因为字符识别和mac不太一样


#include <iostream>
#include "string"
using namespace std;
//int i;
#define Maxsize 50
int Flag=1;
typedef struct Mystack{
    string data[Maxsize];
    int top;
    // top<Maxsize;
    
}*mystack;
void Initstack(mystack &S){
    S->top=-1;
}

void Push(mystack &S,string m){
    S->data[++S->top]=m;
}

void Pop(mystack &S,string &x){
    x=S->data[S->top];
    // S->data[S->top]=NULL;
    S->top--;
    
    //S.data[S.top]=NULL;
    
    //return x;
}

string compare(string a,string b){
    int m,n;
    if(a=="+"||a=="-"){
        m=0;
    }else if(a=="*"||a=="/"){
        m=1;
    }
    if(b=="+"||b=="-"){
        n=0;
    }else if(b=="*"||b=="/"){
        n=1;
    }else{
        n=-1;
    }
    
    string result;
    if(m==n){
        result="equal";
        
    }else if(m>n){
        result="high";
        
    }else if(m<n){
        result="low";
        
    }
    
    return result;
}

mystack change(string str,int i,mystack &S1,mystack &S2){
    // int i=str.length();
    //Mystack S2;
    //Initstack(S1);
    //Initstack(S2);
    cout<<"haha\n";
    for(int j=0;j<i;j++){
        string st;
        st=str[j];
        //cout<<str[j]<<'?'<<'\n';
        if(st=="("){
            Flag=1;
            Push(S2, "(");
            continue;
        }else if(st=="+"||st=="-"||st=="*"||st=="/"){
            Flag=1;
            
            if(S2->top==-1){
                Push(S2, st);
                continue;
            }else if(S2->top!=-1&&compare(st, S2->data[S2->top])=="high"){
                Push(S2, st);
                continue;
            }else {
                string x;
                while(S2->top!=-1&&compare(st, S2->data[S2->top])!="high"){
                    Pop(S2, x);
                    Push(S1, x);
                }
                
                Push(S2,st);
                continue;
                
                
                
            }
            
            
        }else if(st==")"){
            Flag=1;
            string x;
            while(S2->data[S2->top]!="("){
                Pop(S2, x);
                Push(S1, x);
            }
            Pop(S2, x);
            continue;
        }else{
            if(Flag==1){
                Push(S1, st);
                Flag=0;
                continue;
            }else{
                S1->data[S1->top]=S1->data[S1->top]+st;
                continue;
            }
        }
        
    }
    string v;
    while(S2->top!=-1){
        Pop(S2, v);
        Push(S1, v);
        
    }
    return S1;
    
}

void Outputstack(mystack s){
    int o=s->top;
    while(o!=-1){
        cout<<s->data[o]<<'\n';
        o--;
        
    }
    
}

void Resetstack(mystack &a,mystack &b){
    string x;
    while(a->top!=-1){
        Pop(a, x);
        Push(b, x);
    }
}

double getendvalue(mystack &L){
    string m,k;
    int i=0;
    //Pop(L, m);double x=atof(m.c_str());
    double x,y[10];
    while(L->top!=-1){
        Pop(L, k);
        if(k=="+"){
            i--;
            y[(i-1)]=y[(i-1)]+y[i];
            continue;
        }else if(k=="-"){
            i--;
            y[(i-1)]=y[(i-1)]-y[i];
            continue;
        }else if(k=="*"){
            i--;
            y[(i-1)]=y[(i-1)]*y[i];
            continue;
        }else if(k=="/"){
            i--;
            y[(i-1)]=y[(i-1)]/y[i];
            continue;
        }else{
            
            y[i]=atof(k.c_str());
            i++;
            continue;
            
        }
        
    }
    x=y[--i];
    return x;
    
}

int main(){
    
    string str;
    cout<<"请输入你想要计算的式子：";
    cin>>str;
    int i=(int)str.length();
    Mystack *a,*b,*c;
    a=new Mystack();
    b=new Mystack();
    c=new Mystack();
    Initstack(a);
    Initstack(b);
    Initstack(c);
    change(str,i,a,b);
    //cout<<i;
    //cin>>str;
    //  Mystack *L;
    // *L=change(str);
    //Outputstack(a);
    Resetstack(a, c);
    
    //Outputstack(c);
    
    double m;
    m=getendvalue(c);
    cout<<"result=\n"<<m<<"\n//";
    Outputstack(b);
    
}

