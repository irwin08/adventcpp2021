// Adapted from day 9


#include <vector>
#include <memory>

template<class T>
struct Node {
    std::vector<std::weak_ptr<Node<T>>> edges;
    T data;
    bool energized = false;

    Node(T data) : data{data}, edges{} { }

    void energize() {
        if(data < 9 && data > 0) {
            data++;
        }
        else if(data == 9) {
            data = 0;
            energized = true;
            for(auto nbhr : edges) {
                if(auto nbhr_node = nbhr.lock()) {
                    nbhr_node->energize();
                }
                else {
                    std::cerr << "Could not lock pointer" << std::endl;
                }
            }
        }
        else if(data == 0) {
            //if already energized, do nothing
            if(!energized) {
                data++;
            }
        }
    }

    void deenergize() {
        energized = false;
    }
};


//basically a wrapper for a vector that you can't remove nodes from
template<class T>
class Graph {
    public:
        void add_node(T data) {
            Node new_node {data};
            nodes.push_back(std::make_shared<Node<T>>(new_node));
        }

        std::weak_ptr<Node<T>> get(std::size_t i) {
            auto ret = std::weak_ptr<Node<T>>{};
            ret = nodes[i];
            return ret;
        }

        std::shared_ptr<Node<T>> operator[](int index) {
            return nodes[index];
        }

        int size() {
            return nodes.size();
        }

        void advance() {
            for(auto node_ptr : nodes) {
                node_ptr->deenergize();
            }
            for(auto node_ptr : nodes) {
                node_ptr->energize();
            }
        }

        void print(int num_of_col) {
            int count = 0;
            for(auto node_ptr : nodes) {
                if(count == num_of_col) {
                    count = 0;
                    std::cout << std::endl;
                }

                std::cout << node_ptr->data;
                count++;
            }
            std::cout << std::endl;
        }

        int count_flashes() {
            int count = 0;
            for(auto node_ptr : nodes) {
                if(node_ptr->data == 0) {
                    count++;
                }
            }
            return count;
        }

    private:
        std::vector<std::shared_ptr<Node<T>>> nodes;
};