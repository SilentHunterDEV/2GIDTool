2GIDTool:
	g++ -O2 -o 2GIDTool.exe 2GIDTool.cpp

debug:
	g++ -O2 -o 2GIDTool.exe -g -Wall -Wextra 2GIDTool.cpp

clean:
	rm 2GIDTool
