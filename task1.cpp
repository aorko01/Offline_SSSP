#include<bits/stdc++.h>
using namespace std;
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        // Use a simple hash combination technique
        return h1 ^ h2;
    }
};
int dp[101][101];

struct Compare {
    bool operator()(const pair<int,int>& a, const pair<int,int>& b) {
        return dp[a.first][a.second]>dp[b.first][b.second]; 
    }
};
class graph
{
    public:
    int v;
    vector<vector<int>> adj;
    graph(int v)
    {
        this->v=v;
        adj.resize(v+1);
    }
    void addEdge(int u,int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
};
int main()
{
    int n,m,c;
    cin>>n>>m>>c;
    graph g(n);
    unordered_map<int,int> price;
    for(int i=1;i<=n;i++)
    {
        int x;
        cin>>x;
        price[i]=x;
    }
    unordered_map<pair<int,int>,int,pair_hash> dist;
    for(int i=0;i<m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        dist[{u,v}]=w;
        dist[{v,u}]=w;
        g.addEdge(u,v);
    }
    
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=c;j++)
        {
            dp[i][j]=INT_MAX;
        }
    }
    dp[1][0]=0;
    int source,destination;
    cin>>source>>destination;
    priority_queue<pair<int,int>,vector<pair<int,int>>,Compare> pq;
    pq.push({source,0});
    while(pq.size()!=0)
    {
        pair<int,int> p=pq.top();
        pq.pop();
        int source_node_no=p.first;
        int fuel_left=p.second;
        if(p.second+1<=c)
        pq.push({p.first,p.second+1});
        for(auto dest_node_no:g.adj[p.first])
        {
            if(dist[{source_node_no,dest_node_no}]<=c)
            {
                if(fuel_left>=dist[{source_node_no,dest_node_no}])
                {
                    int present_cost=(dist[{source_node_no,dest_node_no}])*price[source_node_no];
                    if(present_cost<dp[dest_node_no][fuel_left-dist[{source_node_no,dest_node_no}]])
                    {
                        dp[dest_node_no][fuel_left-dist[{source_node_no,dest_node_no}]]=present_cost+dp[source_node_no][fuel_left];
                        pq.push({dest_node_no,fuel_left-dist[{source_node_no,dest_node_no}]});
                    }
                    // dp[dest_node_no][fuel_left-dist[{source_node_no,dest_node_no}]]=min(dp[dest_node_no][fuel_left-dist[{source_node_no,dest_node_no}]],present_cost);
                    // // pq.push({dest_node_no,fuel_left-dist[{source_node_no,dest_node_no}]});
                }
            }
        }
    }
    if(dp[destination][0]==INT_MAX)
    cout<<"impossible";
    else
    cout<<dp[destination][0];
    return 0;
}