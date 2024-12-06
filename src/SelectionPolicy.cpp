//#pragma once
#include <vector>
#include "Facility.h"
#include "SelectionPolicy.h"
#include <algorithm> 
#include <stdexcept>
#include <iostream>
#include <climits>
using std::string;
using std::vector;



// Naive selection:
NaiveSelection::NaiveSelection() : lastSelectedIndex(-1) {}

const FacilityType& NaiveSelection::selectFacility(const std::vector<FacilityType>& facilitiesOptions) {
    if (facilitiesOptions.empty()) {
        throw std::invalid_argument("No facilities available for selection."); // making sure we didn't get an empty list 
    }

    lastSelectedIndex = (lastSelectedIndex + 1) % facilitiesOptions.size(); //moving on to the next facillity 
    return facilitiesOptions[lastSelectedIndex]; // returning the facillity according to it's index
}

//to string method
const string NaiveSelection::toString() const{
    return "Naive Selection";
}

//clone method
NaiveSelection *NaiveSelection::clone() const{
    return new NaiveSelection (*this);
}

//Balanced selection:
BalancedSelection::BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore)
: LifeQualityScore(LifeQualityScore),EconomyScore(EconomyScore),EnvironmentScore(EnvironmentScore){}
const FacilityType& BalancedSelection::selectFacility(const vector<FacilityType>& facilitiesOptions){
    
   const FacilityType *best = nullptr; // a facility type to return
   int scoreDiff = INT_MAX; // start with the largest int just for finding the smallest value
    

    for(auto &currFacility : facilitiesOptions){
        
        int facilityLifeQuality = currFacility.getLifeQualityScore();
        int facilityEnvironment = currFacility.getEnvironmentScore();
        int facilityEconomy = currFacility.getEconomyScore();

        // temporary variables to see if the current facility has the best balance
        int tempLifeQ = facilityLifeQuality + this->LifeQualityScore;
        int tempEnv = facilityEnvironment + this->EnvironmentScore;
        int tempEco = facilityEconomy + this->EconomyScore; 

        int maxScore = std::max(tempLifeQ, std::max(tempEnv, tempEco));
        int minScore = std::min(tempLifeQ, std::min(tempEnv, tempEco));

        int diffrance = maxScore - minScore; 

        if(diffrance<scoreDiff){
            scoreDiff = diffrance;
            best = &currFacility;
        }
        
    }
    this->LifeQualityScore += best->getLifeQualityScore();
    this->EnvironmentScore += best->getEnvironmentScore();
    this->EconomyScore += best->getEconomyScore();
    return *best;
}

//to string method
const string BalancedSelection::toString() const{
    return "Balanced Selection";
}


//clone method
BalancedSelection* BalancedSelection::clone() const{
    return new BalancedSelection (*this);
}


//Economy Selection:
EconomySelection::EconomySelection() 
: lastSelectedIndex(-1) {}


const FacilityType& EconomySelection::selectFacility(const vector<FacilityType>& facilitiesOptions){
      //adding size_t intead of int
        // if the last facility that we picke was the last facility in the vercotr we reset it to -1 to avoid runtime error
        
        int indexPlacer = this->lastSelectedIndex;
        bool madeFullCircle = false;
        while(!madeFullCircle){
            if (this->lastSelectedIndex >= static_cast<int>(facilitiesOptions.size())){
            this->lastSelectedIndex = -1;
    }
            this->lastSelectedIndex = (this->lastSelectedIndex + 1);
            if(facilitiesOptions[this->lastSelectedIndex].getCategory() == FacilityCategory::ECONOMY){
                return facilitiesOptions[this->lastSelectedIndex];
            }
            if(this->lastSelectedIndex == indexPlacer){
                madeFullCircle = true;
            }
            
        }
        
                    return facilitiesOptions[0];


}


//to string method
const string EconomySelection::toString() const{
    return "Economy Selection";
}


//clone method
EconomySelection* EconomySelection::clone() const{
    return new EconomySelection (*this);
}



// Sustainability Selection:
SustainabilitySelection::SustainabilitySelection() 
    : lastSelectedIndex(-1) {}

const FacilityType& SustainabilitySelection::selectFacility(const vector<FacilityType>& facilitiesOptions){
    //adding size_t intead of int
        // if the last facility that we picke was the last facility in the vercotr we reset it to -1 to avoid runtime error
        
        int indexPlacer = this->lastSelectedIndex;
        bool madeFullCircle = false;
        while(!madeFullCircle){
            if (this->lastSelectedIndex >= static_cast<int>(facilitiesOptions.size())){
            this->lastSelectedIndex = -1;
    }
            this->lastSelectedIndex = (this->lastSelectedIndex + 1);
            if(facilitiesOptions[this->lastSelectedIndex].getCategory() == FacilityCategory::ENVIRONMENT){
                return facilitiesOptions[this->lastSelectedIndex];
            }
            if(this->lastSelectedIndex == indexPlacer){
                madeFullCircle = true;
            }
            
        }
        
                    return facilitiesOptions[0];



    }

    


//to string method
const string SustainabilitySelection::toString() const{
    return "Sustainability Selection";
}


//clone method
SustainabilitySelection* SustainabilitySelection::clone() const{
    return new SustainabilitySelection (*this);
}
