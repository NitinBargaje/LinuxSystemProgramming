#include "dll.h"
#include <memory.h>
#include <stdlib.h>

/* Public function implementation to create and return new empty doubly linked list*/

dll_t * get_new_dll() {
    dll_t* dll = calloc(1, sizeof(dll_t));
    dll->head = NULL;
    return dll;
}

/* Register search callback */
void registerSearchCallback(dll_t *dll, int (*search_callback)(void*, void*)) {
    dll->search_callback = search_callback;
}

/* Register data comparison callback pointer*/
void registerCompareDataCallback(dll_t *dll, int (*compare_data)(void *, void*)) {
    dll->compare_data = compare_data;
}

/* Search by callback */
void* searchByKey(dll_t* dll, void* key) {
    if(!dll || !dll->head) return NULL;
    dll_node_t *head = dll->head;
    while(head) {
        if(dll->search_callback(head->data, key) == 0) return head->data;
        head = head->right;
    }
    return NULL;
}

/* Public function to add new app data to DLL */
int add_data_to_dll(dll_t* dll, void* app_data) {
    if(!dll || !app_data) return -1;

    dll_node_t* dll_new_node = calloc(1, sizeof(dll_node_t));
    dll_new_node->left = NULL;
    dll_new_node->right = NULL;
    dll_new_node->data = app_data;

    /*Now add this to the front of DLL*/
    if(!dll->head) {
        dll->head = dll_new_node;
        return 0;
    }
    
    dll_node_t* first_node = dll->head;
    dll_new_node->right = first_node;
    first_node->left = dll_new_node;
    dll->head = dll_new_node;
    return 0;
}

/* adds data in dll in sorted manner based on compare_data callback provided by library user
    return 0 on success and -1 on failure */
int dll_priority_insertion(dll_t *dll, void *data) {
    if(!dll) return -1;
    // Case 1: empty doubly linked list
    if(!dll->head) {
        dll_node_t *new_node = calloc(1, sizeof(dll_node_t));
        new_node->data = data;
        new_node->left = NULL; new_node->right = NULL;
        dll->head = new_node;
        return 0;
    }

    dll_node_t *head = dll->head;
    while(head->right && dll->compare_data(head->data, data) == -1) head = head->right;

    dll_node_t *new_node = calloc(1, sizeof(dll_node_t));
    new_node->data = data;
    if(dll->compare_data(head->data, data) == 1) {
        if(head->left) {
            new_node->right = head;
            new_node->left = head->left;
            head->left->right = new_node;
            head->left = new_node;
        } else {
            new_node->left = NULL;
            new_node->right = head;
            head->left = new_node;
            dll->head = new_node;
        }
    } else {
        head->right = new_node;
        new_node->left = head;
    }
    return 0;
}