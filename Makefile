# Makefile only for MacOS and Linux (g++)

2GIDTool:
	g++ -O2 -o 2GIDTool 2GIDTool.cpp

debug:
	g++ -O2 -o 2GIDTool -g -Wall -Wextra 2GIDTool.cpp

clean:
	rm 2GIDTool
