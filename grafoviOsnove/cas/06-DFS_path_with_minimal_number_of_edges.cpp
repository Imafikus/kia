/* BFS je prirodno resenje za ovaj problem. Probleme najkraceg puta
u lavirintu smo zato na pocetku kursa i resavali BFS-om */
/* Ovo resenje koristi DFS */
#include <iostream>
#include <vector>
#include <climits>

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

    // Kazemo da je minimalni broj grana na pocetku najveci moguci broj koji cuva int
    min_num_of_edges = INT_MAX;
  }

  // Funkcija koja dodaje granu u -> v u graf
  void add_edge(int u, int v)
  {
    // Sused cvora u je cvor v
    adjacency_list[u].push_back(v);
  }

  void DFS(int u, int v, int current_num_of_edges)
  {
    // Ako smo dosli do ciljnog cvora proveravamo koliki je broj grana na tom put, ako je manji od trenutnog minimuma, onda je to i novi minimum
    if (u == v) {
      if (current_num_of_edges < min_num_of_edges)
        min_num_of_edges = current_num_of_edges;

      // Izlazimo iz rekurzije
      return ;
    }

    // Kazemo da je cvor koji trenutno obradjujemo vec posecen
    visited[u] = true;

    // Uzimamo iteratore na pocetak i kraj kolekcije kako bismo prosli kroz sve susede
    // Ako obratimo paznju videcemo da uzimamo adjacency_list[u].begin() i adjacency_list[u].end(), odnosno uzimamo vector suseda cvora u i obradjujemo njih
    auto begin = adjacency_list[u].begin();
    auto end = adjacency_list[u].end();

    while (begin != end) {
      // Ako smo vec posetili cvor necemo ponovo u njega ici, trazimo neposecene cvorove. Za njih pozivamo DFS rekurzivno.
      // Ovde se krije i uslov izlaska iz rekurzije, jer kada nema vise cvorova koji nisu poseceni necemo ici dalje, tj necemo pozivati DFS ponovo
      // begin i end su iteratori (pokazivacke promenljive), pa da bismo dobili vrednost koju cuva begin moramo da ga dereferenciramo, i zato imamo *begin
      if (!visited[*begin])
        // Kazemo da je broj grana za 1 veci nego do sad, jer se krecemo ka novom cvoru, znaci imamo jos jednu granu na putu
        DFS(*begin, v, current_num_of_edges + 1);

      // Krecemo se kroz kolekciju
      begin++;
    }

    // Ovo je neophodan uslov, jer mi zelimo zapravo da nadjemo sve putanje od u do v da bismo videli koja ima najmanji broj cvorova, tako da kada se zavrsi deo putanje
    // kroz jedan cvor on treba da postane neposecen jer mozda postoji drugi put koji ide kroz taj cvor
    visited[u] = false;
  }

  // Getter za minimalan broj grana
  int get_min_num_of_edges()
  {
    return min_num_of_edges;
  }

private:
  // Lista susedstva. Imamo vector vector-a, sto znaci za svaki od cvorova [0,V) imamo po jednu listu koja cuva susede odgovarajuceg cvora
  std::vector<std::vector<int>> adjacency_list;
  // Broj cvorova grafa
  int V;
  // Lista posecenih cvorova. Da ne bismo ulazili u beskonacnu rekurziju ne zelimo da obilazimo cvorove koje smo vec obisli na putu kojim smo krenuli, zato cuvamo listu
  // posecenih cvorova
  std::vector<bool> visited;
  // Promenljiva koja predstavlja minimalan broj grana na putu od u do v
  int min_num_of_edges;
};


int main ()
{
  int u, v;

  std::cin >> u >> v;

  Graph g(5);

  g.add_edge(0, 1);
  g.add_edge(1, 0);
  g.add_edge(0, 4);
  g.add_edge(4, 0);
  g.add_edge(1, 2);
  g.add_edge(2, 1);
  g.add_edge(2, 4);
  g.add_edge(4, 2);
  g.add_edge(2, 3);
  g.add_edge(3, 2);
  g.add_edge(3, 4);
  g.add_edge(4, 3);

  // g.add_edge(0, 1);
  // g.add_edge(0, 4);
  // g.add_edge(1, 2);
  // g.add_edge(2, 4);
  // g.add_edge(2, 3);
  // g.add_edge(3, 4);

  std::vector<int> result;

  g.DFS(u, v, 0);

  std::cout << g.get_min_num_of_edges() << std::endl;

  return 0;
}
