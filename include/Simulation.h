#pragma once
#include <string>
#include <vector>
#include "Facility.h"
#include "Plan.h"
#include "Settlement.h"
using std::string;
using std::vector;

class BaseAction;
class SelectionPolicy;

class Simulation {
    public:
        Simulation(const string &configFilePath); // e
        void start();
        void addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy); 
        void addAction(BaseAction *action);
        bool addSettlement(Settlement *settlement); // yes
        bool addFacility(FacilityType facility); // yes
        bool isSettlementExists(const string &settlementName); // yes
        Settlement &getSettlement(const string &settlementName); // yes
        Plan &getPlan(const int planID); // problem
        void step();
        void close();
        void open();

        void to_string();

    private:
        bool isRunning;
        int planCounter; //For assigning unique plan IDs
        vector<BaseAction*> actionsLog;
        vector<Plan> plans;
        vector<Settlement*> settlements;
        vector<FacilityType> facilitiesOptions;
};
