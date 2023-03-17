all: build/$(file)
	./build/$(file)

build/$(file): $(file).c src/*.c
	gcc $(file).c src/*.c -o build/$(file)

clean:
	rm build/*