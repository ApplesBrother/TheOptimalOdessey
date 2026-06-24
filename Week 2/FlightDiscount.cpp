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
        vector<bool> visited(n+1,false);
        priority_queue<pair<long long,int>> q;
        vector<long long> distance(n+1,INF);
        vector<long long> cdistance(n+1,INF);
        distance[1]=0;
        cdistance[1]=0;
        q.push({0,1});
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
        q.push({0,1});
        vector<bool> visited1(n+1,false);
        while(!q.empty()){
                int s=q.top().second;
                q.pop();
                if(visited1[s]){
                        continue;
                }
                for(auto k:adjacency[s]){
                        if(visited1[k.first]){
                                continue;
                        }
                        if(cdistance[k.first]>min(distance[s]+k.second/2,cdistance[s]+k.second)){
                                cdistance[k.first]=min(distance[s]+k.second/2,cdistance[s]+k.second);
                                q.push({-min(cdistance[k.first],distance[k.first]),k.first});
                        }
                }
                visited1[s]=true;
        }
        cout<<cdistance[n]<<"\n";
        return 0;
}