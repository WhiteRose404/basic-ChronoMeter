#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

int flag = 1, End = 1;
// pthread_cond_t flagviewer;
// pthread_mutex_t flagcontroler
void* run(void* time){
    int seconds = *(int *) time;
    for(int i=seconds;i>0;i--){
        while(!flag){
            sleep(1);
        }
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
        scanf("%d",&flag);
    }
}

int main(){
    pthread_t clock,event;
    int N = 3600;
    pthread_create(&clock,NULL,&run,&N);
    pthread_create(&event,NULL,&listen,NULL);
    pthread_join(clock,NULL);
    pthread_join(event,NULL);
    return 0;
}
