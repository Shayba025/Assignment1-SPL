//#include "Simulation.h"
#include <iostream>
#pragma once
#include <string>
#include <vector>
using std::string;
#include "Facility.h"
using std::vector;
using namespace std;

// Simulation* backup = nullptr;

int main(int argc, char** argv){
  std::cout << "ivgy"<< endl;
   // if(argc!=2){
   //     cout << "usage: simulation <config_path>" << endl;
  //      return 0;
  //  }
    // string configurationFile = argv[1];
    // Simulation simulation(configurationFile);
    // simulation.start();
    // if(backup!=nullptr){
    // 	delete backup;
    // 	backup = nullptr;
    // }
    return 0;

}

/*
// check stuff:
int main() {
    try {
        // יצירת מתקנים לדוגמה
        vector<FacilityType> facilities = {
            FacilityType(FacilityCategory::ECONOMY, "Economy Facility A", 5, 3, 2),
            FacilityType(FacilityCategory::ENVIRONMENT, "Environment Facility B", 2, 6, 8),
            FacilityType(FacilityCategory::LIFE_QUALITY, "Life Quality Facility C", 7, 4, 5),
            FacilityType(FacilityCategory::ECONOMY, "Economy Facility D", 3, 2, 1)
        };

        // יצירת Selection Policies
        NaiveSelection naiveSelection;
        BalancedSelection balancedSelection(10, 15, 20);
        EconomySelection economySelection;
        SustainabilitySelection sustainabilitySelection;

        // בדיקת Naive Selection
        cout << "=== Testing NaiveSelection ===" << endl;
        for (size_t i = 0; i < facilities.size(); ++i) {
            const FacilityType& facility = naiveSelection.selectFacility(facilities);
            cout << "Selected facility: " << facility.getName() << endl;
        }

        // בדיקת Balanced Selection
        cout << "\n=== Testing BalancedSelection ===" << endl;
        const FacilityType& balancedFacility = balancedSelection.selectFacility(facilities);
        cout << "Selected facility: " << balancedFacility.getName() << endl;

        // בדיקת Economy Selection
        cout << "\n=== Testing EconomySelection ===" << endl;
        const FacilityType& economyFacility = economySelection.selectFacility(facilities);
        cout << "Selected facility: " << economyFacility.getName() << endl;

        // בדיקת Sustainability Selection
        cout << "\n=== Testing SustainabilitySelection ===" << endl;
        const FacilityType& sustainabilityFacility = sustainabilitySelection.selectFacility(facilities);
        cout << "Selected facility: " << sustainabilityFacility.getName() << endl;

        // בדיקת מקרי קצה
        cout << "\n=== Testing Edge Cases ===" << endl;

        // מקרה 1: וקטור ריק
        vector<FacilityType> emptyFacilities;
        try {
            naiveSelection.selectFacility(emptyFacilities);
        } catch (const invalid_argument& e) {
            cout << "Caught exception for empty facilities: " << e.what() << endl;
        }

        // מקרה 2: קטגוריה שאינה קיימת
        vector<FacilityType> noEconomyFacilities = {
            FacilityType(FacilityCategory::ENVIRONMENT, "Environment Facility B", 2, 6, 8)
        };
        try {
            economySelection.selectFacility(noEconomyFacilities);
        } catch (const runtime_error& e) {
            cout << "Caught exception for missing category: " << e.what() << endl;
        }

    } catch (const exception& e) {
        cout << "An unexpected error occurred: " << e.what() << endl;
    }

    return 0;
}
*/
//}




