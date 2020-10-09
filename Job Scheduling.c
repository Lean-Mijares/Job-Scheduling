#include<stdio.h>
#include<stdlib.h>

int i, t, size,*pr, maxdeadline =0, jobprofit=0, select;

typedef struct {
    int temp;
    int jobid;
    int jobdeadline;
    int jobprofit;
}job;

int point(void* a,void* b);
int sequence(job* p,int size,int maxdeadline,int* pr);

int main() {
    system("mode con: cols=70 lines=30");
    printf("\t\t\tJOB SCHEDULING WITH DEADLINE\n\n");
    printf("Enter number of jobs: ");
    scanf("%d",&size);
    job *p=(job*)calloc(size,sizeof(job));

    for(i=0;i<size;i++) {
        printf("\nEnter JobID, Deadline, and Profit for Job [%d]: ", i+1);
        scanf("%d%d%d",&p[i].jobid,&p[i].jobdeadline,&p[i].jobprofit);
        p[i].temp=i+1;
        if(p[i].jobdeadline>maxdeadline)
            maxdeadline=p[i].jobdeadline;
    }

    pr=(int*)calloc(maxdeadline,sizeof(int));
    sequence(p,size,maxdeadline,pr);

    printf("\n\nJob Sequence is: ");
    for(int i=0;i<maxdeadline;i++){
        if(pr[i])
            printf("%d ",pr[i]);
    }
    printf("\nTotal Profit is: %d\n\n",jobprofit);
    return 0;
}
int point(void* x,void* y) {
    int temp1 = ((job*)y)->jobprofit;
    int temp2 = ((job*)x)->jobprofit;
    return (temp1-temp2);
}

int sequence(job* p,int size,int maxdeadline,int* pr) {
    qsort(p,size,sizeof(job),point);

    for(i=0, t=0; i < size && t < maxdeadline; i++) {
        select=p[i].jobdeadline-1;
        while(pr[select] && select>=0)
            select--;
        if(select!=-1) {
            pr[select]=p[i].temp;
            jobprofit= jobprofit+p[i].jobprofit;
            t++;
        }
    }
    printf("\n");
    for(i=0; i<50; i++) {
        printf("=");
    }
    printf("\n|\tJOB ID\t JOB DEADLINE\tJOB PROFIT\t |\n");
    for(i=0; i<50; i++) {
        printf("=");
    }
    printf("\n");
    for(i=0; i<size; i++){
        printf("|\t %d", p[i].jobid);
        printf("\t\t%d", p[i].jobdeadline);
        printf("\t\t%d\t |\n", p[i].jobprofit);
    }
    for(i=0; i<50; i++) {
        printf("=");
    }
}
