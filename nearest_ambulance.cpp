/*Project name : 
Team members : Gurkirat Singh

*/

/*
File input format
number of nodes
(h,a,edge wt) repeat for n nodes
.
.
.
.

*/

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>

typedef struct status
{
    int h;//this will show hospital availability at a parrticular location
    int a;;//this will show ambulance availability at a parrticular location
    int w;//this will denote edge weight
}status;

typedef struct priority_queue
{
    int node;
    int weight;
}pq;

int string_to_num(char str[])
{
    int num=0;
    for(int i=0;str[i]!='\0';i++)
    {
        num=(num*10)+(str[i]-'0');
    }
    return num;
}

int isEmpty(pq p[],int n)
{
    for(int i=0;i<n;i++)
    {
        if(p[i].node!=-1 || p[i].weight!=-1)
        return 0;
    }
    return 1;
}

pq front(pq p[],int n)
{
    //this element returns the node with min weight and also deques it at the same time
    pq temp;
    int ind=-1;
    temp.weight=INT_MAX;
    for(int i=0;i<n;i++)
    {
        if(p[i].weight<temp.weight && p[i].weight!=-1) 
        {
            temp=p[i];
            ind=i;
        }
    }
    if(ind!=-1)
    {
        p[ind].weight=-1;
        p[ind].node=-1;
    }
    return temp;
}

void dijkstra_amb_to_hosp(status **arr,int n,int src)
{
    //modified dijkstra's algo to find shortest path between hospital and the ambulance
    //the source in this case would be the current location of patient
    int distance[n];
    for(int i=0;i<n;i++)
    {
        distance[i]=772681;
    }
    pq p[100];
    for(int i=0;i<100;i++)
    {
        p[i].node=-1;
        p[i].weight=-1;
    }
    int l=0;
    distance[src]=0;
    p[l].node=src;
    p[l].weight=0;
    while (!isEmpty(p,l+1))
    {
        pq temp=front(p,l+1);
        int node=temp.node;
        int curr_dist=temp.weight;

        for(int i=0;i<n;i++)
        {
            int next_dist=curr_dist + arr[node][i].w;
            if(arr[node][i].h==1 && arr[node][i].w != 0 && next_dist<distance[i] )
            {
                distance[i]=next_dist;
                l=l+1;
                p[l].node=i;
                p[l].weight=next_dist;
            }
        }
    }

    int min_dist=772681;//this var will store the nearest distance ambulance from patient
    int hosp_loc=-1;
    for(int i=0;i<n;i++)
    {
        if(distance[i]<min_dist && distance[i]!=0)
        {
            min_dist=distance[i];
            hosp_loc=i;
        }
    }
    printf("\n\nThe nearest hospital is at location %d at a distance %d KM.",hosp_loc,min_dist);
    //assuming the speed of ambulance is 90 KM/hrs then the estimated time of arrival would be
    float time=((min_dist*1.0)/90)*60;
    printf("\nThe Ambulance will reach hospital in %f minutes.",time);
}


void dijkstra_pat_to_amb(status **arr,int n,int src)
{
    //modified dijkstra's algo to find shortest path between ambulance and the patient
    int distance[n];
    for(int i=0;i<n;i++)
    {
        distance[i]=772681;
    }
    pq p[100];
    for(int i=0;i<100;i++)
    {
        p[i].node=-1;
        p[i].weight=-1;
    }
    int l=0;
    distance[src]=0;
    p[l].node=src;
    p[l].weight=0;
    while (!isEmpty(p,l+1))
    {
        pq temp=front(p,l+1);
        int node=temp.node;
        int curr_dist=temp.weight;

        for(int i=0;i<n;i++)
        {
            int next_dist=curr_dist + arr[node][i].w;
            if(arr[node][i].a==1 && arr[node][i].w != 0 && next_dist<distance[i] )
            {
                distance[i]=next_dist;
                l=l+1;
                p[l].node=i;
                p[l].weight=next_dist;
            }
        }
    }

    int min_dist=772681;//this var will store the nearest distance ambulance from patient
    int amb_loc=-1;
    for(int i=0;i<n;i++)
    {
        if(distance[i]<min_dist && distance[i]!=0)
        {
            min_dist=distance[i];
            amb_loc=i;
        }
    }
    printf("\n\nThe nearest ambulance is at location %d at a distance %d KM.",amb_loc,min_dist);
    //assuming the speed of ambulance is 90 KM/hrs then the estimated time of arrival would be
    float time=((min_dist*1.0)/90)*60;
    printf("\nThe Ambulance will arrive in %f minutes.\n",time);
    dijkstra_amb_to_hosp(arr,n,src);
}


int main()
{
    FILE *ptr=fopen("file_input.txt","r");
    char nodes_count[4];//this will store number of nodes in the graph in string format
    fscanf(ptr,"%s",nodes_count);
    int n=string_to_num(nodes_count);//this will store number of nodes in the graph in integer format

    //here we are creating an adjacency matrix of status data type
    status **arr=(status ** )malloc((sizeof(status *)*n));

    for(int i=0;i<n;i++)
    {
        arr[i]=(status *)malloc(sizeof(status)*n);
        for(int j=0;j<n;j++)
        {
            char hosp[10];
            char amb[10];
            char wt[10];
            fscanf(ptr,"%s",hosp);
            fscanf(ptr,"%s",amb);
            fscanf(ptr,"%s",wt);
            int h=string_to_num(hosp);
            int a=string_to_num(amb);
            int w=string_to_num(wt);
            arr[i][j].h=h;
            arr[i][j].a=a;
            arr[i][j].w=w;
        }
    }

    int pat_loc;
    printf("\n\nPlease Enter patients location : ");
    scanf("%d",&pat_loc);

    for(int i=0;i<n;i++)
    {
        arr[i][pat_loc].a=0;
        arr[i][pat_loc].h=0;
    }

    dijkstra_pat_to_amb(arr,n,pat_loc);

}