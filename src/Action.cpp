#include <iostream>
#include <fstream>
#include <string>
#include "Simulation.h"
# include "Auxiliary.h"
# include "Facility.h"
# include "Plan.h"
# include "SelectionPolicy.h"
# include "Settlement.h"
# include "Action.h"


//builder and methods
BaseAction::BaseAction()
:status(ActionStatus::ERROR), errorMsg(""){}


void BaseAction::complete(){
    status = ActionStatus::COMPLETED;
}

void BaseAction::error(string errorMsg){
    status = ActionStatus::ERROR;
    this->errorMsg = errorMsg; 
    std::cout << "ERROR:" << this->errorMsg << std::endl; 
}

ActionStatus BaseAction::getStatus() const {
    return this->status; 
}

const string& BaseAction::getErrorMsg() const{
    return this->errorMsg;
}



//simulate step class
SimulateStep::SimulateStep(const int numOfSteps)
: BaseAction(), numOfSteps(numOfSteps){}

// act performs number of steps according to numOfSteps
void SimulateStep::act(Simulation &simulation){
     int i = numOfSteps;
        while (i>0){
            i--;
            simulation.step();
        }
        complete();
}


//toString method
const string SimulateStep::toString()const  {
string statusStr = "";

    if(this->getStatus() == ActionStatus::ERROR){  
     statusStr = "ERROR"; 
     }            

    if(this->getStatus() == ActionStatus::COMPLETED){
        statusStr = "COMPLETED"; 
    }

    string numOfStepsStr = std::to_string(numOfSteps);

    return "status:" + statusStr + "Number Of Steps:" + numOfStepsStr;
}



//clone method
SimulateStep *SimulateStep::clone() const{
    return new SimulateStep(*this);
}



//add plan builder
AddPlan:: AddPlan (const string &settlementName, const string &selectionPolicy) 
:settlementName(settlementName), selectionPolicy(selectionPolicy){}

//act method
void AddPlan::act(Simulation &simulation){
    Settlement &settlement = simulation.getSettlement(settlementName);
    SelectionPolicy *myPolicy = nullptr;

    //checks the requiered policy 
    if(selectionPolicy == "nve"){
        myPolicy =  new NaiveSelection();
    }
    else if(selectionPolicy == "bal"){
        myPolicy = new BalancedSelection(0,0,0); //defult values 
    }
    else if(selectionPolicy == "eco"){
        myPolicy = new EconomySelection();
    }
    else if (selectionPolicy == "env"){
        myPolicy = new SustainabilitySelection();
    }
    //creates a new plan to the settlement and the chosen policy
    simulation.addPlan(settlement, myPolicy);

    complete(); //updates the status as completed
}


//to string method (AddPlan)
 const string AddPlan::toString() const {
    return "Settlement name:" + this->settlementName + "Selection Policy:" + this->selectionPolicy;
 }


//clone method (AddPlan)
AddPlan *AddPlan::clone() const {
    return new AddPlan(this->settlementName,this->selectionPolicy );
}


/*
class AddSettlement : public BaseAction {
    public:
        AddSettlement(const string &settlementName,SettlementType settlementType);
        void act(Simulation &simulation) override;
        AddSettlement *clone() const override;
        const string toString() const override;
    private:
        const string settlementName;
        const SettlementType settlementType;
};*/

//continue from here
AddSettlement:: AddSettlement(const string &settlementName, const SettlementType settlementType)
:settlementName(settlementName),settlementType(settlementType){}