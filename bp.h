/** @file */ 
//!  Flow class. 
/*!
  @section Description
	This class contain various data structures and functions to store and process the given graph and find the Max Flow of the graph , also the s-t cut partition using the Ford Fulkerson Algorithm
*/
class Flow
{
    vector< int > *adjlist; /*!< *adjlist: Stores the adjacency list of the graph */
    bool *visited; /*!< *visited: Maintains the visited nodes during the first DFS call  */
    vector<int>augmented_path;/*!< augmented_path: Stores the path from Source to Sink*/
    int nodes; /*!< nodes: Stores the nodes in the graph */
    int edges;/*!< edges: Stores the edges in the graph */
    int max_flow; /*!< max_flow: Stores the result i.e.,the max flow of graph */
    map< pair<int,int> ,int> edge_flow;/*!< edge_flow : Stores the edge as key and flow through it as value {u->v}:{flow} */
    int *par;/*!< par: stores the par of each node in bfs call*/
    public:

    unordered_map< int,int > reorder; /*!< reorder: Hashes the arbitarily numbered nodes into a uniform 1-indexed nodes */
	unordered_map< int,int > rehash; /*!< rehash: Stores the reverse hashes */

    //!  The Flow class constructor 
	/*!
	@brief
		The function initializes the values of various data structures of the Flow class
	@param n An integer denoting the number of nodes in the graph
    @param e An integer denoting the number of edges in the graph
	*/
    Flow(int n,int e)
    {
        nodes = n;
        edges = e;
        max_flow = 0;
        adjlist = new vector< int >[5*n+1];
        visited = new bool[5*n+1];
        par = new int[5*n+1];
        for(int i = 0; i <= 5*n; i++)
            visited[i]=0,par[i]=-1;    
    }

    //!  addEdge function
	/*!
	@brief
		The function adds an edge from u --> v in the graph
	@param u An integer denoting the source node
	@param v An integer denoting the destination node
	*/
	void addEdge(int u,int v){
		adjlist[u].pb(v); /*!< Adds the edge from from u --> v */
        adjlist[v].pb(u);
        edge_flow[{u,v}]=1;/*!< Assigns flow to edge*/
        if(!edge_flow[{0,u}])
        adjlist[0].pb(u),adjlist[u].pb(0);
        if(!edge_flow[{v,nodes+1}])
        adjlist[nodes+1].pb(v),adjlist[v].pb(nodes+1);
        edge_flow[{0,u}]=1;
        edge_flow[{v,nodes+1}]=1;
	}

    //!  bfs_Augmented function
	/*!
	@brief
		The function finds the Augmented Path in the Residual Graph starting from source
	@param cur An integer denoting the start node of the call
	@param p An integer denoting the par of the start node
	*/
    void bfs_Augmented(int cur,int p)
    {
        visited[cur]=true;
        par[cur]=p;
        queue<int>q;
        q.push(cur);
        while(!q.empty()){
            p = q.front();
            q.pop();
            for(auto j : adjlist[p]){
                if(!visited[j] and edge_flow[{p,j}]>0)
                    q.push(j),par[j]=p,visited[j]=true;
            }
        }
    }
    //!  bfs_Augmented_edges function
    /*!
    @brief
        The function finds the edges that result maximum matchin
    @param cur An integer denoting the start node of the call
    @param p An integer denoting the par of the start node
    @param source An integer denoting the source of the graph
    @param sink An integer denonting the sink of the graph
    */
    void bfs_Augmented_edges(int cur,int p,int source,int sink)
    {
        visited[cur]=true;
        par[cur]=p;
        queue<int>q;
        q.push(cur);
        while(!q.empty()){
            p = q.front();
            q.pop();
            for(auto j : adjlist[p]){
                if(!visited[j] and edge_flow[{p,j}]==0){
                    q.push(j),par[j]=p,visited[j]=true;
                    if(p!=source and j!=sink)
                        cout<<p<<" "<<j<<endl;
                }
            }
        }
    }


    //!	 ford_fulkerson function
	/*!
	@brief
		The function implements ford-fulkerson algorithm and returns the max-flow of the graph
    @param source An integer denoting the source of the directed graph
    @param sink An integer denoting the sink of the directed graph
	*/
    int ford_fulkerson(int source,int sink)
    {

        fill(visited,visited+5*nodes+1,0);

        par[sink] = -1;

        bfs_Augmented(source,-1);

        if(par[sink]==-1)  /*!<No more Augmented path possible*/
            return 0;      

        int minflow=1e9; /*!< minflow: Stores the min flow in the augmented path */

        augmented_path.clear();

        int temp = sink; 

        augmented_path.pb(sink);

        while(par[temp]!=-1){
            temp=par[temp];
            augmented_path.pb(temp);
        }
        
        /*!<Augmented path is stored in reversed order and so reversing it to get actual order*/
        reverse(augmented_path.begin(),augmented_path.end());

        for(int var = 1; var < augmented_path.size() ;var++ ){
            minflow = min(minflow , edge_flow[{augmented_path[var-1],augmented_path[var]}]);
        }
        
        for(int var = 1; var < augmented_path.size() ;var++ ){
            edge_flow[{augmented_path[var-1],augmented_path[var]}]-=minflow;
            edge_flow[{augmented_path[var],augmented_path[var-1]}]+=minflow;
        }

        cerr<<minflow<<endl;
        return minflow + ford_fulkerson(source,sink);
    }
    //!  printSTpartition function
	/*!
	@brief
		The function prints max flow , also prints the edges in the resulting graph that give maximum matching
    @param source An integer denoting the source of the directed graph
    @param sink An integer denoting the sink of the directed graph
    */
    void printSTpartition(int source,int sink)
    {
        cerr<<"Max Flow is : "<<ford_fulkerson(source,sink)<<endl;
        fill(visited,visited+5*nodes+1,false);
        bfs_Augmented_edges(source,-1,source,sink);
        return ;
    }

};