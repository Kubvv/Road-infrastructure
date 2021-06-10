default: roadInfrastructure

reader.o: Reader.cpp
	g++ -c -Wall -Wextra -pedantic Reader.cpp -o reader.o

city.o: City.cpp
	g++ -c -Wall -Wextra -pedantic City.cpp -o city.o

roadMap.o: RoadMap.cpp City.h
	g++ -c -Wall -Wextra -pedantic RoadMap.cpp -o roadMap.o

writer.o: Writer.cpp
	g++ -c -Wall -Wextra -pedantic Writer.cpp -o writer.o

main.o: Main.cpp RoadMap.h Reader.h Writer.h
	g++ -c -Wall -Wextra -pedantic Main.cpp -o main.o

roadInfrastructure: main.o roadMap.o city.o reader.o writer.o
	g++ main.o roadMap.o city.o reader.o writer.o -o roadInfrastructure

clean:
	del -f main.o
	del -f roadMap.o
	del -f city.o
	del -f reader.o
	del -f writer.o
	del -f roadInfrastructure.exe