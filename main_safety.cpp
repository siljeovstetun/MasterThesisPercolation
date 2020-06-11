#include <iostream>
#include <cmath>
#include <time.h>

#include "solver.h"
#include "utilities.h"

using namespace std;



int main(){
  srand(time(NULL));
  int time = 350;
  double dt = 0.01;
  int numberOfIterations = (int) time/dt;

  int numberOfPeople = 900;
  int L = 120;
  double v0 = 0;
  int step = 10;
  double probabilitySerious = 0.;
  double probabilityInfected = 0.75/2000;
  double probabilityQuarantine = 0.;
  double infectionRadius = 4.1;

  int numberOfInfected;
  int infectionNumber;
  double *R = new double [(int) numberOfIterations/step];

  double *x = new double [(int)(numberOfPeople*numberOfIterations/step)];
  double *y = new double [(int)(numberOfPeople*numberOfIterations/step)];
  double *condition = new double [(int)(numberOfPeople*numberOfIterations/step)];
  People people[numberOfPeople];


  for(int i=0; i<numberOfPeople; i++)
  {
    people[i] = People(L, i, numberOfPeople, v0);
  }

  people[(int) numberOfPeople/2].setCondition(1, 0);
  people[(int) numberOfPeople/4].setCondition(1, 0);


  for(int i=0; i<numberOfIterations; i++)
  {
    //movePeople(people, x, y, condition, numberOfPeople, L, v0, dt, i, step, probabiliySerious,
               //probabilityInfected, infectionRadius);
      quarantine(people, x, y, condition, numberOfPeople, L, v0, dt, i, step,
                 probabilityInfected, infectionRadius, probabilityQuarantine);

    numberOfInfected = 0;
    infectionNumber = 0;
    for(int j=0; j<numberOfPeople; j++)
    {
      if(people[j].getCondition() == 1 && (i - people[j].getTime()) > 1500)
      {
        numberOfInfected ++;
        infectionNumber += people[j].getNumberOfInfected();
      }
    }

    if(i%step==0)
    {
      if(numberOfInfected == 0)
      {
        R[(int) i/step] = 0;
      }
      else
      {
        R[(int) i/step] = (double) infectionNumber/numberOfInfected;
      }
    }

  }

  int infect = 0;
  int pep = 0;
  for(int j=0; j<numberOfPeople; j++)
  {

    if(people[j].getCondition() == 2)
    {

      infect += people[j].getNumberOfInfected();
      pep++;
    }
  }
  cout <<(double) infect/pep << endl;

  writeToFileHDF5(x, y, condition, numberOfPeople, numberOfIterations, L, dt, step, R);

  return 0;
}
