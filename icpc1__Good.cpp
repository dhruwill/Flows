/*#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC optimize("unroll-loops")
*/
#include<bits/stdc++.h>
using namespace std;
#define testcase(t) int t;cin>>t;while(t--)
#define pb push_back
#define eb emplace_back
#define ll long long int
#define int long long
#define double long double
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define mod 1000000007
#define endl "\n"
#define imax INT_MAX
#define imin INT_MIN
bool sortbysec(const pair<int,int> &a,
              const pair<int,int> &b)
{
    return (a.second < b.second);
}
int nod(int n)
{
	string s = to_string(n);
	return (int)s.length();
}
int a[100];
int isit(int l,int r){
	int f=0;
	for(int i=l;i<=r;i++){
		for(int j=i;j<=r;j++)
		{
			int sum=0;
			for(int k=i;k<=j;k++)
				sum+=a[k];
			if(!sum)
				f=1;
		}
		
	}
	return 1-f;
}
vector<int>v[100000];
map< pair <int,int> , int > m; 
int max_flow;
int par[1000000];
bool vis[100000];
vector<int>aug;
void bfs(int i,int p)
{
	par[i]=p;
	vis[i]=true;
	queue<int>q;
	q.push(i);
	while(!q.empty()){
		p = q.front();
		q.pop();
		for(auto j : v[p])
			if(!vis[j] and m[{p,j}])
				q.push(j),par[j]=p,vis[j]=true;
	}
}
int ford(int s,int t)
{
	memset(vis,0,sizeof(vis));
	par[t]=-1;
	bfs(s,-1);
	if(par[t]==-1)
		return 0;
	aug.clear();
	int flow = 1e9;
	int y = t;
	aug.pb(y);
	while(par[y]!=-1)
		y=par[y],aug.pb(y);
	reverse(aug.begin(),aug.end());
	for(int i=1;i<aug.size();i++)
		flow=min(flow,m[{aug[i-1],aug[i]}]);
	for(int i=1;i<aug.size();i++)
		m[{aug[i-1],aug[i]}]-=flow,m[{aug[i],aug[i-1]}]+=flow;
	return flow+ford(s,t);
}
void printstc(int s,int n)
{
	memset(vis,0,sizeof(vis));
	bfs(s,-1);
	cout<<"Partition A: ";
	for(int i=1;i<=n;i++)
		if(vis[i])
			cout<<i<<" ";
	cout<<"\nPartition B: ";
	for(int i=1;i<=n;i++)
		if(!vis[i])
			cout<<i<<" ";
}
int32_t main()
{
	IOS
	//n==1
	testcase(t){
	int nof,nom;
	cin>>nof>>nom;
	int a,b,c;
	for(int i=0;i<nom;i++)
	{
		cin>>a>>b>>c;
		v[a].pb(b);
		v[b].pb(a);
		m[{a,b}]=c;
	}
	cout<<ford(1,nof)<<endl;
	printstc(1,nof);
	m.clear();
 }
}