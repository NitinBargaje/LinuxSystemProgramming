#include "dll.h"
#include <stdlib.h>
#include <memory.h>

/* linked list utility functions */

/* return 0 on success and -1 on failure */
int remove_data_from_dll_by_data_ptr(dll_t *dll, void* data) {
    if(!dll || !dll->head) return -1;

    dll_node_t *head = dll->head;
    while(head) {
        if(head->data == data) {
            dll_node_t *temp = head;
            if(head->left && head->right) {
                head->left->right = head->right;
                head->right->left = head->left;
            } else if(head->left) {
                head->left->right = NULL;
            } else {
                dll->head = head->right;
            }
            temp->left = NULL; temp->right = NULL; temp->data = NULL;
            free(temp);
            return 0;
        }
        head = head->right;
    }
    return -1;
}

/* return 0 if empty -1 otherwise */
int is_dll_empty(dll_t *dll) {
    if(!dll || !dll->head) return 0;
    return -1;
}

/* delete recursively all nodes from dll*/
void deleteNodeRescursive(dll_node_t *cur_node) {
    if(cur_node->right) deleteNodeRescursive(cur_node->right);
    cur_node->right = NULL;
    cur_node->left = NULL;
    cur_node->data = NULL;
    free(cur_node);
}
/* delete all nodes from a dll, but do not free appln data*/
void drain_dll(dll_t *dll) {
    if(!dll || !dll->head) return;
    deleteNodeRescursive(dll->head);
    dll->head = NULL;
}