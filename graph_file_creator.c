#include "graph_file_creator.h"

static char *get_token(char *str, char *token);
static graph create_empty_graph_read_from_file(FILE *fp);
static void add_edges_in_graph_read_from_file(FILE *fp, graph G);

static char *get_token(char *str, char *token) {
    int index = 0;
    while (str[index] != ',' && str[index] != '\n') {
        token[index] = str[index];
        ++index;
    }

    token[index] = '\0';

    if (str[index] == '\n') {
        return NULL;
    }

    return (str + index + 1);
}


static graph create_empty_graph_read_from_file(FILE *fp) {

    char str[40];
    fgets(str, 40, fp);

    char token[20];
    get_token(str, token);
    int vertices = atoi(token);

    return GRAPH_create_empty_graph(vertices);
}

static void add_edges_in_graph_read_from_file(FILE *fp, graph G) {
    int edge_info[] = {0,0,0};
    int i;
    char str[40];

    while (fgets(str, 40, fp)) {
        i = 0;
        char token[20];
        char *sub_name = get_token(str, token);
        edge_info[0] = atoi(token);

        while (sub_name) {
            sub_name = get_token(sub_name, token); // to go on
            edge_info[++i] = atoi(token);
        }

        GRAPH_add_edge(G, edge_info[0], edge_info[1], edge_info[2]);
    }
}

/*********** Public Interfaces ************/

graph GRAPH_FILE_CREATOR_create_graph(FILE *fp) {
    if (!fp) {
        return NULL;
    }

    graph G = create_empty_graph_read_from_file(fp);

    if (!G) {
        return NULL;
    }

    add_edges_in_graph_read_from_file(fp, G);
    return G;
}
