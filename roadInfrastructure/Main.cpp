/** @file
 * Klasa glowna programu
 *
 * @author Jakub Grondziowski <jakugro762@student.polsl.pl>
 */
#include <cstring>
#include "RoadMap.h"
#include "Reader.h"
#include "Writer.h"

using namespace std;

/** @brief Sortuje i sprawdza przelaczniki podane przez uzytkownika.
 * Sprawdza, czy podano 2 przelaczniki -i, -o oraz sortuje je na potrzeby programu.
 * @param[in] argv - przelaczniki podane przez uzytkownika,
 * @param[in, out] parameters - tablica z posortowanymi argumentami przelacznikow.
 * @return true, jesli podane zostaly przelaczniki -i, -o i false w przeciwnym wypadku.
 */
bool sortParameters(char* argv[], string (&parameters)[2])
{
    bool result = true;
    int i = 1;

    while (i <= 3 && result)
    {
        if (strcmp(argv[i], "-i") == 0 && parameters[0] == "")
        {
            parameters[0] = string(argv[i + 1]);
        }
        else if (strcmp(argv[i], "-o") == 0 && parameters[1] == "")
        {
            parameters[1] = string(argv[i + 1]);
        }
        else
        {
            result = false;
        }
        i += 2;
    }

    return result;
}

int main(int argc, char* argv[])
{
    string parameters[2];

    if (argc == 5 && sortParameters(argv, parameters))
    {
        vector<string> inputLines;
        read(parameters[0], inputLines);
        RoadMap rm = createRoadMap(inputLines);
        createOptimizedRoadNet(rm);
        list<tuple<string, string, double>> results = createResultList(rm);
        writeResults(parameters[1], results);
    }
    else
    {
        cout << "Uruchom program z linii polecen, wykorzystujac wszystkie nastepujace przelaczniki dokladnie jeden raz: " << endl;
        cout << "-i plik wejsciowy z nazwami miast i kosztem budowy drog" << endl;
        cout << "-o plik wynikowy z wyznaczonymi drogami" << endl;
    }

    return 0;
}
