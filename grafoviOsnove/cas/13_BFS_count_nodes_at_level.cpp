#include <iostream>
#include <vector>
#include <queue>

// Klasa kojom cemo predstavljati graf
class Graph
{
public:
  // Konstruktor za graf koji samo prima broj cvorova grafa
  Graph(int V)
  {
    // Broj cvorova grafa je jednak prosledjenom argumentu
    this->V = V;

    // Alociramo mesto za V bool vrednosti koje ce cuvati posecene cvorove
    visited.resize(V);
    // Na pocetku nijedan cvor nije posecen
    /********* C++ deo *********/
    //  std::fill() prima iterator na pocetak kolekcije i kraj kolekcije i vrednost kojom treba popuniti celu kolekciju
    std::fill(visited.begin(), visited.end(), false);

    // Alociramo memoriju za V vectora, jer znamo da ce ih biti V, a svaki od njih cemo povecavati za po jedan element pomocu vector.push_back()
    adjacency_list.resize(V);

    // Alociramo mesto za V int vrednosti koje ce cuvati nivoe cvorova
    levels.resize(V);
  }

  // Funkcija koja dodaje granu u -> v u graf
  void add_edge(int u, int v)
  {
    // Sused cvora u je cvor v
    adjacency_list[u].push_back(v);
  }

  // Obilazak grafa u sirinu
  void BFS(int u, int level)
  {
    // Red koji koristimo za cuvanje cvorova grafa
    std::queue<int> nodes;

    // Dodajemo pocetni cvor iz koga krecemo
    nodes.push(u);

    // Pomocna promenljiva u koju cemo smestati cvorove koje uzimamo iz reda
    int pom;

    // Nivo korenog cvora je 0
    int current_level = 0;

    levels[u] = current_level;

    // Idemo dok god imamo cvorova u redu
    while (!nodes.empty()) {
      // Uzimamo cvor sa pocetka reda
      /********* C++ deo *********/
      // Metod front() samo uzima element sa pocetka reda ali ga i ne uklanja
      pom = nodes.front();
      // Skidamo cvor sa pocetka reda
      /********* C++ deo *********/
      // Metod pop() skida element sa pocetka reda
      nodes.pop();

      // Kazemo da je trenutni cvor posecen
      visited[pom] = true;

      // Uzimamo iteratore na pocetak i kraj vektora koji cuva susede trenutnog cvora
      auto begin = adjacency_list[pom].begin();
      auto end = adjacency_list[pom].end();

      while (begin != end) {
        // Ukoliko nismo vec posetili cvor zelimo i njega da posetimo, pa ga dodajemo u red kako bi u nekoj od narednih iteracija bio obradjen
        if (!visited[*begin]) {
          // Cvor svakog od potomaka je za jedan veci od nivoa oca
          levels[*begin] = levels[pom] + 1;
          nodes.push(*begin);
        }

        // Krecemo se kroz kolekciju
        begin++;
      }
    }

    // Brojac cvorova na nivou level
    int counter = 0;

    // Prolazimo kroz listu nivoa i
    for (int x : levels) {
      // Ako je cvor na nivou level uvecavamo brojac
      if (x == level)
        counter++;
    }

    std::cout << counter << std::endl;
  }

private:
  // Lista susedstva. Imamo vector vector-a, sto znaci za svaki od cvorova [0,V) imamo po jednu listu koja cuva susede odgovarajuceg cvora
  std::vector<std::vector<int>> adjacency_list;
  // Broj cvorova grafa
  int V;
  // Lista posecenih cvorova. Da ne bismo ulazili u beskonacnu rekurziju ne zelimo da obilazimo cvorove koje smo vec obisli na putu kojim smo krenuli, zato cuvamo listu
  // posecenih cvorova
  std::vector<bool> visited;
  // Lista nivoa za svaki od cvorova
  std::vector<int> levels;
};

int main ()
{
  Graph g(8);

  g.add_edge(0, 1);
  g.add_edge(0, 4);
  g.add_edge(0, 7);
  g.add_edge(4, 6);
  g.add_edge(4, 5);
  g.add_edge(4, 2);
  g.add_edge(7, 3);

  int level;

  std::cin >> level;

  g.BFS(0, level);

  return 0;
}
