#include "dijkstra_calculator.h"

void DIJKSTRA_CALC_set_source_id(dijkstra_calculator_t *d_calculator, graph_vertex_id_t source_id) {
    d_calculator->source = source_id;
}

void DIJKSTRA_CALC_set_target_id(dijkstra_calculator_t *d_calculator, graph_vertex_id_t target_id) {
    d_calculator->target = target_id;
}

void DIJKSTRA_CALC_set_graph_and_init(dijkstra_calculator_t *d_calculator, graph G) {
    d_calculator->G = G;
    d_calculator->algo_node_table = DIJKSTRA_algo_node_table_create(d_calculator->source, G->nodes);
}

void DIJKSTRA_CALC_run(dijkstra_calculator_t *d_calculator) {
    graph_vertex_id_t currentNode = d_calculator->source;
    graph_vertex_id_t targetNode = d_calculator->target;
    algo_node_ptr_t algo_node_table = d_calculator->algo_node_table;
    graph G = d_calculator->G;

    while (currentNode != targetNode) {
        DIJKSTRA_algo_visit_node(currentNode, G, algo_node_table);
        currentNode = DIJKSTRA_algo_find_best_neighbor_of_visited_node(currentNode, G, algo_node_table);
    }
}

void DIJKSTRA_CALC_output_results(const dijkstra_calculator_t *d_calculator) {
    algo_node_ptr_t algo_node_table = d_calculator->algo_node_table;
    graph_vertex_id_t source = d_calculator->source;
    graph_vertex_id_t target = d_calculator->target;
    DIJKSTRA_algo_print_path(algo_node_table, source, target);
    printf("For target node cost from source is: %d\n", algo_node_table[target - 1].cost_from_source);
}

void DIJKSTRA_CALC_clean_sources(dijkstra_calculator_t *d_calculator) {
    algo_node_ptr_t algo_node_table = d_calculator->algo_node_table;

    if (algo_node_table) {
        free(algo_node_table);
    }
}
