#include <iostream>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <time.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <wait.h>
#include "timer.h"

using namespace std;

long double calc(int n)
{
  srand(getpid() * time(NULL));
  double x;
  double y;
  double d;
  double P = 0;

  for (int i = 0; i < n; i++)
  {
    x = ((double)rand() / RAND_MAX) * 3.1415;
    d = ((double)rand() / RAND_MAX);
    y = 0.5 * sin(x);
    if (d <= y)
    {
      P++;
    }
  }
  return (long double)n / P;
}

int main(int argc, char **argv)
{
  int n;

  n = stoi(argv[1]);

  int shmPro = shmget(IPC_PRIVATE, 4 * sizeof(long double), IPC_CREAT | 0600);
  long double *procs = (long double *)shmat(shmPro, NULL, 0);
  for (int i = 0; i < 4; i++)
  {
    procs[i] = (long double)0;
  }
  pid_t pid = fork();
  Timer t;
  if (pid)
  {
    pid_t process_1 = pid;
    pid = fork();
  }
  if (pid)
  {
    pid_t process_2 = pid;
    pid = fork();
  }
  if (pid)
  {
    pid_t process_3 = pid;
    pid = fork();
  }
  if (pid)
  {
    pid_t process_4 = pid;
  }
  if (pid == 0)
  {
    long double pi = calc((int)(n / 4));
    //cout << pi << endl;
    for (int i = 0; i < 4; i++)
    {
      if (procs[i] == 0)
      {
        procs[i] = pi;
        break;
      }
    }
  }
  else
  {
    wait(NULL);
    wait(NULL);
    wait(NULL);
    wait(NULL);
    long double tavg = (long double)0;
    for (int i = 0; i < 4; i++)
    {
      tavg += (long double)procs[i];
    }
    tavg = (long double)tavg / 4;
    cout << t.elapsed() << "\t" << tavg << "\t";
  }
  return 0;
}