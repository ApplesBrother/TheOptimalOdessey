#include <vector>
using namespace std;

double tour_cost(const vector<int>& tour,vector<vector<double>>& dist){
        double sum=0;
        for(int i=0;i<tour.size()-1;i++){
                sum+=dist[tour[i]][tour[i+1]];
        }
        sum+=dist[tour[tour.size()-1]][tour[0]];
        return sum;
}

vector<int> nearest_neighbor_tour(vector<vector<double>>& dist){
        vector<int> tour;
        vector<int> visited(dist.size(),false);
        int present=0;
        while(!visited[present]){
                tour.push_back(present);
                visited[present]=true;
                int minvertex=0;
                int mincost=1000000;
                for(int i=0;i<dist.size();i++){
                        if(i==present){
                                continue;
                        }
                        if(!visited[i]&&dist[present][i]<mincost){
                                mincost=dist[present][i];
                                minvertex=i;
                        }
                }
                present=minvertex;
        }
        tour.push_back(present);
        return tour;
}

vector<int> two_opt_neighbor(const vector<int>& current){
        vector<int> neighbor=current;
        int n=current.size();
        int i=1+rand()%(n-1);
        int j=1+rand()%(n-1);
        while(i==j){
                i=1+rand()%(n-1);
                j=1+rand()%(n-1);
        }
        if(i>j){
                int temp=j;
                j=i;i=temp;
        }
        reverse(neighbor.begin()+i,neighbor.begin()+j+1);
        return neighbor;
}

double acceptance_probability(double old_cost, double new_cost, double temperature){
        if(new_cost<old_cost){
                return 1;
        }
        return exp((old_cost-new_cost)/temperature);
}

vector<int> simulated_annealing(vector<vector<double>>& dist,double initial_temp = 10000.0,double cooling_rate = 0.965,double min_temp = 1e-6,int iters_per_temp = 200){
        vector<int> current=nearest_neighbor_tour(dist);
        vector<int> best=current;
        double T=initial_temp;
        mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
        uniform_real_distribution<double> prob(0.0, 1.0);
        while(T>min_temp){
                for(int i=0;i<iters_per_temp;i++){
                        vector<int> neighbor=two_opt_neighbor(current);
                        if(acceptance_probability(tour_cost(current,dist),tour_cost(neighbor,dist),T)>prob(rng)){
                                current=neighbor;
                        }
                }
                T*=cooling_rate;
        }
        return current;
}
