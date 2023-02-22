all: build/main
	./build/main

build/main: main.c src/*.c
	gcc main.c src/*.c -o build/main

test-performance:
	gcc src/polynomial.c src/interpolate.c performance/performance.c -o build/performance
	./build/performance

clean:
	rm build/*