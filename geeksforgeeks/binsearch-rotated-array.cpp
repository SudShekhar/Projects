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
int bins(int * arr, int n,int k){
int l = 0;
int r = n-1;
int m = (l+r)/2;
	while(arr[m]!=k){
	if(l > r)return -1;
	if((arr[m-1] < k && arr[l]<k) || (arr[m-1]>k &&arr[l]>k)|| arr[m-1]<k && arr[l]>k){
	//vallue is bigger
	l = m+1;
	}
	else{
	r = m-1;
	}
	//value is smaller
	m = (l+r)/2;
	}
	return m;
}

int main()
{
int arr[100];
int n;
si(n);
rep(i,n)si(arr[i]);
int x;
while(1)
{
	si(x);
	printf("%d\n",bins(arr,n,x));
}
return 0;
}

