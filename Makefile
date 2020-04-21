
all: Simorg

Simorg: main.cpp 
	g++ main.cpp -o Simorg 
	./Simorg -f envs/simple1.txt

random:
	g++ main.cpp -o Simorg 
	./Simorg

file2: 
	g++ main.cpp -o Simorg 
	./Simorg -f envs/simple2.txt

file3: 
	g++ main.cpp -o Simorg 
	./Simorg -f envs/simple3.txt

clean: 
	rm Simorg 