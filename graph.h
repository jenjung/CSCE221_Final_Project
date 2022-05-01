#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#include <iostream>
#include <queue>

class Graph {
private:
    // TODO(student): implement graph
    struct edge {
        size_t source;
        size_t destination;
        double weight;

        edge (size_t s, size_t d, double w) : source(s), destination(d), weight(w) {}
    };

    struct vertex {
        bool known;
        size_t distance;
        std::list<edge> connectedEdges;

        size_t id;
        vertex * path;

        vertex (std::list<edge> t = {}, size_t i = 0) : known(false), distance(), path(), id(i), connectedEdges() {
            for (auto & ele : t) {
                connectedEdges.push_back(ele);
            }
        }

        vertex (const vertex & v) : known(v.known), distance(v.distance), path(v.path), id(v.id), connectedEdges(v.connectedEdges) {};

        vertex & operator = (const vertex & v) {
            known = v.known;
            distance = v.distance;
            path = v.path;
            id = v.id;
            for (edge e : v.connectedEdges) {
                connectedEdges.push_back(e);
            }
            return * this;
        } 
    };

    size_t edgeCount;
    std::vector<vertex*> vertexList;

public:
    // Task 1
    Graph() : vertexList(), edgeCount(0) {};
    Graph(const Graph& other) : vertexList(), edgeCount(other.edgeCount) {
        for (vertex * v : other.vertexList) {
            vertexList.push_back(v);
        }
    };
    Graph& operator=(const Graph& other) {
        if (&other == this) {
            return *this;
        }
        edgeCount = other.edgeCount;
        vertex * temp;
        for (vertex * v : other.vertexList) {
            temp = new vertex(v->connectedEdges, v->id);
            vertexList.push_back(temp);
        }
        return *this;
    };
    ~Graph() {
        for (vertex * v : vertexList) {
            delete v;
        }
        edgeCount = 0;
    };

    size_t vertex_count() const {
        return vertexList.size();
    };
    size_t edge_count() const {
        return edgeCount;
    };

    bool contains_vertex(size_t id) const {
        for (vertex * v : vertexList) {
            if (v->id == id) {
                return true;
            }
        }
        return false;
    };
    bool contains_edge(size_t src, size_t dest) const {
        for (vertex * v : vertexList) {
            for (edge t : v->connectedEdges) {
                if (t.source = src && t.destination == dest) {
                    return true;
                }
            }
        }
        return false;
    };
    double cost(size_t src, size_t dest) const {
        if (contains_edge(src, dest) == false) {
            return INFINITY;
        }
        vertex* source;
        for(auto& v : vertexList){
            if(v->id==src){
                source = v;
            }
        }

        size_t w;
        for(auto& e : source->connectedEdges){
            if(e.destination==dest){
                w=e.weight;
            }
        }
        return w;
        
    };

    bool add_vertex(size_t id) {
        if (contains_vertex(id) == true) {
            return false;
        }
        std::list<edge> newEdge;
        vertex * tempVertex = new vertex(newEdge, id);
        vertexList.push_back(tempVertex);
        return true;
    };
    bool add_edge(size_t src, size_t dest, double weight=1) {
        if(contains_vertex(src)==false||contains_vertex(dest)==false||contains_edge(src,dest)==true){
            return false;
        }

        vertex* source;
        for(auto& v : vertexList){
            if(v->id==src){
                source = v;
            }
        }

        edge newEdge = edge(src, dest, weight);
        source->connectedEdges.push_back(newEdge);
        ++edgeCount;
        return true;
    };
    bool remove_vertex(size_t id) {
        if (contains_vertex(id) == false) {
            return false;
        }
        for (vertex * v : vertexList) {
            remove_edge(v->id, id);
        }
        std::vector<vertex *>::iterator it = vertexList.begin();
        while (it != vertexList.end()) {
            if ((*it)->id == id) {
                vertexList.erase(it);
                return true;
            }
            else {
                it++;
            }
        }
        return false;
    };
    bool remove_edge(size_t src, size_t dest) {
        if (contains_edge(src, dest) == false) {
            return false;
        }
        vertex * tempVertex;
        for (vertex * v : vertexList) {
            if (v->id == src) {
                tempVertex = v;
            }
        }
        std::list<edge>::iterator it = tempVertex->connectedEdges.begin();
        while (it != tempVertex->connectedEdges.end()) {
            if (it->destination == dest) {
                tempVertex->connectedEdges.erase(it);
                --edgeCount;
                return true;
            }
            else {
                ++ it;
            }
        }
        return false;
    };

    // Task 2
    void prim(size_t source_id);
    bool is_path(size_t id) const;
    void print_path(size_t dest_id, std::ostream& os=std::cout) const;

    // Task 3
    void dijkstra(size_t source_id);
    double distance(size_t id) const;
    void print_shortest_path(size_t dest_id, std::ostream& os=std::cout) const;
};

#endif  // GRAPH_H


// //erase function

// std::unordered_map<size_t, Vertex*> map;
// for (auto[v_id, v] : map) {
//     if (v_id == id) {
//         std::cout << v_id << std::endl;
//     }
// }

// delete map[id];
// map.erase(id);

// //easiest if there is a map of map
// std::unordered_map<size_t, Vertex*> vertices;
                    
// //                 src_id                    dest_id weight
// std::unordered_map<size_t, std::unordered_map<size_t, double>> edges;
