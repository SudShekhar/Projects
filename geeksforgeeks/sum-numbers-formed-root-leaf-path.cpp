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
struct st{
	int val;
	st* left;
	st* right;
	st(int a):val(a),left(NULL),right(NULL){};
};
void levelTraversal(st* root){
	queue<st*> q;
	q.push(root);

	while(!q.empty())
	{
		st* temp = q.front();
		q.pop();
		printf("%d ",temp->val);
		if(temp->left)
			q.push(temp->left);
		if(temp->right)
			q.push(temp->right);

	}
	return;

}
st* insert(st* root,int val){
	if(root == NULL){
		st* temp = new st(val);
		return temp;
	}
	//st* oldRoot = root;
	if(root->val < val)
		root->right = insert(root->right,val);
	else root->left = insert(root->left,val);	
	return root;
}

void preorder(st* root){
	if(root==NULL)return;
	printf("%d ",root->val);
	preorder(root->left);
	preorder(root->right);
}

void inorder(st* root){
	if(root == NULL)return;
	inorder(root->left);

	printf("%d ",root->val);
	inorder(root->right);
}

st* del(st* root, int val){
	if(root==NULL)
		return root;

	if(root->val > val)
		root->left = del(root->left,val);
	else if(root->val < val)
		root->right = del(root->right,val);
	else{
		if(root->left ==NULL && root->right == NULL){
			delete(root);
			return NULL;
		}
		else if (root->left !=NULL && root->right!=NULL){
			st* temp = root->right;
			while(temp->left!=NULL)temp = temp->left;

			root->val = temp->val;
			root->right =  del(root->right,root->val);
			return root;
		}
		else{
			if(root->right){
				st* temp = root->right;
				delete root;
				return temp;
			}
			else if (root->left){
				st* temp = root->left;
				delete root;
				return temp;

			}
		}

	}
	return root;
}
int stck[100];
int top,bot;
int GANS;
void sumVal(st* root){
	if(root == NULL)return;
	if(root->left ==  NULL && root->right == NULL){
		int ans=0;
		int val = 1;
	for(int i = top-1;i>=0;i--)
		ans+= stck[i]*val,val*=10;	
	rep(i,top)printf("%d ",stck[i]);
	printf("\n--%d-\n",root->val);
		
	GANS += (10*ans + root->val);

	printf("ga %d\n",GANS);

	return;
	}
	stck[top++] = root->val;
	
	sumVal(root->left);
	sumVal(root->right);
	top--;
	
	return;
}
int main()
{
	st* root = NULL;
	int i;
	int top = 0;
	GANS = 0;
	while(1){
		scanf("%d",&i);
		if(!i)break;
		root = insert(root,i);
		//preorder(root);
	//	printf("\n");
	}
	printf("itm\n");
	while(1){
		scanf("%d",&i);
		if(!i)break;
		root = del(root,i);
	//	preorder(root);
	//	printf("\n");

	}
	//sumVal(root);
	//printf("%d\n",GANS);
	levelTraversal(root);
	return 0;
}

