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
int arr[1000];
int sear(int cumm,int maxVal){
	while(



}
int read1(int idx){
	int sum=0;
	while(idx > 0)
	{
		sum+= arr[idx];
		idx-= idx&-idx;
	}
	return sum;
}

void update(int idx, int val,int maxVal){

	while(idx <= maxVal){
		arr[idx]+=val;
		idx+= idx& -idx;
	}
	return ;
}

int readOnly(int idx){
	int z = idx - (idx&-idx);
	int y = idx-1;
	int ans=arr[idx];
	
	while(y!=z){
		ans-= arr[y];
		y -= y&-y;
	}
	return ans;

}
int main()
{
	int n,x;
	si(n);
	fill(arr,0);
	rep(i,n)
		si(x),update(i+1,x,n);
	FOR(i,1,n+1)
		cout<<arr[i]<<" ";
	cout<<endl;

	while(1){
		si(x);
		cout<<"Solo "<<readOnly(x) << " cumm "<<read1(x)<<endl;
	}


	return 0;
}

