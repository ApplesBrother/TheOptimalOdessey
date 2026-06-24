#include<bits/stdc++.h>
using namespace std;

void dfs(vector<int> adjacency[],vector<bool> &visited,int pos){
        if(visited[pos]){
                return;
        }
        visited[pos]=true;
        for(auto k:adjacency[pos]){
                dfs(adjacency,visited,k);
        }
        return;
}

int main(){
        int n,m;
        cin>>n>>m;
        vector<char> space(m*n);
        vector<int> adjacency[m*n];
        vector<bool> visited(m*n,false);
        for(int i=0;i<m*n;i++){
                cin>>space[i];
                if(i>=m){
                        if(space[i-m]=='.'&&space[i]=='.'){
                                adjacency[i-m].push_back(i);
                                adjacency[i].push_back(i-m);
                        }
                }
                if(i%m>0){
                        if(space[i]=='.'&&space[i-1]=='.'){
                                adjacency[i-1].push_back(i);
                                adjacency[i].push_back(i-1);
                        }
                }
        }
        int count=0;
        for(int i=0;i<m*n;i++){
                if(space[i]=='#'){
                        continue;
                }
                if(visited[i]){
                        continue;
                }
                dfs(adjacency,visited,i);
                count++;
        }
        cout<<count<<"\n";
        return 0;
}