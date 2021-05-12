#include "dijkstra.h"

typedef struct {
    algo_node_ptr_t algo_node_table;
    graph G;
    graph_vertex_id_t source;
    graph_vertex_id_t target;
} dijkstra_calculator_t;

void DIJKSTRA_CALC_set_source_id(dijkstra_calculator_t *d_calculator, graph_vertex_id_t source_id);
void DIJKSTRA_CALC_set_target_id(dijkstra_calculator_t *d_calculator, graph_vertex_id_t target_id);
void DIJKSTRA_CALC_set_graph_and_init(dijkstra_calculator_t *d_calculator, graph G);
void DIJKSTRA_CALC_run(dijkstra_calculator_t *d_calculator);

void DIJKSTRA_CALC_output_results(const dijkstra_calculator_t *d_calculator);
void DIJKSTRA_CALC_clean_sources(dijkstra_calculator_t *d_calculator);

