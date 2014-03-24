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
class tree{
	public:
		int val;
		struct tree* left;
		tree* right;
	public:
		tree(int val):val(val),left(NULL), right(NULL) {};

		void* insert(int v){
			if(v< val && left== NULL)
				left= new tree(v);
			else if (v>val && right==NULL)
				right = new tree(v);
			else if(v < val && left !=NULL)
				left->insert(v);
			else right->insert(v);
			//return;
		}
		void* pr(){
			if(left)left->pr();
			cout<<val<<" ";
			if(right) right->pr();
			//return;
		}

		//	void findRight(int val){
		//	queue<tree*> arr;


		//	}
};

void findRight(int v,tree* root){
	queue<tree*>arr;
	queue<int> ql;
	ql.push(0);
	arr.push(root);
	tree* node;
	int level;
	while(!arr.empty())
	{
		node = arr.front();
		arr.pop();
		level = ql.front();
		ql.pop();
		if(node->val == v)
		{
			if(!arr.empty() && ql.front() == level)
				cout<<arr.front()->val<<endl;
			else cout<<"No right node";
			return;
		}
		if(node->left)
			arr.push(node->left),ql.push(level+1);
		if(node->right)
			arr.push(node->right),ql.push(level +1);

	}
	cout<<"not found"<<endl;
	return;
}

void deepestLeftLeaf(tree* root){
	stack<tree*> arr;
	stack<int> ql;
	arr.push(root);
	ql.push(0);
	int back = 0;
	tree* node;
	int level;
	while(!arr.empty()){
		node = arr.top();
		arr.pop();
		cout<<"got "<<node->val<<endl;
		level = ql.top();;
		ql.pop();
		if(node->left == NULL && node->right == NULL){
			//could be an answer
			if(level > back)
			{
				cout<<node->val<<endl;
				//return;
			}
			//else is a right node
		}
		if(node->right)
			arr.push(node->right),ql.push(level+1);	
		if(node->left)
			arr.push(node->left),ql.push(level+1);
		back = level;
	}

	return;
}
int main()
{
	tree* root = new tree(4);
	root->left = new tree(6);
	root->left->left = new tree(5);
	root->right = new tree (7);
	root->right->right = new tree (10);
	root->right->left = new tree (9);
	root->pr();
	findRight(6,root);
	cout<<endl;
	deepestLeftLeaf(root);
	return 0;
}

