#include <stdio.h>
#include <stdlib.h>

typedef struct Edge{
    int so,de,w;
    struct Edge* link;
}E;

E *f=NULL,*t=NULL;

void printEdge(){
    E *temp=f;
    printf("Edge Weight\n");
    while(temp!=NULL){
        printf("%d-%d   %d\n",temp->so,temp->de,temp->w);
        temp=temp->link;
    }
}

void swap(E *t1, E *t2){
    int a,b,c;   
    a = t1->so; b = t1->de; c = t1->w;
    t1->so = t2->so;    t1->de = t2->de;   t1->w  = t2->w; 
    t2->so = a; t2->de = b; t2->w  = c;
}

void sortEdge(int e){
    int i,j;
	E *temp = f;
	for(i=0;i<e-1;i++){
        temp=f;
		while(temp->link){
			if(temp->w > temp->link->w){
				swap(temp,temp->link);
			}
			temp=temp->link;
		}
	}
}

void addEdge(int s, int d, int we){
    E *temp;
    temp = (E*)malloc(sizeof(E));
    temp->so = s;
    temp->de = d;
    temp->w = we;
    temp->link=NULL;
    if(!f){
        f = temp;
        t = temp;
    }
        else{
            t->link=temp;
            t=temp;     
        }
}

void deleteEdge(E *temp){
    E *t1,*t0,*t2;
    t1 = f;
    t2=t1->link;
    while(t1!=temp){
        t0=t1;
        t1=t2;
        t2=t2->link;
    }
    t0->link=t2;
    free(temp);
}

void solve(int **graph, int n){
    int *check;
    int i,j,edge=0;
    check = (int*)malloc(n*sizeof(int));
    for(i=0;i<n;i++){check[i]=1;}
    E *temp = f;
    while(temp){
        i=temp->so;
        j=temp->de;
        if(check[i]==1&&check[j]==1){
            check[i]=0;
            check[j]=0;
            edge++;
        }  
        else if(check[i]==0&&check[j]==1){
                check[j]=0;
                edge++;
        }

        else if(check[i]==1&&check[j]==0){
                check[i]=0;
                edge++;
        }    
        else{
            deleteEdge(temp);
        }
        temp=temp->link;
    }
}
    

int main(){
    int **graph;
    int n,e,j,i;
    e=0;
    printf("Enter no.of vertices:");scanf("%d",&n);
    graph = (int**)malloc(n*sizeof(int*));
    for(i=0;i<n;i++){graph[i] = (int*)malloc(n*sizeof(int));}
  
    printf("Enter the adjacency matrix:-\n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            scanf("%d",&graph[i][j]);
            if(graph[i][j]!=0){e++;}
        }
    }
    e/=2;
     for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(graph[i][j]!=0){
                addEdge(i,j,graph[i][j]);
                graph[j][i]=0;
            }
        }
    }
    sortEdge(e);
    solve(graph,n);
    printf("\nMST of given graph:\n");
    printEdge();
    return 0;
}