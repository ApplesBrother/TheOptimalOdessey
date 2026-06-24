#include<bits/stdc++.h>
using namespace std;

void dfs(vector<int> connected[],vector<bool> &visited,vector<int> &parent,int pos,bool &valid){
        if(valid){
                return;
        }
        for(auto k:connected[pos]){
                if(k==parent[pos]){
                        continue;
                }
                if(visited[k]){
                        valid=true;
                        int len=0;
                        int i=pos;
                        while(i!=k){
                                len++;
                                i=parent[i];
                        }
                        cout<<len+2<<endl;
                        i=pos;
                        cout<<pos<<" ";
                        while(i!=k){
                                cout<<parent[i]<<" ";
                                i=parent[i];
                        }
                        cout<<pos<<endl;
                        return;
                }
                visited[k]=true;
                parent[k]=pos;
                dfs(connected,visited,parent,k,valid);
                if(valid){
                        return;
                }
        }
        return;
}

int main(){
        int n,m;cin>>n>>m;
        vector<int> connected[n+1];
        int x,y;
        while(m--){
                cin>>x>>y;
                connected[y].push_back(x);
                connected[x].push_back(y);
        }
        vector<bool> visited(n+1);
        bool valid=false;
        for(int i=1;i<=n;i++){
                if(visited[i]){
                        continue;
                }
                vector<int> parent(n+1);
                visited[i]=true;
                dfs(connected,visited,parent,i,valid);
                if(valid){
                        return 0;
                }
        }
        if(!valid){
                cout<<"IMPOSSIBLE\n";
                return 0;
        }
}
