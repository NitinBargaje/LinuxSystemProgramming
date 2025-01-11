/* Header file for doubly linked list */

typedef struct dll_node_ {
    void *data;
    struct dll_node_* left;
    struct dll_node_* right;
} dll_node_t;

typedef struct dll_ {
    dll_node_t *head;
    int (*search_callback)(void*, void*);
    int (*compare_data)(void*, void*);
} dll_t;

/* Public function declaration to create and return a new empty doubly linked list*/

dll_t* get_new_dll();

/* Register search callback */
void registerSearchCallback(dll_t *dll, int (*search_callback)(void*, void*));

/* Register data comparison callback pointer*/
void registerCompareDataCallback(dll_t *dll, int (*compare_data)(void *, void*));

/* Search by callback */
void* searchByKey(dll_t* dll, void* key);

/* adds data to the end of dll*/
int add_data_to_dll (dll_t *dll, void* app_data);

/* adds data in dll in sorted manner based on compare_data callback provided by library user*/
int dll_priority_insertion(dll_t *dll, void *data);

/* linked list utility functions */

/* return 0 on success and -1 on failure */
int remove_data_from_dll_by_data_ptr(dll_t *dll, void* data);

/* return 0 if empty -1 otherwise */
int is_dll_empty(dll_t *dll);

/* delete all nodes from a dll, but do not free appln data*/
void drain_dll(dll_t *dll);
