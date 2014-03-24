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
struct node{
	int data;
	struct node* left;
	struct node*right;
};
node* insert(node* root,int n)
{
	if(root==NULL){
	node* temp = (node*)malloc(sizeof(node));
	temp->left=NULL;
	temp->right=NULL;
	temp->data = n;
	return temp;
	}
	if(n < root->data)
		root->left = insert(root->left,n);
	else root->right = insert(root->right,n);

}

int height(node* root){
if(root==NULL)return 0;
int l = height(root->left);
int r = height(root->right);

return (max(l,r))+1;

}

int dia(node* root){
if(root==NULL)return 0;

int ld = dia(root->left);
int rd = dia(root->right);

int lh = height(root->left);
int rh = height(root->right);

return (max((lh+rh+1),(max(ld,rd))));

}

void prn(node* root){
if(root==NULL)return;
prn(root->left);
cout<<root->data<< " ";
prn(root->right);
return;

}

int main()
{
node* r=NULL;
int x;
while(1){
si(x);
if(x==0)break;
r=insert(r,x);
prn(r);
cout<<endl;
}
cout<<dia(r)<<endl;

return 0;
}

