#include "Myclasses.h"

using namespace std;

int main(int argc,char* argv[]){

    School myschool(atoi(argv[1]),atoi(argv[2]),atoi(argv[3]),atoi(argv[4]));
    myschool.StartSimulation();
    myschool.print();

    return 0;
}