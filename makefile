all:
	gcc -o heap_sort heap_sort.c -lm

clean:
	rm -rf *.o heap_sort
