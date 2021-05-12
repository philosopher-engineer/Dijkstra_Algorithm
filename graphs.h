#ifndef GRAPHS_H
#define GRAPHS_H

#include <stdio.h>
#include <stdlib.h>

/* Service definitions */
typedef enum {
    FALSE = 0,
    TRUE
} bool_t;

typedef enum {
    RETURN_OK = 1,
    RETURN_NOK
} return_t;

/* Graph definitions */

typedef int graph_vertex_id_t;
typedef int graph_edge_weight_t;
typedef int graph_vertex_degree_t;

typedef struct {
    graph_vertex_id_t graph_vertex_id;
    graph_edge_weight_t graph_edge_weight;
} adjacent_edge_t;

typedef struct adjacent_edge_node_t{
    adjacent_edge_t adjacent_edge;
    struct adjacent_edge_node_t *next_node;
} adjacent_edge_node_t;

typedef struct {
    adjacent_edge_node_t *head;
    adjacent_edge_node_t *tail;
} adjacency_list_t;

typedef struct {
    graph_vertex_id_t graph_vertex_id;
    graph_vertex_degree_t graph_vertex_degree;
    adjacency_list_t adjacency_list;
} graph_vertex_t;

typedef graph_vertex_t* graph_vertices_table_t;

typedef struct {
    int nodes;
    int edges;
    graph_vertices_table_t graph_vertices_table;
} graph_t;

typedef graph_t* graph;

/***************************************/

/* Public Interfaces */

graph GRAPH_create_empty_graph(int vertices); /* Creates/Initializes a graph with vertices and zero edges */

void GRAPH_add_edge(graph g, graph_vertex_id_t source, graph_vertex_id_t target, graph_edge_weight_t edge_weight);
int  GRAPH_get_number_of_vertices(graph g);
int  GRAPH_get_number_of_edges(graph g);
void GRAPH_destroy(graph g);

void GRAPH_set_node_degree(graph g, graph_vertex_degree_t* degree_arr);
void GRAPH_print_node_degree(graph g);

#endif
