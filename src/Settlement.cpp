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

const std::string typeToString(const SettlementType &type){
 //convert the status enum to viable string for the toString method
 // determaning the string using the case method of enum
string typeStr="";
 
    switch(type){
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
        <<  " type: " << typeToString(this->type);
    return  oss.str();
}




