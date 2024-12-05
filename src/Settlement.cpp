#include "Settlement.h"
#include <string>
#include <sstream>

// settlement constructur
Settlement::Settlement(const string &name, SettlementType type)
    : name(name), type(type)
{}


// getter for name
const string &Settlement::getName() const {
    return this->name;
}

// getter for settlement type
SettlementType Settlement::getType() const{
    return this->type;
}

 // convert the status enum to viable string for the toString method
const string Settlement::typeToString() const {
 // determaning the string using cases
string typeStr="";
 
    switch(this->type){
        case SettlementType::VILLAGE: 
            typeStr = "VILLAGE";
            break;
        case SettlementType::CITY:
            typeStr = "CITY";
            break;
        case SettlementType::METROPOLIS: 
            typeStr = "METROPOLIS";
            break;
    }

    return typeStr;  

}




const string Settlement::toString() const{
    string returnString = "name: " + this->name 
        + " type: " + typeToString();
    return  returnString;
}

// getting the construction limit based on type
const int Settlement::getConstructionLimit() const{
     // determaning the value using cases
    switch (this->type)
    {
    case SettlementType::VILLAGE:
        return 1;
        break;
    case SettlementType::CITY:
        return 2;
        break;
    case SettlementType::METROPOLIS:
        return 3;
        break;
    default:
        return 0;
        break;
    }
}
