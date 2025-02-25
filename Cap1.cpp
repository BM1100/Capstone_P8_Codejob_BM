#include<iostream>
#include<bits/stdc++.h>
#include<fstream>
#include<string>
#include<cstring>
using namespace std;

#define alphabets_in_english 26

class node{
    public:
    string data;
    node* left;
    node* right;

    node(){
        data="";
        left=NULL;
        right=NULL;
    }
    node(string str){
        data=str;
        left=NULL;
        right=NULL;
    }
};

class DLL{
    public:
    node* head;

    DLL(){head=NULL;}
    void insert(string str){
        node* n=new node(str);
        if(head==NULL){
            insertathead(str);
            return;
        }
        node* temp=head;
        while(temp->right!=NULL){
            temp=temp->right;
        }
        temp->right=n;
        n->left=temp;
    }

    void insertathead(string str){
        node* n= new node(str);
        n->right=head;

        if(head!=NULL){
            head->left=n;
        }
        head=n;
    }

    void display(){
        node*temp=head;
        int i=0;
        while(temp!=NULL){
            i++;
            cout<<i<<" "<<temp->data<<endl;
            temp=temp->right;
        }
        cout<<endl;
    }

    void pop(){
        node* temp=head;
        if(head->right=NULL){
            head=NULL;
        }
        while(temp->right!=NULL){
            temp=temp->right;
        }
        node*save = temp->left->right;
        temp->left->right=NULL;
        delete save;
    }

    friend void clear(DLL list);
    
};



class trienode{
    trienode* children[alphabets_in_english];

    bool isend;
    public:

    friend void insert(trienode *root,string key);
    friend bool search(trienode* root, string key);
    friend trienode* getnode();
    friend string missingchar(trienode*root,string str,DLL* list);
    friend void incorrect_arrange(string str, int l, int r,trienode*root,DLL* list);
    friend void extrachar(string str,trienode* root,DLL* list);
    friend void exchange_char(string str,trienode* root,DLL* list);
    friend void permute(string str,trienode*root,DLL* list);
};
    trienode* getnode(){
        trienode* node=new trienode;

        node->isend=false;
        for(int i=0;i<alphabets_in_english;i++){
            node->children[i]=NULL;
        }
        return node;
    }

    void insert(trienode *root,string key){
        trienode* temp=root;
        for(int i=0;i<key.length();i++){
            int index=key[i]-'a';
            if(!temp->children[index]){
                temp->children[index]=getnode();
            }
            temp=temp->children[index];
        }
        temp->isend=true;
    }

    bool search(trienode* root, string key){
        trienode* temp= root;
        for (int i = 0; i < key.length(); i++){
            int index = key[i] - 'a';
            if(!temp->children[index]){
                return false;
            }
            temp=temp->children[index];
        }
        return temp->isend;
    }
    void permute(string str,trienode*root,DLL* list){
        char last=str.back();
        str.pop_back();
        for(int i=0;i<str.length();i++){
            string s2=str.substr(0,i)+last+str.substr(i,str.length());
            if(search(root,s2)){
                
                list->insert(s2);
                
            } 
        }
    }
    string missingchar(trienode*root,string str,DLL* list){
        int x = str.length();
        string s1;
        s1.append(str);
        string lower_alpha[] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
        for(int i=0;i<=25;i++){
            string word="";
            string D=lower_alpha[i];
            word=s1;
            word.append(D);
            if(search(root,word)){
                list->insert(word);
            } 
            permute(word,root,list);

        }

        
    }

    void incorrect_arrange(string str, int l, int r,trienode*root,DLL* list){ 
        string a=str;
        if (l == r){ 
            if(search(root,a)){
                //cout<< a <<endl;
                list->insert(a);
                
            } 
        }
        else { 
            for (int i = l; i <= r; i++) { 
                swap(a[l], a[i]); 
                incorrect_arrange(a, l + 1, r,root,list); 
                swap(a[l], a[i]); 
            } 
        } 
    } 

    void extrachar(string str,trienode* root,DLL* list){
        string s2;
        for(int i=0;i<str.length();i++)
        {
            s2=str;
            for(int j=i;j<str.length();j++)
            {
                s2[j]=str[j+1];
            }
            s2.pop_back();
            if(search(root,s2)){
                //cout<< s2 <<endl;
                list->insert(s2);
                //list->display();
            } 
            
        }
    }
    queue<string> store(string s){
        queue<string> stc;
        string temp="";
        for(int i=0;i<s.length();i++)
        {
            if(s[i]==' ')
            {
            stc.push(temp);
            temp="";          
            }
            else if((s[i]=='.')||(s[i]==',')||(s[i]=='?')||(s[i]=='!')||(s[i]==':')){
                stc.push(temp);
                string punctuation;
                punctuation.push_back(s[i]);
                stc.push(punctuation);
                temp=""; 
            }
            else
            {
            temp=temp+s[i];
            }
        
        }
        stc.push(temp);   
        cout<<endl;
        return stc;
    }
 
    void exchange_char(string str, trienode* root,DLL* list){
        string s2=str;
        string lower_alpha[] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
        for(int i=0;i<s2.length();i++){
            for(int j=0;j<26;j++){
                s2.replace(i,1,lower_alpha[j]);
                if(search(root,s2)){
                    //cout<< s2 <<endl;
                    list->insert(s2);
                } 
            }
            s2=str;
        }
    }
    string lowercase(string str){
    for(int i=0;i<str.length();i++){
        if((str[i]>=65)&&(str[i])<=90){
            str[i]+=32;
        }
        else {
        continue;}
    }
    return str;
    }

    string uppercase_first_char(string str){
        if((str[0]>=97)&&(str[0]<=122)){
        str[0]-=32;
        return str;}
        else 
        return str;
    }
    
int main(){
    trienode* root = getnode();
    ifstream in("words.txt");
    string st;
    queue<string> storage_file;
    while(!in.eof()){
        getline(in,st);
        insert(root,st);
    }
    in.close();
    string sentence;
    ifstream pull("sample.txt");
    while(!pull.eof()){
        getline(pull,sentence);
        storage_file=store(sentence);
        
    }
    pull.close();
   
    queue<string> output;
    while(!storage_file.empty()){
        DLL* list=new DLL();
        string stored=storage_file.front();
        stored=lowercase(stored);
        
        if((stored==",")||(stored==".")||(stored=="!")||(stored=="?")||(stored==" ")||(stored=="")){
            output.push(storage_file.front());
        }
        else if(!search(root,stored)){
            cout<<"Incorrect spelling :"<<stored<<endl;
            incorrect_arrange(stored,0,stored.length()-2,root,list);
            extrachar(stored,root,list);
            exchange_char(stored,root,list);
            missingchar(root,stored,list);
            list->display();
            cout<<"Enter the index of the word you want to replace with"<<endl;
            cout<<"Enter 0 to Add to dictionary"<<endl;
            int index;
            cin>>index;
            if(index==0){
                insert(root,stored);
                output.push(stored);
                
            }

            else{
            node*temp=list->head;
            for(int i=0;i<index-1;i++){
                temp=temp->right;
            }
            output.push(temp->data);
            }

            
        }
        else {
            output.push(storage_file.front());
        }
        
        storage_file.pop();
    }

    
    string to_out="";
    while(!output.empty()){
        if(to_out.back()=='.'||to_out.empty()){
            output.front()=uppercase_first_char(output.front());
            to_out=to_out+output.front();
            to_out=to_out+" ";
            output.pop();
        }
        else if((output.front()==",")||(output.front()=="!")||(output.front()==":")||(output.front()=="?")||(output.front()==".")){
            to_out.pop_back();
            to_out=to_out+output.front();
            to_out=to_out+" ";
            output.pop();
        }
        else{
        to_out=to_out+output.front();
        to_out=to_out+" ";
        output.pop();}
    }
    cout<<to_out<<endl;
    ofstream out("sample.txt");
    out<<to_out;
    out.close();
    return 0;
}


    