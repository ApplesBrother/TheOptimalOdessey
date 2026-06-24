#include<bits/stdc++.h>
using namespace std;

void classify(vector<int> &visited,vector<int> adjacency[],int pos){
        for(auto pos1:adjacency[pos]){
                if(visited[pos1]==1){
                        continue;
                }
                visited[pos1]=1;
                classify(visited,adjacency,pos1);
        }
        return;
}

int main(){
        int n,m;cin>>n>>m;
        vector<int> adjacency[n+1];
        vector<int> visited(n+1,0);
        visited[n]=1;
        int x,y;
        for(;m>0;m--){
                cin>>x>>y;
                adjacency[x].push_back(y);
                adjacency[y].push_back(x);
        }
        classify(visited,adjacency,n);
        if(visited[1]!=1){
                cout<<"IMPOSSIBLE\n";
                return 0;
        }
        queue<int> q;
        bool visited1[n+1]={false};
        int distance[n+1]={0};
        vector<int> parent(n+1);
        visited1[1]=true;
        parent[1]=0;
        parent[0]=-1;
        distance[1]=0;
        q.push(1);
        while(!q.empty()){
                int s=q.front();
                q.pop();
                for(auto k: adjacency[s]){
                        if(visited1[k]){
                                continue;
                        }
                        visited1[k]=true;
                        distance[k]=distance[s]+1;
                        parent[k]=s;
                        q.push(k);
                        if(k==n){
                                while(!q.empty()){
                                        q.pop();
                                }
                                break;
                        }
                }
        }
        vector<int> path;
        cout<<distance[n]+1<<endl;
        int i=n;
        while(parent[i]!=-1){
                path.push_back(i);
                i=parent[i];
        }
        for(int i=path.size();i>0;i--){
            cout<<path[i-1]<<" ";
        }
        cout<<endl;
        return 0;
}