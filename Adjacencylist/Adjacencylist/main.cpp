#include <iostream>
#include <string>
#define MAX_VERTEX_NUM 13

typedef struct QNode
{
	int vex;
	QNode *next;
}QNode,QueuePtr;

struct LinkQueue
{
	QueuePtr *front;
	QueuePtr *rear;
	LinkQueue()
	{
		QueuePtr *p = new QueuePtr;
		this->front=this->rear=p;
		this->front->next=NULL;
	}
	void EnQueue(int v)
	{
		QueuePtr *p = new QueuePtr;
		p->vex=v;
		p->next=NULL;
		this->rear->next=p;
		this->rear=p;
	}
	int DeQueue()
	{
		if (this->front==this->rear)
		{
			return 0;
		}
		
		QueuePtr *pp=this->front->next;
		this->front->next=pp->next;
		int e = pp->vex;
		if (this->rear==pp)
		{
			this->rear=this->front;
		}
		delete pp;
		return e;
	}
	bool QueueEmpty()
	{
		if (this->front==this->rear)
		{
			return true;
		}
		return false;
	}
};

bool visited[MAX_VERTEX_NUM];
typedef struct ArcNode 
{
	int adjvex;
	ArcNode *nextarc;
}ArcNode;

typedef struct VNode 
{
	std::string data;
	ArcNode *firstarc;
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct  
{
	AdjList vertices;
	//VNode vertices[MAX_VERTEX_NUM];
	int vexnum,arcnum;
	int kind;
}ALGraph;

void DFS(ALGraph &G,int v)
{
	visited[v]=true;
	std::cout<<G.vertices[v].data<<std::endl;

	for (ArcNode *pp = G.vertices[v].firstarc;pp;pp=pp->nextarc)
	{
		if (!visited[pp->adjvex])
		{
			DFS(G,pp->adjvex);
		}
	}
}



void BFS(ALGraph &G)
{
	for (unsigned int i=0;i<G.vexnum;i++) visited[i]=false;
	LinkQueue vexQueue;

	for (unsigned int v=0;v<G.vexnum;v++)
	{

		if (!visited[v])
		{
			visited[v]=true;
			std::cout<<G.vertices[v].data<<std::endl;
			vexQueue.EnQueue(v);
			while (!vexQueue.QueueEmpty())
			{
				int u = vexQueue.DeQueue();
				for (ArcNode *pp = G.vertices[u].firstarc;pp;pp=pp->nextarc)
				{
					if (!visited[pp->adjvex])
					{
						std::cout<<G.vertices[pp->adjvex].data<<std::endl;
						visited[pp->adjvex]=true;
						vexQueue.EnQueue(pp->adjvex);
					}
				}
			}
		}
	}
}

struct ArcBox 
{
	int tailvex,headvex;
	ArcBox *tlink,*hlink;
};

struct VexNode 
{
	std::string data;
	ArcBox *firstin,*firstout;
};

struct OLGraph 
{
	VexNode xlist[4];
	int vexnum,arcnum;
};
void DFS(OLGraph &G,int v)
{
	visited[v]=true;
	for (ArcBox *pp=G.xlist[v].firstout;pp;pp=pp->tlink)
	{
		if (!visited[pp->headvex])
		{
			DFS(G,pp->headvex);
		}
	}
	std::cout<<v<<std::endl;

}
void DFSh(OLGraph &G,int v)
{
	visited[v]=true;
	for (ArcBox *pp=G.xlist[v].firstin;pp;pp=pp->hlink)
	{
		if (!visited[pp->tailvex])
		{
			DFS(G,pp->tailvex);
		}
	}
	std::cout<<v<<std::endl;

}
struct BiTNode 
{
	std::string data;
	BiTNode *lchild,*rchild;
};
void PreOderTraverse(BiTNode *T)
{
	if (T)
	{
		std::cout<<T->data;
		if (T->lchild)
		{
			PreOderTraverse(T->lchild);
		}
		if (T->rchild)
		{
			PreOderTraverse(T->rchild);
		}
	}
}
void MOrderTranverse(BiTNode *T)
{
	if (T)
	{
		MOrderTranverse(T->lchild);
		std::cout<<T->data;
		MOrderTranverse(T->rchild);
	}
}
void LOrderTranverse(BiTNode *T)
{
	if (T)
	{
		LOrderTranverse(T->lchild);
		LOrderTranverse(T->rchild);
		std::cout<<T->data;
	}
}
struct CSNode 
{
	std::string data;
	CSNode *lchild,*rsibling;
};
void DFSTree(ALGraph G,int v,CSNode **T)
{
	visited[v]=true;
	bool first = true;
	CSNode **q;
	for (ArcNode *pp = G.vertices[v].firstarc;pp;pp=pp->nextarc)
	{
		if (!visited[pp->adjvex])
		{
			CSNode *p = new CSNode;
			p->data=G.vertices[pp->adjvex].data;
			p->lchild=NULL;
			p->rsibling=NULL;
			if (first)
			{
				(*T)->lchild=p;
				q=&(p->rsibling);
				first =false;
			}
			else
			{
				*q=p;
				q=&(p->rsibling);
			}
			DFSTree(G,pp->adjvex,&p);
		}
	}
	//delete q;

}
void DFSForest(ALGraph G,CSNode **T)
{
	*T=NULL;
	CSNode **q;
	for (unsigned int v=0;v<G.vexnum;++v)
	{
		visited[v]=false;
	}
	for (unsigned int v=0;v<G.vexnum;++v)
	{
		if (!visited[v])
		{
			CSNode *p = new CSNode;
			p->data = G.vertices[v].data;
			p->lchild=NULL;
			p->rsibling=NULL;
			
			if (!(*T))
			{
				*T=p;
				q = &(p->rsibling);
			}
			else
			{
				*q = p;
				q = &(p->rsibling);
			}
			DFSTree(G,v,&p);
		}
	}
	//delete q;
}
int main()
{
	ALGraph allGraph;

	allGraph.vexnum = 13;
	allGraph.arcnum = 13;
	allGraph.kind = 0;

	allGraph.vertices[0].data="A";
	allGraph.vertices[1].data="B";
	allGraph.vertices[2].data="C";
	allGraph.vertices[3].data="D";
	allGraph.vertices[4].data="E";
	allGraph.vertices[5].data="F";
	allGraph.vertices[6].data="G";
	allGraph.vertices[7].data="H";
	allGraph.vertices[8].data="I";
	allGraph.vertices[9].data="J";
	allGraph.vertices[10].data="K";
	allGraph.vertices[11].data="L";
	allGraph.vertices[12].data="M";

	allGraph.vertices[0].firstarc = new ArcNode;
	allGraph.vertices[0].firstarc->adjvex=11;
	allGraph.vertices[0].firstarc->nextarc = new ArcNode;
	allGraph.vertices[0].firstarc->nextarc->adjvex=5;
	allGraph.vertices[0].firstarc->nextarc->nextarc=new ArcNode;
	allGraph.vertices[0].firstarc->nextarc->nextarc->adjvex=2;
	allGraph.vertices[0].firstarc->nextarc->nextarc->nextarc=new ArcNode;
	allGraph.vertices[0].firstarc->nextarc->nextarc->nextarc->adjvex=1;
	allGraph.vertices[0].firstarc->nextarc->nextarc->nextarc->nextarc=NULL;

	allGraph.vertices[1].firstarc = new ArcNode;
	allGraph.vertices[1].firstarc->adjvex = 12;
	allGraph.vertices[1].firstarc->nextarc = new ArcNode;
	allGraph.vertices[1].firstarc->nextarc->adjvex=0;
	allGraph.vertices[1].firstarc->nextarc->nextarc = NULL;

	allGraph.vertices[2].firstarc = new ArcNode;
	allGraph.vertices[2].firstarc->adjvex=0;
	allGraph.vertices[2].firstarc->nextarc=NULL;

	allGraph.vertices[3].firstarc = new ArcNode;
	allGraph.vertices[3].firstarc->adjvex=4;
	allGraph.vertices[3].firstarc->nextarc= NULL;

	allGraph.vertices[4].firstarc = new ArcNode;
	allGraph.vertices[4].firstarc->adjvex=3;
	allGraph.vertices[4].firstarc->nextarc = NULL;

	allGraph.vertices[5].firstarc = new ArcNode;
	allGraph.vertices[5].firstarc->adjvex=0;
	allGraph.vertices[5].firstarc->nextarc=NULL;

	allGraph.vertices[6].firstarc = new ArcNode;
	allGraph.vertices[6].firstarc->adjvex=10;
	allGraph.vertices[6].firstarc->nextarc=new ArcNode;
	allGraph.vertices[6].firstarc->nextarc->adjvex=8;
	allGraph.vertices[6].firstarc->nextarc->nextarc=new ArcNode;
	allGraph.vertices[6].firstarc->nextarc->nextarc->adjvex=7;
	allGraph.vertices[6].firstarc->nextarc->nextarc->nextarc=NULL;

	allGraph.vertices[7].firstarc = new ArcNode;
	allGraph.vertices[7].firstarc->adjvex=10;
	allGraph.vertices[7].firstarc->nextarc=new ArcNode;
	allGraph.vertices[7].firstarc->nextarc->adjvex=6;
	allGraph.vertices[7].firstarc->nextarc->nextarc=NULL;

	allGraph.vertices[8].firstarc = new ArcNode;
	allGraph.vertices[8].firstarc->adjvex=6;
	allGraph.vertices[8].firstarc->nextarc=NULL;

	allGraph.vertices[9].firstarc = new ArcNode;
	allGraph.vertices[9].firstarc->adjvex=12;
	allGraph.vertices[9].firstarc->nextarc=new ArcNode;
	allGraph.vertices[9].firstarc->nextarc->adjvex=11;
	allGraph.vertices[9].firstarc->nextarc->nextarc=NULL;

	allGraph.vertices[10].firstarc = new ArcNode;
	allGraph.vertices[10].firstarc->adjvex=7;
	allGraph.vertices[10].firstarc->nextarc=new ArcNode;
	allGraph.vertices[10].firstarc->nextarc->adjvex=6;
	allGraph.vertices[10].firstarc->nextarc->nextarc=NULL;

	allGraph.vertices[11].firstarc = new ArcNode;
	allGraph.vertices[11].firstarc->adjvex=12;
	allGraph.vertices[11].firstarc->nextarc=new ArcNode;
	allGraph.vertices[11].firstarc->nextarc->adjvex=9;
	allGraph.vertices[11].firstarc->nextarc->nextarc=new ArcNode;
	allGraph.vertices[11].firstarc->nextarc->nextarc->adjvex=0;
	allGraph.vertices[11].firstarc->nextarc->nextarc->nextarc=NULL;

	allGraph.vertices[12].firstarc = new ArcNode;
	allGraph.vertices[12].firstarc->adjvex=11;
	allGraph.vertices[12].firstarc->nextarc=new ArcNode;
	allGraph.vertices[12].firstarc->nextarc->adjvex=9;
	allGraph.vertices[12].firstarc->nextarc->nextarc=new ArcNode;
	allGraph.vertices[12].firstarc->nextarc->nextarc->adjvex=1;
	allGraph.vertices[12].firstarc->nextarc->nextarc->nextarc=NULL;
	for (unsigned int i=0;i<allGraph.vexnum;i++) visited[i]=false;
	for (int v=0;v<allGraph.vexnum;v++)
	{
		if(!visited[v])
		{
			DFS(allGraph,v);
		}
	}
	
	
	BFS(allGraph);
	
	OLGraph olGraph;
	olGraph.vexnum=4;
	olGraph.arcnum=7;

	for (unsigned int i=0;i<4;i++)
	{
		olGraph.xlist[i].firstin=NULL;
		olGraph.xlist[i].firstout=NULL;
	}
	int t,h;
	for (unsigned int i=0;i<olGraph.arcnum;i++)
	{
		std::cin>>t>>h;
		ArcBox *pp=new ArcBox;
		pp->tailvex=t;
		pp->headvex=h;
		pp->hlink=NULL;
		pp->tlink=NULL;
		ArcBox **po;
		po = &(olGraph.xlist[t].firstout);
		ArcBox **pi;
		pi = &(olGraph.xlist[h].firstin);
		while (true)
		{
			if (*po==NULL)
			{

				*po = pp;
				break;
			}
			else
			{
				po = &((*po)->tlink);
			}
		}
		while (true)
		{
			if (*pi==NULL)
			{
				*pi = pp;
				break;
			}
			else
			{
				pi = &((*pi)->hlink);
			}
		}
	}
	BiTNode *biTNode = new BiTNode;
	biTNode->data = "-";
	biTNode->lchild = new BiTNode;
	biTNode->lchild->data="+";
	biTNode->lchild->lchild = new BiTNode;
	biTNode->lchild->lchild->data="a";
	biTNode->lchild->lchild->lchild=NULL;
	biTNode->lchild->lchild->rchild=NULL;
	biTNode->lchild->rchild = new BiTNode;
	biTNode->lchild->rchild->data="*";
	biTNode->lchild->rchild->lchild=new BiTNode;
	biTNode->lchild->rchild->lchild->data="b";
	biTNode->lchild->rchild->lchild->lchild=NULL;
	biTNode->lchild->rchild->lchild->rchild=NULL;
	biTNode->lchild->rchild->rchild=new BiTNode;
	biTNode->lchild->rchild->rchild->data="-";
	biTNode->lchild->rchild->rchild->lchild=new BiTNode;
	biTNode->lchild->rchild->rchild->lchild->data="c";
	biTNode->lchild->rchild->rchild->lchild->lchild=NULL;
	biTNode->lchild->rchild->rchild->lchild->rchild=NULL;
	biTNode->lchild->rchild->rchild->rchild=new BiTNode;
	biTNode->lchild->rchild->rchild->rchild->data="d";
	biTNode->lchild->rchild->rchild->rchild->lchild=NULL;
	biTNode->lchild->rchild->rchild->rchild->rchild=NULL;

	biTNode->rchild=new BiTNode;
	biTNode->rchild->data="/";
	biTNode->rchild->lchild=new BiTNode;
	biTNode->rchild->lchild->data="e";
	biTNode->rchild->lchild->lchild=NULL;
	biTNode->rchild->lchild->rchild=NULL;
	biTNode->rchild->rchild=new BiTNode;
	biTNode->rchild->rchild->data="f";
	biTNode->rchild->rchild->lchild=NULL;
	biTNode->rchild->rchild->rchild=NULL;

	PreOderTraverse(biTNode);
	std::cout<<std::endl;
	MOrderTranverse(biTNode);
	std::cout<<std::endl;
	LOrderTranverse(biTNode);
	std::cout<<std::endl;
	CSNode *F = NULL;
	for (unsigned int i=0;i<olGraph.vexnum;i++) visited[i]=false;
	DFS(olGraph,0);
	for (unsigned int i=0;i<olGraph.vexnum;i++) visited[i]=false;
	DFSh(olGraph,0);
	DFSForest(allGraph,&F);
}