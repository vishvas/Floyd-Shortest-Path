all: run

run:  
	gcc -o floydShortestPath.o floydShortestPath.c -lm
	 
	
clean: floydShortestPath.c
	rm floydShortestPath.o
