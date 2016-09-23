#include <cstdio>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;
class treap
{
public:
	class treapnode{
	public:
		treapnode *lr[2],*p;
		int Priority,Value;
		treapnode(treapnode* f,int val){
			p=f,Priority=rand()%1000000007,Value=val,lr[0]=NULL,lr[1]=NULL;
		}
		int lorr(treapnode *x){return (lr[0]==x)? 0 : 1;}
	};
	treapnode *root;
	treap(){
		root=NULL;
		srand(time(NULL));
	}
	treapnode* srch(treapnode *p,treapnode *c,int s){
		if(c==NULL)return p;
		else if(s==c->Value)return c;
		else if(s<c->Value)return srch(c,c->lr[0],s);
		else if(s>c->Value)return srch(c,c->lr[1],s);
	}
	void rotate_l(treapnode *x){
		treapnode *y=x->lr[1];
		if(root==x)root=y;
		y->p=x->p;
		x->lr[1]=y->lr[0];
		y->lr[0]=x;
		x->p=y;
		if(y->p!=NULL){y->p->lr[y->p->lorr(x)]=y;}
		if(x->lr[1]!=NULL){x->lr[1]->p=x;}
	}
	void rotate_r(treapnode *x){
		treapnode *y=x->lr[0];
		if(root==x)root=y;
		y->p=x->p;
		x->lr[0]=y->lr[1];
		y->lr[1]=x;
		x->p=y;
		if(y->p!=NULL){y->p->lr[y->p->lorr(x)]=y;}
		if(x->lr[0]!=NULL){x->lr[0]->p=x;}
	}
	void siftup(treapnode *c){
		while(c->p!=NULL&&c->p->Priority<c->Priority){(c->p->lr[0]==c)? rotate_r(c->p):rotate_l(c->p);}
	}
	void insert(int s){
		treapnode *tmp=srch(NULL,root,s);
		if(tmp==NULL)root=new treapnode(tmp,s);
		else if(tmp->Value>s)tmp->lr[0]=new treapnode(tmp,s),siftup(tmp->lr[0]);
		else if(tmp->Value<s)tmp->lr[1]=new treapnode(tmp,s),siftup(tmp->lr[1]);
	}
	bool find(int s){
		treapnode *tmp=srch(NULL,root,s);
		return (tmp!=NULL&&tmp->Value==s);
	}
};
treap tp;
int main()
{
	int n,t,m;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&t);
		tp.insert(t);
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&t);
		if(tp.find(t))
			printf("y\n");
		else
			printf("n\n");
	}
}
/*
void inorder(treapnode *c)
{
	if(c==NULL)return;
	inorder(c->lr[0]);
	if(c->lr[0]!=NULL)printf("%d %d | ",c->lr[0]->Value,c->lr[0]->Priority);
	else printf("0 0 | ");
	printf("%d %d",c->Value,c->Priority);
	if(c->lr[1]!=NULL)printf(" | %d %d\n",c->lr[1]->Value,c->lr[1]->Priority);
	else printf(" | 0 0\n");
	inorder(c->lr[1]);
}
*/
