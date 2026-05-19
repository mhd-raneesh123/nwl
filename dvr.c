#include<stdio.h>
#define INF 999
int main()
{
        int i,j,k,n;
        int cost[10][10],distance[10][10],next[10][10];
        printf("enter the number of routers\n");
        scanf("%d",&n);
        printf("enter the cost matrix\n");
        for(i=0;i<n;i++)
        {
                for(j=0;j<n;j++)
                {
                        scanf(" %d",&cost[i][j]);
                        distance[i][j]=cost[i][j];
                        if(i==j)
                                next[i][j]=i;
                        else if(cost[i][j]!=INF)
                                next[i][j]=j;
                        else
                                next[i][j]=-1;
                }
        }
        for(k=0;k<n;k++)
        {
                for(i=0;i<n;i++)
                {
                        for(j=0;j<n;j++)
                        {
                                if(distance[i][k]+distance[k][j]<distance[i][j])
                                {
                                        distance[i][j]=distance[i][k]+distance[k][j];
                                        next[i][j]=next[i][k];
                                }
                        }
                }
        }
        for(i=0;i<n;i++)
        {
                printf("router %d\n",i);
                printf("destination\tdistance\t\tnext\t\n");
                for(j=0;j<n;j++)
                {
                        printf("%d",j);
                        if(distance[i][j]>=INF)
                                printf("\t\t-1");
                        else
                                printf("\t\t%d",distance[i][j]);
                        printf("\t\t\t%d\n",next[i][j]);
                }
        }
        printf("\nfinal cost matrix\n");
        for(i=0;i<n;i++)
        {
                printf("\t%d",i);
        }
        printf("\n----------------------\n");
        for(i=0;i<n;i++)
        {
                printf("%d  |",i);
                for(j=0;j<n;j++)
                {
                        printf("\t%d",distance[i][j]);
                }
                printf("\n");
        }
        return 0;
}