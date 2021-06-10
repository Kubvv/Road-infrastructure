/** @file
 * Interfejs klasy przechowujacej informacje o mapie drogowej.
 *
 * @author Jakub Grondziowski <jakugro762@student.polsl.pl>
 */
#include "City.h"

using namespace std;

/**
 * Struktura przechowujaca informacje o mapie drogowej (graf).
 */
struct RoadMap
{
	vector<tuple<int, int, double>> roads; ///< wektor wszystkich drog, w formacie numer miasta1, numer miasta2, koszt.
	vector<City> cities; ///< wektor wszystkich miast.
};

/** @brief Tworzy strukture przechowujaca mape drogowa.
 * Korszystajac z danych zapisanych w pliku wejsciowym, tworzy obraz mapy drogowej (grafu) i listy drog. 
 * @param[in] userInput - linie danych wprowadzonych przez uzytkownika,
 * @return nowa, utworzona struktura typu RoadMap.
 */
RoadMap createRoadMap(const vector<string> &userInput);

/** @brief Decyduje, ktore drogi umozliwia optymalne polaczenie miast.
 * Po kolei usuwa drogi, zaczynajac od najdrozszej, sprawdzajac, czy jej usuniecie
 * powoduje przerwanie spojnosci grafu. Jesli tak, przywraca ja.
 * @param[in, out] rm - wskaznik na strukture opisujaca mape drogowa.
 */
void createOptimizedRoadNet(RoadMap &rm);

/** @brief Tworzy czytelniejsza liste wynikow.
 * Formatuje wyniki z formy int, int, double do string, string, double. 
 * @param[in] rm - struktura opisujaca mape drogowa.
 * @return lista wynikowa z optymalnymi drogami do budowy w formacie string, string, double.
 */
list<tuple<string, string, double>> createResultList(const RoadMap &rm);
