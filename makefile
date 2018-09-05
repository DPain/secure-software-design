CC=gcc
	
markovian: markovian.c;
	$(CC) -o a.out markovian.c `pkg-config --cflags --libs glib-2.0`

clean:
	rm *.o

