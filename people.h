class People
{
  public:
    int condition; // 0 = healty, 1 = sick, 2 = imune
    int infectedTime;
    double xPosition;
    double yPosition;
    double angle;
    int numberOfInfected;
    int neighbours[4];

    People();

    People(int L, int i, int N, int n1, int n2, int n3, int n4);

    void setCondition(int condition, int time);

    void setPosition(double x, double y, double angle);

    void setNumberOfInfected();

    void setNeighbour(int num, int neighbour);

    int getCondition();

    double getxPosition();

    double getyPosition();

    double getAngle();

    int getTime();

    int getNumberOfInfected();

    int getNeighbours(int num);
};
