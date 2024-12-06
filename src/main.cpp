

/*
#include "Simulation.h"
#include <iostream>

using namespace std;

Simulation* backup = nullptr;

int main(int argc, char** argv){
    if(argc!=2){
        cout << "usage: simulation <config_path>" << endl;
        return 0;
    }
    string configurationFile = argv[1];
    Simulation simulation(configurationFile);
    simulation.start();
    if(backup!=nullptr){
    	delete backup;
    	backup = nullptr;
    }
    return 0;
}
*/

# include "Plan.h"
#include "Facility.h"
#include "Action.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
#include"Auxiliary.h"
#include <iostream>
#include <string>
#include <fstream> 
#include <Simulation.h>


int main(){

   Simulation *s1 = new Simulation("config_file.txt");
    s1->to_string();
    s1->start();

    s1->to_string();
    return 0;

}
