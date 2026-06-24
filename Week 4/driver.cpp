#include<bits/stdc++.h>
#include"json.hpp"
#include<chrono>
#include"Graph.h"
#define INF 1000000000
using namespace std;
using namespace std::chrono;
using json=nlohmann::ordered_json;

void TSPBruteForce(vector<vector<int>> &distance,vector<int> &nodes,vector<bool> visited,int left,vector<int> path,int cost,vector<int> &pathm,int &costm){
        if(left==0){
                if(cost+distance[path[path.size()-1]][path[0]]<costm){
                        pathm=path;
                        pathm.push_back(path[0]);
                        costm=cost+distance[path[path.size()-1]][path[0]];
                }
                return;
        }
        for(int i=0;i<nodes.size();i++){
                if(!visited[i]){
                        visited[i]=true;
                        path.push_back(nodes[i]);
                        int x=0;
                        if(left!=nodes.size()){
                                x=distance[path[path.size()-2]][path[path.size()-1]];
                        }
                        if(cost+x>costm){
                                path.pop_back();
                                visited[i]=false;
                                continue;
                        }
                        TSPBruteForce(distance,nodes,visited,left-1,path,cost+x,pathm,costm);
                        path.pop_back();
                        visited[i]=false;
                }
        }
        return;
}

void TSPOptimized(vector<vector<int>> &distance,vector<int> &nodes,vector<int> &tour,int &costm){
        int n=nodes.size();
        if(n==0){
                tour.clear();
                costm=0;
                return;
        }
        if(n==1){
                tour={nodes[0],nodes[0]};
                costm=0;
                return;
        }
        int total=1<<n;
        vector<vector<int>> dp(total,vector<int>(n,INF));
        vector<vector<int>> parent(total,vector<int>(n,-1));
        dp[1][0]=0;
        for(int mask=1;mask<total;mask++){
                for(int last=0;last<n;last++){
                        if(!(mask&(1<<last))) continue;
                        if(dp[mask][last]==INF) continue;
                        for(int next=0;next<n;next++){
                                if(mask&(1<<next)) continue;
                                int newmask=mask|(1<<next);
                                int cost=dp[mask][last]+distance[nodes[last]][nodes[next]];
                                if(cost<dp[newmask][next]){
                                        dp[newmask][next]=cost;
                                        parent[newmask][next]=last;
                                }
                        }
                }
        }
        int full=total-1;
        int lastnode=-1;
        costm=INF;
        for(int last=1;last<n;last++){
                int cost=dp[full][last]+distance[nodes[last]][nodes[0]];
                if(cost<costm){
                        costm=cost;
                        lastnode=last;
                }
        }
        tour.clear();
        int mask=full;
        int curr=lastnode;
        while(curr!=-1){
                tour.push_back(nodes[curr]);
                int prev=parent[mask][curr];
                mask=mask^(1<<curr);
                curr=prev;
        }
        reverse(tour.begin(),tour.end());
        tour.push_back(nodes[0]);
}

int main(int argc, char* argv[]){

    if (argc < 4) {
        std::cerr << "Usage: ./{executable} <graph.json> <queries.json> <output.json>\n";
        return 1;
    }

    std::string graph_json_file = argv[1];
    std::string query_json_file = argv[2];
    std::string output_file = argv[3];

    std::ifstream file1(graph_json_file);

    if (!file1.is_open()) {
        std::cerr << "Error: Could not open " << graph_json_file << '\n';
        return 1;
    }

    nlohmann::json graph_json;
    file1 >> graph_json;
    Graph map(graph_json);

    std::ifstream file2(query_json_file);

    if (!file2.is_open()) {
        std::cerr << "Error: Could not open " << query_json_file << '\n';
        return 1;
    }

    json query_json;
    file2 >> query_json;

    json output_json;

    output_json["meta"] = {{"id", query_json["meta"]["id"]}};
    output_json["results"] = nlohmann::json::array();

    std::string type;

    for(auto event : query_json["events"]){
        type = event["type"];
        if(type=="tsp"){
                json result;
                result["id"]=event["id"];
                vector<int> nodes;
                for(auto i:event["nodes"]){
                        nodes.push_back(i);
                }
                vector<int> tour,path;
                path.push_back(0);
                int cost=0;
                int costm=INF;
                vector<bool> visited(nodes.size(),false);
                visited[0]=true;
                TSPBruteForce(map.distance,nodes,visited,nodes.size()-1,path,cost,tour,costm);
                result["brute_force"]["optimal_cost"]=costm;
                result["brute_force"]["tour"]=tour;
                vector<int>tour1;
                costm=INF;
                TSPOptimized(map.distance,nodes,tour1,costm);
                result["held_karp"]["optimal_cost"]=costm;
                result["held_karp"]["tour"]=tour1;
                output_json["results"].push_back(result);
        }
    }
    ofstream(output_file)<<output_json.dump(4);
    return 0;
}
