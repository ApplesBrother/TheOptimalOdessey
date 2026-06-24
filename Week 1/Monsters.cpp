#include<bits/stdc++.h>
using namespace std;
#define INF 1000000

int main(){
        int n,m;cin>>n>>m;
        char space[m*n];
        vector<int> adjacency[m*n];
        int start;
        vector<int> monsters;
        for(int i=0;i<n;i++){
                for(int j=0;j<m;j++){
                        cin>>space[i*m+j];
                        if(space[i*m+j]=='A'){
                                start=i*m+j;
                                space[i*m+j]='.';
                        }
                        if(space[i*m+j]=='M'){
                                monsters.push_back(i*m+j);
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
        vector<int> mdistance(m*n,INF);
        vector<int> parent(m*n);
        queue<int> q;
        for(auto k:monsters){
                q.push(k);
                mdistance[k]=0;
        }
        while(!q.empty()){
                int s=q.front();
                q.pop();
                for(auto k:adjacency[s]){
                        if(mdistance[k]>mdistance[s]+1){
                                mdistance[k]=mdistance[s]+1;
                                q.push(k);
                        }
                }
        }
        vector<bool> visited(m*n,false);
        q.push(start);
        vector<int> distance(m*n,INF);
        distance[start]=0;
        while(!q.empty()){
                int s=q.front();
                q.pop();
                if(s%m==0||s%m==m-1||(s>=0&&s<m)||(s>=(n-1)*m&&s<m*n)){
                                        cout<<"YES\n";
                                        vector<char> path;
                                        while(s!=start){
                                                if(parent[s]-s==m){
                                                        path.push_back('U');
                                                }
                                                else if(parent[s]-s==-m){
                                                        path.push_back('D');
                                                }
                                                else if(parent[s]-s==1){
                                                        path.push_back('L');
                                                }
                                                else if(parent[s]-s==-1){
                                                        path.push_back('R');
                                                }
                                                s=parent[s];
                                        }
                                        cout<<path.size()<<endl;
                                        for(int i=path.size()-1;i>=0;i--){
                                                cout<<path[i];
                                        }
                                        cout<<endl;
                                        return 0;
                                }
                for(auto k:adjacency[s]){
                        if(distance[s]+1<mdistance[k]&&distance[s]+1<distance[k]){
                                distance[k]=distance[s]+1;
                                q.push(k);
                                parent[k]=s;
                        }

                }
        }
        cout<<"NO\n";
        return 0;
}

