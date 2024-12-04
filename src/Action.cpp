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


//toString method (SimulateStep:)
const string SimulateStep::toString()const  {
string statusStr = "";

    if(this->getStatus() == ActionStatus::ERROR){  
     statusStr = "ERROR: Couldn't simulate step"; 
     }            

    if(this->getStatus() == ActionStatus::COMPLETED){
        statusStr = "imulate Step: COMPLETED"; 
    }

    string numOfStepsStr = std::to_string(numOfSteps);

    return "status:" + statusStr + "Number Of Steps:" + numOfStepsStr;
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
    return "Settlement name:" + this->settlementName + "Selection Policy:" + this->selectionPolicy;
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
        simulation.addSettlement(new Settlement(settlementName,settlementType));
}

//clone method (AddSettlement)
AddSettlement *AddSettlement::clone() const{
    return new AddSettlement(this->settlementName, this->settlementType);
}

//to string method (AddSettlement)
 const std::string AddSettlement::toString() const{
    if(this->getStatus() == ActionStatus::ERROR){
        return "AddSettlement:: ERROR";
    }
    else{
        return "Settlemet Name: COMPLETED  Settlement Name:" + settlementName + "settlement Type:" + typeToString(settlementType);
 
    }
 }
/*
class AddFacility : public BaseAction {
    public:
        AddFacility(const string &facilityName, const FacilityCategory facilityCategory, const int price, const int lifeQualityScore, const int economyScore, const int environmentScore);
        void act(Simulation &simulation) override;
        AddFacility *clone() const override;
        const string toString() const override;
    private:
        const string facilityName;
        const FacilityCategory facilityCategory;
        const int price;
        const int lifeQualityScore;
        const int economyScore;
        const int environmentScore;*/


// AddFacility constractor
AddFacility::AddFacility(const string &facilityName, const FacilityCategory facilityCategory, const int price, const int lifeQualityScore, const int economyScore, const int environmentScore)
:facilityName(facilityName),facilityCategory(facilityCategory),price(price),lifeQualityScore(lifeQualityScore),economyScore(economyScore),environmentScore(environmentScore){}


//clone method (AddFacility)
AddFacility *AddFacility::clone() const{
    return new AddFacility(*this);
}


//to string method (AddFacility)
const string AddFacility::toString() const{
   return  "Add Facility: Facility Name:" + facilityName + "Facility Category:" + categoryAsString(facilityCategory) 
             + "price:" + std::to_string(price) + "Life Quality Score:" + std::to_string(lifeQualityScore) + 
            "Economy Score:" + std::to_string(economyScore) + "Enviroment Score:" + std::to_string(environmentScore); 
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