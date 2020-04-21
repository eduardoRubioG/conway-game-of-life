
all: Simorg

Simorg: main.cpp 
	g++ -std=c++11 main.cpp -o Simorg 

random:
	g++ -std=c++11 main.cpp -o Simorg 
	./Simorg

file1: 
	g++ -std=c++11 main.cpp -o Simorg 
	./Simorg -f envs/simple1.txt

file2: 
	g++ -std=c++11 main.cpp -o Simorg 
	./Simorg -f envs/simple2.txt

file3: 
	g++ -std=c++11 main.cpp -o Simorg 
	./Simorg -f envs/simple3.txt

clean: 
	rm Simorg 