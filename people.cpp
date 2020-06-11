#include <iostream>
#include <cmath>

#include "people.h"

using namespace std;

People::People(){}

People::People(int L, int i, int N, int n1, int n2, int n3, int n4)
{
  condition = 0;
  xPosition = L / ((int) sqrt(N)) * (i % (int) sqrt(N));
  yPosition = L / ((int) sqrt(N)) * (int) (i / (int) sqrt(N));
  angle = -M_PI + (double)rand()/RAND_MAX * 2 * M_PI;
  numberOfInfected = 0;
  neighbours[0] = n1;
  neighbours[1] = n2;
  neighbours[2] = n3;
  neighbours[3] = n4;
}


void People::setCondition(int cond, int time)
{
  condition = cond;

  if(cond == 1) // condition = 1 means that the person get infected
  {
    infectedTime = time;
  }
}

void People::setPosition(double x, double y, double angle){
  xPosition = x;
  yPosition = y;
  angle =  angle;
}

void People::setNumberOfInfected(){
  numberOfInfected++;
}

void People::setNeighbour(int num, int neighbour)
{
  neighbours[num] = neighbour;
}

int People::getCondition()
{
    return condition;
}

double People::getxPosition()
{
    return xPosition;
}

double People::getyPosition()
{
    return yPosition;
}

double People::getAngle()
{
    return angle;
}

int People::getTime()
{
  return infectedTime;
}

int People::getNumberOfInfected()
{
  return numberOfInfected;
}

int People::getNeighbours(int num)
{
  return neighbours[num];
}
