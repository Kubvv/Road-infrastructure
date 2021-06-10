/** @file
 * Klasa wypisujaca wynik dzialania programu do pliku.
 *
 * @author Jakub Grondziowski <jakugro762@student.polsl.pl>
 */
#include <fstream>
#include "Writer.h"

using namespace std;

void writeResults(string &file, list<tuple<string, string, double>> &proposedRoads)
{
	ofstream writeFile;
	writeFile.open(file);

	for (tuple<string, string, double> &road : proposedRoads)
	{
		writeFile << get<0>(road) << " " << get<1>(road) << " " << get<2>(road) << endl;
	}

	writeFile.close();
}