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
int rbins(int arr[],int l,int r,int k){
int m = l + (r-l)/2;
int n = r+1;
while(1){
	if(l > r) return -1;
	if(m > 0 && arr[m] >k && arr[m-1] < k)
		return m;
	if(arr[m]==k){
	while(arr[m]==k && m <n)m++;
	if(m < n)
		return arr[m];
	else return -1;
	}

	if(arr[m] > k) //middle is bigger
		r = m-1;
	else if (arr[m] < k)
		l = m+1;
	m = l + (r-l)/2;

}
}

int lbins(int arr[],int l,int r,int k){
int m = l+(r-l)/2;

while(1){
	if(l>r)break;
	if(arr[m]<k && arr[m+1]>=k)
		return arr[m];
	if(arr[m]==k){
	while(arr[m]==arr[m-1])m--;
		if(m>0)
			return arr[m-1];
		else return -1;
	}
	if(arr[m] > k)
		r = m-1;
	else if (arr[m] < k)
		l = m+1;

	m = l + (r-l)/2;
}
return -1;
}

int find(int arr[],int k,int n){
return rbins(arr,0,n-1,k);
}

int main()
{
int arr[]= {1,1,1,3,4,5,6,7,10};
int x;
while(1){
si(x);
printf("%d\n",find(arr,x,9));
}
return 0;
}

