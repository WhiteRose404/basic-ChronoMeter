#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

int flag = 1, End = 1;

pthread_cond_t flagviewer;
pthread_mutex_t flagcontroler;

void* run(void* time){
    int seconds = *(int *) time;
    for(int i=seconds;i>0;i--){
        pthread_mutex_lock(&flagcontroler);
        while(!flag){
            printf("Enter a non 0 value to continue :");
            fflush(NULL);
            pthread_cond_wait(&flagviewer,&flagcontroler);
        }
        pthread_mutex_unlock(&flagcontroler);
        int k = i;
        int s = k%60; k = k/60;
		int m = k%60; k = k/60;
		int h = k%60; 
 	 	printf("%02d:%02d:%02d /*-*\\\n",h,m,s);
		sleep(1);
	}
    End = 0;
	return NULL;
}


void* listen(void* empty){
    while(End){
        int flaglocal=flag;
        scanf("%d",&flaglocal);
        pthread_mutex_lock(&flagcontroler);
        flag = flaglocal;
        pthread_cond_signal(&flagviewer);
        pthread_mutex_unlock(&flagcontroler);
    }
}
int fill(){
    int in,out;
    printf("Iclock\n");
    printf("Hours: "); scanf("%d",&in); out = in*3600;
    printf("Minutes: "); scanf("%d",&in); out += in*60;
    printf("Seconds: "); scanf("%d",&in); out += in;
    return out;
}

int main(){
    pthread_t clock,event;
    int seconds = fill();
    pthread_create(&clock,NULL,&run,&seconds);
    pthread_create(&event,NULL,&listen,NULL);
    pthread_join(clock,NULL);
    return 0;
}
