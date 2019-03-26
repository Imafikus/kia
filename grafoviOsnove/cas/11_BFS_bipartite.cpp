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
    // Metod std::fill() prima iterator na pocetak kolekcije i kraj kolekcije i vrednost kojom treba popuniti celu kolekciju
    std::fill(visited.begin(), visited.end(), false);

    // Alociramo memoriju za V vectora, jer znamo da ce ih biti V, a svaki od njih cemo povecavati za po jedan element pomocu vector.push_back()
    adjacency_list.resize(V);

    // Alociramo mesto za V int vrednosti koje ce cuvati boje cvorova
    colors.resize(V);

    // Svi cvorovi imaju boju -1 na pocetku
    std::fill(colors.begin(), colors.end(), -1);
  }

  // Funkcija koja dodaje granu u -> v u graf
  void add_edge(int u, int v)
  {
    // Sused cvora u je cvor v
    adjacency_list[u].push_back(v);
  }

  // Obilazak grafa u sirinu
  bool BFS(int u)
  {
    // Red koji koristimo za cuvanje cvorova grafa
    std::queue<int> nodes;

    // Dodajemo pocetni cvor iz koga krecemo
    nodes.push(u);

    // Pomocna promenljiva u koju cemo smestati cvorove koje uzimamo iz reda
    int pom;

    // Prvi cvor ima boju 0
    colors[u] = 0;

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
        // Ako je susednom cvoru *begin vec dodeljena boja i ako je ona ista kao i boja njegovog suseda
        //	znaci da graf nije bipartitan pa vracamo false
        if (colors[*begin] == colors[pom])
          return false;

        // Ukoliko nismo vec posetili cvor zelimo i njega da posetimo, 
		// pa ga dodajemo u red kako bi u nekoj od narednih iteracija bio obradjen
        if (!visited[*begin]) {
          // Boja svakog susednog cvora je razlicita od boje cvora pom
          colors[*begin] = !colors[pom];
          nodes.push(*begin);
        }

        // Krecemo se kroz kolekciju
        begin++;
      }
    }

    // Ako smo dosli do ovde prosli smo sve cvorove i nismo nasli da graf nije bipartitan pa vracamo true
    return true;
  }

private:
  // Lista susedstva. Imamo vector vector-a, 
  // sto znaci za svaki od cvorova [0,V) imamo po jednu listu koja cuva susede odgovarajuceg cvora
  std::vector<std::vector<int>> adjacency_list;
  // Broj cvorova grafa
  int V;
  // Lista posecenih cvorova. Da ne bismo ulazili u beskonacnu rekurziju ne zelimo da obilazimo cvorove koje smo vec obisli na putu kojim smo krenuli, zato cuvamo listu
  // posecenih cvorova
  std::vector<bool> visited;
  // Lista boja za svaki od cvorova
  std::vector<int> colors;
};

int main ()
{
  Graph g(6);

  g.add_edge(0, 1);
  g.add_edge(1, 2);
  g.add_edge(2, 3);
  g.add_edge(3, 4);
  g.add_edge(4, 5);
  g.add_edge(5, 0);
  // Dodati ovu granu u graf i videti rezultat
  // g.add_edge(2, 0);

  std::cout << g.BFS(0) << std::endl;

  return 0;
}
