#include <pthread.h>

// 插桩并运行程序，在程序退出前，输出线程间共享的全局变量（被多于一个线程读或写的全局变量）的符号名
// 在此样例中，应输出如下一行信息（字典序排序）：
// shared variables: [count, data2]

pthread_mutex_t ma, mb;
int data1, data2, data3;
pthread_t t1, t2;
int count = 0;

void *__attribute__((noinline)) thread_func(void *arg)
{
  pthread_mutex_lock(&ma);
  if (count++)
    data1++;
  else
    data2++;
  pthread_mutex_unlock(&ma);

  return 0;
}

int __attribute__((noinline)) main()
{

  pthread_mutex_init(&ma, 0);
  pthread_mutex_init(&mb, 0);

  data2 = 10;
  data3 = 10;

  pthread_create(&t1, 0, thread_func, 0);
  pthread_create(&t2, 0, thread_func, 0);

  pthread_join(t1, 0);
  pthread_join(t2, 0);

  return 0;
}
