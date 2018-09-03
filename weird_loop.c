

int main(void) {
    int i = 0;
    for(;;) {
        if(i < 5) {
            printf("%d\n", i);
            i++;
        } else {
            break;
        }
    }
}
