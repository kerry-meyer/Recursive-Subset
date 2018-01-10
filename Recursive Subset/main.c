//
//  main.c
//  Recursive Subset
//
//  Created by Kerry Meyer on 12/28/17.
//  Copyright © 2017 Kerry Meyer. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define max_elements 10


typedef struct subset_t_ {
    int subset_count;
    int *subset_elements;
} subset_t;

void get_subsets(int *curr_set, int item_count, subset_t *all_subsets, int *howmany_subsets);

int main(int argc, const char * argv[]) {
    // insert code here...
    int main_set[max_elements];
    int items = 0;
    char add_one = 'N';
    int i, j;
    subset_t all_subsets[(1 << (max_elements)) - 1];
    int howmany_subsets = 0;
    char inbuf[80];
    
    
    /*
     * Get input for the main set.
     */
    while (items < max_elements) {
        printf("Add a main set element? ('Y' or 'N'; Up to %d more items can be added.\n",
               max_elements - items);
        fgets(inbuf, 80, stdin);
        sscanf(inbuf, "%c", &add_one);
        if (add_one == 'Y') {
            printf("Enter the next item\n");
            fgets(inbuf, 80, stdin);
            sscanf(inbuf, "%d", &main_set[items++]);
        } else {
            if (add_one != 'N') {
                printf("Invalid response %c (0x%x)\n", add_one, (int)add_one);
                continue;
            }
            break;
        }
    }
    
    if (!items) {
        printf("No items specified for the main set. Exiting.\n");
        return(0);
    } else {
        printf("%d items entered\n", items);
    }
    
    /*
     * Echo the resulting input set.
     */
    printf("Main set input completed. Listing items:\n\n");
    for (i = 0; i < items; i++) {
        printf("main_set[%d] = %d\n", i, main_set[i]);
    }
    
    /*
     * Fill in the subset list.
     */
    get_subsets(main_set, items, all_subsets, &howmany_subsets);
    
    /*
     * Print the subset list.
     */
    printf("List of Subsets:\n\n");
    for (i = 0; i < howmany_subsets; i++) {
        printf("Subset %d\n", i);
        for (j = 0; j < all_subsets[i].subset_count; j++) {
            if (j != (all_subsets[i].subset_count -1)) {
                printf("%d, ", all_subsets[i].subset_elements[j]);
            } else {
                printf("%d\n\n", all_subsets[i].subset_elements[j]);
            }
        }
    }
            
    return 0;
}

void get_subsets (int *curr_set, int item_count, subset_t *all_subsets, int *howmany_subsets)
{
    int old_saved_index, new_saved_index, curr_index;
    int subset_size;
    
    printf("get_subsets: input number of subsets = %d\n", *howmany_subsets);
    printf("item_count = %d\n", item_count);
    all_subsets[*howmany_subsets].subset_elements = malloc(sizeof(int));
    all_subsets[*howmany_subsets].subset_elements[0] = curr_set[0];
    all_subsets[*howmany_subsets].subset_count = 1;
    (*howmany_subsets)++;
    printf("After post-increment, howmany_subsets = %d\n", *howmany_subsets);
    if (item_count <= 1) {
        return;
    }
    
    /*
     * Add the list of all subsets of the current set excluding the first element,
     * but remember the starting point of the subset list to be generated. This will
     * be used to generate a list of sets containing each of the generated subsets
     * with the first member of the current set added as a member.
     */
    old_saved_index = *howmany_subsets;
    get_subsets(curr_set + 1, item_count - 1, all_subsets, howmany_subsets);
    
    /*
     * Add to the list all of the subsets containing the union of the first
     * element of the current set with each of the subsets listed in the previous
     * step.
     */
    new_saved_index = *howmany_subsets;
    for (curr_index = old_saved_index; curr_index < new_saved_index; curr_index++) {
        subset_size = all_subsets[curr_index].subset_count;
        all_subsets[*howmany_subsets].subset_elements = malloc((subset_size + 1) * sizeof(int));
        memcpy(all_subsets[*howmany_subsets].subset_elements,
               all_subsets[curr_index].subset_elements, (subset_size * sizeof(int)));
        all_subsets[*howmany_subsets].subset_elements[subset_size] = curr_set[0];
        all_subsets[*howmany_subsets].subset_count = subset_size + 1;
        (*howmany_subsets)++;
    }
}
