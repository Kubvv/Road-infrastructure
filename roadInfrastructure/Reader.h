/** @file
 * Interfejs klasy czytajacej dane z pliku.
 *
 * @author Jakub Grondziowski <jakugro762@student.polsl.pl>
 */
#include <iostream>
#include <vector>

using namespace std;

/** @brief Czyta dane z pliku.
 * Czyta dane z pliku o sciezce @p file i zapisuje przeczytany tekst do @p roads.
 * @param[in] file - sciezka do pliku wejsciowego,
 * @param[in, out] proposedRoads - wektor drog zawartych w pliku wejsciowym.
 */
void read(string &file, vector<string>& roads);
