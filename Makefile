PP=g++ -O3 -Wall -Wno-deprecated
CODES=main.cpp io.cpp command.cpp index.cpp

.PHONY: main

main: $(CODES)
	$(PP) main.cpp -o main

debug: $(CODES)
	$(PP) main.cpp -o main -DDEBUG

run: main
	./main < input > output
