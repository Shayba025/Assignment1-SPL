#include <iostream>
#include <fstream>
#include <string>
#include "Simulation.h"
# include "Action.h"
# include "Auxiliary.h"
# include "Facility.h"
# include "Plan.h"
# include "SelectionPolicy.h"
# include "Settlement.h"
/*
class Simulation {
    public:
        Simulation(const string &configFilePath);
        void start();
        void addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy);
        void addAction(BaseAction *action);
        bool addSettlement(Settlement *settlement);
        bool addFacility(FacilityType facility);
        bool isSettlementExists(const string &settlementName);
        Settlement &getSettlement(const string &settlementName);
        Plan &getPlan(const int planID);
        void step();
        void close();
        void open();

    private:
        bool isRunning;
        int planCounter; //For assigning unique plan IDs
        vector<BaseAction*> actionsLog;
        vector<Plan> plans;
        vector<Settlement*> settlements;
        vector<FacilityType> facilitiesOptions;
};*/



void Simulation::HandleConfigFileRow(row){
    // spliting string via spaces
    std::stringstream ss(row);
    string word;
    boolean gotType = false;
    while (!gotType && row >> word) {
        // we check if word is settlement or facility or plan
        // yes we cahnge to got type and we call the function that adds it to the vector
        if word = 
    }
}


//Simulation builder:
Simulation::Simulation(const string &configFilePath)

 :isRunning(false), planCounter(0), 
    actionsLog(),
    plans(),
    settlements(),
    facilitiesOptions()
 
 
 
 {
    // opening the file
    // we try 3 times if the file won't open it's a problem with the file
    //check with ido
    std::ifstream configfile (configFilePath);

    string row; // initiallating the string that will hold the text row by row.

    //Read each line of the file
    while(getline(configfile, row)){
        HandleConfigFileRow(row);

    }
    configfile.close();
 }




//start method
void Simulation::start(){
    isRunning =true; 
    string input ="";
   std:: cout << "Simulation has started!" << std::endl;

   while (isRunning){
    getline(std::cin, input);
    std:: cout << "type an action or 'stop' to finish the simulation" << std::endl;
    if(input == "stop"){
        isRunning = false;
        std:: cout << "Simulation has finished" << std::endl;
    }


   }
   
}