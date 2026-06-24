#include<bits/tdc++.h>
#include"json.hpp"
#include<chrono>
#include"Graph.h"
#define INF 1000000000
using namespace std;
using namespace std::chrono;
using json=nlohmann::ordered_json;

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
        if(type=="find_path"){
                string b[]={"dijkstra","astar_euclidean","astar_manhattan"};
                json result;
                result["id"]=event["id"];
                const int start=int(event["start"]["y"])*map.m+int(event["start"]["x"]);
                const int stop=int(event["goal"]["y"])*map.m+int(event["goal"]["x"]);
                vector<vector<float>>  h(3,vector<float>(map.m*map.n,0));
                int ms=int(event["start"]["x"]),ns=int(event["start"]["y"]);
                int me=int(event["goal"]["x"]),ne=int(event["goal"]["y"]);
                for(int i=0;i<map.m*map.n;i++){
                        int m=i%map.m,n=i/map.m;
                        h[1][i]=sqrt((m-me)*(m-me)+(n-ne)*(n-ne));
                        h[2][i]=abs(m-me)+abs(n-ne);
                }
                for(int i=0;i<3;i++){
                        auto begin=high_resolution_clock::now();
                        vector<bool> complete(map.m*map.n,false);
                        vector<float> distance(map.m*map.n,INF);
                        priority_queue<pair<float,int>> q;
                        vector<Node> parent(map.m*map.n);
                        distance[start]=0;
                        int count=0;
                        int len=0;
                        q.push({0,start});
                        while(!q.empty()){
                                Node s=q.top().second;
                                q.pop();
                                if(complete[s.pos]){
                                        continue;
                                }
                                for(auto k:map.get_neighbors(s)){
                                        if(complete[k.pos]){
                                                continue;
                                        }
                                        if(distance[k.pos]>distance[s.pos]+1){
                                                distance[k.pos]=distance[s.pos]+1;
                                                q.push({-distance[k.pos]-h[i][k.pos],k.pos});
                                                parent[k.pos]=s;
                                        }
                                }
                                complete[s.pos]=true;
                                count++;
                                if(s.pos==stop){
                                        break;
                                }
                        }
                        if(complete[stop]){
                                int s=stop;
                                while(s!=start){
                                        len++;
                                        s=parent[s].pos;
                                }
                                auto end=high_resolution_clock::now();
                                auto t=duration<double,milli>(end-begin);
                                result[b[i]]={{"path_found",true},{"path_length",len},{"nodes_explored",count},{"time_ms",t.count()}};
                                continue;
                        }
                        result[b[i]]={{"path_found",false}};
                }
                output_json["results"].push_back(result);
        }
    }
    ofstream(output_file)<<output_json.dump(4);
    return 0;
}
