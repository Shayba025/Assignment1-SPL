#pragma once
#include <vector>
#include "Facility.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
using std::vector;

enum class PlanStatus {
    AVALIABLE,
    BUSY,
};

class Plan {
    public:
        Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions);
        
        //rule of 5 methods:
        //copy constructer
        Plan(const Plan& other);
        //copy assignment operator as instructed will be deleted
        Plan& operator=(const Plan& other) = delete;
        //move constructor
        Plan(Plan&& other) noexcept;
        //move assignment operator aas instructed will be deleted
        Plan& operator=(Plan&& other) = delete;
        //Destructor 
        ~Plan();

        // making a function that deletes the faclities and construction vectors we dont need to avoid memory leaks.
        void facilitiesAndUnderConstructionClearer();
        

        const int getlifeQualityScore() const;
        const int getEconomyScore() const;
        const int getEnvironmentScore() const;
        void setSelectionPolicy(SelectionPolicy *selectionPolicy);
        void step();
        void printStatus();
        const vector<Facility*> &getFacilities() const;
        void addFacility(Facility* facility);

        // modyfing status to string variable mainly to avoid messy code in the to String function and make it more readable
        const string statusToString() const;
        const string toString() const;

        // adding get function for plan_id
        const int getPlan_id() const;


    private:
        int plan_id;
        const Settlement &settlement;
        SelectionPolicy *selectionPolicy; //What happens if we change this to a reference?
        PlanStatus status;
        vector<Facility*> facilities;
        vector<Facility*> underConstruction;
        const vector<FacilityType> &facilityOptions;
        int life_quality_score, economy_score, environment_score;
};

