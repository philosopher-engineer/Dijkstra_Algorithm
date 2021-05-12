#include "dijkstra_calculator.h"
#include "graph_file_creator.h"

int main() {

    FILE *fp = fopen("/tmp/graph.txt", "r");
    if (NULL == fp) {
        perror("Error in opening file");
        return -1;
    }

    graph G = GRAPH_FILE_CREATOR_create_graph(fp);

    printf("Number of vertices is %d\n", GRAPH_get_number_of_vertices(G));
    printf("Number of edges is %d\n", GRAPH_get_number_of_edges(G));

    graph_vertex_id_t source = 1;
    graph_vertex_id_t target = 5;

    dijkstra_calculator_t calculator;

    DIJKSTRA_CALC_set_source_id(&calculator, source);
    DIJKSTRA_CALC_set_target_id(&calculator, target);
    DIJKSTRA_CALC_set_graph_and_init(&calculator, G);
    DIJKSTRA_CALC_run(&calculator);
    DIJKSTRA_CALC_output_results(&calculator);
    DIJKSTRA_CALC_clean_sources(&calculator);

    GRAPH_destroy(G);
    fclose(fp);
	
    return 0;
}
