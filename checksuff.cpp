#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int currLifeQuality = 10;
    int currEnvironment = 25;
    int currEconomy = 15;

    int maxScore = std::max(currLifeQuality, std::max(currEnvironment, currEconomy));
    int minScore = std::min(currLifeQuality, std::min(currEnvironment, currEconomy));

    int diffrance = maxScore - minScore;

    cout << "Max Score: " << maxScore << endl;
    cout << "Min Score: " << minScore << endl;
    cout << "Difference: " << diffrance << endl;

    return 0;
}
