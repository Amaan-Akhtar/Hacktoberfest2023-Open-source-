/*
Given an m x n board of characters and a list of strings words, return all words on the board.

Each word must be constructed from letters of sequentially adjacent cells, where adjacent cells are
horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.
*/
class Node{
    public:
    int endofword;
    Node*child[26];
    Node(){
        for(int i=0;i<26;i++) child[i] = NULL;
        endofword=0;
    }
};
class Trie{
    public:
    Node *root;
    Trie(){
        root = new Node;
    }
    void insert(string s){
        Node *temp = root;
        for(int i=0;i<s.size();i++){
            int idx = s[i]-'a';
            if(!temp->child[idx]){
                temp->child[idx] = new Node();
            }
            temp = temp->child[idx];
        }
        temp->endofword+=1;
    }
};
class Solution {
public:
    vector<int>dir={0,1,0,-1,0};
    vector<string>ans;
    void dfs(vector<vector<char>>& A,int i,int j,Node*root,string temp){
        if(root==NULL) return;
        temp.push_back(A[i][j]); 
        A[i][j] = '?';
        if(root->endofword)    ans.push_back(temp),root->endofword-=1;
        for(int d=0;d<4;d++){
            int x = i+dir[d],y=j+dir[d+1];
            if(x<0||y<0||x>=A.size()||y>=A[0].size()) continue;
            if(A[x][y]>='a'&&A[x][y]<='z'){
                dfs(A,x,y,root->child[A[x][y]-'a'],temp);
            }
        }
        A[i][j] = temp[temp.size()-1];
        temp.pop_back();
    }
    vector<string> findWords(vector<vector<char>>& A, vector<string>& words) {
        Trie *t = new Trie();
        ans.clear();
        for(auto i:words) t->insert(i);
        for(int i=0;i<A.size();i++){
            for(int j=0;j<A[0].size();j++){
                string temp="";
                dfs(A,i,j,t->root->child[A[i][j]-'a'],temp);
            }
        }
        return ans;
    }
};
