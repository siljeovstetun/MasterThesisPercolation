#include <iostream>
#include <cmath>
#include <time.h>
#include <fstream>

#include "solver.h"
#include "utilities.h"

using namespace std;


int main(){
  srand(time(NULL));
  int time = 500;
  double dt = 0.01;
  int numberOfIterations = (int) time/dt;
  int numberOfProbabilities = 101;
  int N = 30*30;
  int L = 30*4;
  double infectionRadius = 4.1;
  int step = 100;


  int numberOfInfected;
  int infectionNumber;
  int numberOfRunnings = 60;
  double *x = new double [(int) (N*numberOfIterations/step)];
  double *y = new double [(int) (N*numberOfIterations/step)];
  int *condition = new int [(int) (N*numberOfIterations/step)];


  cout << (int) (N*numberOfIterations/step) << endl;

  People people[N];
  double probabilityInfected[numberOfProbabilities] = {0};
  double infectedAfterRunningTime[numberOfProbabilities * numberOfRunnings] = {0};



  for(int i=0; i<numberOfProbabilities; i++)
  {
    probabilityInfected[i] = (double) i/(numberOfProbabilities - 1)/2000;
    //probabilityInfected[i] = 0.8/2000;
  }

  for(int middle=0; middle<numberOfRunnings; middle++)
  {
    cout << middle << endl;

    for(int prob=0; prob<numberOfProbabilities; prob++)
    {
      for(int i=0; i<N; i++)
      {
        int n1 = (i+1) % ((int) sqrt(N)) + (int) i/((int) sqrt(N)) * sqrt(N);
        int n2 = (i-1+ (int) sqrt(N)) % ((int) sqrt(N)) + (int) i/(int)sqrt(N) * sqrt(N);
        int n3 = (i + (int) sqrt(N)) % N;
        int n4 = (i - (int) sqrt(N) + N) % N;
        people[i] = People(L, i, N, n1, n2, n3, n4 );
      }
      /*for(int i=0; i<90; i++){
        int person = (double)rand()/RAND_MAX * N;
        int neighbour = (double)rand()/RAND_MAX * N;
        people[person].setNeighbour(0, neighbour);
        people[neighbour].setNeighbour(0, person);
      }*/
      people[(int) (double)rand()/RAND_MAX * N].setCondition(1, 0);
      people[(int) (double)rand()/RAND_MAX * N].setCondition(1, 0);
      //people[(int)N/2 + 15].setCondition(1,0);

      for(int i=0; i<numberOfIterations; i++)
      {
          infect(people, N, i, probabilityInfected[prob], x, y, condition, step);
      }

      int numberSubceptilbe = 0;
      for(int j=0; j<N; j++)
      {
        if(people[j].getCondition() == 0 )
        {
          numberSubceptilbe++;
        }
      }
      infectedAfterRunningTime[middle * numberOfProbabilities + prob] = 1. - ((double) numberSubceptilbe/N);

    }
  }

  ofstream outFile1("../data/infected_60.dat");
  ofstream outFile2("../data/probability_60.dat");


  for(int i = 0; i < numberOfProbabilities * numberOfRunnings; ++i) {
    outFile1 << infectedAfterRunningTime[i] << '\n';
  }

  for(int i = 0; i < numberOfProbabilities; ++i) {
    outFile2 << probabilityInfected[i] << '\n';
  }


  return 0;
}
