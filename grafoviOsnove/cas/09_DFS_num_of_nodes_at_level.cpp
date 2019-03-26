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

    // Na pocetku kazemo da nemamo nijedan cvor na odredjenom nivou
    num_of_nodes = 0;
  }

  // Funkcija koja dodaje granu u -> v u graf
  void add_edge(int u, int v)
  {
    // Sused cvora u je cvor v
    adjacency_list[u].push_back(v);
  }

  void DFS(int u, int level, int current_level)
  {
    // Kazemo da je cvor koji trenutno obradjujemo vec posecen
    visited[u] = true;

    // Ako je nivo na kome je trenutni cvor jednak trazenom nivou uvecavamo broj cvorova na tom nivou
    if (current_level == level)
      num_of_nodes++;

    // Uzimamo iteratore na pocetak i kraj kolekcije kako bismo prosli kroz sve susede
    // Ako obratimo paznju videcemo da uzimamo adjacency_list[u].begin() i adjacency_list[u].end(), odnosno uzimamo vector suseda cvora u i obradjujemo njih
    auto begin = adjacency_list[u].begin();
    auto end = adjacency_list[u].end();

    while (begin != end) {
      // Ako smo vec posetili cvor necemo ponovo u njega ici, trazimo neposecene cvorove. Za njih pozivamo DFS rekurzivno.
      // Ovde se krije i uslov izlaska iz rekurzije, jer kada nema vise cvorova koji nisu poseceni necemo ici dalje, tj necemo pozivati DFS ponovo
      // begin i end su iteratori (pokazivacke promenljive), pa da bismo dobili vrednost koju cuva begin moramo da ga dereferenciramo, i zato imamo *begin
      if (!visited[*begin])
        // Pozivamo rekurziju i kazemo da je trenutni nivo za 1 veci, jer idemo dublje kroz stablo
        DFS(*begin, level, current_level + 1);

      // Krecemo se kroz kolekciju
      begin++;
    }
  }

  // Getter za broj cvorova na odredjenom nivou
  int get_num_of_nodes()
  {
    return num_of_nodes;
  }

private:
  // Lista susedstva. Imamo vector vector-a, sto znaci za svaki od cvorova [0,V) imamo po jednu listu koja cuva susede odgovarajuceg cvora
  std::vector<std::vector<int>> adjacency_list;
  // Broj cvorova grafa
  int V;
  // Lista posecenih cvorova. Da ne bismo ulazili u beskonacnu rekurziju ne zelimo da obilazimo cvorove koje smo vec obisli na putu kojim smo krenuli, zato cuvamo listu
  // posecenih cvorova
  std::vector<bool> visited;
  // Promenljiva koja oznacava broj cvorova na odgovarajucem nivou
  int num_of_nodes;
};

int main()
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

    g.DFS(0, level, 0);

    std::cout << g.get_num_of_nodes() << std::endl;

    return 0;
}
