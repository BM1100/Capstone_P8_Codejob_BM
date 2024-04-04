#include<iostream>
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


int main(){
    trienode* root = getnode();
    ifstream in("words.txt");
    string st;
    while(!in.eof()){
        getline(in,st);
        insert(root,st);
    }

    if(!search(root,"stac")){
    missingchar(root,"stac");}
    return 0;
}