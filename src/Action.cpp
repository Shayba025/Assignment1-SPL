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
# include "Settlement.cpp" //becasue we have created a static method

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
:settlementName(settlementName), selectionPolicy(selectionPolicy){}

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


//AddSettlement constractor
AddSettlement:: AddSettlement(const string &settlementName, const SettlementType settlementType)
:settlementName(settlementName),settlementType(settlementType){}

//act (AddSettlement)
void:: AddSettlement::act(Simulation &simulation){

    if(simulation.isSettlementExists(settlementName)){
    error("Error: Settlement already exists");
    
    }
    else{
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
        return "Settlemet Name Status: COMPLETED  Settlement Name:" + settlementName + "settlement Type:" + typeToString(settlementType);
 
    }
 }



// AddFacility constractor
AddFacility::AddFacility(const string &facilityName, const FacilityCategory facilityCategory, const int price, const int lifeQualityScore, const int economyScore, const int environmentScore)
:facilityName(facilityName),facilityCategory(facilityCategory),price(price),lifeQualityScore(lifeQualityScore),economyScore(economyScore),environmentScore(environmentScore){}



//act method (AddFacility)
void::AddFacility::act(Simulation &simulation){
    FacilityType facility (facilityName, facilityCategory, price, lifeQualityScore, economyScore, environmentScore);

        if()
        }
        else{
            (simulation.addFacility(facility)){
            complete();
        }
}//////////////////////////////////////////////////// complete act with the is facility exists method



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




 //convert the status enum to viable string for the toString method
 // determaning the string using the case method of enum
    string categoryAsString(const FacilityCategory &category){
     string currCategory = "";
            switch (category)
            {
            case FacilityCategory::LIFE_QUALITY:
                currCategory = "LIFE_QUALITY";
                break;
            
            case FacilityCategory::ECONOMY:
                currCategory = "ECONOMY";
                break;
            case FacilityCategory::ENVIRONMENT:
                currCategory = "ENVIRONMENT";
                break;
            default:
            currCategory = "Unknown";
            break;
        }
        return currCategory;

}

/*
class PrintPlanStatus: public BaseAction {
    public:
        PrintPlanStatus(int planId);
        void act(Simulation &simulation) override;
        PrintPlanStatus *clone() const override;
        const string toString() const override;
    private:
        const int planId;
};*/

//print plan constractor
PrintPlanStatus::PrintPlanStatus(int planId):planId(planId){}

//act method (print plan)
void PrintPlanStatus::act(Simulation &simulation){
    Plan myPlan = simulation.getPlan(planId);
    std::cout << "Plan Status:" + myPlan.toString() << std::endl;
}
//clone method (print plan)
 PrintPlanStatus *PrintPlanStatus::clone() const{
    return new PrintPlanStatus(*this);
 }

//to string method (print plan)
 const string PrintPlanStatus::toString() const{//need to implement a method that returns if the plan exists
    if(this.get)
 }



/*
class ChangePlanPolicy : public BaseAction {
    public:
        ChangePlanPolicy(const int planId, const string &newPolicy);
        void act(Simulation &simulation) override;
        ChangePlanPolicy *clone() const override;
        const string toString() const override;
    private:
        const int planId;
        const string newPolicy;
};*/

//change plan policy builder
ChangePlanPolicy::ChangePlanPolicy(const int planId, const string &newPolicy)
:planId(planId), newPolicy(newPolicy){}

//act method (change plan policy)
void ChangePlanPolicy::act(Simulation &simulation){

    if(((simulation.getPlan(planId)).getSelectionPolicy()).getSelectionPolicyName() == newPolicy
    || simulation.getPlan(planId)){
        error("Cannot change selection policy");
    }

    //to check which policy is needed
    if(newPolicy=="nve"){
        (simulation.getPlan(planId)).setSelectionPolicy(new NaiveSelection);
        complete();
    }
    else if(newPolicy=="bal"){
        (simulation.getPlan(planId)).setSelectionPolicy(new BalancedSelection(0,0,0));//defult values
        complete();
    }
    else if(newPolicy=="eco"){
        (simulation.getPlan(planId)).setSelectionPolicy(new EconomySelection);
        complete();
    }
    else if(newPolicy=="env"){
        (simulation.getPlan(planId)).setSelectionPolicy(new SustainabilitySelection);
        complete();
    }
    else{
        error("");
    }
}