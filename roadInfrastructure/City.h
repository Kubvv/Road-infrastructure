/** @file
 * Interfejs klasy przechowujacej informacje o miescie.
 *
 * @author Jakub Grondziowski <jakugro762@student.polsl.pl>
 */
#include <iostream>
#include <vector>
#include <list>

using namespace std;

/**
 * Struktura przechowujaca informacje o miescie (wierzcholku grafu).
 */
struct City
{
	string name; ///< nazwa miasta.
	int number = -1; ///< numer miasta.
	list<pair<int, double>> roads; ///< lista drog wychodzacych z miasta (krawedzie).
};

/** @brief Tworzy strukture przechowujaca informacje o wierzcholku.
 * Przypisuje do nowej struktury czesc parametrow i zwraca strukture.
 * @param[in] cityName - nazwa miasta,
 * @param[in] cityNumber - numer miasta.
 * @return nowa, utworzona strukture typu City.
 */
City createCity(const string &cityName, const int cityNumber);

/** @brief Dodaje krawedz pomiedzy wierzcholkami.
 * Dodaje w strukturze @p c droge prowadzaca do miasta o numerze @p destinationIndex.
 * @param[in, out] c - wskaznik na strukture przechowujaca informacje o miescie,
 * @param[in] destinationIndex - numer miasta do ktorego prowadzi droga,
 * @param[in] cost - koszt budowy drogi.
 */
void addConnection(City &c, const int destinationIndex, const double cost);

/** @brief Usuwa krawedz pomiedzy wierzcholkami.
 * Usuwa w strukturze @p c droge prowadzaca do miasta o numerze @p destination.
 * @param[in, out] c - wskaznik na strukture przechowujaca informacje o miescie,
 * @param[in] destinationIndex - numer miasta do ktorego prowadzi droga.
 * @param[in] cost - koszt budowy drogi.
 */
void deleteConnection(City &c, const int destinationIndex, const double cost);

/** @brief Zwraca wektor sasiadow miasta @p c.
 * Odszukuje i zwraca wartosci liczbowe miast, ktore maja polaczenie z miastem @p c.
 * @param[in] c - struktura opisujaca miasto
 * @param[in, out] neighbours - wektor sasiadow miasta. 
 */
void getNeighbouringCities(City &c, vector<int> &neighbours);