#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <numeric>
#include "graph.h"


std::vector<int> low_points_risk(Graph<int>& graph) {

    std::vector<int> low_points {};

    for(int i = 0; i < graph.size(); i++) {
        auto node_ptr = graph.get(i);
        if(auto node = node_ptr.lock()) {
            if(std::all_of(node->edges.begin(), node->edges.end(), [&](auto& nbhr){
                if(auto nbhr_ptr = nbhr.lock()) {
                    return (nbhr_ptr->data > node->data);
                }
                else {
                    std::cerr << "Unable to lock node" << std::endl;
                    return false;
                }
             })) {
                 low_points.push_back(node->data);
             }
        }
        else {
            std::cerr << "Unable to lock node" << std::endl;
        }
    }
    return low_points;
}


int main() {

    Graph<int> graph;

    std::ifstream input {"input.txt"};
    std::string line;
    int line_count = 0;

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
                }
            }
            else {
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

    auto low = low_points_risk(graph);

    auto sum = std::accumulate(low.begin(), low.end(), low.size());

    std::cout <<  "Sum of risk: " << sum << std::endl;


    return 0;
}