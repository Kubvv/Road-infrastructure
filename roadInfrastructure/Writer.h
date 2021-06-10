/** @file
 * Interfejs klasy wypisujacej wynik dzialania programu do pliku.
 *
 * @author Jakub Grondziowski <jakugro762@student.polsl.pl>
 */
#include <iostream>
#include <string>
#include <tuple>
#include <list>

using namespace std;

/** @brief wypisuje wynik dzialania programu do pliku.
 * Korzystajac z danych w @p proposedRoads przepisuje wynik do pliku o sciezce @p file.
 * @param[in] file - sciezka do pliku wynikowego,
 * @param[in] proposedRoads - lista z wynikami dzialania programu.
 */
void writeResults(string &file, list<tuple<string, string, double>> &proposedRoads);
