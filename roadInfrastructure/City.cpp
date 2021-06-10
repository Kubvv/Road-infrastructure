/** @file
 * Klasa wykonujaca operacje zwiazane z miastami.
 *
 * @author Jakub Grondziowski <jakugro762@student.polsl.pl>
 */
#include <algorithm>
#include "City.h"

City createCity(const string &cityName, const int cityNumber)
{
	City c;
	c.name = cityName;
	c.number = cityNumber;
	return c;
}

void addConnection(City &c, const int destinationIndex, const double cost)
{
	pair<int, double> edge = make_pair(destinationIndex, cost);
	c.roads.push_back(edge);
}

void deleteConnection(City &c, const int destinationIndex, const double cost)
{
	c.roads.remove(make_pair(destinationIndex, cost));
	/*bool done = false;
	bool found = false;
	list<pair<int, double>>::iterator it = c.roads.begin();
	list<pair<int, double>>::iterator buff;

	while (it != c.roads.end() && !done)
	{
		if (it->first == destinationIndex)
		{
			buff = it;
			found = true;
		}
		else if (found)
		{
			c.roads.erase(buff);
			done = true;
		}

		it++;
	}*/
}

void getNeighbouringCities(City &c, vector<int>& neighbours)
{
	list<pair<int, double>>::iterator it = c.roads.begin();

	for (; it != c.roads.end(); it++)
	{
		neighbours.push_back(it->first);
	}
}