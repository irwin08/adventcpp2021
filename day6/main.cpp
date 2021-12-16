#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>













class Lanternfish {

    public:

        Lanternfish(int timer=8) {
            days_remaining = timer;
        }

        Lanternfish() = delete;
        Lanternfish(const Lanternfish&) = delete;
        Lanternfish(Lanternfish&&) = default;

        void next_day() {

            for(auto& child : children) {  
                child->next_day();
            }

            //check must come after handling children, or else we will double count
            if(days_remaining == 0) {
                //need to create children
                children.push_back(std::make_unique<Lanternfish>(8));
                days_remaining = 7;
            }

            days_remaining--; //must be done last so don't accidentally create children early!
        }

        //gets number of offspring + self
        int count_family() {
            int count = 1;

            for(auto& child : children) {
                count += child->count_family();    
            }

            return count;
        }

    private:
        int days_remaining;
        std::vector<std::unique_ptr<Lanternfish>> children;
}; 







std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream {s};
    while(std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void  load_data(std::vector<Lanternfish>& initial) {
    std::ifstream file {"input.txt"};
    if(!file.is_open()) {
        std::cerr << "Unable to open file input.txt!" << std::endl;
        throw std::runtime_error("Unable to open file input.txt!");
    }

    std::string line;
    while(std::getline(file, line)) {
        auto components = split(line, ',');
        for(auto component : components) {
            initial.push_back(Lanternfish(std::stoi(component)));
        }
    }
}



int main() {

    //part 1, unfortunately won't work for part 2, too much recursion
    /*std::vector<Lanternfish> initial_fish;

    load_data(initial_fish);

    for(int i = 0; i < 80; i++) {
        for(auto& fish : initial_fish) {
            fish.next_day();
        }
    }

    int total_count = 0;
    for(auto& fish : initial_fish) {
        total_count += fish.count_family();
    }

    std::cout << total_count << std::endl;*/

    std::vector<int> lanterns {3,5,2,5,4,3,2,2,3,5,2,3,2,2,2,2,3,5,3,5,5,2,2,3,4,2,3,5,5,3,3,5,2,4,5,4,3,5,3,2,5,4,1,1,1,5,1,4,1,4,3,5,2,3,2,2,2,5,2,1,2,2,2,2,3,4,5,2,5,4,1,3,1,5,5,5,3,5,3,1,5,4,2,5,3,3,5,5,5,3,2,2,1,1,3,2,1,2,2,4,3,4,1,3,4,1,2,2,4,1,3,1,4,3,3,1,2,3,1,3,4,1,1,2,5,1,2,1,2,4,1,3,2,1,1,2,4,3,5,1,3,2,1,3,2,3,4,5,5,4,1,3,4,1,2,3,5,2,3,5,2,1,1,5,5,4,4,4,5,3,3,2,5,4,4,1,5,1,5,5,5,2,2,1,2,4,5,1,2,1,4,5,4,2,4,3,2,5,2,2,1,4,3,5,4,2,1,1,5,1,4,5,1,2,5,5,1,4,1,1,4,5,2,5,3,1,4,5,2,1,3,1,3,3,5,5,1,4,1,3,2,2,3,5,4,3,2,5,1,1,1,2,2,5,3,4,2,1,3,2,5,3,2,2,3,5,2,1,4,5,4,4,5,5,3,3,5,4,5,5,4,3,5,3,5,3,1,3,2,2,1,4,4,5,2,2,4,2,1,4};
    std::vector<int> new_friends;

    for(int day = 0; day < 256; day++) {
        for(auto& num : lanterns) {
            if(num == 0) {
                new_friends.push_back(8);
                num = 7;
            }
            num--;
        }

        lanterns.insert(lanterns.end(), new_friends.begin(), new_friends.end());
        new_friends.clear();
    }

    std::cout << lanterns.size() << std::endl;

    return 0;
}