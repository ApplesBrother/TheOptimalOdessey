#include<bits/stdc++.h>
using namespace std;

int main(){
        int n,m;cin>>n>>m;
        char space[m*n];
        vector<int> adjacency[m*n];
        int start,stop;
        for(int i=0;i<n;i++){
                for(int j=0;j<m;j++){
                        cin>>space[i*m+j];
                        if(space[i*m+j]=='A'){
                                start=i*m+j;
                                space[i*m+j]='.';
                        }
                        if(space[i*m+j]=='B'){
                                stop=i*m+j;
                                space[i*m+j]='.';
                        }
                        if(i==0){
                                if(j!=0){
                                        if(space[i*m+j]=='.'&&space[i*m+j-1]=='.'){
                                                adjacency[i*m+j].push_back(i*m+j-1);
                                                adjacency[i*m+j-1].push_back(i*m+j);
                                        }
                                }
                        }
                        else if(i!=0){
                                if(j!=0){
                                        if(space[i*m+j]=='.'&&space[i*m+j-1]=='.'){
                                                adjacency[i*m+j].push_back(i*m+j-1);
                                                adjacency[i*m+j-1].push_back(i*m+j);
                                        }
                                        if(space[i*m-m+j]=='.'&&space[i*m+j]=='.'){
                                                adjacency[i*m+j].push_back(i*m-m+j);
                                                adjacency[i*m-m+j].push_back(i*m+j);
                                        }
                                }
                                else{
                                        if(space[i*m-m+j]=='.'&&space[i*m+j]=='.'){
                                                adjacency[i*m+j].push_back(i*m-m+j);
                                                adjacency[i*m-m+j].push_back(i*m+j);
                                        }
                                }
                        }
                }
        }
        queue<int> q;
        int distance[m*n];
        bool visited[m*n]={false};
        distance[start]=0;
        int parent[m*n];
        q.push(start);
        while(!q.empty()){
                int s=q.front();
                q.pop();
                for(auto k:adjacency[s]){
                        if(visited[k]){
                                continue;
                        }
                        visited[k]=true;
                        parent[k]=s;
                        distance[k]=distance[s]+1;
                        q.push(k);
                        if(k==stop){
                                while(!q.empty()){
                                        q.pop();
                                }
                                break;
                        }
                }
        }
        if(visited[stop]){
                cout<<"YES\n";
        }
        else{
                cout<<"NO\n";
                return 0;
        }
        vector<int> path;
        int i=stop;
        while(i!=start){
                path.push_back(i);
                i=parent[i];
        }
        cout<<distance[stop]<<endl;
        path.push_back(start);
        for(int i=path.size();i>0;i--){
                int y=path[i-2],x=path[i-1];
                x=y-x;
                if(x==m){
                        cout<<"D";
                }
                else if(x==-m){
                        cout<<"U";
                }
                else if(x==1){
                        cout<<"R";
                }
                else if(x==-1){
                        cout<<"L";
                }
        }
        return 0;
}