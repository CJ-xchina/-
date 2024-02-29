#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#define SIZE 1000

// 插桩并运行程序，在程序退出前，输出存在数据竞争的全局变量（没有被同一个互斥锁保护、被多于一个线程读或写、且至少被一个线程写的全局变量）的符号名
// 在此样例中，应输出如下一行信息（字典序排序）：
// race variables: [data1, data3]

pthread_mutex_t ma, mb;
int data1 = 0, data2 = 0, data3 = 0;
pthread_t threads[SIZE];

void *__attribute__((noinline)) thread_func(void *arg)
{
  
  int x = rand();
  if ((x % 3) == 1)
    data1++;
  pthread_mutex_lock(&ma);
  if ((x % 3) == 2)
    data2++;
  pthread_mutex_unlock(&ma);
  pthread_mutex_lock((x % 3) == 0 ? &ma : &mb);
  data3++;
  pthread_mutex_unlock((x % 3) == 0 ? &ma : &mb);
  return 0;
}

int __attribute__((noinline)) main()
{
  srand(clock());
  pthread_mutex_init(&ma, 0);
  pthread_mutex_init(&mb, 0);
  pthread_mutex_lock(&ma);
  pthread_mutex_lock(&mb);
  data2 = 10;
  data3 = 10;
  pthread_mutex_unlock(&mb);
  pthread_mutex_unlock(&ma);
  for (int idx = 0; idx < SIZE; idx++)
    pthread_create(&(threads[idx]), 0, thread_func, 0);

  for (int idx = 0; idx < SIZE; idx++)
    pthread_join(threads[idx], 0);

  printf("data1:%d data2: %d data3: %d\n", data1, data2, data3);

  return 0;
}
