#include "Settlement.h"
#include <string>
#include <sstream>

// sellement constructur
// variables: name, type
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


const string Settlement::typeToString() const {
 //convert the status enum to viable string for the toString method
 // determaning the string using the case method of enum
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
    std::ostringstream oss; //will be destroyed automatically when we leave the function since it's local
    // using the oss method for an efficient string "combiner"
    oss << "name: " << this->name 
        <<  " type: " << typeToString();
    return  oss.str();
}

//getting the construction limit based on type
const int Settlement::getConstructionLimit() const{
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
