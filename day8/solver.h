#include <string>
#include <vector>


class Digit {

public:
    bool top = false;
    bool bottom = false;
    bool top_left = false;
    bool top_right = false;
    bool bottom_left = false;
    bool bottom_right = false;
    bool middle = false;

    friend bool operator==(const Digit& d1, const Digit& d2) {
        return ((d1.top == d2.top) && (d1.bottom == d2.bottom) && (d1.top_left == d2.top_left) && (d1.top_right == d2.top_right) &&
         (d1.bottom_left == d2.bottom_left) && (d1.bottom_right == d2.bottom_right) && (d1.middle == d2.middle)); 
    }
};


class Solver {
    
    public:
        Solver(std::vector<std::string> signals, std::vector<std::string> output);

        //returns decoded output
        int solve();


    private:
        
        std::vector<std::string> signals;
        std::vector<std::string> output;

        std::vector<Digit> displays;

        std::string one;
        std::string four;
        std::string seven;
        std::string eight;
};