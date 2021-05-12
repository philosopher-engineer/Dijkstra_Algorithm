#include "dijkstra.h"

static void dijkstra_algo_node_table_init(algo_node_ptr_t node_table, graph_vertex_id_t source, int vertices);
static void dijkstra_algo_recursively_print_optimal_subpath(algo_node_ptr_t node_table, graph_vertex_id_t source, graph_vertex_id_t target);

static void dijkstra_algo_node_table_init(algo_node_ptr_t node_table, graph_vertex_id_t source, int vertices) {
    int i = 0;
    if (node_table) {
        for (i = 0; i < vertices; ++i) {
            if (i == source - 1) {
                node_table[i].cost_from_source = 0;
                node_table[i].previous_node_in_path = source;
            }
            else {
                node_table[i].cost_from_source = INFINITY;
                node_table[i].previous_node_in_path = UNDEFINED;
            }
            node_table[i].graph_vertex_id = i + 1;
            node_table[i].isVisited = FALSE;
        }
    }
}

/* Suboptimality principle according to Dynamic programming rule "Each subset of the (optimal) solution is the optimal solution of every subproblem" */
static void dijkstra_algo_recursively_print_optimal_subpath(algo_node_ptr_t node_table, graph_vertex_id_t source, graph_vertex_id_t target) {
    if (node_table) {
        if (target == source) {
            return;
        }
        else {
            dijkstra_algo_recursively_print_optimal_subpath(node_table, source, node_table[target - 1].previous_node_in_path);
            printf("%d -> ", node_table[target - 1].previous_node_in_path);
        }
    }
}

/* Public Interfaces for Dijkstra's Algorithm */

algo_node_ptr_t DIJKSTRA_algo_node_table_create(graph_vertex_id_t source, int vertices) {
    if (vertices < 0) {
        puts("Invalid number of vertices. Should be positive!");
        return NULL;
    }

    algo_node_ptr_t node_table;

    node_table = (algo_node_ptr_t)malloc(vertices*sizeof(algo_record_item_t));
    dijkstra_algo_node_table_init(node_table, source, vertices);

    return node_table;
}

void DIJKSTRA_algo_visit_node(graph_vertex_id_t node, graph G, algo_node_ptr_t node_table) {
    /* Access node's neighbours */
    adjacent_edge_node_t *listCurrent = G->graph_vertices_table[node - 1].adjacency_list.head;

    if (!node_table[node - 1].isVisited) {
        while (listCurrent) {
            if (!node_table[listCurrent->adjacent_edge.graph_vertex_id - 1].isVisited &&
                    node_table[node - 1].cost_from_source + listCurrent->adjacent_edge.graph_edge_weight <
                    node_table[listCurrent->adjacent_edge.graph_vertex_id - 1].cost_from_source) {
                // Update neighbor cost from source
                node_table[listCurrent->adjacent_edge.graph_vertex_id - 1].cost_from_source =
                        node_table[node - 1].cost_from_source + listCurrent->adjacent_edge.graph_edge_weight;
                // Update previous node in optimal path
                node_table[listCurrent->adjacent_edge.graph_vertex_id - 1].previous_node_in_path = node;
            }
            listCurrent = listCurrent->next_node;
        }
        printf("Now node %d is considered as VISITED\n", node);
        node_table[node - 1].isVisited = TRUE;
    }
}

graph_vertex_id_t DIJKSTRA_algo_find_best_neighbor_of_visited_node(graph_vertex_id_t node, graph G, algo_node_ptr_t node_table) {

    if (!node_table[node - 1].isVisited) {
        puts("Cannot choose best neighbour of an unvisited node!!!");
        return -1;  // Error result - TODO: Create an Error handling enum
    }
    adjacent_edge_node_t *listCurrent = G->graph_vertices_table[node - 1].adjacency_list.head;
    cost_from_source_t min_cost = INFINITY;
    graph_vertex_id_t best_neighbor_id;

    while (listCurrent) {
        if (!node_table[listCurrent->adjacent_edge.graph_vertex_id - 1].isVisited) {
            if (node_table[listCurrent->adjacent_edge.graph_vertex_id - 1].cost_from_source < min_cost) {
                min_cost = node_table[listCurrent->adjacent_edge.graph_vertex_id - 1].cost_from_source;
                best_neighbor_id = listCurrent->adjacent_edge.graph_vertex_id;
            }
            listCurrent = listCurrent->next_node;
        }
        else {
            listCurrent = listCurrent->next_node;
        }
    }
    printf("Best node id choosen is %d\n",best_neighbor_id);
    return best_neighbor_id;
}

void DIJKSTRA_algo_print_path(algo_node_ptr_t node_table, graph_vertex_id_t source, graph_vertex_id_t target) {
    if (node_table) {
        dijkstra_algo_recursively_print_optimal_subpath(node_table, source, target);
        /* Finally print target node for full path */
        printf("%d\n", target);
    }
}
