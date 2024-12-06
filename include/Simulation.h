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
       // Move constructor
        Simulation(Simulation &&other) noexcept;
        // Move assignment operator
        Simulation &operator=(Simulation &&other) noexcept;
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

        // making sure we have plan to return before calling the function
        bool isPlanExisting(const int planID);

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
        void executePlanCommand(const string &settlementName, const string &selectionPolicy);
        void executeSettlementCommnad(const string &name, SettlementType type);
        void executePrintPlanStatusCommnad(int plan_id);
        /////////////////
    private:
        bool isRunning;
        int planCounter; //For assigning unique plan IDs
        vector<BaseAction*> actionsLog;
        vector<Plan> plans;
        vector<Settlement*> settlements;
        vector<FacilityType> facilitiesOptions;
};
