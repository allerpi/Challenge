#ifndef _GRAPH_H_
#define _GRAPH_H_

#include<iostream> 
#include <list>
#include <vector>
#include <queue>
#include <stack>

template <class T>
class GraphVertex
{
private:
    T val;
    std::vector<int> adj;
public: 
    ~GraphVertex() {};
    GraphVertex() {};
    GraphVertex(T _val) {val = _val;};

    T get_val() {return val;};
    void set_val(T _val) {val = _val;};

    std::vector<int> get_adj() {return adj;};
    void add_to_adj(int idx) {adj.push_back(idx);};
};

template <class T>
class Graph
{
private:
    std::vector<GraphVertex<T> > nodes;
    bool is_directed;

public:
    ~Graph() {};
    Graph() { is_directed=false; };
    Graph(bool is_it_directed) { is_directed = is_it_directed; };

    void add_node(T val) {
        GraphVertex<T> node(val);
        nodes.push_back(node);
    };

    void add_edge(int src, int dst) {
        nodes[src].add_to_adj(dst);
        if (!is_directed)
            nodes[dst].add_to_adj(src);
    };

    void BFS(int start_vertex) {
        std::queue<int> searching;
        std::vector<bool> visited (nodes.size(), false);
        std::vector<int> temp;

        searching.push(start_vertex);

        while(!searching.empty()) {
            // move on to next vertex in searching
            start_vertex = searching.front();
            searching.pop();
            visited[start_vertex] = true;
            
            // print vertex
            std::cout << nodes[start_vertex].get_val() << " ";

            // add neighbours
            temp = nodes[start_vertex].get_adj();
            for(int i = 0; i < temp.size(); i++) {
                // make sure vertex hasn't been visited
                if(!visited[temp[i]]) {
                    searching.push(temp[i]);

                    // mark as visited, so neighbours aren't added many times
                    visited[temp[i]] = true;
                }
            }
        }

        std::cout << std::endl;
    };

    void DFS(int start_vertex) {
        std::stack<int> searching;
        std::vector<int> visited (nodes.size(), false);
        std::vector<int> temp;
        
        searching.push(start_vertex);

        while(!searching.empty()) {
            // move on to next vertex in searching
            start_vertex = searching.top();
            searching.pop();
            visited[start_vertex] = true;
            
            // print vertex
            std::cout << nodes[start_vertex].get_val() << " ";

            // add neighbours
            temp = nodes[start_vertex].get_adj();
            for(int i = 0; i < temp.size(); i++) {
                // make sure vertex hasn't been visited
                if(!visited[temp[i]]) {
                    searching.push(temp[i]);

                    // mark as visited, so neighbours aren't added many times
                    visited[temp[i]] = true;
                }
            }
        }

        std::cout << std::endl;
    }
    
    // find node with the most neighbours
    T most_neighbours() {
        int max_neighbours = 0;
        int max_node = 0;
        
        for (int i = 0; i < nodes.size(); i++) {
            if(nodes[i].get_adj().size() > max_neighbours) {
                max_neighbours = int(nodes[i].get_adj().size());
                max_node = i;
            }
        }
        
        return nodes[max_node].get_val();
    }
    
    // only applies for directed graphs, amount of graphs pointing to target_node
    int appearances(int target_node) {
        int count = 0;
        
        for(int i = 0; i < nodes.size(); i++) {
            vector<int> conn = nodes[i].get_adj();
            // check if current node has target_node as a neighbour
            // make sure target_node's connections to itself aren't counted
            if(i != target_node && std::find(conn.begin(), conn.end(), target_node) != conn.end()) {
                count++;
            }
        }
        
        return count;
    }
    
    GraphVertex<T> get_node(int i) { return nodes[i]; }
    
    
};

#endif
