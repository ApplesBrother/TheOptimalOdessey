#include<bits/stdc++.h>
using namespace std;

void classify(int i,int count,vector<int> adjacency[],vector<int> &visited){
        visited[i]=count;
        for(auto k:adjacency[i]){
                if(visited[k]!=0){
                        continue;
                }
                classify(k,count,adjacency,visited);
        }
        return;
}

int main(){
        int n,m;cin>>n>>m;
        vector<int> adjacency[n];
        vector<int> visited(n,0);
        while(m){
                m--;
                int x,y;
                cin>>x>>y;
                adjacency[x-1].push_back(y-1);
                adjacency[y-1].push_back(x-1);
        }
        vector<int> visited1;
        int count=0;
        for(int i=0;i<n;i++){
                if(visited[i]==0){
                        count++;
                        visited1.push_back(i);
                        classify(i,count,adjacency,visited);
                }
        }
        cout<<count-1<<endl;
        for(int i=0;i<count-1;i++){
            cout<<visited1[i]+1<<" "<<visited1[i+1]+1<<endl;
        }
}