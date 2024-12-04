#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;

class Facility;

enum class SettlementType {
    VILLAGE,
    CITY,
    METROPOLIS,
};

class Settlement {
    public:
        Settlement(const string &name, SettlementType type);
        const string &getName() const;
        SettlementType getType() const;

        // instead of using the switch method for the enum in the to string method we create sub function
        // that is doing it for us so the code will look cleaner.
        const string typeToString() const;

        const string toString() const;
        
        // adding the getConstructionLimit for the step method in plan.
        const int getConstructionLimit() const;

        private:
            const string name;
            SettlementType type;
};
