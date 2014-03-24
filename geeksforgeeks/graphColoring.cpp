// Standard includes
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<limits.h>
#include<string.h>

//Data Structures
#include<algorithm>
#include<list>
#include<vector>
#include<string>
#include<set>
#include<map>
#include<utility>
#include<stack>
#include<queue>
using namespace std;

#define FOR(i,a,b) for(int i= (int )a ; i < (int )b ; ++i)
#define rep(i,n) FOR(i,0,n)
#define INF INT_MAX
#define all(x) x.begin(),x.end()
#define LET(x,a) __typeof(a) x(a)
#define IFOR(i,a,b) for(LET(i,a);i!=(b);++i)
#define EACH(it,v) IFOR(it,v.begin(),v.end())
#define pb push_back
#define sz(x) int(x.size())
#define mp make_pair
#define fill(x,v) memset(x,v,sizeof(x))
#define si(n) scanf("%d",&n)
#define pi(n) printf("%d ",n)
#define pil(n) printf("%d\n",n)
#define sl(n) scanf("%lld",&n)
#define sd(n) scanf("%lf",&n)
#define ss(n) scanf("%s",n)

typedef pair<int,int> pr;
typedef vector<int> vec;
typedef vector<vec> matrix;
typedef long long LL;
#define mod 1000000007
#define max(a,b) a>b?a:b
#define min(a,b) a<b?a:b
#define sqr(x) (x*x)
class Graph{
	public:
		int V;
		list<int> *adj;
	Graph(int v){
		v=V;
		adj = new list<int>[V];
	}	
	void addEdge(int u,int v)
	{
		adj[v].push_back(u);
		adj[u].pb(v);
	}
	void printGraph(){
	rep(i,V){
		EACH(it,adj[i])
			cout<<i<<"<-> "<<*it<<endl;
	
	}
	}

	void colorGraph(){
	vector<bool> result(V,false);
	int col=0;
	rep(i,V){
	vector<bool> alloted(V,false);

	EACH(it,adj[i])
	{
		if(result[*it]!=false)
			alloted[*it]=true;
	}
	rep(k,V+1)
		{
			//break;
		result[i]=k;break;
		}
	}
	cout<<"colors ";
	rep(i,V)
		cout<<result[i]<<" ";
	cout<<endl;
	}
	
};

int main()
{
Graph g(3);
g.addEdge(1,2);
g.printGraph();
//g.colorGraph();
return 0;
}

