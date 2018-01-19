//
//  main.c
//  route-check
//
//  Created by Kerry Meyer on 1/12/18.
//  Copyright © 2018 Kerry Meyer. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
 * An array of graph_node_t instances contains an "adjacent neighbor" list head for
 * each of the nodes in the graph. The "adjacent neighbor" list head contains the
 * "parent" node number (same as the array index) and a pointer to the adjacency
 * entry for the first neighboring node. This, in turn contains the node number for
 * the adjacent node and a pointer to the adjacendy entry for the next neighbor of
 * the parent node. Both the list head and the adjacency entry
 * are specified by a graph_node_t struct.
 */
#define NUMBER_OF_NODES 10

typedef struct graph_node_t_ {
    unsigned node_num;
    struct graph_node_t_ *next_neighbor;
} graph_node_t;

graph_node_t graph_array[NUMBER_OF_NODES];
char inbuf[80];
char maybe_quit;
unsigned source;
unsigned destination;

void graph_init(void);
bool is_reachable(unsigned source, unsigned destination);


int main(int argc, const char * argv[]) {
    // insert code here...
    bool reachable;

    graph_init();

    while (true) {
    
        printf("Enter source node to check reachability or 'Q' to quit.\n");
    
        fgets(inbuf, 80, stdin);
        sscanf(inbuf, "%c", &maybe_quit);
        if (maybe_quit == 'Q') {
            printf("Exiting ...\n");
            return(0);
        } else {
            if (sscanf(inbuf, "%u", &source) != 1) {
                printf("Input error. Restarting input collection\n");
                continue;
            }
            printf("Enter destination node to check reachability.\n");
            fgets(inbuf, 80, stdin);
            if (sscanf(inbuf, "%u", &destination) != 1) {
                printf("Input error. Restarting input collection\n");
                continue;
            }
        }
        
        reachable = is_reachable(source, destination);
    
        printf("Node %u is%s reachable from node %u\n", destination, reachable ? "" : " not", source);
    }
    
    return 1;
}

void graph_init (void)
{
    graph_node_t *curr_neighbor, *next_neighbor;
    
    graph_array[0].node_num = 0;
    curr_neighbor = malloc(sizeof(graph_node_t));
    graph_array[0].next_neighbor = curr_neighbor;
    curr_neighbor->node_num = 1;
    next_neighbor = malloc(sizeof(graph_node_t));
    curr_neighbor->next_neighbor = next_neighbor;
    curr_neighbor = next_neighbor;
    curr_neighbor->node_num = 2;
    next_neighbor = malloc(sizeof(graph_node_t));
    curr_neighbor->next_neighbor = next_neighbor;
    curr_neighbor = next_neighbor;
    curr_neighbor->node_num = 7;
    curr_neighbor->next_neighbor = NULL;

    graph_array[1].node_num = 1;
    curr_neighbor = malloc(sizeof(graph_node_t));
    graph_array[1].next_neighbor = curr_neighbor;
    curr_neighbor->node_num = 3;
    next_neighbor = malloc(sizeof(graph_node_t));
    curr_neighbor->next_neighbor = next_neighbor;
    curr_neighbor = next_neighbor;
    curr_neighbor->node_num = 4;
    curr_neighbor->next_neighbor = NULL;

    graph_array[2].node_num = 2;
    curr_neighbor = malloc(sizeof(graph_node_t));
    graph_array[2].next_neighbor = curr_neighbor;
    curr_neighbor->node_num = 9;
    curr_neighbor->next_neighbor = NULL;

    graph_array[3].node_num = 3;
    graph_array[3].next_neighbor = NULL;

    graph_array[4].node_num = 4;
    curr_neighbor = malloc(sizeof(graph_node_t));
    graph_array[4].next_neighbor = curr_neighbor;
    curr_neighbor->node_num = 5;
    curr_neighbor->next_neighbor = NULL;

    graph_array[5].node_num = 5;
    graph_array[5].next_neighbor = NULL;
    
    graph_array[6].node_num = 6;
    curr_neighbor = malloc(sizeof(graph_node_t));
    graph_array[6].next_neighbor = curr_neighbor;
    curr_neighbor->node_num = 7;
    curr_neighbor->next_neighbor = NULL;
    
    graph_array[7].node_num = 7;
    curr_neighbor = malloc(sizeof(graph_node_t));
    graph_array[7].next_neighbor = curr_neighbor;
    curr_neighbor->node_num = 8;
    next_neighbor = malloc(sizeof(graph_node_t));
    curr_neighbor->next_neighbor = next_neighbor;
    curr_neighbor = next_neighbor;
    curr_neighbor->node_num = 9;
    curr_neighbor->next_neighbor = NULL;

    graph_array[8].node_num = 8;
    graph_array[8].next_neighbor = NULL;
    
    graph_array[9].node_num = 9;
    graph_array[9].next_neighbor = NULL;
}

bool is_reachable (unsigned source, unsigned destination)
{
    graph_node_t *curr_neighbor;
    
    /*
     * Trivial case: source and destination are the same.
     */
    if (source == destination) {
        return(true);
    }
    
    /*
     * Recursively check reachability of the destination via neighbor nodes.
     */
    curr_neighbor = graph_array[source].next_neighbor;
    
    while (curr_neighbor) {
    
        /*
         * Is this neighbor the destination node?
         */
        if (curr_neighbor->node_num == destination) {
            return(true);
        }
        
        /*
         * Is the destination reachable via this neighbor?
         */
        if (is_reachable(curr_neighbor->node_num, destination)) {
                return(true);
        }
        
        /*
         * Try the next neighbor.
         */
        curr_neighbor = curr_neighbor->next_neighbor;
    }
    return (false);
}
