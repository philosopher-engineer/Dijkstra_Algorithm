#include "graphs.h"
#include <limits.h>

#define INFINITY INT_MAX
#define UNDEFINED 0

typedef int cost_from_source_t;

typedef struct {
    graph_vertex_id_t graph_vertex_id;
    cost_from_source_t cost_from_source;
    bool_t isVisited;
    graph_vertex_id_t previous_node_in_path;
} algo_record_item_t;

typedef algo_record_item_t* algo_node_ptr_t;

algo_node_ptr_t DIJKSTRA_algo_node_table_create(graph_vertex_id_t source, int vertices);

void DIJKSTRA_algo_visit_node(graph_vertex_id_t node, graph G, algo_node_ptr_t node_table);

graph_vertex_id_t DIJKSTRA_algo_find_best_neighbor_of_visited_node(graph_vertex_id_t node, graph G, algo_node_ptr_t node_table);

void DIJKSTRA_algo_print_path(algo_node_ptr_t node_table, graph_vertex_id_t source, graph_vertex_id_t target);
