#include <glib.h>

typedef struct {
   GHashTable* map;
} Probabilities;

int main(void) {
    GHashTable* hash = g_hash_table_new_full(g_str_hash, g_direct_equal, NULL, g_free);
    
    Probabilities *prob_dist1 = (Probabilities*) malloc(sizeof(Probabilities));
    prob_dist1->map = g_hash_table_new(g_str_hash, g_int_equal);
    g_hash_table_insert(prob_dist1->map, "Virginia", GINT_TO_POINTER(20));
    g_hash_table_insert(prob_dist1->map, "Texas", GINT_TO_POINTER(40));
    g_hash_table_insert(prob_dist1->map, "Ohio", GINT_TO_POINTER(40));
    
    Probabilities *prob_dist2 = (Probabilities*) malloc(sizeof(Probabilities));
    prob_dist2->map = g_hash_table_new(g_str_hash, g_int_equal);
    g_hash_table_insert(prob_dist2->map, "Virginia", GINT_TO_POINTER(10));
    g_hash_table_insert(prob_dist2->map, "Texas", GINT_TO_POINTER(50));
    g_hash_table_insert(prob_dist2->map, "Ohio", GINT_TO_POINTER(40));
    
    g_hash_table_insert(hash, "1", prob_dist1);
    g_hash_table_insert(hash, "2", prob_dist2);
    printf("There are %d keys in the hash\n", g_hash_table_size(hash));
    printf("There are %d keys in the prob_dist1\n", g_hash_table_size(prob_dist1->map));
    printf("There are %d keys in the prob_dist1 which is in 1\n", g_hash_table_size(g_hash_table_lookup(hash, "1")));
    g_hash_table_destroy(hash);
    
    return 0;
}