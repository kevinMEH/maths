all:
	gcc main.c src/*.c -o build/main
	./build/main

test-performance:
	gcc src/polynomial.c src/interpolate.c performance/performance.c -o build/performance
	./build/performance

clean:
	rm build/*