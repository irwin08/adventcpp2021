#include <vector>
#include <memory>

template<class T>
struct Node {
    std::vector<std::weak_ptr<Node<T>>> edges;
    T data;

    Node(T data) : data{data}, edges{} { }
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
    private:
        std::vector<std::shared_ptr<Node<T>>> nodes;
};