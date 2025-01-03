
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
        if (this->selectionPolicy != nullptr) {  
            delete this->selectionPolicy;  
            this->selectionPolicy = nullptr;
    }
    if(other.selectionPolicy != nullptr){
        this->selectionPolicy = other.selectionPolicy->clone();
    }
    else{
        this->selectionPolicy = nullptr;
    }
    //deep copy for facilites
    for(auto facility : other.facilities) {
        this->facilities.push_back(facility);
    }
    //deep copy for underConstruction
    for(auto facility : other.underConstruction) {
        this->underConstruction.push_back(facility);
    }
  }
   

// function for reseting/deleting the vectors facilities and underConstruction
void Plan::facilitiesAndUnderConstructionClearer(){
    //delete all facility object we have from facilites
    for(auto facility : this->facilities) {
        if(facility != nullptr){
            delete facility;
            facility = nullptr;
        }
    }
    //delete all facility object we have from underConstructions
    for(auto facility : this->underConstruction) {
       if(facility != nullptr){
            delete facility;
            facility = nullptr;
        }
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
    this->selectionPolicy = nullptr;
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
        this->selectionPolicy = nullptr;
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
        for(size_t i = this->underConstruction.size(); i<= constructionLimit; i++){
            Facility *new_facility = new Facility(selectionPolicy->selectFacility(facilityOptions),settlement.getName());
            // consider adding case of what if facility is null ptr maybe printh somesheet
            this->addFacility(new_facility) ; // Add to underConstruction
            this->status = PlanStatus::BUSY;
            
        }
    }
    //step 3 iterating over underconstruction :
    // iterating over the array
    for (auto iter = this->underConstruction.begin(); iter != this->underConstruction.end(); ) {
        // iter is a pointer so we need to get the obj itself
        Facility *facility = *iter;
        facility->step();
       if(facility->getStatus() == FacilityStatus::OPERATIONAL){
            // after the bilding i Operatiomnal we need to update the settlement scores
            this->life_quality_score += facility->getLifeQualityScore();
            this->economy_score += facility->getEconomyScore();
            this->environment_score += facility->getEnvironmentScore();
            //remove vevtor from Undercondtructor and add to finished facilities
            iter = this->underConstruction.erase(iter);
            this->facilities.push_back(facility); 
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
    this->underConstruction.push_back(facility);

    
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
    string returnStr =  "plan id: " + std::to_string(this->plan_id) + " \n "
        + " Settlement " + this->settlement.getName() + " \n ";
        returnStr += " status : " + statusToString() + " \n ";

        // if is nullptr can't use the g et name function run time compilation
    if(selectionPolicy != nullptr) {
            returnStr += "selection policy: " + selectionPolicy->toString() + " \n "; 
     }   
 else {
         returnStr += "selection policy: no policy given  \n ";
    }
        
        returnStr+= "life quality score: " + std::to_string(life_quality_score) + " \n "
        + "economy score: " + std::to_string(economy_score) + " \n "
        + "environment score: " + std::to_string(environment_score) + "\n"
        + "facilities: ";
        // iterating other the facilities
        for (auto facility : this->facilities){
            returnStr += "  \n " + facility->toString() + "  \n ";
        }
        returnStr += "under construction : ";
        // iterating other the under construction facilities
         for (auto facility : this->underConstruction){
            returnStr += "  \n " + facility->toString() + "  \n ";
        }


    return returnStr;
}
