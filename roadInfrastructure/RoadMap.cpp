/** @file
 * Klasa wykonujaca operacje zwiazane z mapa drog.
 *
 * @author Jakub Grondziowski <jakugro762@student.polsl.pl>
 */
#include <sstream>
#include <unordered_set>
#include <algorithm>
#include <stack>
#include <set>
#include <tuple>
#include "RoadMap.h"

/** @brief Porownuje wartosci zapisane na 3 pozycji tupli.
 * Umozliwia sortowanie tupli ze wzgledu na element na 2 pozycji. 
 * @param[in] x - pierwszy tuple,
 * @param[in] y - drugi tuple.
 * @return true, jesli wartosc na 2 pozycji tupla nr 1 jest wieksza od 2 pozycji tupla nr 2
 * i false w przeciwnym przypadku.
 */
bool sortbyth(const tuple<int, int, double> &x,
	const tuple<int, int, double> &y)
{
	return (get<2>(x) > get<2>(y));
}

/** @brief dzieli @p line w miejscach spacji.
 * @param[in] line - linia danych.
 * @param edgeInfo - tablica z podzielonym danymi na miasta i koszt.
 */
void splitLine(string &line, string(&edgeInfo)[3])
{
	istringstream stringSplitter(line);

	for (int i = 0; i < 3; i++)
	{
		stringSplitter >> edgeInfo[i];
	}
}

/** @brief zwraca numer miasta o nazwie @p cityName.
 * @param[in] rm - struktura opisujaca mape drogowa,
 * @param[in] cityName - nazwa szukanego miasta.
 * @return numer miasta o wskazanej nazwie.
 */
int getCityIndex(const RoadMap &rm, const string &cityName)
{
	bool found = false;
	int result = -1;

	for (unsigned int i = 0; i < rm.cities.size() && !found; i++)
	{
		if (rm.cities[i].name.compare(cityName) == 0)
		{
			found = true;
			result = i;
		}
	}

	return result;
}

/** @brief zwraca nazwe miasta o numerze @p index.
 * @param[in] rm - struktura opisujaca mape drogowa,
 * @param[in] index - numer szukanego miasta.
 * @return nazwe miasta o wskazanym indeksie.
 */
string getCityName(const RoadMap &rm, const int index)
{
	return rm.cities[index].name;
}

/** @brief Dodaje nowe polaczenie pomiedzy miastami.
 * Dodaje do struktury @p rm dane odnosnie drogi (krawedzi grafu).
 * @param[in, out] rm - wskaznik na strukture opisujaca mape drogowa,
 * @param[in] city1 - nazwa pierwszego miasta,
 * @param[in] city2 - nazwa drugiego miasta,
 * @param[in] cost - koszt drogi laczacej dwa miasta.
 */
void addRoad(RoadMap &rm, const string &city1, const string &city2, const double cost)
{
	int tasksDone = 0;
	tuple<int, int, double> road;
	get<2>(road) = cost;

	for (unsigned int i = 0; i < rm.cities.size() && tasksDone < 2; i++)
	{
		if (rm.cities[i].name.compare(city1) == 0)
		{
			addConnection(rm.cities[i], getCityIndex(rm, city2), cost);
			get<0>(road) = i;
			tasksDone++;
		}
		else if (rm.cities[i].name.compare(city2) == 0)
		{
			addConnection(rm.cities[i], getCityIndex(rm, city1), cost);
			get<1>(road) = i;
			tasksDone++;
		}
	}
 
	rm.roads.push_back(road);
}

RoadMap createRoadMap(const vector<string> &userInput)
{
	RoadMap rm;
	City newCity;
	unordered_set <string> usedCities;

	for (string line : userInput)
	{
		if (!line.empty())
		{
			string edgeInfo[3];
			splitLine(line, edgeInfo);
			if (usedCities.find(edgeInfo[0]) == usedCities.end())
			{
				newCity = createCity(edgeInfo[0], usedCities.size());
				rm.cities.push_back(newCity);
				usedCities.insert(edgeInfo[0]);
			}
			if (usedCities.find(edgeInfo[1]) == usedCities.end())
			{
				newCity = createCity(edgeInfo[1], usedCities.size());
				rm.cities.push_back(newCity);
				usedCities.insert(edgeInfo[1]);
			}

			addRoad(rm, edgeInfo[0], edgeInfo[1], stod(edgeInfo[2]));
		}
	}

	return rm;
}

/** @brief Dodaje na stos nie odwiedzone miasta.
 * Sprawdza, czy sasiedzi poprzedniego wierzcholka byli juz odwiedzani lub sa na stosie, 
 * jesli nie, dodaje je do tego stosu i zbioru odwiedzonych miast.
 * @param[in] neighbours - wektor sasiadow poprzedniego wierzcholka,
 * @param[in, out] toVisit - stos wierzcholkow nie odwiedzonych,
 * @param[in, out] visited - zbior wierzcholkow odiedzonych lub czekajachych na stosie.
 */
void addCitiesToVisit(const vector<int> &neighbours, stack<int> &toVisit, set<int> &visited)
{
	for (unsigned int i = 0; i < neighbours.size(); i++)
	{
		if (visited.find(neighbours[i]) == visited.end())
		{
			toVisit.push(neighbours[i]);
			visited.insert(neighbours[i]);
		}
	}
}

/** @brief Sprawdza Dfs'em, czy graf zachowal spojnosc.
 * Zaczynajac od miasta 0, funkcja przechodzi przez graf i sprawdza, czy odwiedzila
 * wszystkie wierzcholki.
 * @param[in] cityGraph - wektor miast, reprezentujace wierzcholki grafu.
 * @return true, jesli graf zachowal spojnosc i false w przeciwnym przypadku.
 */
bool areCitiesConnected(vector<City> &cityGraph)
{
	stack<int> toVisit;
	toVisit.push(0);
	set<int> visited;
	visited.insert(0);
	vector<int> neighbours;

	while (!toVisit.empty() && visited.size() < cityGraph.size())
	{
		int currentCity = toVisit.top();
		toVisit.pop();
		getNeighbouringCities(cityGraph[currentCity], neighbours);
		addCitiesToVisit(neighbours, toVisit, visited);
	}

	return visited.size() == cityGraph.size();
}

void createOptimizedRoadNet(RoadMap &rm)
{
	sort(rm.roads.begin(), rm.roads.end(), sortbyth);

	for (unsigned int i = 0; i < rm.roads.size(); i++)
	{
		deleteConnection(rm.cities[get<0>(rm.roads[i])], get<1>(rm.roads[i]), get<2>(rm.roads[i]));
		deleteConnection(rm.cities[get<1>(rm.roads[i])], get<0>(rm.roads[i]), get<2>(rm.roads[i]));
		if (!areCitiesConnected(rm.cities))
		{
			addConnection(rm.cities[get<0>(rm.roads[i])], get<1>(rm.roads[i]), get<2>(rm.roads[i]));
			addConnection(rm.cities[get<1>(rm.roads[i])], get<0>(rm.roads[i]), get<2>(rm.roads[i]));
		}
		else
		{
			get<2>(rm.roads[i]) = -get<2>(rm.roads[i]);
		}
	}
}

list<tuple<string, string, double>> createResultList(const RoadMap &rm)
{
	list<tuple<string, string, double>> result;
	tuple<string, string, double> road;

	for (unsigned int i = 0; i < rm.roads.size(); i++)
	{
		if (get<2>(rm.roads[i]) >= 0)
		{
			get<0>(road) = getCityName(rm, get<0>(rm.roads[i]));
			get<1>(road) = getCityName(rm, get<1>(rm.roads[i]));
			get<2>(road) = get<2>(rm.roads[i]);
			result.push_back(road);
		}
	}

	return result;
}
