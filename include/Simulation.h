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
        /////////////////////////
        //rule of 5:
        // Copy Constructor
       // Simulation::Simulation(const Simulation& other);
        // Move Constructor
       // Simulation::Simulation(Simulation&& other) noexcept
        // check if we need to add rule of 5 opertors
        ~Simulation();
        // while contructing and extracting the data from the config file we need to deteminate if we're going to build a plan, settlemet or facility and act accordinly
        // this function will check the "type" of the line object and create the right object in our code
        void createObjectBasedType(vector<string> &arguments);
        // the policy we choose is different based on the commnad line in the config file
        // this function determinate whatt policy to choose for the plan we're building
        void createPlanBasedPolicy(vector<string> &arguments);
        /////////////////////////
        void start();
        void addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy); 
        void addAction(BaseAction *action);
        bool addSettlement(Settlement *settlement); // yes
        bool addFacility(FacilityType facility); // yes
        bool isSettlementExists(const string &settlementName); // yes
        Settlement &getSettlement(const string &settlementName); // yes
        Plan &getPlan(const int planID); // yes
        void step();
        void close();
        void open(); //yes

        void to_string();
        /////////////////
        // special functions to interact with the actions:
        // cehcking if the command meets the critiria, has the correct name and gives all the right arguments
        void validateCommnad(vector<string> &commandAsvector);
        void executeStepCommand(int &numOfSteps);
        /////////////////
    private:
        bool isRunning;
        int planCounter; //For assigning unique plan IDs
        vector<BaseAction*> actionsLog;
        vector<Plan> plans;
        vector<Settlement*> settlements;
        vector<FacilityType> facilitiesOptions;
};
