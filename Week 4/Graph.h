#include<bits/stdc++.h>
using namespace std;
using json=nlohmann::ordered_json;
#define INF 1000000000

class Graph{
        public:
                int n=0;
                vector<vector<int>> distance;
                Graph(json graph_json){
                        for(auto i:graph_json["nodes"]){
                                n++;
                        }
                        distance=vector<vector<int>>(n,vector<int>(n,INF));
                        for(int i=0;i<n;i++){
                                distance[i][i]=0;
                        }
                        for(auto i:graph_json["edges"]){
                                int u=i["u"],v=i["v"],w=i["w"];
                                distance[u][v]=w;
                                distance[v][u]=w;
                        }
                        for(int i=0;i<n;i++){
                                for(int j=0;j<n;j++){
                                        for(int k=0;k<n;k++){
                                                distance[i][j]=min(distance[i][j],distance[i][k]+distance[k][j]);
                                        }
                                }
                        }

};
