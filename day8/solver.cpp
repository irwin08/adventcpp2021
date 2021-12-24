#include "solver.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <cmath>



Solver::Solver(std::vector<std::string> signals, std::vector<std::string> output) {
    this->signals = signals;
    this->output = output;


    for(auto signal : signals) {
        if(signal.length() == 2)
            one = signal;
        else if(signal.length() == 3)
            seven = signal;
        else if(signal.length() == 4)
            four = signal;
        else if(signal.length() == 7)
            eight = signal;
    }

    std::vector<std::string *> uniques {&one, &four, &seven, &eight};

    if(std::ranges::any_of(uniques, [](auto unique){ return *unique == "";})) {
        std::cerr << "Error: Malformed data input. Cannot find 1,4,7 & 8!" << std::endl;
        std::terminate();
    }

    Digit zero;
    zero.top = true;
    zero.top_right = true;
    zero.top_left = true;
    zero.bottom_right = true;
    zero.bottom_left = true;
    zero.bottom = true;
    displays.push_back(zero);

    Digit one;
    one.top_right = true;
    one.bottom_right = true;
    displays.push_back(one);

    Digit two;
    two.top = true;
    two.top_right = true;
    two.middle = true;
    two.bottom_left = true;
    two.bottom = true;
    displays.push_back(two);

    Digit three;
    three.top = true;
    three.top_right = true;
    three.middle = true;
    three.bottom_right = true;
    three.bottom = true;
    displays.push_back(three);

    Digit four;
    four.top_left = true;
    four.middle = true;
    four.top_right = true;
    four.bottom_right = true;
    displays.push_back(four);

    Digit five;
    five.top = true;
    five.top_left = true;
    five.middle = true;
    five.bottom_right = true;
    five.bottom = true;
    displays.push_back(five);

    Digit six;
    six.top = true;
    six.top_left = true;
    six.middle = true;
    six.bottom_right = true;
    six.bottom_left = true;
    six.bottom = true;
    displays.push_back(six);

    Digit seven;
    seven.top = true;
    seven.top_right = true;
    seven.bottom_right = true;
    displays.push_back(seven);

    Digit eight;
    eight.top = true;
    eight.top_left = true;
    eight.top_right = true;
    eight.middle = true;
    eight.bottom_right = true;
    eight.bottom_left = true;
    eight.bottom = true;
    displays.push_back(eight);

    Digit nine;
    nine.top = true;
    nine.top_left = true;
    nine.top_right = true;
    nine.middle = true;
    nine.bottom_right = true;
    nine.bottom = true;
    displays.push_back(nine);
}


std::vector<std::vector<char>> permutations(std::vector<char> set, int size) {
    /*if(size == 1) {
        return std::vector<std::vector<char>>{set};
    }

    std::vector<std::vector<char>> perms = {};

    for(int i = 0; i < size; i++) {
        auto new_perms = permutations(set, size-1);
        //std::move(new_perms.begin(), new_perms.end(), std::back_inserter(perms));
        perms.insert(perms.end(), new_perms.begin(), new_perms.end());

        if ((size % 2) == 0) {
            //even
            std::swap(set[i], set[size-1]);
        }
        else {
            //odd
            std::swap(set[0], set[size-1]);
        }
    }*/

    std::vector<std::vector<char>> perms = {};

    do {
        perms.push_back(set);
    } while(std::next_permutation(set.begin(), set.end()));

    return perms;
}


int Solver::solve() {

    //brute force approach
    //randomly assign each wire to a digit section. Then check if all signals produce valid numbers. Assume this is a unique solution
    // bottom, bottom_left, bottom_right, middle, top_left, top_right, top
    std::vector<char> sections {'a', 'b', 'c', 'd', 'e', 'f', 'g'};

    auto perms = permutations(sections, sections.size());

    auto correct_perm = std::vector<char>{};




    for(auto perm : perms) {


        bool correct = true;
        for(auto sig : signals) {
            // check if each signal corresponds to display
            Digit dig_attempt;
            if(sig.find(std::string(1, perm[0])) != std::string::npos) {
                dig_attempt.bottom = true;
            }
            if(sig.find(std::string(1,perm[1])) != std::string::npos) {
                dig_attempt.bottom_left = true;
            }
            if(sig.find(std::string(1,perm[2])) != std::string::npos) {
                dig_attempt.bottom_right = true;
            }
            if(sig.find(std::string(1,perm[3])) != std::string::npos) {
                dig_attempt.middle = true;
            }
            if(sig.find(std::string(1,perm[4])) != std::string::npos) {
                dig_attempt.top_left = true;
            }
            if(sig.find(std::string(1,perm[5])) != std::string::npos) {
                dig_attempt.top_right = true;
            }
            if(sig.find(std::string(1,perm[6])) != std::string::npos) {
                dig_attempt.top = true;
            }

            correct = (std::find(displays.begin(), displays.end(), dig_attempt) != displays.end());

            if(!correct) {
                break;
            }
        }
        if(!correct)
            continue;
        correct_perm = perm;
    }

    std::vector<int> nums;

    for(auto out : output) {
        Digit found_digit;
        
        for(int i = 0; i < out.length(); i++) {

            if(out[i] == correct_perm[0]) {
                found_digit.bottom = true;
            }
            if(out[i] == correct_perm[1]) {
                found_digit.bottom_left = true;
            }
            if(out[i] == correct_perm[2]) {
                found_digit.bottom_right = true;
            }
            if(out[i] == correct_perm[3]) {
                found_digit.middle = true;
            }
            if(out[i] == correct_perm[4]) {
                found_digit.top_left = true;
            }
            if(out[i] == correct_perm[5]) {
                found_digit.top_right = true;
            }
            if(out[i] == correct_perm[6]) {
                found_digit.top = true;
            }
        }

        for(int i = 0; i < displays.size(); i++) {
            if(displays[i] == found_digit) {
                nums.push_back(i);
            }
        }
    }

    int final_num = 0;

    for(int i = 0; i < nums.size(); i++) {
        final_num += (nums[i] * (pow(10,(nums.size()-1)-i)));
    }

    return final_num;
}
