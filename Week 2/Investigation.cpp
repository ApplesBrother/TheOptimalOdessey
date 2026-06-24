#include<bits/stdc++.h>
using namespace std;
#define INF 1.0e+18

int main(){
        int n,m;cin>>n>>m;
        vector<pair<int,long long>> adj[n+1],adj1[n+1];
        int x,y;
        long long z;
        while(m--){
                cin>>x>>y>>z;
                adj[x].push_back({y,z});
                adj1[y].push_back({x,z});
        }
        vector<bool> visited(n+1,false);
        vector<long long> distance(n+1,INF);
        vector<int> mn(n+1,INF);
        mn[1]=0;
        vector<int> mx(n+1,0);
        vector<long long> count(n+1,0);
        count[1]=1;
        distance[1]=0;
        priority_queue<pair<long long,int>> q;
        q.push({0,1});
        while(!q.empty()){
                int s=q.top().second;
                q.pop();
                if(visited[s]){
                        continue;
                }
                for(auto k:adj[s]){
                        if(visited[k.first]){
                                continue;
                        }
                        if(distance[k.first]>distance[s]+k.second){
                                distance[k.first]=distance[s]+k.second;
                                q.push({-distance[k.first],k.first});
                        }
                }
                visited[s]=true;
                for(auto k:adj1[s]){
                        if(visited[k.first]&&distance[k.first]+k.second==distance[s]){
                                count[s]=(count[s]+count[k.first])%(1000000007);
                                mx[s]=max(mx[s],mx[k.first]+1);
                                mn[s]=min(mn[s],mn[k.first]+1);
                        }
                }
        }
        cout<<distance[n]<<" "<<count[n]<<" "<<mn[n]<<" "<<mx[n]<<"\n";
        return 0;
}
