#include<bits/stdc++.h>
using namespace std;
#define INF 1e18

int main(){
        int n,m;cin>>n>>m;
        vector<pair<int,long long>> adjacency[n+1];
        int x,y;
        long long z;
        while(m--){
                cin>>x>>y>>z;
                adjacency[x].push_back({y,z});
        }
        vector<long long> distance(n+1,INF);
        distance[1]=0;
        priority_queue<pair<long long,int>> q;
        q.push({0,1});
        vector<bool> visited(n+1,false);
        while(!q.empty()){
                int s=q.top().second;
                q.pop();
                if(visited[s]){
                        continue;
                }
                for(auto k:adjacency[s]){
                        if(visited[k.first]){
                                continue;
                        }
                        if(distance[k.first]>distance[s]+k.second){
                                distance[k.first]=distance[s]+k.second;
                                q.push({-distance[k.first],k.first});
                        }
                }
                visited[s]=true;
        }
        for(auto k:distance){
                if(k==INF){
                        continue;
                }
                cout<<k<<" ";
        }
        cout<<"\n";
        return 0;
}