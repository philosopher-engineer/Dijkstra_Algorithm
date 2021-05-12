#include "graphs.h"

static bool_t graph_is_vertex_in_adjacency_list(adjacency_list_t adj_list, graph_vertex_id_t id);
static return_t graph_add_vertex_in_adjacency_list(adjacency_list_t* adj_list_ref, graph_vertex_id_t id, graph_edge_weight_t edge_weight);
static void graph_destroy_adjacency_list(adjacency_list_t* adj_list_ref);
static void graph_vertices_table_init(graph_vertices_table_t g, int vertices);

static bool_t graph_is_vertex_in_adjacency_list(adjacency_list_t adj_list, graph_vertex_id_t id) {
    if (!adj_list.head) {
        return FALSE;
    }
    adjacent_edge_node_t *current = adj_list.head;
    bool_t ret = FALSE;

    while (current) {
        if (current->adjacent_edge.graph_vertex_id == id) {
            ret = TRUE;
            break;
        }
        current = current->next_node;
    }
    return ret;
}

static return_t graph_add_vertex_in_adjacency_list(adjacency_list_t* adj_list_ref, graph_vertex_id_t id, graph_edge_weight_t edge_weight) {

    if (!graph_is_vertex_in_adjacency_list(*adj_list_ref, id)) {
        /* Build new node */
        adjacent_edge_node_t* new_node = (adjacent_edge_node_t*)malloc(sizeof(adjacent_edge_node_t));
        new_node->adjacent_edge.graph_vertex_id = id;
        new_node->adjacent_edge.graph_edge_weight = edge_weight;
        new_node->next_node = NULL;

        if (!adj_list_ref->head) {
            adj_list_ref->head = new_node;
            adj_list_ref->tail = new_node;
        }
        else {
            adj_list_ref->tail->next_node = new_node;
            adj_list_ref->tail = new_node;
        }
        return RETURN_OK;
    }
    else {
        puts("This edge has already been added. Graph does not support multiple edges between 2 nodes.");
    }
    return RETURN_NOK;
}

static void graph_destroy_adjacency_list(adjacency_list_t* adj_list_ref) {
    if (!adj_list_ref) {
        puts("NULL list object - Nothing to destroy");
        return;
    }
    if (!adj_list_ref->head) {
        puts("Empty list object - Nothing to destroy");
        return;
    }
    adjacent_edge_node_t* current = adj_list_ref->head;
    while (current) {
        adj_list_ref->head = current->next_node;
        free(current);
        current = adj_list_ref->head;
    }
}

static void graph_vertices_table_init(graph_vertices_table_t g, int vertices) {
    int i = 0;
    if (g) {
        for (i = 0; i < vertices; ++i) {
            g[i].graph_vertex_id = i + 1;
            g[i].graph_vertex_degree = 0;
            g[i].adjacency_list.head = NULL;
            g[i].adjacency_list.tail = NULL;
        }
    }
}

/********* Public Interfaces ********/

graph GRAPH_create_empty_graph(int vertices) {
    if (vertices < 0) {
        puts("Invalid number of vertices. Should be positive!");
        return NULL;
    }
    graph g = (graph)malloc(sizeof(graph_t));

    g->nodes = vertices;
    g->edges = 0;

    /* Allocate memory for vertices table */
    g->graph_vertices_table = (graph_vertices_table_t)malloc(vertices * sizeof(graph_vertex_t));
    if (g->graph_vertices_table) {
        /* Initialize table */
        graph_vertices_table_init(g->graph_vertices_table, vertices);
    }

    return g;
}

void GRAPH_add_edge(graph g, graph_vertex_id_t source, graph_vertex_id_t target, graph_edge_weight_t edge_weight) {
    if (!g) {
        puts("Invalid graph object, has not been created in memory!!!");
        return;
    }

    if (graph_add_vertex_in_adjacency_list(&g->graph_vertices_table[source-1].adjacency_list, target, edge_weight) == RETURN_OK) {
        g->graph_vertices_table[source-1].graph_vertex_degree ++;
        g->edges ++;
    }
}

int GRAPH_get_number_of_vertices(graph g) {
    if (!g) {
        puts("Invalid graph object, has not been created in memory!!!");
        return -1;
    }
    return g->nodes;
}

int GRAPH_get_number_of_edges(graph g) {
    if (!g) {
        puts("Invalid graph object, has not been created in memory!!!");
        return -1;
    }
    return g->edges;
}

void GRAPH_destroy(graph g) {
    int i;
    if(g) {
        for (i = 0; i < g->nodes; ++i) {
            graph_destroy_adjacency_list(&g->graph_vertices_table[i].adjacency_list);
        }
        free(g->graph_vertices_table);
    }
    free(g);
}


