#include <iostream>
#include <string> 
#include <fstream>
#include "graph.h"

int main() {



    Graph<int> graph;

    std::ifstream input {"input.txt"};
    std::string line;
    int line_count = 0;

    //graph construction taken from day 9
    while(std::getline(input, line)) {

        for(int i = 0; i < line.length(); i++) {
            
            if(i == 0) {
                graph.add_node(std::stoi(line.substr(i,1)));
                if(line_count != 0) {
                    if(auto ptr = graph.get(((line_count*line.length())+i)).lock(); auto ptr_2 = graph.get(((line_count-1)*line.length())+i).lock()) {
                        //add node from previous row as neighbor
                        ptr->edges.push_back(graph.get(((line_count-1)*line.length())+i));
                        ptr_2->edges.push_back(graph.get(((line_count*line.length())+i)));
                    }
                    else {
                        std::cerr << "Error: Could not lock pointer to node" << std::endl;
                    }
                    //add diagonal (top-left)
                    if(auto ptr = graph.get(((line_count*line.length())+i)).lock()) {
                        if(auto diag_ptr = graph.get(((line_count-1)*line.length())+(i+1)).lock()) {
                            ptr->edges.push_back(graph.get(((line_count-1)*line.length())+(i+1)));
                            diag_ptr->edges.push_back(graph.get(((line_count*line.length())+i)));
                        }
                        else {
                            std::cerr << "Error: Could not lock pointer to node" << std::endl;
                        }
                    }
                }
            }
            else {
                graph.add_node(std::stoi(line.substr(i,1)));
                if(line_count != 0) {
                    if(auto ptr = graph.get(((line_count*line.length())+i)).lock(); auto ptr_2 = graph.get(((line_count-1)*line.length())+i).lock()) {
                        //add node from previous row as neighbor
                        ptr->edges.push_back(graph.get(((line_count-1)*line.length())+i));
                        ptr_2->edges.push_back(graph.get(((line_count*line.length())+i)));

                        //add previous row diagonal as neighbor (top-left)
                        if(auto diag_ptr = graph.get(((line_count-1)*line.length())+(i-1)).lock()) {
                            ptr->edges.push_back(graph.get(((line_count-1)*line.length())+(i-1)));
                            diag_ptr->edges.push_back(graph.get(((line_count*line.length())+i)));
                        }
                        else {
                            std::cerr << "Error: Could not lock pointer to node" << std::endl;
                        }
                        //add top-right as neighbor (if i != (line.length()-1)
                        if(i != (line.length()-1)) {
                            if(auto diag_ptr = graph.get(((line_count-1)*line.length())+(i+1)).lock()) {
                                ptr->edges.push_back(graph.get(((line_count-1)*line.length())+(i+1)));
                                diag_ptr->edges.push_back(graph.get(((line_count*line.length())+i)));
                            }
                            else {
                                std::cerr << "Error: Could not lock pointer to node" << std::endl;
                            }
                        }
                    }
                    else {
                        std::cerr << "Error: Could not lock pointer to node" << std::endl;
                    }
                }
                if(auto ptr = graph.get((line_count*line.length())+(i-1)).lock(); auto ptr_2 = graph.get((line_count*line.length())+i).lock()) {
                    ptr->edges.push_back(graph.get((line_count*line.length())+i));
                    ptr_2->edges.push_back(graph.get((line_count*line.length())+(i-1)));    
                }
                else {
                    std::cerr << "Error: Could not lock pointer to node" << std::endl;
                }
            }
        }

        line_count++;
    }

    //part 1
    /*int count = 0;

    for(int i = 0; i < 100; i++) {
        graph.advance();
        count += graph.count_flashes();
    }

    std::cout << "Flashes: " << count << std::endl;*/

    bool sync = false;
    int round = 0;

    while(!sync) {
        graph.advance();
        if(graph.count_flashes() == 100)
            sync = true;
        round++;
    } 

    std::cout << "Sync at round " << round << std::endl;

    return 0;
}