#include<bits/stdc++.h>
using namespace std;
using json=nlohmann::ordered_json;
const double INF = numeric_limits<double>::infinity();

class Graph{
        public:
                vector<vector<double>> adj;
                int n;
                Graph(json graph_json){
                        n=graph_json["nodes"].size();
                        adj=vector<vector<double>>(n,vector<double>(n,INF));
                        for(int i=0;i<n;i++){
                                adj[i][i]=0;
                        }
                        for(auto i:graph_json["edges"]){
                                int u=i["u"],v=i["v"];
                                double w=i["w"];
                                adj[u][v]=w;
                                adj[v][u]=w;
                        }
                }
};

vector<vector<double>> floyd_warshall(vector<vector<double>>& adj,vector<int>& nodes){
        int n=adj.size();
        for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                        for(int k=0;k<n;k++){
                                if(adj[i][k]+adj[k][j]<adj[i][j]){
                                        adj[i][j]=adj[i][k]+adj[j][k];
                                }
                        }
                }
        }
        vector<vector<double>> adj1(nodes.size(),vector<double>(nodes.size()));
        for(int i=0;i<nodes.size();i++){
                for(int j=0;j<nodes.size();j++){
                        adj1[i][j]=adj[nodes[i]][nodes[j]];
                }
        }
        return adj1;
}

vector<pair<int,int>> prim_mst(vector<vector<double>>& dist){
        int n=dist.size();
        vector<bool> connected(n,false);
        connected[0]=true;
        priority_queue<tuple<float,int,int>> q;
        vector<pair<int,int>> v;
        for(int i=0;i<n;i++){
                q.push({-dist[i][0],0,i});
        }
        while(!q.empty()){
                auto [a,b,c]=q.top();
                q.pop();
                if(connected[c]){
                        continue;
                }
                connected[c]=true;
                v.push_back({b,c});
                for(int i=0;i<n;i++){
                        q.push({-dist[i][c],c,i});
                }
        }
        return v;
}

vector<pair<int,int>> perfect_matching(vector<int>& odds,vector<vector<double>>& dist){
        vector<pair<int,int>> v;
        priority_queue<tuple<double,int,int>> q;
        int n=odds.size();
        vector<bool> done(n,false);
        for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                        if(i==j){
                                continue;
                        }
                        q.push({-dist[odds[i]][odds[j]],i,j});
                }
        }
        int count=(n/2);
        while(count){
                auto [a,b,c]=q.top();
                q.pop();
                if(done[b]||done[c]){
                        continue;
                }
                done[b]=true;
                done[c]=true;
                count--;
                v.push_back({odds[b],odds[c]});
        }
        return v;
}

vector<int> eulerian_circuit(int m, vector<vector<pair<int,int>>>& adj_list){
        vector<int> degree(m);
        vector<bool> visited(m,false);
        int total_edges=0;
        for(int i=0;i<m;i++){
                degree[i]=adj_list[i].size();
                total_edges+=degree[i];
        }
        total_edges/=2;
        vector<bool> used(total_edges,false);
        vector<int> v;
        v.push_back(0);
        visited[0]=true;
        int present=0;
        while(degree[present]){
                for(auto k:adj_list[present]){
                        if(!used[k.second]){
                                degree[present]--;
                                degree[k.first]--;
                                v.push_back(k.first);
                                total_edges--;
                                used[k.second]=true;
                                present=k.first;
                                visited[present]=true;
                                break;
                        }
                }
        }
        while(total_edges){
                vector<int> v1;
                for(int i=0;;i++){
                        if(degree[v[i]]){
                                v1.push_back(v[i]);
                                present=v[i];
                                while(degree[present]){
                                        for(auto k:adj_list[present]){
                                                if(!used[k.second]){
                                                        degree[present]--;
                                                        degree[k.first]--;
                                                        v1.push_back(k.first);
                                                        total_edges--;
                                                        used[k.second]=true;
                                                        present=k.first;
                                                        visited[present]=true;
                                                        break;
                                                }
                                        }
                                }
                                v1.pop_back();
                                v.insert(v.begin()+i+1, v1.begin()+1, v1.end());
                                break;
                        }
                }
        }

        return v;
}

double tour_cost(const vector<int>& tour,vector<vector<double>>& dist){
        int sum=0;
        for(int i=0;i<tour.size()-1;i++){
                sum+=dist[tour[i]][tour[i+1]];
        }
        sum+=dist[tour[tour.size()-1]][tour[0]];
        return sum;
}

// Steps: Floyd-Warshall -> MST -> odd vertices -> matching -> Eulerian circuit -> shorcutting
vector<int> christofides(vector<vector<double>>& adj,vector<int>& nodes){
        vector<vector<double>> adj1=floyd_warshall(adj,nodes);
        vector<pair<int,int>> v=prim_mst(adj1);
        vector<int> degree(nodes.size(),0);
        int edge_count=0;
        vector<vector<pair<int,int>>> adj_list(nodes.size());
        for(auto k:v){
                degree[k.first]++;
                degree[k.second]++;
                adj_list[k.first].push_back({k.second,edge_count});
                adj_list[k.second].push_back({k.first,edge_count});
                edge_count++;
        }
        vector<int> odds;
        for(int i=0;i<nodes.size();i++){
                if(degree[i]%2){
                        odds.push_back(i);
                }
        }
        vector<pair<int,int>> v1=perfect_matching(odds,adj1);
        for(auto k:v1){
                adj_list[k.first].push_back({k.second,edge_count});
                adj_list[k.second].push_back({k.first,edge_count});
                edge_count++;
        }
        vector<int> tour=eulerian_circuit(nodes.size(),adj_list);
        for(int i=0;i<tour.size()-1;i++){
                if(tour[i]==-1){
                        continue;
                }
                for(int j=i+1;j<tour.size();j++){
                        if(tour[j]==tour[i]){
                                tour[j]=-1;
                        }
                }
        }
        vector<int> tour_final;
        for(int i=0;i<tour.size();i++){
                if(tour[i]!=-1){
                        tour_final.push_back(nodes[tour[i]]);
                }
        }
        return tour_final;
}
