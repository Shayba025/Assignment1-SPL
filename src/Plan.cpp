
# include "Plan.h"
# include "Settlement.h"
# include <string>
#include <sstream>
#include <vector>
#include <iostream>


// plan constructor
Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions)
//no need to initilized facilites/underconstructions becuase c++ will create the empty vector on it's own
  : plan_id(planId),
    settlement(settlement),
    //maybe change
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
    //deep copy for
    for (const Facility *facility : other.underConstruction) {
        this->underConstruction.push_back(new Facility(*facility));
    }
  }



// function for reseting/deleting the vectors facilities and underConstruction
void Plan::facilitiesAndUnderConstructionclearer(){
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


// maybe delete
//copy assignment operator 
Plan& Plan::operator=(const Plan& other) {
    // see if i need to change faclitiy options as well
    //first we want to avoid self assign
    if (this != &other) {
    //delete current resourses
    facilitiesAndUnderConstructionclearer();
    delete this->selectionPolicy;
    
    //copy values from other
    //cant assign settlements and facilites options since they are const
    this->plan_id = other.plan_id;
    //if is nullptr we cant call the clone function run time compilation
    if(other.selectionPolicy != nullptr){
        this->selectionPolicy = other.selectionPolicy->clone();
        
    }
    else{
        this->selectionPolicy = nullptr;
    }
    
    
    this->status = other.status;
    this->life_quality_score = other.life_quality_score;
    this->economy_score = other.economy_score;
    this->environment_score = other.environment_score;

    //deep copy for facilites
    for (const Facility *facility : other.facilities) {
        this->facilities.push_back(new Facility(*facility));
    }
    //deep copy for underConstruction
    for (const Facility *facility : other.underConstruction) {
        this->underConstruction.push_back(new Facility(*facility));
    }
    }
    return *this;
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
    
    //ask ido if to do move to selectiopn policy
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

//mybe delete
//move operator
Plan& Plan::operator=(Plan&& other) noexcept
{
    //first we want to avoid self assign
    if (this != &other) {
    //moving stack data
    this->plan_id = other.plan_id;
    //deleting selection policy to avoid data leaks
    delete this->selectionPolicy;
    if(other.selectionPolicy != nullptr){
        this->selectionPolicy = other.selectionPolicy->clone();
         //avoiding memory leak
        other.selectionPolicy = nullptr;
    }
    else{
        this->selectionPolicy = nullptr;
    }
   
    this->status = other.status;
    this->life_quality_score = other.life_quality_score;
    this->economy_score = other.economy_score;
    this->environment_score = other.environment_score;
    


    //moving dynamic data
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
    return *this;
}

//destructor
Plan::~Plan(){
    // we delete all variables on the heap, the 2 vectors facilites and underConstraction and the objects in them
    // select policy
    // we dont delete the settlement object
    facilitiesAndUnderConstructionclearer();
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
    for (auto it = this->underConstruction.begin(); it != this->underConstruction.end(); ) {
        Facility *facility = *it;
        FacilityStatus currStatus = facility->step();
       if(currStatus == FacilityStatus::OPERATIONAL){
            //remove vevtor from Undercondtructor
            this->facilities.push_back(*this->underConstruction.erase(it)); 
       }
       else{
        it = it+1;
       }
    }
    //step 4 updating plan status:
    //adding size_t instead of int
    size_t constructionLimit = this->settlement.getConstructionLimit();//verify about get constraction limit
    if(this->underConstruction.size() < constructionLimit){
        this->status = PlanStatus::AVALIABLE;
    }
}

//finish
void Plan::printStatus(){
    std::cout << statusToString();

}

const vector<Facility*> &Plan::getFacilities() const{
    return this->facilities;
}

void Plan::addFacility(Facility* facility){
    this->underConstruction.push_back(new Facility(*facility));
}

// static function that transaltes planStatus to string
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

const string Plan::toString() const{
    // creating oss object
    std::ostringstream oss;
    oss << "plan id: " << this->plan_id << " | "
        << " Settlement " << this->settlement.getName() << " | ";
        // if is ullptr can't use the get name function run time compilation
        if (selectionPolicy != nullptr) {
        oss << "selection policy: " << selectionPolicy->toString() << " | "; 
    } else {
        oss << "selection policy: no policy given  | ";
    }
    oss << " status : " << statusToString() << " | "
        << "life quality score: " << life_quality_score << " | "
        << "economy score: " << economy_score << " | "
        << "environment score: " << environment_score << "\n"
        << "facilities: ";
        // iterating other the facilities
        for (const Facility* facility : this->facilities){
            oss << "  | " << facility->toString() << "  | ";
        }
        oss << "under construction : ";
        // iterating other the under construction facilities
         for (const Facility* facility : this->underConstruction){
            oss << "  | " << facility->toString() << "  | ";
        }


    return oss.str();
}
