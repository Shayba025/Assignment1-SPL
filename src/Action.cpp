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

// BaseAction:
// constructor
BaseAction::BaseAction()
  : errorMsg(), status(ActionStatus::ERROR){}

// after compliting the action we update the status
void BaseAction::complete(){
    status = ActionStatus::COMPLETED;
}

// if we couldnt finish the action we print we couldnt finish it to the user
void BaseAction::error(string errorMsg){
    status = ActionStatus::ERROR;
    this->errorMsg = errorMsg; 
    std::cout << "ERROR:" << this->errorMsg << std::endl; 
}

// getter for status
ActionStatus BaseAction::getStatus() const {
    return this->status; 
}

// getter for errorMsg
const string& BaseAction::getErrorMsg() const{
    return this->errorMsg;
}



// SimulateStep
// Constructor
SimulateStep::SimulateStep(const int numOfSteps)
: BaseAction(), numOfSteps(numOfSteps){}

// act performs number of steps according to numOfSteps
void SimulateStep::act(Simulation &simulation){
    for(int i =0; i<this->numOfSteps; i++){
        simulation.step();
        
    }
        complete();
}


//to String method (SimulateStep:)
const string SimulateStep::toString()const  {
string statusStr = "";

    if(this->getStatus() == ActionStatus::ERROR){  
     statusStr = "Couldn't simulate step"; 
     }            

    else{
        statusStr = "Simulate Step Status: COMPLETED"; 
    }

    string numOfStepsStr = std::to_string(numOfSteps);

    return "Status:" + statusStr + "Number Of Steps:" + numOfStepsStr;
}



//clone method (SimulateStep)
SimulateStep *SimulateStep::clone() const{
    return new SimulateStep(*this);
}


//add plan builder
AddPlan:: AddPlan (const string &settlementName, const string &selectionPolicy) 
  :  BaseAtction() ,settlementName(settlementName), selectionPolicy(selectionPolicy){}

//act method (AddPlan)
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
    if(this->getStatus() == ActionStatus::ERROR){  
     return"Couldn't Add Plan"; 
     }            

    else{
          return "Add Plan Status: COMPLETED Settlement name:" + this->settlementName + "Selection Policy:" + this->selectionPolicy; 
    }  
 }


//clone method (AddPlan)
AddPlan *AddPlan::clone() const {
    return new AddPlan(this->settlementName,this->selectionPolicy );
}

