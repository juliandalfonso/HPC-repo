#include <iostream>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <time.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <wait.h>
#include "Timer.h"

using namespace std;

double dartboardPI(int ndarts)
{
  double x, y;
  int i, count = 0;
  double z;
  double pi;
  for (i = 0; i < ndarts; i++)
  {
    x = (double)rand() / RAND_MAX;
    y = (double)rand() / RAND_MAX;
    z = x * x + y * y;
    if (z <= 1)
      count++;
  }
  pi = (double)count / ndarts * 4;
  return pi;
}

int dartboard(int ndarts)
{
  srand(getpid() * time(NULL));
  double x, y;
  int i, count = 0;
  double z;

  for (i = 0; i < ndarts; i++)
  {
    x = (double)rand() / RAND_MAX;
    y = (double)rand() / RAND_MAX;
    z = x * x + y * y;
    if (z <= 1)
      count++;
  }

  return count;
}

long double dartboardAveragePI(int niter, int ndarts)
{
  double avg = 0;
  long double pi;

  for (int i = 0; i < niter; i++)
  {
    avg += dartboard(ndarts);
  }
  pi = (long double)avg / niter / ndarts * 4;
  return pi;
}

long double call_proc(int niter, int ndarts)
{
  int shmPro = shmget(IPC_PRIVATE, 4 * sizeof(long double), IPC_CREAT | 0600);
  long double *procs = (long double *)shmat(shmPro, NULL, 0);
  for (int i = 0; i < 4; i++)
  {
    procs[i] = (long double)0;
  }
  double base_pi = 3.14159, err;
  pid_t pid = fork();
  Timer t;
  //pid_t process_1, process_2, process_3, process_4;
  if (pid)
  {
    pid_t process_1 = pid;
    //calculo de un fragmento
    //cout << "Proceso 1" << process_1 << endl;
    pid = fork();
  }
  if (pid)
  {
    pid_t process_2 = pid;
    //cout << "Proceso 2" << process_2 << endl;
    pid = fork();
  }
  if (pid)
  {
    pid_t process_3 = pid;
    //cout << "Proceso 3" << getpid() << endl;
    pid = fork();
  }
  if (pid)
  {
    pid_t process_4 = pid;
    //cout << "Proceso 4" << getpid() << endl;
  }
  if (pid == 0)
  {
    //cout << "Proceso Hijo (1)" << getpid() << endl;
    long double pi = dartboardAveragePI((int)(niter / 2), (int)(ndarts / 2));
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
    //cout << t.elapsed() << "\n";

    cout << t.elapsed() << "\t" << tavg << "\t";
    return tavg;
    //print_matriz(matrix, a.size(), b.size());
    //cout << "Finalizado correctamente" << endl;
  }
  return (long double)0;
}

int main(int argc, char **argv)
{
  int niter = stoi(argv[1]);
  int ndarts = stoi(argv[2]);
  long double avg = call_proc(niter, ndarts);
  return 0;
}