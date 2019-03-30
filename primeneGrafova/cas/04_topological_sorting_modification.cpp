#include <iostream>
#include <vector>
#include <queue>
#include <numeric>

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

    // Imamo V cvorova pa nam je vektor ulazinh stepena velicine V
    in_degrees.resize(V);
    // Na pocetku svi cvorovi imaju ulazni stepen 0
    std::fill(in_degrees.begin(), in_degrees.end(), 0);

    found = false;
  }

  // Funkcija koja dodaje granu u -> v u graf, i menja ulazni stepen cvora
  void add_edge(int u, int v)
  {
    // Sused cvora u je cvor v
    adjacency_list[u].push_back(v);

    // Kada dodamo granu u -> v znaci da se ulazni stepen cvora v povecava za 1
    in_degrees[v]++;
  }

  void topological_sorting(std::vector<int> &result)
  {
    // Red koji koristimo za cuvanje cvorova koje treba obraditi
    std::queue<int> nodes;

    // Odmah dodamo sve cvorove ciji je ulazni stepen 0
    for (int i = 0; i < V; i++)
      if (!in_degrees[i]) {
        nodes.push(i);
      }
    // Pomocni cvor u koji smestamo ono sto izvucemo iz reda
    int tmp;

    while (nodes.size()) {
      // Uzimamo cvor sa pocetka reda
      tmp = nodes.front();

      // Skidamo cvor sa pocetka reda
      nodes.pop();

      result.push_back(tmp);

      // Prolazimo kroz sve cvorove koji su susedni cvoru tmp, smanjujemo im ulazni stepen, i onda ako je neki dosao do ulaznog stepena 0, znaci da smo obisli sve njegove
      // susede tako da se i on moze dodati na kraj reda
      for (int node : adjacency_list[tmp]) {
        in_degrees[node]--;

        if (!in_degrees[node])
          nodes.push(node);
      }
    }
  }

  void DFS(int u)
  {
    // Ako smo usli u vec posecen cvor ovo znaci da smo nasli kraj ciklusa, tako da samo ispisujemo krajnji cvor i zavrsavamo funkciju
    if (visited[u]) {
      std::cout << u << "\n";
      found = true;
      return ;
    }

    // Oznacavamo da je trenutni cvor posecen
    visited[u] = true;


    // Ispisujemo trenutni cvor
    std::cout << u << " -> ";

    // Uzimamo iteratore na pocetak i kraj kolekcije kako bismo prosli kroz sve susede
    // Ako obratimo paznju videcemo da uzimamo adjacency_list[u].begin() i adjacency_list[u].end(), odnosno uzimamo vector suseda cvora u i obradjujemo njih
    auto begin = adjacency_list[u].begin();
    auto end = adjacency_list[u].end();

    while (begin != end) {
      // Ako smo vec posetili cvor necemo ponovo u njega ici, trazimo neposecene cvorove. Za njih pozivamo DFS rekurzivno.
      // Ovde se krije i uslov izlaska iz rekurzije, jer kada nema vise cvorova koji nisu poseceni necemo ici dalje, tj necemo pozivati DFS ponovo
      // begin i end su iteratori (pokazivacke promenljive), pa da bismo dobili vrednost koju cuva begin moramo da ga dereferenciramo, i zato imamo *begin
      if (!found)
        DFS(*begin);
      // Krecemo se kroz kolekciju
      begin++;
    }

  }

  void find()
  {
    // Vektor result koji ce cuvati redosled cvorova u topoloskom sortitanju grafa
    std::vector<int> result;

    // Pokrenemo algoritam za topolosko sortiranje
    topological_sorting(result);

    // Promenljiva koja oznacava da li ispisujemo ciklus ili topoloski poredak
    bool topological = true;

    // Idemo kroz sve cvorove i ako naidjemo na cvor koji ima stepen veci od 0, znaci da topolosko sortiranje ne postoji odnosno da imamo ciklus, stavljamo topological na
    // false da to oznacimo
    for (int i = 0; i < V; i++)
      if (in_degrees[i]) {
        topological = false;
      }

    // Ako treba da ispisemo topoloski poredak, ispisujemo sve iz vektora result
    if (topological) {
      std::cout << "Topological sorting: ";
      for (int x : result)
        std::cout << x << " ";
      std::cout << "\n";
      return ;
    }

    std::cout << "Cycle: ";

    // Ako imamo ciklus, pozivamo DFS iz prvog cvora ciji je ulazni stepen > 0 i u DFS-u zapravo ispisujemo ciklus koji postoji
    for (int i = 0; i < V; i++)
      if (in_degrees[i] != 0) {
        DFS(i);
        return ;
      }
  }
private:
  // Lista susedstva. Imamo vector vector-a, sto znaci za svaki od cvorova [0,V) imamo po jednu listu koja cuva susede odgovarajuceg cvora
  std::vector<std::vector<int>> adjacency_list;
  // Broj cvorova grafa
  int V;
  // Lista posecenih cvorova. Da ne bismo ulazili u beskonacnu rekurziju ne zelimo da obilazimo cvorove koje smo vec obisli na putu kojim smo krenuli, zato cuvamo listu
  // posecenih cvorova
  std::vector<bool> visited;
  // Struktura stek u koju cemo smestati cvorove grafa
  std::vector<int> in_degrees;
  bool found;
};

int main ()
{
  Graph g(5);

  g.add_edge(0, 1);
  g.add_edge(1, 2);
  g.add_edge(2, 3);
  g.add_edge(3, 4);
  g.add_edge(4, 1);
  g.add_edge(4, 2);
  // g.add_edge(0, 1);
  // g.add_edge(1, 4);
  // g.add_edge(2, 4);
  // g.add_edge(3, 0);
  // g.add_edge(3, 2);
  // g.add_edge(5, 2);
  // g.add_edge(5, 4);

  // g.add_edge(0, 1);
  // g.add_edge(1, 2);
  // g.add_edge(2, 3);
  // g.add_edge(3, 4);
  // g.add_edge(4, 3);
  // g.add_edge(4, 5);
  // g.add_edge(5, 6);

  g.find();

  return 0;
}
