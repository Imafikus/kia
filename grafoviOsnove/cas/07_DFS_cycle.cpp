#include <iostream>
#include <vector>

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
  }

  // Funkcija koja dodaje granu u -> v u graf
  void add_edge(int u, int v)
  {
    // Sused cvora u je cvor v
    adjacency_list[u].push_back(v);
  }

  bool DFS(int u)
  {
    // Kazemo da je cvor koji trenutno obradjujemo vec posecen
    visited[u] = true;

    // Uzimamo iteratore na pocetak i kraj kolekcije kako bismo prosli kroz sve susede
    // Ako obratimo paznju videcemo da uzimamo adjacency_list[u].begin() i adjacency_list[u].end(), odnosno uzimamo vector suseda cvora u i obradjujemo njih
    auto begin = adjacency_list[u].begin();
    auto end = adjacency_list[u].end();

    while (begin != end) {
      // Ako smo dosli do cvora koji smo vec posetili na trenutnom putu onda znaci da imamo ciklus i vracamo true. Obratiti paznju na deo NA TRENUTNOM PUTU,
      //kako imamo rekurziju i ako nam je graf 0 -> 1, 1 -> 2, 0 -> 2 on nema ciklus. Jedan put je 0 -> 1 -> 2 a drugi 0 -> 1 -> 2.
      // Da gledamo uopsteno da li je cvor posecen a ne NA TRENUTNOM PUTU onda bismo kada idemo 0 -> 2 naisli na cvor koji je vec posecen i onda bi bilo da imamo ciklus,
      // zato svaki put kada zavrsimo rekurzivni poziv kazemo da je cvor u neposecen, tj visited[u] = false;
      if (visited[*begin]) {
        return true;
      }
      // Ako nam neki rekurzivi poziv vrati true to znaci da smo u nekom podgrafu nasli ciklus pa samo vracamo true
      else if (DFS(*begin)) {
        return true;
      }

      // Krecemo se kroz kolekciju
      begin++;
    }

    // Objasnjenje gore
    visited[u] = false;
    // Nemamo ciklus na ovom putu, ako na nekom drugom putu naidjemo na ciklus to cemo u while petlji detektovati i vratiti true
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
  // g.add_edge(0, 2);

  std::cout << g.DFS(0) << std::endl;

  return 0;
}
