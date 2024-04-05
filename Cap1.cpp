#include<iostream>
#include<bits/stdc++.h>
#include<fstream>
#include<string>
#include<cstring>
using namespace std;

#define alphabets_in_english 26

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
        //making a string for length of n+1 length
        string s1;
        s1.append(str);
        string lower_alpha[] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
        for(int i=0;i<=25;i++){
            string word="";
            string D=lower_alpha[i];
            word=s1;
            word.append(D);
            // cout<<word<<" ";
            // cout<<search(root,word)<<endl;
            if(search(root,word)){
                cout<<word<<endl;
            }

        }

        
    }

    void incorrect_arrange(string str, int l, int r,trienode*root){ 
        string a=str;
        if (l == r){ 
            //cout << a <<"=>"<<search(root,a)<<endl;
            if(search(root,a)){
                cout<< a <<endl;
            } 
        }
        else { 
            // Permutations made 
            for (int i = l; i <= r; i++) { 
    
                // Swapping done 
                swap(a[l], a[i]); 
    
                // Recursion called 
                incorrect_arrange(a, l + 1, r,root); 
    
                // backtrack 
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
        storage_file=store(sentence);
    }
    if(!search(root,"stac")){
    missingchar(root,"stac");
    incorrect_arrange("stac",0,sizeof("stac")-2,root);
    extrachar("bstar",root);}
    return 0;
}

    