

int main(void) {
    char string[] = "HELLO";
    
    char* ptr = &string;
    
    printf("%s, %p, %s, %p\n", string, &string, ptr, ptr);
}
