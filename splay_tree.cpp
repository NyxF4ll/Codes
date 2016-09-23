#include <cstdio>
#include <algorithm>
#include <cstdlib>
using namespace std;
class splaytree
{
public:
	typedef struct node{
		int v;
		node *lr[2],*p;
		void populate(node *f,int s){v=s,p=f,lr[0]=NULL,lr[1]=NULL;}
		int lorr(node *x){return (lr[0]==x)? 0 : 1;}
	};
	node *root;
	splaytree(){root=NULL;}
private:
	void rotate_l(node *x){
		node *y=x->lr[1];
		y->p=x->p;
		x->lr[1]=y->lr[0];
		y->lr[0]=x;
		x->p=y;
		if(y->p!=NULL){y->p->lr[y->p->lorr(x)]=y;}
		if(x->lr[1]!=NULL){x->lr[1]->p=x;}
	}
	void rotate_r(node *x){
		node *y=x->lr[0];
		y->p=x->p;
		x->lr[0]=y->lr[1];
		y->lr[1]=x;
		x->p=y;
		if(y->p!=NULL){y->p->lr[y->p->lorr(x)]=y;}
		if(x->lr[0]!=NULL){x->lr[0]->p=x;}
	}
	void splay(node *c){
		int t1,t2;
		node *tn2,*tn1;
		while(c!=NULL&&c->p!=NULL){
			tn1=c->p,tn2=c->p->p;
			t1=tn1->lorr(c);
			(tn2==NULL) ? t2=-1 : t2=tn2->lorr(tn1);
			if(t1==1&&t2==-1){rotate_l(tn1);}
			else if(t1==0&&t2==-1){rotate_r(tn1);}
			else if(t1==1&&t2==1){rotate_l(tn2),rotate_l(tn1);}
			else if(t1==0&&t2==1){rotate_r(tn1),rotate_l(tn2);}
			else if(t1==1&&t2==0){rotate_l(tn1),rotate_r(tn2);}
			else if(t1==0&&t2==0){rotate_r(tn2),rotate_r(tn1);}
		}
		root=c;
	}
	node* srch(node *x,node *res,int s){
		if(x==NULL)return res;
		else if(x->v==s)return x;
		else if(x->v>s)return srch(x->lr[0],x,s);
		else if(x->v<s)return srch(x->lr[1],x,s);
	}
public:
	void insert(int s){
		node *t1=srch(root,NULL,s),*t2=(node*)(malloc(sizeof(node)));
		t2->populate(t1,s);
		if(t1==NULL){root=t2;}
		else if(t1->v>s){t1->lr[0]=t2,splay(t2);}
		else if(t1->v<s){t1->lr[1]=t2,splay(t2);}
	}
	bool find(int s){
		splay(srch(root,NULL,s));
		return !(root==NULL||root->v!=s);
	}
};
splaytree sp;
int main()
{
	int n,t,m;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&t);
		sp.insert(t);
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&t);
		if(sp.find(t))
			printf("y\n");
		else
			printf("n\n");
	}
}
