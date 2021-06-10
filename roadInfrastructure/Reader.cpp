/** @file
 * Klasa czytajaca dane z pliku.
 *
 * @author Jakub Grondziowski <jakugro762@student.polsl.pl>
 */
#include <fstream>
#include <string>
#include "Reader.h"

void read(string &file, vector<string>& roads)
{
	ifstream inputFile(file);
	string word;

	while (getline(inputFile, word))
	{
		roads.push_back(word);
	}

	inputFile.close();
}