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
        size[a]+=size[b];
        link[b]=a;
        return;
}

bool same(int a,int b,vector<int> &link){
        return find(a,link)==find(b,link);
}

int main(){
        int n,m;cin>>n>>m;
        int x,y;
        vector<int> size(n+1,1);
        vector<int> link(n+1);
        for(int i=0;i<n;i++){
                link[i+1]=i+1;
        }
        int count=n;
        int mx=1;
        while(m--){
                cin>>x>>y;
                if(!same(x,y,link)){
                        unite(x,y,link,size);
                        mx=max(size[find(y,link)],max(mx,size[find(x,link)]));
                        count--;
                }
                cout<<count<<" "<<mx<<"\n";
        }
        return 0;
}