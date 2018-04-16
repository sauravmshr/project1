#include<stdio.h>

#include<stdlib.h>

#include<strings.h>

#define MAX 50

int time;

typedef struct process

{

            int pid,AT,BT,CT,TAT,WT,RT,type;

}process;

typedef struct queue{

            int q[MAX];

            int f,r;

}queue;

 

void display(process p[],int n)

{

            int i;

            printf("Pid AT BT CT TAT WT type\n");

            for(i=0;i<n;i++)

            {

                        printf("%3d %2d %2d %2d %3d %2d %d\n",p[i].pid,p[i].AT,p[i].BT,p[i].CT,p[i].TAT,p[i].WT,p[i].type);

            }

            printf("\n");

}

 

void insert(queue *t,int ele)

{

            t->r++;

            t->q[t->r] = ele;

}

int queueFront(queue *t){

            return t->q[t->f];

}

int delete1(queue *t){

            int i=t->f;

            int z=t->q[t->f];

            while(i < t->r){

                        t->q[i] = t->q[i+1];

                        i++;

            }

            t->r--;

            return z;

}

 

void sort(process p[],int n)

{

            int i,j;

            process val;

            for(i=0;i<n-1;i++)

            {

                        val = p[i+1];

                        for(j=i;j>=0;j--)

                        {

 

 

                                    if(val.type<p[j].type)

                                                p[j+1] = p[j];

                                    else

                                                break;

                        }

                        p[j+1] = val;

            }

}

void sortAT(process p[],int n)

{

            int i,j;

            process val;

            for(i=0;i<n-1;i++)

            {

                        val = p[i+1];

                        for(j=i;j>=0;j--)

                        {

                                    if(val.AT<p[j].AT)

                                                p[j+1] = p[j];

                                    else

                                                break;

                        }

                        p[j+1] = val;

            }

}          

int fcfs(process p[],int n,int time)

{

            int i;

            for(i=0;i<n;i++)

            {

                        if(p[i].type == 1&&p[i].RT != 0)

                                    break;

            }

            if(i==n)

                        return 0;

            p[i].RT--;

            if(p[i].RT == 0)

            {

                        p[i].CT  = time+1;

                        p[i].TAT = p[i].CT - p[i].AT;

                        p[i].WT  = p[i].TAT - p[i].BT;

            }

}

void rr(process p[],queue *t,int tq,int n,int time)

{

            int i,runTime,cp;

            cp = queueFront(t);

            for(i=0;i<n;i++)

                        if(p[i].pid == cp)

                                    break;

            p[i].RT--;

            runTime = p[i].BT-p[i].RT;

            if(runTime%tq == 0 && p[i].RT != 0)

            {

                        delete1(t);

                        insert(t,cp);

            }

            if(p[i].RT == 0)

            {

                        p[i].CT  = time+1;

                        p[i].TAT = p[i].CT - p[i].AT;

                        p[i].WT  = p[i].TAT - p[i].BT;

                        delete1(t);

            }

}

float avgTAT(process p[],int n)

{

            int i;

            float avg=0;

            for(i=0;i<n;i++)

                        avg += p[i].TAT;

            avg = avg / n;

            return avg;

}

float avgWT(process p[],int n)

{

            int i;

            float avg=0;

            for(i=0;i<n;i++)

                        avg += p[i].WT;

            avg = avg / n;

            return avg;

}

void mlqueue(process p[],int n,int tq)

{

            int t,i,j,T=0,hp

            queue x;

            x.f = 0;

            x.r = -1;

            for(i=0;i<n;i++)

                        T += p[i].BT;

            sortAT(p,n);

            sort(p,n);

            for(t=0;t<T;t++)

            {

                        for(i=0;i<n;i++)

                                    if(p[i].type == 0&&p[i].AT==t)

                                                insert(&x,p[i].pid);

            for(i=0;i<n;i++)

            if(p[i].AT <= t&&p[i].RT != 0)

                break;

                        if(i==n)

                                    break;

                        switch(p[i].type)

                        {

                                    case 0 :rr(p,&x,tq,n,t);

                                                            break;

                                    case 1 :fcfs(p,n,t);

                                                            break;

                                    default:printf("Invalid Type!\n");

                                                            exit(1);

                        }

            }

}

void main()

{

            int i,n,q;

            process p[MAX];

            float avg_tat,avg_wt;

            printf("Enter no. of processes: ");

            scanf("%d",&n);

            for(i=0;i<n;i++)

            {

                        printf("Enter arrival and burst time for p%d: ",i+1);

                        scanf("%d%d",&p[i].AT,&p[i].BT);

                        printf("0->Faculty && 1-> Student\n");

                        scanf("%d",&p[i].type);

                        p[i].pid = i+1;

                        p[i].RT = p[i].BT;

            }

            printf("Enter time quantum: ");

            scanf("%d",&q);

            mlqueue(p,n,q);

            display(p,n);

            avg_tat = avgTAT(p,n);

            printf("average TAT = %.2f ms\n",avg_tat);

            avg_wt = avgWT(p,n);

            printf("average WT= %.2f ms\n",avg_wt);

}

