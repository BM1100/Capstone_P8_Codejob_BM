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
        while(temp!=NULL){
            cout<<temp->data<<" ";
            temp=temp->right;
        }
        cout<<endl;
    }
}; DLL list_correct;

class trienode{
    trienode* children[alphabets_in_english];

    bool isend;
    public:

    friend void insert(trienode *root,string key);
    friend bool search(trienode* root, string key);
    friend trienode* getnode();
    friend string missingchar(trienode*root,string str);
    friend void incorrect_arrange(string str, int l, int r,trienode*root);
    friend void extrachar(string str,trienode* root);
    friend void exchange_char(string str,trienode* root);
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
    string missingchar(trienode*root,string str){
        int x = str.length();
        string s1;
        s1.append(str);
        string lower_alpha[] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
        for(int i=0;i<=25;i++){
            string word="";
            string D=lower_alpha[i];
            word=s1;
            word.append(D);
            incorrect_arrange(word,0,word.length()-1,root);

        }

        
    }

    void incorrect_arrange(string str, int l, int r,trienode*root){ 
        string a=str;
        if (l == r){ 
            if(search(root,a)){
                cout<< a <<endl;
                list_correct.insert(a);
            } 
        }
        else { 
            for (int i = l; i <= r; i++) { 
                swap(a[l], a[i]); 
                incorrect_arrange(a, l + 1, r,root); 
                swap(a[l], a[i]); 
            } 
        } 
    } 

    void extrachar(string str,trienode* root){
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
                cout<< s2 <<endl;
                list_correct.insert(s2);
            } 
            
        }
    }
    stack<string> store(string s){
        stack<string> stc;
        string temp="";
        for(int i=0;i<s.length();i++)
        {
            if(s[i]==' ')
            {
            stc.push(temp);
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
 
    void exchange_char(string str, trienode* root){
        string s2=str;
        string lower_alpha[] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
        for(int i=0;i<s2.length();i++){
            for(int j=0;j<26;j++){
                s2.replace(i,1,lower_alpha[j]);
                if(search(root,s2)){
                    cout<< s2 <<endl;
                    list_correct.insert(s2);
                } 
            }
            s2=str;
        }
    }
    
int main(){
    trienode* root = getnode();
    ifstream in("words.txt");
    string st;
    stack<string> storage_file;
    while(!in.eof()){
        getline(in,st);
        insert(root,st);
    }
    in.close();
    string sentence;
    ifstream pull("sample.txt");
    while(!pull.eof()){
        getline(pull,sentence);
        if((sentence.back()==',')||(sentence.back()=='.')||(sentence.back()==':')){
            sentence.pop_back();
        }
        storage_file=store(sentence);
    }
    // if(!search(root,"stac")){
    //     missingchar(root,"stac");
    //     incorrect_arrange("stac",0,sizeof("stac")-2,root);
    //     extrachar("stac",root);
    //     exchange_char("stac",root);
    // }
    
    while(!storage_file.empty()){
        if(!search(root,storage_file.top())){
            cout<<"Incorrect spelling :"<<storage_file.top()<<endl;
            incorrect_arrange(storage_file.top(),0,storage_file.top().length()-2,root);
            extrachar(storage_file.top(),root);
            exchange_char(storage_file.top(),root);
        }
        storage_file.pop();
    }
    
    return 0;
}

    