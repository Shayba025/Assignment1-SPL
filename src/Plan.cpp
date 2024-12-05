
# include "Plan.h"
# include "Settlement.h"
# include <string>
#include <sstream>
#include <vector>
#include <iostream>


// plan constructor
Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions)
  : plan_id(planId),
    settlement(settlement),
    selectionPolicy(selectionPolicy),
    status(PlanStatus::AVALIABLE),
    facilities(),
    underConstruction(),
    facilityOptions(facilityOptions),
    life_quality_score(0),
    economy_score(0),
    environment_score(0)
    
  {}
    
//copy constructor
Plan::Plan(const Plan& other)
  : plan_id(other.plan_id),
    settlement(other.settlement),
    //we add a clone of the selection policy to avoid shallow copy
    selectionPolicy(nullptr),
    status(other.status),
    facilities(),
    underConstruction(),
    facilityOptions(other.facilityOptions),
    life_quality_score(other.life_quality_score),
    economy_score(other.economy_score),
    environment_score(other.environment_score)
    
  {
    //deep copy for selection policy
    if(other.selectionPolicy != nullptr){
        this->selectionPolicy = other.selectionPolicy->clone();
    }
    else{
        this->selectionPolicy = nullptr;
    }
    //deep copy for facilites
    for (const Facility *facility : other.facilities) {
        this->facilities.push_back(new Facility(*facility));
    }
    //deep copy for underConstruction
    for (const Facility *facility : other.underConstruction) {
        this->underConstruction.push_back(new Facility(*facility));
    }
  }
   

// function for reseting/deleting the vectors facilities and underConstruction
void Plan::facilitiesAndUnderConstructionClearer(){
    //delete all facility object we have from facilites
    for (const Facility *facility : this->facilities) {
        delete facility;
    }
    //delete all facility object we have from underConstructions
    for (const Facility *facility : this->underConstruction) {
        delete facility;
    }
    //empty the vectors facilites and UnderConstrauctions before inserting other objects
    this->facilities.clear();
    this->underConstruction.clear();

}

//move constructor
Plan::Plan(Plan&& other) noexcept
    //moving stack data
    : plan_id(other.plan_id),
    settlement(other.settlement),
    selectionPolicy(nullptr),
    status(other.status),
    facilities(),
    underConstruction(),
    facilityOptions(other.facilityOptions),
    life_quality_score(other.life_quality_score),
    economy_score(other.economy_score),
    environment_score(other.environment_score)
        
{
    //moving dynamic data
    if(other.selectionPolicy != nullptr){
        this->selectionPolicy = other.selectionPolicy->clone();
    }   
    // we'll assgin nullptr but we alreaedy did so no need
    
    this->facilities = std::move(other.facilities);  
    this->underConstruction = std::move(other.underConstruction);  
    
    //clearing other:
    other.selectionPolicy = nullptr;
    other.status = PlanStatus::AVALIABLE;
    other.facilities.clear();
    other.underConstruction.clear();
    other.life_quality_score = 0;
    other.economy_score = 0;
    other.environment_score = 0;

    }



Plan::~Plan(){
    // we delete all variables on the heap, the 2 vectors facilites and underConstraction and the objects in them
    // select policy
    // we dont delete the settlement object
    facilitiesAndUnderConstructionClearer();
    delete this->selectionPolicy;
}



// getter for life quality score
const int Plan::getlifeQualityScore() const{
    return this->life_quality_score;
}

// getter for economy score
const int Plan::getEconomyScore() const{
    return this->economy_score;
}

// getter for enviroment score
const int Plan::getEnvironmentScore() const{
    return this->environment_score;
}

// setter for selection policy
void Plan::setSelectionPolicy(SelectionPolicy *selectionPolicy){
    // deleting the previous policy to avoid memory leaks
    if (this->selectionPolicy != nullptr) {
        delete this->selectionPolicy; 
}
    //deep copy for selection policy
    if(selectionPolicy != nullptr){

        this->selectionPolicy = selectionPolicy->clone();
    }
    else{
        this->selectionPolicy = nullptr;
    }
}


// finish
void Plan::step(){
    //step 1:
    if(this->status == PlanStatus::AVALIABLE){
        //start choosing buildings to build
    //step 2:
        //adding size_t instead of int
        size_t constructionLimit = this->settlement.getConstructionLimit();
        while(this->underConstruction.size() < constructionLimit){
            Facility *new_facility = new Facility(selectionPolicy->selectFacility(facilityOptions),settlement.getName());
            // consider adding case of what if facility is null ptr maybe printh somesheet
            this->addFacility(new_facility) ; // Add to underConstruction
            
        }
    }
    //step 3 iterating over underconstruction :
    // iterating over the array
    for (auto iter = this->underConstruction.begin(); iter != this->underConstruction.end(); ) {
        // iter is a pointer so we need to get the obj itself
        Facility *facility = *iter;
        FacilityStatus currStatus = facility->step();
       if(currStatus == FacilityStatus::OPERATIONAL){
            // after the bilding i Operatiomnal we need to update the settlement scores
            this->life_quality_score = facility->getLifeQualityScore();
            this->economy_score = facility->getEconomyScore();
            this->environment_score = facility->getEnvironmentScore();
            //remove vevtor from Undercondtructor and add to finished facilities
            this->facilities.push_back(*this->underConstruction.erase(iter)); 
       }
       else{
        iter = iter+1;
       }
    }
    //step 4 updating plan status:
    //adding size_t instead of int
    size_t constructionLimit = this->settlement.getConstructionLimit();
    if(this->underConstruction.size() < constructionLimit){
        this->status = PlanStatus::AVALIABLE;
    }
}

// printing the status of the plan
void Plan::printStatus(){
    std::cout << statusToString();

}

// getter for facilities
const vector<Facility*> &Plan::getFacilities() const{
    return this->facilities;
}

// we dont  cahnge plan scores while under constructions
void Plan::addFacility(Facility* facility){
    this->underConstruction.push_back(new Facility(*facility));

    
}
// modifying the enum to string for the to string
const string Plan::statusToString() const{
    string statusStr="";
 
    switch(this->status){
        case PlanStatus::AVALIABLE: 
            statusStr = "AVALIABLE";
            break;
        case PlanStatus::BUSY:
            statusStr = "BUSY";
            break;
        default:
            statusStr = "AVALIABLE";
            break;
    }

    return statusStr;  
}

// getter for plan_id
const int Plan::getPlan_id() const{
    return this->plan_id;
}

const string Plan::toString() const{
    // creating oss object
    string returnStr =  "plan id: " + std::to_string(this->plan_id) + " | "
        + " Settlement " + this->settlement.getName() + " | ";
        // if is ullptr can't use the get name function run time compilation
    if (selectionPolicy != nullptr) {
            returnStr + "selection policy: " + selectionPolicy->toString() + " | "; 
}   else {
         returnStr + "selection policy: no policy given  | ";
    }
        returnStr + " status : " + statusToString() + " | "
        + "life quality score: " + std::to_string(life_quality_score) + " | "
        + "economy score: " + std::to_string(economy_score) + " | "
        + "environment score: " + std::to_string(environment_score) + "\n"
        + "facilities: ";
        // iterating other the facilities
        for (const Facility* facility : this->facilities){
            returnStr + "  | " + facility->toString() + "  | ";
        }
        returnStr + "under construction : ";
        // iterating other the under construction facilities
         for (const Facility* facility : this->underConstruction){
            returnStr + "  | " + facility->toString() + "  | ";
        }


    return returnStr;
}

//getter for plan's current selection policy 
const SelectionPolicy& Plan::getSelectionPolicy() const{
    return *this->selectionPolicy;
}