#include <glib.h>
#include <stdio.h>

int main(void) {
    GHashTable *hash = g_hash_table_new(g_str_hash, g_str_equal);
    
    GHashTable *prob_dist1 = g_hash_table_new(g_str_hash, g_str_equal);
    g_hash_table_insert(prob_dist1, "Virginia", GINT_TO_POINTER(20));
    g_hash_table_insert(prob_dist1, "Texas", GINT_TO_POINTER(33));
    g_hash_table_insert(prob_dist1, "Ohio", GINT_TO_POINTER(30));
    g_hash_table_insert(prob_dist1, "Delaware", GINT_TO_POINTER(17));
    
    GHashTable *prob_dist2 = g_hash_table_new(g_str_hash, g_str_equal);
    g_hash_table_insert(prob_dist2, "Virginia", GINT_TO_POINTER(10));
    g_hash_table_insert(prob_dist2, "Texas", GINT_TO_POINTER(50));
    g_hash_table_insert(prob_dist2, "Ohio", GINT_TO_POINTER(40));
    
    g_hash_table_insert(hash, "1", (gpointer) prob_dist1);
    g_hash_table_insert(hash, "2", (gpointer) prob_dist2);
    printf("There are %u keys in the hash\n", g_hash_table_size(hash));
    printf("There are %u keys in the prob_dist1\n", (unsigned int) g_hash_table_size(prob_dist1));
    
    printf("There are %d keys in the prob_dist1 which is in 1\n", g_hash_table_size(g_hash_table_lookup(hash, "1")));
    printf("Value is %d for the key: %s in the prob_dist1\n", GPOINTER_TO_INT(g_hash_table_lookup(g_hash_table_lookup(hash, "1"), "Delaware")), "Delaware");
    
    printf("There are %d keys in the prob_dist2 which is in 2\n", g_hash_table_size(g_hash_table_lookup(hash, "2")));
    printf("Value is %d for the key: %s in the prob_dist2\n", GPOINTER_TO_INT(g_hash_table_lookup(g_hash_table_lookup(hash, "2"), "Virginia")), "Virginia");
    
    g_hash_table_destroy(prob_dist1);
    g_hash_table_destroy(prob_dist2);
    g_hash_table_destroy(hash);
    
    return 0;
}