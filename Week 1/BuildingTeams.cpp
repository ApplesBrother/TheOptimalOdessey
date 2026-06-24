#include<bits/stdc++.h>
using namespace std;

void classify(vector<int> adjacency[],vector<bool> &visited,vector<int> &team,int pos,bool &valid){
        for(auto k:adjacency[pos]){
                if(valid){
                        if(visited[k]){
                                if(team[pos]==team[k]){
                                        valid=false;
                                }
                                continue;
                        }
                        visited[k]=true;
                        team[k]=3-team[pos];
                        classify(adjacency,visited,team,k,valid);
                }
        }
        return;
}


int main(){
        int n,m;cin>>n>>m;
        vector<int> adjacency[n+1];
        int x,y;
        while(m--){
                cin>>x>>y;
                adjacency[x].push_back(y);
                adjacency[y].push_back(x);
        }
        vector<bool> visited(n+1);
        vector<int> team(n+1);
        team[1]=1;
        bool valid=true;
        for(int i=1;i<=n;i++){
            if(visited[i]==false){
                team[i]=1;
                visited[i]=true;
                classify(adjacency,visited,team,i,valid);
            }
            if(!valid){
                break;
            }
        }
        if(!valid){
                cout<<"IMPOSSIBLE\n";
                return 0;
        }
        for(int i=1;i<=n;i++){
                cout<<team[i]<<" ";
        }
        cout<<endl;
        return 0;
}