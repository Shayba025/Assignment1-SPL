#include "Simulation.h"
#include <fstream> 
#include "Auxiliary.h"
#include "Settlement.h"
#include "Facility.h"
#include "SelectionPolicy.h"
#include "Plan.h"

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
            
        else if(arguments[0] == "facility"){
            // we create a new facilityOption
            // we declate new facility while converting the text variables to the type the constructor ueses
            FacilityType *newFacility = new FacilityType(arguments[1], static_cast<FacilityCategory>(std::stoi(arguments[2])) ,std::stoi(arguments[3]),std::stoi(arguments[4]),std::stoi(arguments[5]),std::stoi(arguments[6]));
            addFacility(*newFacility);
            // we're not adding a pointer but the object itself so we delete the object we created to avoide memory leak
            delete(newFacility);

        }
        else if(arguments[0] == "plan"){
            // creating the plan based on the selection policy
            // if the settelement doensn't exists we can't do anything
            if(isSettlementExists(arguments[1])){
                SelectionPolicy *selectedPolicy;
                if(arguments[2] == "eco"){
                    selectedPolicy = new EconomySelection();
                    addPlan(getSettlement(arguments[1]), selectedPolicy);
                    // we're not adding a pointer but the object itself so we delete the object we created to avoide memory leak
                    delete(selectedPolicy);

                }
                else if(arguments[2] == "bal"){
                    // since we creating new plan it's scores are by default 0 (we ahven't build anything)
                    selectedPolicy = new BalancedSelection(0,0,0);
                    addPlan(getSettlement(arguments[1]), selectedPolicy);
                    // we're not adding a pointer but the object itself so we delete the object we created to avoide memory leak
                    delete(selectedPolicy);
                    
                }
                else if(arguments[2] == "env"){
                    selectedPolicy = new SustainabilitySelection();
                    addPlan(getSettlement(arguments[1]), selectedPolicy);
                    // we're not adding a pointer but the object itself so we delete the object we created to avoide memory leak
                    delete(selectedPolicy);

                }
                else if(arguments[2] == "nve"){
                    selectedPolicy = new NaiveSelection();
                    addPlan(getSettlement(arguments[1]), selectedPolicy);
                    // we're not adding a pointer but the object itself so we delete the object we created to avoide memory leak
                    delete(selectedPolicy);
            }
            
         }
            
        }

    
}
    configfile.close();
}


void Simulation::start(){
    // first we check the simulation is not running
    if(this->isRunning){
        std::count << "the Simulation alreadt running you need to clsoe it brfore starting again"
    }
    else{

    }
}


void Simulation::addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy){
    // create and insert
    this->plans.push_back(*new Plan(this->planCounter, settlement, selectionPolicy, this->facilitiesOptions));
    // making changes after init
    this->planCounter = this->planCounter + 1;
    
    // delete(selectionPolicy);
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
    for(FacilityType currFacility : this->facilitiesOptions)
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
    for(Settlement *currSettlement : this->settlements)
    {
        if(settlementName == currSettlement->getName()){
            return true;
        }
    }
    return false;
}


Settlement &Simulation::getSettlement(const string &settlementName)
{
    for(Settlement *currSettlement : this->settlements)
    {
        if(settlementName == currSettlement->getName()){
            return *currSettlement;
        }
    }
    // we return a static settlement and later it will be deleted automatically
    static Settlement nullSttlement("nullSettlement", SettlementType::CITY);
    return nullSttlement;
}


void Simulation::to_string(){
    for(Settlement *set : this->settlements){
        std::cout << set->toString() << std::endl;
    }
    for(FacilityType fac : this->facilitiesOptions){
        std::cout << fac.toString() << std::endl;
    }
    for(Plan pla : this->plans){
        std::cout << pla.toString() << std::endl;
    }
}
