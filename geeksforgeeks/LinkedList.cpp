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

typedef vector<int> vec;
typedef vector<vec> matrix;
typedef long long LL;
#define mod 1000000007
#define max(a,b) a>b?a:b
#define min(a,b) a<b?a:b
#define sqr(x) (x*x)
struct st{
	int val;
	st* next;
	st(int v): val(v),next(NULL){};
};

class LinkedList{
private:
	st* head;
	st* pairSwap(st* head){
		if(head == NULL || head->next == NULL)
				return head;
		st* temp = head->next->next;
		st* ret = head->next;
		head->next->next = head;
		head->next = pairSwap(temp);

		return ret;
	}
st* insert(st* node,int val){
	if(node == NULL)
	{
		st* temp = (st*)malloc(sizeof(st));
		temp->next = NULL;
		temp->val = val;
		return temp;
	}
	st* old = node;
	while(node->next)node = node->next;

	node->next = insert(node->next,val);
	return old;
}

st* del(st* node , int val){
	if(node == NULL)
		return NULL;
	if(node->val == val)return node->next;
	st* old= node;
	while(node->next->val!=val)node= node->next;
	st* temp  = node->next;
	node->next = node->next->next;
	free( temp);

	return old;
}
void pr(st* node){
	while(node){
	printf("%d ",node->val);
	node = node->next;
	}

}
st* reverse(st* node){
	st *t1,*t2,*t3;
	t1 = node;
	t2 = NULL;
	//t2 = t1->next;
	while(t1){
		//t3 = t2->next; //store upcoming value
		//t2->next = t1;
		t3 = t1->next;
		t1->next = t2;
		t2 = t1;
		t1 = t3;
	
	}

	return t2;
}
	int addFromLL(st* node,st* other){
		if(node == NULL)
			return 0;

		int carry = addFromLL(node->next,other->next);
		node->val += carry + other->val;
		carry = node->val /10;
		node->val %=10;
		return carry; 
	}
	st* rotateByK(st* node,int v){
		st* temp = node;
		while(v--)
			temp = temp->next;
		//get nth node
		st* nextStart = node;
		while(temp->next)
			temp=temp->next,nextStart=nextStart->next;
		//1 2 3 4 5 , 2 ==> nextStart points at 3 now
		st* newList = nextStart->next;
		nextStart->next = NULL;
		//newList = reverse(newList);
		// got 5 4
		temp = newList;
		while(temp->next)
			temp= temp->next;
		temp->next = node;
		return newList;
	}	
st* deleteRightNodeIfHasGreaterValue(st* node){
	if(node == NULL || node->next==NULL)return node;

	 if(node->next->val > node->val){
	 	st* temp = node->next;
	 	cout<<"Deleting "<<node->val<<endl;
	 	free(node);
	 	return deleteRightNodeIfHasGreaterValue(temp);
	 }
	 else {
	 	cout<<"stored "<<node->val<<endl;
	 	node->next = deleteRightNodeIfHasGreaterValue(node->next);
	 	return node;
	 }
	}

	void detectAndRemoveLoop(st* head){
		st* node1,*node2;
		node1 = head;
		node2 = head->next;
		while(node1 && node2 && node2->next){
			node1 = node1->next;
			node2=node2->next->next;
			if(node1 == node2){
				cout<<"Looped at "<<node1->val<<endl;
				removeLoop(node1,head);
			}
		}
		return;
	}
	void removeLoop(st* node,st* head){
		st* temp = node;
		int num=1;
		while(temp->next!=node)
			temp=temp->next,num++;
		node = head;
		temp =head;
		rep(i,num)
			temp = temp->next;
		while(temp->next!=head->next)
			temp=temp->next,head=head->next;
		cout<<"presently "<<temp->val<<" points to "<<temp->next->val<<endl;
		temp->next = NULL;
	}
	public:
		void pr(){
			pr(head);
			cout<<endl;
			return;
		}
		LinkedList(){
			head = NULL;
		}
		void pairSwap(){
			head = pairSwap(head);
			pr(head);
			cout<<endl;
			return;
		}
		void insert(int v){
			head = insert(head,v);
			return;
		}
		void del(int v){
			head = del(head,v);
		}
		void reverse(){
			head = reverse(head);
		}
		void addFromLL(LinkedList *B){
			addFromLL(head,B->head);
		}
		void rotateByK(int v){
			head = rotateByK(head,v);
			pr(head);
			cout<<endl;
		}
		void deleteRightNodeIfHasGreaterValue(){
			head = deleteRightNodeIfHasGreaterValue(head);
			//cout<<head<<endl;
			pr(head);
			cout<<endl;
		}
		void createLoop(int k){
			st* temp = head;

			while(k--)temp=temp->next;
			st* pt = head;
			while(temp->next){
				pt=pt->next;
				temp=temp->next;
			}
			temp->next= pt;
		}
		void detectAndRemoveLoop(){
			detectAndRemoveLoop(head);
		}
};

int main()
{

	LinkedList A;
	rep(i,10)
		A.insert(i);
	A.createLoop(1);	

	LinkedList B;
	rep(i,5)
		B.insert(i+5);	
	A.detectAndRemoveLoop();
	A.pr();
	return 0;
}

