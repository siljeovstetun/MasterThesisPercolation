#include <iostream>
#include <cmath>
#include <omp.h>

#include "people.h"

using namespace std;



void infect(People *people, int N, int it, double p, double *x, double *y, int *condition, int step)
{

  double quarantine;
  double infected;
  double random;
  int person;

  for(int i=0; i<N; i++)
  {
    if(people[i].getCondition() == 1)
    {
      if((it - people[i].getTime()) > 2000)
      {
        people[i].setCondition(2, 0);
      }
      else
      {
        for(int j=0; j<4; j++)
        {
          random = (double)rand()/RAND_MAX;
          if(random < p && people[people[i].getNeighbours(j)].getCondition() == 0)
          {
            people[people[i].getNeighbours(j)].setCondition(1, it);
            people[i].setNumberOfInfected();
          }
        }
      }

    }
  }
  /*if(it%step == 0)
  {
    for(int k=0; k<N; k++)
    {
      x[(int) (it * N/step) + k] = people[k].getxPosition();
      y[(int) (it * N/step) + k] = people[k].getyPosition();
      condition[(int) (it * N/step) + k] = people[k].getCondition();
    }
  }*/

}
