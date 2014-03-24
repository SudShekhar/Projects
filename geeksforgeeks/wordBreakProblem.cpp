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
bool inDict(string toCheck)
{
	string dict[] = {"i","am","sam","samsung","mobile","ice",
		"cream","icecream","man","go","mango"};
//	cout<<"checking "<<toCheck<<endl;
	int len = sizeof(dict)/sizeof(dict[0]);
	
	rep(i,len)
	{
		if(dict[i].compare(toCheck)==0)
		{//	cout<<"found"<<toCheck<<"\n";
			return true;
		}
	}
	return false;
}

bool wordp(string a,string result)
{
	int i,j;
	int f=0;
	int len = a.size();
	//vector<bool> wp( len, false);
	for(i=1;i<=len;i++)
	{
	vector<bool> wp( len, false);
		if(wp[i]==false && inDict(a.substr(0,i)))
			wp[i]=true;
	if(wp[i])
	{
	if(i==len){
		/*
		if(lev == 0){
			int j = 0;
			FOR(i,1,len+1)
				if(wp[i])
					cout<<a.substr(j,i-j)<<" ",j=i;
			f=1;
			cout<<endl;
		}*/
			
			//	else 	return true;
		cout << result+a<<endl;
		return true;
	
	}
	for(j=i+1;j<=len;j++)
	{
		if(wp[j]==false && wordp(a.substr(i,j-i), result+a.substr(0,i)+" "))
			wp[j]=true;
		if(wp[j]==true && j == len){
		/*if(lev == 0){/lev

			int j=0;
			FOR(i,1,len+1)
				if(wp[i])
					cout<<a.substr(j,i-j)<<" ",j=i;
			cout<<endl;
			f=1;
		///	cout<<a<<endl,f=1; 
		}
		else return true;
	*/	cout<< result + a <<endl;
			return true;
		}
		
	}
	}
	}
//	rep(i,len)cout<<wp[i]<<" - ";
//	cout<<endl;
	if(f==0)
	return false;
	else return true;
	
}

int main()
{
string a;
while(1){
cin>>a;
	if( wordp(a,""))cout<<"yes\n";
	else cout<<"no\n";
}
return 0;
}

