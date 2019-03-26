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
    // Funkcija std::fill() prima iterator na pocetak kolekcije i kraj kolekcije i vrednost kojom treba popuniti celu kolekciju
    std::fill(visited.begin(), visited.end(), false);

    // Alociramo memoriju za V vectora, jer znamo da ce ih biti V, a svaki od njih cemo povecavati za po jedan element pomocu vector.push_back()
    adjacency_list.resize(V);

    // Alociramo mesto za V int vrednosti koje ce cuvati roditelje cvorova
    parents.resize(V);
    // Na pocetku svi cvorovi imaju roditelja -1
    /********* C++ deo *********/
    // Funkcija std::fill() prima iterator na pocetak kolekcije i kraj kolekcije i vrednost kojom treba popuniti celu kolekciju
    std::fill(parents.begin(), parents.end(), -1);
  }

  // Dodajemo granu u -> v i v -> u, posto je graf neusmeren, mozemo to ovako da oznacimo
  void add_edge(int u, int v)
  {
    // Sused cvora v je cvor u
    adjacency_list[v].push_back(u);
    // Sused cvora u je cvor v
    adjacency_list[u].push_back(v);
  }

  bool BFS(int u)
  {
    // Red koji koristimo za cuvanje cvorova grafa
    std::queue<int> nodes;

    // Dodajemo pocetni cvor iz koga krecemo
    nodes.push(u);

    // Pomocna promenljiva u koju cemo smestati cvorove koje uzimamo iz reda
    int pom;

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
        // Ukoliko cvor nije posecen zelimo da ga posetimo (dodajemo ga u red) i kazemo da je trenutni cvor njegov roditelj
        if (!visited[*begin]) {
          parents[*begin] = pom;
          nodes.push(*begin);
        }
        // Inace ako je vec posecen i ako mu je roditelj razlicit od cvora koji se razmatra onda znaci da imamo ciklus i samo vracamo true
        else if (parents[pom] != *begin)
          return true;

        // Krecemo se kroz kolekciju
        begin++;
      }
    }

    // Ukoliko u petlji nismo detektovali ciklus vracamo false jer ga nema
    return false;
  }

private:
  // Lista susedstva. Imamo vector vector-a, sto znaci za svaki od cvorova [0,V) imamo po jednu listu koja cuva susede odgovarajuceg cvora
  std::vector<std::vector<int>> adjacency_list;
  // Broj cvorova grafa
  int V;
  // Lista posecenih cvorova. Da ne bismo ulazili u beskonacnu rekurziju ne zelimo da obilazimo cvorove koje smo vec obisli na putu kojim smo krenuli, zato cuvamo listu
  // posecenih cvorova
  std::vector<bool> visited;
  // Vektor koji nam cuva roditelje cvorova
  std::vector<int> parents;
};

int main ()
{
  Graph g(4);

  g.add_edge(0, 1);
  g.add_edge(0, 2);
  g.add_edge(1, 2);
  g.add_edge(2, 0);
  g.add_edge(2, 3);
  g.add_edge(3, 3);

  // Graph g(3);
  // g.add_edge(0, 1);
  // g.add_edge(1, 2);

  std::cout << g.BFS(0) << std::endl;

  return 0;
}
