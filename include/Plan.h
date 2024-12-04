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
        //copy assignment operator
        Plan& operator=(const Plan& other);
        //move constructor
        Plan(Plan&& other) noexcept;
        //move assignment operator
        Plan& operator=(Plan&& other) noexcept;
        //Destructor 
        ~Plan();

        //vector 
        void facilitiesAndUnderConstructionclearer();

        const int getlifeQualityScore() const;
        const int getEconomyScore() const;
        const int getEnvironmentScore() const;

        void setSelectionPolicy(SelectionPolicy *selectionPolicy);
        // this one
        void step();
        // what do they mean by status
        void printStatus();

        // these 3 r ez to constrcut
        const vector<Facility*> &getFacilities() const;
        void addFacility(Facility* facility);
        const string toString() const;

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

