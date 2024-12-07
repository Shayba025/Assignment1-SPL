#include "Simulation.h"
#include <fstream> 
#include "Auxiliary.h"
#include "Settlement.h"
#include "Facility.h"
#include "SelectionPolicy.h"
#include "Plan.h"
#include <cinttypes>
#include "Action.h"

Simulation::Simulation(const string &configFilePath)
  : isRunning(false),
    planCounter(0),
    actionsLog(),
    plans(),
    settlements(),
    facilitiesOptions()
{
    // reading the config file
    std::ifstream configfile(configFilePath);
    string line;
    while (std::getline(configfile, line)) {
        // spliting the text into lines
        vector<string> arguments = Auxiliary::parseArguments(line);
        // if the line is not empty meaning there is a text there
        if(arguments.size() > 0){
            createObjectBasedType(arguments);
        }
}
    configfile.close();
}

// dustructor
Simulation::~Simulation() {
    // delete all action logs
    for (auto action : actionsLog) {
        delete action; 
        action = nullptr;
    }
    // delete all settlement
    for (auto settlement : settlements) {
        delete settlement; 
        settlement = nullptr;
    }
    this->actionsLog.clear();
    this->settlements.clear();
    this->plans.clear();
    this->facilitiesOptions.clear();

}


//move constractor
Simulation::Simulation(Simulation &&other) noexcept
:isRunning(other.isRunning),planCounter(other.planCounter),actionsLog(std::move(other.actionsLog)),
plans(std::move(other.plans)),settlements(std::move(other.settlements)), facilitiesOptions(std::move(other.facilitiesOptions)){
    other.planCounter = 0;
    other.isRunning = false;
}


// move assignment operator
Simulation& Simulation::operator=(Simulation &&other) noexcept{
    
    if(this != &other){ //checking if the current simulation is the same as being copied
        //deletions
        for(auto *settlement : settlements){
            delete settlement;
        }
        for(auto *action : actionsLog){
            delete action;
        }
        actionsLog.clear();
        settlements.clear();
        //coping the values
        isRunning = other.isRunning;
        planCounter = other.planCounter;
        actionsLog = std::move(other.actionsLog);
        plans = std::move(other.plans);
        settlements = std::move(other.settlements);
        facilitiesOptions = std::move(other.facilitiesOptions);


        other.isRunning = false;
        other.planCounter = 0;
    }
return *this;
}




// helpr function for constructor - creating the object based the specific type from argument
void Simulation::createObjectBasedType(vector<string> &arguments){
        // the arguments[0] is the type of the object we want to create
        // creating settlement
        if(arguments[0] == "settlement")
        {
            // we need to modify the text into the enum for settlement variable
            SettlementType typeAsInt = static_cast<SettlementType>(std::stoi(arguments[2]));

            // in the method of simmulation we create the object on the heap and only reatrun to the vctor it's pointer
            Settlement *newSettlement = new Settlement(arguments[1],typeAsInt);
            addSettlement(newSettlement);
        }
        
        //creating facility
        else if(arguments[0] == "facility"){
            // we create a new facilityOption
            // we declate new facility while converting the text variables to the type the constructor ueses
            FacilityType *newFacility = new FacilityType(arguments[1], static_cast<FacilityCategory>(std::stoi(arguments[2])) ,std::stoi(arguments[3]),std::stoi(arguments[4]),std::stoi(arguments[5]),std::stoi(arguments[6]));
            addFacility(*newFacility);
            // we're not adding a pointer but the object itself so we delete the object we created to avoide memory leak
            delete(newFacility);
            newFacility = nullptr;

        }
        // creating Plan
        else if(arguments[0] == "plan"){
            // creating the plan based on the selection policy
            // if the settelement doensn't exists we can't do anything
            if(isSettlementExists(arguments[1])){
                createPlanBasedPolicy(arguments);
              
        }
}

          
}



// helper function for createObjectBasedType
// creating the right policy for the plan
void Simulation::createPlanBasedPolicy(vector<string> &arguments){
      SelectionPolicy *selectedPolicy;
      if(arguments[2] == "eco"){  
        selectedPolicy = new EconomySelection();
        addPlan(getSettlement(arguments[1]), selectedPolicy);
        // we're not adding a pointer but the object itself so we delete the object we created to avoide memory leak
        delete(selectedPolicy);
        selectedPolicy = nullptr;

        }
        else if(arguments[2] == "bal"){
            // since we creating new plan it's scores are by default 0 (we ahven't build anything)
            selectedPolicy = new BalancedSelection(0,0,0);
            addPlan(getSettlement(arguments[1]), selectedPolicy);
            // we're not adding a pointer but the object itself so we delete the object we created to avoide memory leak
            delete(selectedPolicy);
            selectedPolicy = nullptr;
            
        }
        else if(arguments[2] == "env"){
            selectedPolicy = new SustainabilitySelection();
            addPlan(getSettlement(arguments[1]), selectedPolicy);
            // we're not adding a pointer but the object itself so we delete the object we created to avoide memory leak
            delete(selectedPolicy);
            selectedPolicy = nullptr;

        }
        else if(arguments[2] == "nve"){
            selectedPolicy = new NaiveSelection();
            addPlan(getSettlement(arguments[1]), selectedPolicy);
            // we're not adding a pointer but the object itself so we delete the object we created to avoide memory leak
            delete(selectedPolicy);
            selectedPolicy = nullptr;
    }
            
         }



// starting the simulation
void Simulation::start(){
    // first we check the simulation is not running
    // stupid and maybe remove it
    if(this->isRunning){
        std::cout << "the Simulation already running you need to clsoe it brfore starting again";
    }
    else{
        std::cout << "the Simulation has started" << std::endl;
        open();
        string userCommand; 
        while(this->isRunning){
            std::getline(std::cin, userCommand);
            vector<string> commandAsvector = Auxiliary::parseArguments(userCommand);
            // close => finishing simulation
            if(commandAsvector[0] == "close"){
                std::cout << "closing simulation" << std::endl;
                this->isRunning = false;
                // close();
            }
            else{
                validateCommnad(commandAsvector);
            }
            
        }
    }
}




void Simulation::addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy){
    // we assume the action that called this function is the last one sice after every call for action we call it's 
    // simulation function so by default our action is the last action 
    // create and insert
    Plan *addedPlan = new Plan(this->planCounter, settlement, selectionPolicy, this->facilitiesOptions);
    this->plans.push_back(*addedPlan);
    // making changes after init
    this->planCounter = this->planCounter + 1;
    
    // delete(selectionPolicy);
}




void Simulation::addAction(BaseAction *action){
    this->actionsLog.push_back(action);
}


bool Simulation::addSettlement(Settlement *settlement){
    if(isSettlementExists(settlement->getName())){
        // couldnt add settlement because it is already exists so we failed to add it -> false
        return false;
    }
    this->settlements.push_back(settlement);
    return true;
    
}

bool Simulation::addFacility(FacilityType facility){
    // checking if facility name already existing
    // added reference
    for(auto &currFacility : this->facilitiesOptions)
    {
        if(facility.getName() == currFacility.getName()){
            // facility already existing
            return false;
        }
    }
    // no facility type in option
    this->facilitiesOptions.push_back(facility);
    return true;
}

// we check if the settlement name is in our settlements vector
// if it is the settlement exist else its not so we return false;
bool Simulation::isSettlementExists(const string &settlementName){
    for(auto &currSettlement : this->settlements)
    {
        if(settlementName == currSettlement->getName()){
            return true;
        }
    }
    return false;
}


Settlement &Simulation::getSettlement(const string &settlementName)
{
    for(auto &currSettlement : this->settlements)
    {
        if(settlementName == currSettlement->getName()){
            return *currSettlement;
        }
    }
    // we return a static settlement and later it will be deleted automatically
    static Settlement nullSttlement("nullSettlement", SettlementType::CITY);
    return nullSttlement;
}

Plan &Simulation::getPlan(const int planID){
    for (Plan &plan : plans) {
        if (plan.getPlan_id() == planID) {  // Assuming Plan has a method getID() to get its ID
            return plan;
        }
    }
    // return
}

bool Simulation::isPlanExisting(const int planID){
    if(planID < 0 || static_cast<size_t>(planID > plans.size())){
        return false;
    }
     for (Plan &plan : plans) {
        if (plan.getPlan_id() == planID) {  // Assuming Plan has a method getID() to get its ID
            return true;;
        }
    }
    return false;
}


void Simulation::step(){
    for(auto &pla : this->plans){
        pla.step();
    }
}

// open command - open the user-interface communiccation
void Simulation::open(){
    this->isRunning = true;
}

// delete before submiting
void Simulation::to_string(){
    for(auto set : this->settlements){
        std::cout << set->toString() << std::endl;
    }
    for(auto fac : this->facilitiesOptions){
        std::cout << fac.toString() << std::endl;
    }
    for(auto pla : this->plans){
        std::cout << pla.toString() << std::endl;
    }
}


void  Simulation::validateCommnad(vector<string> &commandAsVector){
    // dealing with SimulateStep command:
    if(commandAsVector[0] == "step"){
        // valid input step <int>
        if(commandAsVector.size() == 2) {
            // we assume it's a positive number as instructed
            int numOfSteps = std::stoi(commandAsVector[1] );
                executeStepCommand(numOfSteps);
            
        }
    }
    else if(commandAsVector[0] == "plan"){
        // valid input plan <settlement_name> <selection_policy>
        if(commandAsVector.size() == 3) {
                executePlanCommand(commandAsVector[1], commandAsVector[2]);
            
        }
        else{
            std::cout << "invalid input" << std::endl;
        }
        
    }

    else if(commandAsVector[0] == "settlement"){
        // valid input settlement <settlement_name> <settlement_type>
        if(commandAsVector.size() == 3) {
            executeSettlementCommnad(commandAsVector[1], static_cast<SettlementType>(std::stoi(commandAsVector[2])));
    }
         else{
            std::cout << "invalid input" << std::endl;
        }
    }

    else if(commandAsVector[0] == "facility"){
            // valid input settlement <settlement_name> <settlement_type>
            if(commandAsVector.size() == 7) {
                executeFacilityCommnad(commandAsVector[1], static_cast<FacilityCategory>(std::stoi(commandAsVector[2])),std::stoi(commandAsVector[3]),std::stoi(commandAsVector[4]),std::stoi(commandAsVector[5]),std::stoi(commandAsVector[6]));
        }
            else{
                std::cout << "invalid input" << std::endl;
            }
        }

    else if(commandAsVector[0] == "planStatus"){
    // valid input settlement <settlement_name> <settlement_type>
        if(commandAsVector.size() == 2) {
            executePrintPlanStatusCommnad(std::stoi(commandAsVector[1]));
        }
        else{
                std::cout << "invalid input" << std::endl;
            }
}
}

void Simulation::executeStepCommand(int &numOfSteps){
        BaseAction *stepAction = new SimulateStep(numOfSteps);
        addAction(stepAction);
        // executing the steps
        stepAction->act(*this);
        // As instructed we assume this action wont result in an error
        

}

void Simulation::executePlanCommand(const string &settlementName, const string &selectionPolicy){
    BaseAction *planAction = new AddPlan(settlementName, selectionPolicy);
    planAction->act(*this);
    addAction(planAction);

}


void Simulation::executeSettlementCommnad(const string &name, SettlementType type){
    BaseAction *settlementAction = new AddSettlement(name, type);
    settlementAction->act(*this);
    addAction(settlementAction);
}


void Simulation::executeFacilityCommnad(const string &facilityName, const FacilityCategory facilityCategory, const int price, const int lifeQualityScore, const int economyScore, const int environmentScore){
    BaseAction *facilityAction = new AddFacility(facilityName, facilityCategory, price, lifeQualityScore, economyScore, environmentScore);
    facilityAction->act(*this);
    addAction(facilityAction);
}

void Simulation::executePrintPlanStatusCommnad(int plan_id){
    BaseAction *printPlanAction = new PrintPlanStatus(plan_id);
    addAction(printPlanAction);
    printPlanAction->act(*this);
}
