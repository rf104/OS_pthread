#include <pthread.h>
#include<bits/stdc++.h>

#define n 10
#define thread_num 2

int arr[n] = {1,2,3,4,5,3,2,1,5,5};

void *routine(void *arg){
    int *index = (int*)arg;///stores a
    int sum=0;
    for(int j=0;j<n/thread_num;j++)
    {
        sum+=arr[*index + j] ;// 0+1+2+3+4+
    }
    printf("Local SUM = %d\n",sum);

    *(int*)arg = sum;

}

int main()
{
    pthread_t th[thread_num];
    for(int i=0;i<thread_num;i++){
        int *a = (int*)malloc(sizeof(int));
        *a = (n/thread_num)*i; ///i=0 then a=0 and when i = 1 then a=0+(10/2);
        if(pthread_create(&th[i],NULL,&routine, a)!=0){
        perror("Failed to create thread\n");
        }
    }

    int *res;

    for(int i=0;i<thread_num;i++){
        if(pthread_join(th[i], (void**)&res)!=0){
        perror("Failed to join thread\n");
        }

    }

}
