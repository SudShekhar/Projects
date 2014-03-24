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
	int val,lissVal;
	struct node* left,*right;
	node(int v) :val(v),lissVal(0),left(NULL),right(NULL){};
};


class tree{
private:
node* head;
	
node* insert(node* root,int val){
	if(root == NULL)
	{
		return new node(val);
	}
	else{
	if(root->val < val)
		root->right = insert(root->right,val);
	else root->left = insert(root->left,val);
	return root;
	}
}
void serialize(node* root){
	if(root == NULL)return;
	cout<<root->val<<"(";
	serialize(root->left);
	cout<<")(";
	serialize(root->right);
	cout<<")";
	return;
}

void spiralPrint(node* root){
	stack<node*>left;
	stack <node*> right;
	left.push(root);
	node * temp;
	while(1){
		cout<<"from left ";
		while(!left.empty()){
			temp = left.top();
			left.pop();
			cout<<temp->val<< " ";
			if(temp->left)
				right.push(temp->left);
			if(temp->right)
				right.push(temp->right);
		}	
		cout<<endl;
		cout<<" from right";
		while(!right.empty()){
		temp = right.top();
		cout<<temp->val<<" ";
		right.pop();
		if(temp->right)
			left.push(temp->right);
		if(temp->left)
			left.push(temp->left);
		
		}
		cout<<endl;
		if(left.empty() && right.empty())
			break;
	}
	return;
}
void inorder(node* head){
	if(head == NULL)return;
	inorder(head->left);
	cout<<head->val<<" ";
	inorder(head->right);
	}
	
	int LCA(node* root,int a,int b){
		if(root == NULL)return 0;
		int left = LCA(root->left,a,b);
		int right = LCA(root->right,a,b);
		int sum = left + right + ((root->val == a || root->val == b) ?1:0);
		
		if(sum == 2)
				{	printf(" LCA of %d and %d is %d\n",a,b,root->val);
					return 0;
				}
		else return sum;		
	}

node* convertToDLL(node * root){
	if(root == NULL)return NULL;
	node * prev = convertToDLL(root->left);
//	while(root->left)root=root->left;
	if(prev == NULL)
		root->left = NULL;
	else {
		while(prev->right)prev=prev->right;
		prev->right = root;
		root->left = prev;
	}	
	
	node * next = convertToDLL(root->right);
	if(next == NULL)
		root->right = NULL;
	else{
		while(next->left)next = next->left;
		root->right = next;
		next->left = root;
	}	
	//while(root->right)root=root->right;
	return root;
}
	
void DeepestLeftLeaf(node *root, int depth,bool isLeft,int &ans){
		if(root->left == NULL && root->right==NULL){
			if(isLeft)
			{
				cout<<"possible "<<root->val<<endl;
				ans = max(depth,ans);
			
			}
			return;	
		}
		if(root->left){
			DeepestLeftLeaf(root->left,depth+1,true,ans);
		}
		if(root->right){
		DeepestLeftLeaf(root->right,depth+1,false,ans);
		}
		return;
	}
	
void levelOrder(node* root){
	queue<node*> q;
	node* temp;
	q.push(root);
	cout<<"levelOrder == ";
	while(!q.empty()){
		temp = q.front();
		q.pop();
		cout<<temp->val<< " ";
		if(temp->left)
			q.push(temp->left);
		if(temp->right)
			q.push(temp->right);

	}
	cout<<endl;
}	

void reverseLevelOrder(node* root){
	queue<node*> q;
	stack<node*> st;
	q.push(root);
	node* temp;
	cout<<"reverseLevelOrder == ";
	while(!q.empty()){
		temp=q.front();
		q.pop();
		st.push(temp);
		if(temp->right)
			q.push(temp->right);
		if(temp->left)
			q.push(temp->left);
	}
	while(!st.empty()){
		temp = st.top();
		cout<<temp->val<<" ";
		st.pop();	
	}
	cout<<endl;
}
node* createTreeFromSortedArray(vec v,int start,int end){
	if(start > end)return NULL;
	int mid = (start + end)/2;
	node* root = new node(v[mid]);
	root->left = createTreeFromSortedArray(v,start,mid-1);
	root->right = createTreeFromSortedArray(v,mid+1,end);
	return root;
}
int liss(node* root){
	if(root == NULL)return 0;
	if(root->lissVal!=0)
		return root->lissVal;
	int size_excl = liss(root->left) + liss(root->right);
	int size_incl = 1;
	if(root->left)
		size_incl+= liss(root->left->left) + liss(root->left->right);
	if(root->right)
		size_incl+= liss(root->right->left) + liss(root->right->right);
	root->lissVal=  max(size_incl,size_excl);
	//cout<<"Liss of "<<root->val<<" is "<<root->lissVal<<endl;
	return root->lissVal;
}
public:
tree(int v){
		head = new node(v);
		return;
	}
tree(vec v){
	int len = v.size();
	head = createTreeFromSortedArray(v,0,len-1);
	return;
}	
void insert(int v){
		head = insert(head,v);
		return;
	}
void spiralPrint(){
	spiralPrint(head);
	cout<<endl;
	}
void inorder(){
	inorder(head);
	cout<<endl;
	}
void serialize(){
	serialize(head);
	cout<<endl;
	}
void LCA(int a,int b){
	int ans = LCA(head,a,b);
	//cout<<ans<<endl;
	return;
	}
	void convertToDLL(){
	node* temp  = convertToDLL(head);
	while(temp->right)temp=temp->right;
	while(temp)
		cout<<temp->val<<" ",temp = temp->left;
	cout<<endl;	
	}
	
	void DeepestLeftLeaf(){
	int ans = 0;
	DeepestLeftLeaf(head,0,true,ans);
	cout<<ans<<endl;
	}

void levelOrder(){
	levelOrder(head);
	return;
}
void reverseLevelOrder(){
	reverseLevelOrder(head);
	return;
}

int LISS(){
	return liss(head);
}
};

int main()
{
	int arr[] = {1,2,3,4,5,6,7,8};
	vec v(arr,arr+ sizeof(arr)/sizeof(arr[0]));
	tree* B = new tree(v);
	B->spiralPrint();
	tree* A = new tree(5);
	A->insert(2);
	A->insert(3);
	A->insert(4);
	A->insert(7);
	A->insert(6);
	A->insert(8);
	A->insert(9);
	A->insert(1);
//	A->insert(5);
	A->spiralPrint();
	A->inorder();
	//A->serialize();
	A->LCA(6,10);
	//A->convertToDLL();
	A->DeepestLeftLeaf();
	A->levelOrder();
	A->reverseLevelOrder();
	cout<<A->LISS()<<endl;
return 0;
}

