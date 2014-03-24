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
	int d;
	struct node* l;
	struct node* r;
};

node* insert(node* root,int n){
	if(root==NULL){
		node* temp = (node*)malloc(sizeof(node));
		temp->d = n;
		temp->l = NULL;
		temp->r = NULL;
		return temp;
	}

	if(n < root->d)
		root->l = insert(root->l,n);

	else root->r = insert(root->r,n);	

	return root;
}

void prn(node* root){
	if(root==NULL) return;

	prn(root->l);
	cout<<root->d<<" ";
	prn(root->r);
	return;
}
//helper functions above


stack<node*> st;

void inorder(node* root){
	//st.push(root);
	node* temp = root;

	while(root)
		st.push(root),printf("pushed %d\n",root->d),root=root->l;
	node* a;

	while(!st.empty()){

		a=st.top();
		st.pop();
		printf("%d ",a->d);
		a = a->r;
		while(a)
			st.push(a),printf("pushed %d\n",a->d),a = a->r;
	}
	return ;
}

bool hasPath(node* r,int n){
	if(r==NULL){
		if(n==0)return true;
		else return false;
	}

	if(r->d > n)return false;


	return hasPath(r->l,n-r->d) || hasPath(r->r,n- r->d);


}

int main()
{
	node* r =NULL;
	int x;
	while(1){
		si(x);
		if(!x)break;
		r = insert(r,x);
	}
	inorder(r);
	int c;
	si(c);
	cout<<hasPath(r,c);
	return 0;
}

