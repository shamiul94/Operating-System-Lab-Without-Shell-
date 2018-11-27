#include<unistd.h>
#include<bits/stdc++.h>
#include<pthread.h>
#include<semaphore.h>

#define chocolateCake 0
#define vanillaCake 1

using namespace std ; 


queue<int> q1; 
queue<int> q2; 
queue<int> q3; 

sem_t q1_Full; 
sem_t q1_Empty;
sem_t q2_Full; 
sem_t q2_Empty; 
sem_t q3_Full; 
sem_t q3_Empty;  

pthread_mutex_t q1_lock; 
pthread_mutex_t q2_lock; 
pthread_mutex_t q3_lock; 

pthread_mutex_t printLock; 


void initSemAndMtx()
{
    sem_init(&q1_Full, 0, 0); 
    sem_init(&q1_Empty, 0, 5); 

    sem_init(&q2_Full, 0, 0); 
    sem_init(&q2_Empty, 0, 5); 

    sem_init(&q3_Full, 0, 0); 
    sem_init(&q3_Empty, 0, 5); 

    pthread_mutex_init(&q1_lock, 0); 
    pthread_mutex_init(&q2_lock, 0); 
    pthread_mutex_init(&q3_lock, 0); 

    pthread_mutex_init(&printLock, 0); 

    cout << "All semaphores and Mutexes are initiated.\n" << endl; 
}


void* chefXFunc(void* arg)
{
    pthread_mutex_lock(&printLock);
    printf("%s\n\n", (char*)arg); 
    pthread_mutex_unlock(&printLock);

    while(true)
    {
        sem_wait(&q1_Empty);

        pthread_mutex_lock(&q1_lock);

        sleep(2); 
        q1.push(chocolateCake); 

        
        queue<int> tem; 
        while(!q1.empty())
        {
            int u = q1.front(); 
            q1.pop(); 
            tem.push(u); 
        }

        pthread_mutex_lock(&printLock); 

        cout << "---------------------------------------------" << endl; 
        cout << "Chef X pushed a chocolate cake in Queue 1." << endl; 
        cout << "After pushing, Queue 1: " ; 

        while(!tem.empty())
        {
            int u = tem.front(); 
            cout << u << " " ; 
            tem.pop(); 
            q1.push(u); 
        }
        cout << endl ; 

        pthread_mutex_unlock(&printLock); 


        pthread_mutex_unlock(&q1_lock);  

        sem_post(&q1_Full); 
    }
}


void* chefYFunc(void* arg)
{
    pthread_mutex_lock(&printLock);
    printf("%s\n\n", (char*)arg); 
    pthread_mutex_unlock(&printLock);

    while(true)
    {
        sem_wait(&q1_Empty);

        pthread_mutex_lock(&q1_lock);

        sleep(2); 
        q1.push(vanillaCake); 

        
        queue<int> tem; 
        while(!q1.empty())
        {
            int u = q1.front(); 
            q1.pop(); 
            tem.push(u); 
        }

        pthread_mutex_lock(&printLock); 

        cout << "---------------------------------------------" << endl; 
        cout << "Chef Y pushed a vanilla cake in Queue 1." << endl; 
        cout << "After pushing, Queue 1: " ; 

        while(!tem.empty())
        {
            int u = tem.front(); 
            cout << u << " " ; 
            tem.pop(); 
            q1.push(u); 
        }
        cout << endl ; 

        pthread_mutex_unlock(&printLock); 


        pthread_mutex_unlock(&q1_lock);  

        sem_post(&q1_Full); 
    }
}


void* chefZFunc(void* arg)
{

}


void* waiter1Func(void* arg)
{

}


void* waiter2Func(void* arg)
{

}


int main()
{
    pthread_t chefX; 
    pthread_t chefY; 
    
    pthread_t chefZ; 

    pthread_t waiter1; 
    pthread_t waiter2; 

    initSemAndMtx(); 

    pthread_create(&chefX, NULL, chefXFunc,(void*) "Chef X started."); 
    pthread_create(&chefY, NULL, chefYFunc,(void*) "Chef Y started."); 

    pthread_create(&chefZ, NULL, chefZFunc,(void*) "Chef Z started."); 

    pthread_create(&waiter1, NULL, waiter1Func,(void*) "Waiter 1 started."); 
    pthread_create(&waiter2, NULL, waiter2Func,(void*) "Waiter 2 started."); 

    while(1);
    return 0;    
}