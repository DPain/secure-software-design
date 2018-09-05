CC=gcc
CFLAGS="-std=c99"
	
markovian: markovian.c;
	$(CC) $(CFLAGS) -o a.out markovian.c `pkg-config --cflags --libs glib-2.0`

clean:
	rm *.o

