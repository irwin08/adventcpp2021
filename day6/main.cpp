#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <numeric>

std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream {s};
    while(std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}



int main() {

    std::vector<long long> day_counters {0,0,0,0,0,0,0,0,0};

    //load initial state
    std::vector<long long> init {3,5,2,5,4,3,2,2,3,5,2,3,2,2,2,2,3,5,3,5,5,2,2,3,4,2,3,5,5,3,3,5,2,4,5,4,3,5,3,2,5,4,1,1,1,5,1,4,1,4,3,5,2,3,2,2,2,5,2,1,2,2,2,2,3,4,5,2,5,4,1,3,1,5,5,5,3,5,3,1,5,4,2,5,3,3,5,5,5,3,2,2,1,1,3,2,1,2,2,4,3,4,1,3,4,1,2,2,4,1,3,1,4,3,3,1,2,3,1,3,4,1,1,2,5,1,2,1,2,4,1,3,2,1,1,2,4,3,5,1,3,2,1,3,2,3,4,5,5,4,1,3,4,1,2,3,5,2,3,5,2,1,1,5,5,4,4,4,5,3,3,2,5,4,4,1,5,1,5,5,5,2,2,1,2,4,5,1,2,1,4,5,4,2,4,3,2,5,2,2,1,4,3,5,4,2,1,1,5,1,4,5,1,2,5,5,1,4,1,1,4,5,2,5,3,1,4,5,2,1,3,1,3,3,5,5,1,4,1,3,2,2,3,5,4,3,2,5,1,1,1,2,2,5,3,4,2,1,3,2,5,3,2,2,3,5,2,1,4,5,4,4,5,5,3,3,5,4,5,5,4,3,5,3,5,3,1,3,2,2,1,4,4,5,2,2,4,2,1,4};
    for(auto i : init) {
        int index = day_counters.size() - (i+1);
        day_counters[index]++;
    }

    //simulate day
    for(int day = 0; day < 256; day++) {
        long long new_spawn = day_counters[8];
        //shift to right
        for(int i = (day_counters.size()-1); i > 0; i--) {
            
            if(i != 0) {
                day_counters[i] = day_counters[i-1];
            }
        }
        day_counters[0] = new_spawn;
        day_counters[2] += new_spawn;

    }

    //count
    std::cout << std::accumulate(day_counters.begin(), day_counters.end(), (long long)0) << std::endl;

    return 0;
}