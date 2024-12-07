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
    statusStr = "Simulate Step Status: COMPLETED"; 
    string numOfStepsStr = std::to_string(numOfSteps);
    return "Status:" + statusStr + "Number Of Steps:" + numOfStepsStr;
}



//clone method (SimulateStep)
SimulateStep *SimulateStep::clone() const{
    return new SimulateStep(*this);    
}


//add plan builder
AddPlan:: AddPlan (const string &settlementName, const string &selectionPolicy) 
  :  BaseAction() ,settlementName(settlementName), selectionPolicy(selectionPolicy){}

//act method (AddPlan)
void AddPlan::act(Simulation &simulation){
     // checking for errors
    vector<string> policyCodeNames = {"nve", "bal", "eco", "env"};
    bool policyExists = false;
    for(auto str : policyCodeNames){
        if(this->selectionPolicy == str){
            policyExists = true;
        }
    }
    // error occurd
    if(!simulation.isSettlementExists(this->settlementName) || !policyExists){
        error("Cannot create this plan");
    }
    else{
        SelectionPolicy *myPolicy;
        //checks the requiered policy 
        if(this->selectionPolicy == "nve"){
            myPolicy =  new NaiveSelection();
        }
        else if(this->selectionPolicy == "bal"){
            myPolicy = new BalancedSelection(0,0,0); //defult values 
        }
        else if(this->selectionPolicy == "eco"){
            myPolicy = new EconomySelection();
        }
        else if (this->selectionPolicy == "env"){
            myPolicy = new SustainabilitySelection();
        }
        //creates a new plan to the settlement and the chosen policy
        simulation.addPlan(simulation.getSettlement(this->settlementName), myPolicy);

        complete(); //updates the status as completed
        }
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

//AddSettlement constractor
AddSettlement:: AddSettlement(const string &settlementName, const SettlementType settlementType)
  : settlementName(settlementName),settlementType(settlementType){}

//act (AddSettlement)
void:: AddSettlement::act(Simulation &simulation){

    if(simulation.isSettlementExists(settlementName)){
        error("Settlement already exists");
    }
    else{
        // add potential 
        simulation.addSettlement(new Settlement(settlementName,settlementType));
        complete();
    }
        
}

//clone method (AddSettlement)
AddSettlement *AddSettlement::clone() const{
    return new AddSettlement(this->settlementName, this->settlementType);
}

//to string method (AddSettlement)
 const std::string AddSettlement::toString() const{
    if(this->getStatus() == ActionStatus::ERROR){
        return "Add Settlement:: ERROR";
    }
    else{
        return "Settlemet Name Status: COMPLETED  Settlement Name:" + settlementName + "settlement Type:" ;
 
    }
 }


// AddFacility constractor
AddFacility::AddFacility(const string &facilityName, const FacilityCategory facilityCategory, const int price, const int lifeQualityScore, const int economyScore, const int environmentScore)
  : facilityName(facilityName),
    facilityCategory(facilityCategory),
    price(price),
    lifeQualityScore(lifeQualityScore),
    economyScore(economyScore),
    environmentScore(environmentScore){}



//act method (AddFacility)
void::AddFacility::act(Simulation &simulation){
FacilityType *facility = new FacilityType(facilityName, facilityCategory, price, lifeQualityScore, economyScore, environmentScore);
    
        if(simulation.addFacility(*facility)){
            complete();
        }
        else{
            error("Facilty already exists");
        }
    }


//clone method (AddFacility)
AddFacility *AddFacility::clone() const{
    return new AddFacility(*this);
}


//to string method (AddFacility)
const string AddFacility::toString() const{
    if(this->getStatus() == ActionStatus::ERROR){
        return "Add Facility Status: ERROR";
    }
    else{
   return  "Add Facility Status: COMPLETED Facility Name:" + facilityName + "Facility Category:" + categoryAsString(facilityCategory) 
             + "price:" + std::to_string(price) + "Life Quality Score:" + std::to_string(lifeQualityScore) + 
            "Economy Score:" + std::to_string(economyScore) + "Enviroment Score:" + std::to_string(environmentScore); 
            }
}



//print plan constractor
PrintPlanStatus::PrintPlanStatus(int planId)
  : planId(planId){}

//act method (print plan)
void PrintPlanStatus::act(Simulation &simulation){
    if(simulation.isPlanExisting(this->planId)){
        Plan myPlan = simulation.getPlan(this->planId);
        std::cout << "Plan Status:" + myPlan.toString() << std::endl;
    }
    else{
        error("Plan doesn’t exist");
    }
    
}
//clone method (print plan)
 PrintPlanStatus *PrintPlanStatus::clone() const{
    return new PrintPlanStatus(*this);
 }

//to string method (print plan)
 const string PrintPlanStatus::toString() const{//need to implement a method that returns if the plan exists
    //finish
    return "";
 }


