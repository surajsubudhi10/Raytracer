OBJ = main.o
INC = -I "./"

Raytracer: $(OBJ)
	g++ $(OBJ) -o Raytracer.deb
	rm -f $(OBJ)
	
main.o:
	g++ -c main.cpp $(INC)
	
clean:
	rm -f $(OBJ) Raytracer
