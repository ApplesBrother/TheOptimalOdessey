#include<bits/stdc++.h>
using namespace std;

int find(int a,vector<int> &link){
        while(a!=link[a]){
                a=link[a];
        }
        return a;
}

void unite(int a,int b,vector<int> &link,vector<int> &size){
        a=find(a,link);
        b=find(b,link);
        if(size[b]>size[a]){
                int c=a;
                a=b;
                b=c;
        }
        link[b]=a;
        size[a]+=size[b];
        return;
}

bool same(int a,int b,vector<int> &link){
        return find(a,link)==find(b,link);
}

int main(){
        int n,m;cin>>n>>m;
        vector<pair<int,long long>> adjacency[n+1];
        priority_queue<tuple<long long,int,int>> q;
        int x,y;
        long long z;
        while(m--){
                cin>>x>>y>>z;
                adjacency[x].push_back({y,z});
                adjacency[y].push_back({x,z});
                q.push({-z,x,y});
        }
        vector<int> size(n+1,1);
        vector<int> link(n+1);
        for(int i=0;i<n;i++){
                link[i+1]=i+1;
        }
        int count=0;
        long long distance=0;
        while(!q.empty()&&count!=n-1){
                auto [a,b,c]=q.top();
                q.pop();
                if(!same(b,c,link)){
                        unite(b,c,link,size);
                        distance+=a;
                        count++;
                }
        }
        if(count!=n-1){
                cout<<"IMPOSSIBLE\n";
                return 0;
        }
        cout<<-distance<<endl;
        return 0;
}
