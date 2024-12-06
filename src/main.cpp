
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
#include "Settlement.h"
#include "SelectionPolicy.h"
#include"Auxiliary.h"
#include <iostream>
#include <string>
#include <fstream> 
#include <Simulation.h>
/*
   Simulation *s1 = new Simulation("config_file.txt");
   s1->to_string();
    return 0;
    

    std::cout << (s1[0].getPlan()).toString() << std::endl;
*/


int main(){
    

BalancedSelection balanced(70, 50, 60);

    std::cout << "Balanced Selection object created!" << std::endl; 

    FacilityType economyFacility1("Economy Facility 1", FacilityCategory::ECONOMY, 100, 50, 80, 40);
    FacilityType economyFacility2("Economy Facility 2", FacilityCategory::ECONOMY, 120, 60, 85, 35);

    FacilityType environmentFacility1("Environment Facility 1", FacilityCategory::ENVIRONMENT, 200, 70, 40, 90);
    FacilityType environmentFacility2("Environment Facility 2", FacilityCategory::ENVIRONMENT, 220, 75, 45, 95);

    FacilityType lifeQualityFacility1("Life Quality Facility 1", FacilityCategory::LIFE_QUALITY, 300, 90, 60, 50);
    FacilityType lifeQualityFacility2("Life Quality Facility 2", FacilityCategory::LIFE_QUALITY, 320, 95, 65, 55);

     std::vector<FacilityType> facilities = {
        economyFacility1, economyFacility2,
        environmentFacility1, environmentFacility2,
        lifeQualityFacility1, lifeQualityFacility2
    };

      
const FacilityType& chosen = balanced.selectFacility(facilities);

std::cout << chosen.toString() << std::endl;
       
}
