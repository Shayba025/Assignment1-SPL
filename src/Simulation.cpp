#include "Simulation.h"
#include <fstream> 
#include "Auxiliary.h"

Simulation::Simulation(const string &configFilePath)
  : isRunning(false),
    planCounter(0),
    actionsLog(),
    plans(),
    settlements(),
    facilitiesOptions()
{
    std::ifstream configfile(configFilePath);
    std::string line;
    while (std::getline(configfile, line)) {
        std::vector<std::string> arguments = Auxiliary::parseArguments(line);
        if(arguments[0] == "settlement")
        {
            SettlementType typeAsInt = static_cast<SettlementType>(std::stoi(arguments[2]));
            Settlement *newSettlement = new Settlement(arguments[1],typeAsInt);
            addSettlement(newSettlement);
        }
            
        else if(arguments[0] == "facility"){
            FacilityType *newFacility = new FacilityType(arguments[1], static_cast<FacilityCategory>(std::stoi(arguments[2])) ,std::stoi(arguments[3]),std::stoi(arguments[4]),std::stoi(arguments[5]),std::stoi(arguments[6]));
            addFacility(*newFacility);
            delete(newFacility);

        }
        // else if(arguments[0] == "plan"){
        //  addPlan();
        // }
            
        }

    configfile.close();
}

// to do
void Simulation::start(){

}

void Simulation::addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy){
    // create and insert
    this->plans.push_back(*new Plan(this->planCounter, settlement, selectionPolicy, this->facilitiesOptions));
    // making changes after init
    this->planCounter = this->planCounter + 1;
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
    for(auto iter = this->facilitiesOptions.begin() ; iter!= this->facilitiesOptions.end();)
    {
        FacilityType currFacility = *iter;
        if(facility.getName() == currFacility.getName()){
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
    for(auto iter = this->settlements.begin() ; iter!= this->settlements.end();)
    {
        Settlement *currSettlement = *iter;
        if(settlementName == currSettlement->getName()){
            return true;
        }
    }
    return false;
}


Settlement &Simulation::getSettlement(const string &settlementName)
{
    for(auto iter = this->settlements.begin() ; iter!= this->settlements.end();)
    {
        Settlement *currSettlement = *iter;
        if(settlementName == currSettlement->getName()){
            return *currSettlement;
        }
    }
    // we return a static settlement and later it will be deleted automatically
    static Settlement nullSttlement("nullSettlement", SettlementType::CITY);
    return nullSttlement;
}

