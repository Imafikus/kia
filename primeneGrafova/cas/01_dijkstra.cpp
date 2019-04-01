#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <stack>

#define INFINITY INT_MAX

// Struktura koja predefinise operator ()
// kako bismo u priority_queue-u kao treci argument mogli da prosledimo ovu strukturu
struct compare
{
  // Vracamo informaciju o tome da li je duzina puta para p1 veca od duzine puta para p2
  bool operator()(std::pair<int, int> &p1, std::pair<int, int> &p2)
  {
    return p1.second > p2.second;
  }
};

// Klasa kojom cemo predstavljati graf
class Graph
{
public:
  // Konstruktor za graf koji samo prima broj cvorova grafa
  Graph(int V)
  {
    // Broj cvorova grafa je jednak prosledjenom argumentu
    this->V = V;
    // Alociramo memoriju za V vectora, jer znamo da ce ih biti V,
	// a svaki od njih cemo povecavati za po jedan element pomocu vector.push_back()
    adjacency_list.resize(V);
    // Alociramo prostor za V celih brojeva koji cuvaju rastojanja
    distances.resize(V);
    // Na pocetku kazemo da su svi cvorovi udaljeni beskonacno
    std::fill(distances.begin(), distances.end(), INFINITY);

    // Alociramo prostor za V bool vrednosti koji govore da li imamo put do cvora
    path_found.resize(V);
    // Na pocetku kazemo da ni do jednog cvora nemamo put
    std::fill(path_found.begin(), path_found.end(), false);

    // Alociramo prostor za V integer-a
    shortest_path.resize(V);
    // Na pocetku su putanje do svakog cvora beskonacne
    std::fill(shortest_path.begin(), shortest_path.end(), INFINITY);

    // Alociramo prostor za V integer-a
    parents.resize(V);
    // Na pocetku su svi roditelji -1
    std::fill(parents.begin(), parents.end(), -1);
  }

  // Funkcija koja dodaje grane u -> v  i v -> u u graf
  void add_edge(int u, int v, int weight)
  {
    // Funkcija std::make_pair kreira par vrednosti koje se prosledjuju kao argumenti

    // Sused cvora u je cvor v, a tezina je weight
    adjacency_list[u].push_back(std::make_pair(v, weight));
    // Sused cvora v je cvor u a tezina je weight
    adjacency_list[v].push_back(std::make_pair(u, weight));
  }

  void dijkstra(int u, int v)
  {
    // Pravimo min-heap za cuvanje svih cvorova grafa.
	// Svaki cvor heap-a ce biti cvor, kao i najkrace rastojanje do njega koje je do tad nadjeno
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, compare> heap;

    // Udaljenost pocetnog cvora od sebe samog je 0
    distances[u] = 0;

    // Dodajemo cvor u  heap
    heap.push(std::make_pair(u, distances[u]));

    // Najkraci put od pocetnog cvora do samog sebe je 0
    shortest_path[u] = 0;

    std::pair<int, int> tmp;

    // Dok god ima elemenata u min heap-u
    while (!heap.empty()) {
      // Uzimamo koreni element heap-a
      tmp = heap.top();

      // Skidamo element sa vrha heap-a
      heap.pop();

      // Kako moze da se desi da smo neki cvor vise puta ubacili u heap,
	  // ako opet naidjemo na cvor koji je vec obradjen, tj. do kog smo nasli najkraci put,
	  // necemo ponovo da ga obradjujemo
      if (path_found[tmp.first])
        continue;

      // Kada udjemo u cvor, znamo da smo nasli najkraci put do njega pa to i kazemo
      path_found[tmp.first] = true;

      // Prolazimo kroz listu suseda cvora tmp
      // tmp je par ciji je prvi element cvor,  drugi element je cena najkraceg puta do tog cvora,
	  // tako da svuda gde nam treba cvor imamo tmp.first
      for (std::pair<int, int> &neighbour : adjacency_list[tmp.first]) {
        // Ako preko cvora tmp imamo kraci put do nekog suseda,
		// onda azuriramo najkraci put do tog suseda i dodajemo ga na heap
        // Druga opcija je da imamo put jednake tezine koji sadrzi manje grana
        if (distances[neighbour.first] >= distances[tmp.first] + neighbour.second && shortest_path[neighbour.first] > shortest_path[tmp.first] + 1) {
          // Azuriramo duzinu najkraceg put do cvora neighbour
          shortest_path[neighbour.first] = shortest_path[tmp.first] + 1;
          // Azuriramo roditelj cvora neighbour
          parents[neighbour.first] = tmp.first;
          // Azuriramo tezinu puta do cvora neighbour
          distances[neighbour.first] = distances[tmp.first] + neighbour.second;
          // Dodajemo cvor neighbour zajedno sa novom tezinom puta u heap
          heap.push(std::make_pair(neighbour.first, distances[neighbour.first]));
        }
      }
    }

    // Stek na koji smestamo cvorove iz putanje jer rekonstruisanjem kroz roditeljske cvorove dobijamo putanju unazad
    std::stack<int> path;

    // Idemo sve do pocetnog cvora ciji je roditelj i dalje -1, i dodajemo sve na stek
    while (parents[v] != -1) {
      path.push(v);
      // Azuriramo cvor v
      v = parents[v];
    }

    // Dodajemo i pocetni cvor na stek
    path.push(v);

    // Velicina steka
    int n = path.size();

    int node;
    // Dok god ima elemenata na steku uzimamo onaj sa vrha i ispisujemo ga
    while (n > 0) {
      node = path.top();

      // Skidamo element sa steka
      path.pop();

      n--;

      if (n > 0)
        std::cout << node << " -> ";
      else
        std::cout << node << "\n";
    }
  }
private:
  // Lista susedstva. Imamo vektor parova gde je prvi element cvor ka kome vodi grana, a drugi element tezina grane
  std::vector<std::vector<std::pair<int, int>>> adjacency_list;
  // Broj cvorova grafa
  int V;
  // Vektor koji ce da cuva tezinu puta od pocetnog cvora do svakog odgovarajuceg cvora
  std::vector<int> distances;
  // Vektor koji ce nam govoriti do kog cvora smo vec nasli najkraci put
  std::vector<bool> path_found;
  // Vektor koji za svaki cvor cuva duzinu najkraceg puta do tog cvora
  std::vector<int> shortest_path;
  // Vektor koji cuva roditelja za svaki cvor,
  //  tj. cvor preko koga se dolazi do cvora u najkracoj putanji.
    //Preko ovog vektora rekonstruisemo putanju
  std::vector<int> parents;
};

int main ()
{
  Graph g(5);

  g.add_edge(0, 1, 1);
  g.add_edge(1, 2, 4);
  g.add_edge(2, 3, 7);
  g.add_edge(3, 4, 2);
  g.add_edge(4, 0, 11);
  // testirati kvalitet resenja po pitanju broja grana, ako je poslednja grana
  // g.add_edge(4, 0, 10);

  // g.add_edge(0, 1, 1);
  // g.add_edge(1, 2, 2);
  // g.add_edge(2, 3, 3);
  // g.add_edge(0, 4, 1);
  // g.add_edge(4, 5, 2);
  // g.add_edge(5, 6, 3);
  // g.add_edge(6, 7, 4);
  // g.add_edge(7, 3, 5);

  g.dijkstra(0, 3);

  return 0;
}
