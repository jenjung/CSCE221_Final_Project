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
    struct edge{
        size_t source;
        size_t destination;
        double weight;

        edge(size_t src, size_t dest, double w): source(src), destination(dest), weight(w){

        }
    };
    // TODO(student): implement graph
    struct vertex{
        size_t id;
        std::list<edge> connectedEdges;

        vertex(std::list<edge> ce, size_t ID): id(ID), connectedEdges(ce){

        }
    };
    size_t edgeCount;
    std::vector<vertex*> vertex_list;

public:
    // Task 1
    Graph(): edgeCount(0), vertex_list(0){

    };

    Graph(const Graph& other){
        edgeCount=other.edgeCount;
        vertex_list=other.vertex_list;
    };

    Graph& operator=(const Graph& other){
        if(this!=&other){
            edgeCount=other.edgeCount;
            vertex_list=other.vertex_list;
        }
        return *this;
    };

    ~Graph(){
        edgeCount=0;
    };

    size_t vertex_count() const{
        return vertex_list.size();
    };

    size_t edge_count() const{
        return edgeCount;
    };

    bool contains_vertex(size_t id) const{
        for(auto& v : vertex_list){
            if(v->id==id){
                return true;
            }
        }
        return false;
    };

    bool contains_edge(size_t src, size_t dest) const{
        for(auto& v : vertex_list){
            for(auto& e : v->connectedEdges){
                if(e.source==src&&e.destination==dest){
                    return true;
                }
            }
        }
        return false;
    };

    double cost(size_t src, size_t dest) const{
        if(contains_edge(src,dest)==false){
            return INFINITY;
        }

        vertex* source;
        for(auto& v : vertex_list){
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

    // na
    bool add_vertex(size_t id){
        if (contains_vertex(id)==true){
            return false;
        }

        std::list<edge> newedge;
        vertex* newVertex = new vertex(newedge, id);
        vertex_list.push_back(newVertex);
        return true;

    };

    bool add_edge(size_t src, size_t dest, double weight=1){
        if(contains_vertex(src)==false||contains_vertex(dest)==false||contains_edge(src,dest)==true){
            return false;
        }

        vertex* source;
        for(auto& v : vertex_list){
            if(v->id==src){
                source = v;
            }
        }

        edge newEdge = edge(src, dest, weight);
        source->connectedEdges.push_back(newEdge);
        ++edgeCount;
        return true;
    };

    //unni
    bool remove_vertex(size_t id);
    bool remove_edge(size_t src, size_t dest);

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
