#include<bits/stdc++.h>
using namespace std;

int main(){
        int n,m;cin>>n>>m;
        vector<int> adj[n+1];
        vector<int> count(n+1,0);
        vector<int> acount(n+1,0);
        vector<bool> visited(n+1,false);
        acount[1]=1;
        int x,y;
        while(m--){
                cin>>x>>y;
                adj[x].push_back(y);
                count[y]++;
        }
        queue<int> q;
        for(int i=1;i<=n;i++){
                if(count[i]==0){
                        q.push(i);
                }
        }
        while(!q.empty()){
                int s=q.front();
                q.pop();
                for(auto k:adj[s]){
                        count[k]--;
                        acount[k]=(acount[k]+acount[s])%1000000007;
                        if(count[k]==0){
                                q.push(k);
                        }
                }
        }
        cout<<acount[n]<<endl;
        return 0;
}