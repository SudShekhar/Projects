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
//optimal strategy for a game code
int maxVal(vec arr)
{
	int len = arr.size();
	int tble[len][len];
	//memset(tble,0,sizeof(tble));
	int x,y,z;
	fill(tble,0);
	int n = len;
//rep(i,n)
	int i,j;
	rep(l,n)
	{	//cout<<arr[i]<< "- --";
		for(i =0,j = l;j<n;j++,i++)
		{
			x = i+2 <=j ? tble[i+2][j]:0;
			y = i+1 <= j-1? tble[i+1][j-1]:0;	
			z = i <= j-2? tble[i][j-2]:0;	

			tble[i][j] =  max((arr[i] + (min(x,y))), (arr[j] + (min (y,z))));
			//cout << (max(arr[i],arr[j]))<<endl;;
		}
	}
	rep(i,n)
	{
		rep(j,n)cout<<tble[i][j]<<" ";
		cout<<endl;
	}
	return tble[0][len-1];
}


int main()
{
	vec arr;
	int n;
	si(n);
	int x;
	rep(i,n)
		si(x),arr.pb(x);

	cout<<maxVal(arr)<<endl;;
	return 0;
}

