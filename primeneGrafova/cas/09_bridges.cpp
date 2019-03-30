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

    // Alociramo mesto za V int vrednosti koje ce cuvati roditelje cvorova
    parents.resize(V);
    // Na pocetku svi imaju roditelja -1
    /********* C++ deo *********/
    // Funkcija std::fill() prima iterator na pocetak kolekcije i kraj kolekcije i vrednost kojom treba popuniti celu kolekciju
    std::fill(parents.begin(), parents.end(), -1);

    // Na pocetku je time 0
    time = 0;

    // Alociramo mesto za V int vrednosti koje ce cuvati vremena obilaska cvorova
    times.resize(V);
    // Na pocetku svi imaju vreme obilaska -1
    /********* C++ deo *********/
    // Funkcija std::fill() prima iterator na pocetak kolekcije i kraj kolekcije i vrednost kojom treba popuniti celu kolekciju
    std::fill(times.begin(), times.end(), -1);

    // Alociramo mesto za V int vrednosti koje ce cuvati lower times obilaska cvorova
    lower_times.resize(V);
    // Na pocetku svi imaju lower times -1
    /********* C++ deo *********/
    // Funkcija std::fill() prima iterator na pocetak kolekcije i kraj kolekcije i vrednost kojom treba popuniti celu kolekciju
    std::fill(lower_times.begin(), lower_times.end(), -1);
  }

  // Funkcija koja dodaje grane u -> v i v -> u u graf (posto je neusmeren)
  void add_edge(int u, int v)
  {
    // Sused cvora u je cvor v
    adjacency_list[u].push_back(v);

    // Sused cvora v je cvor u
    adjacency_list[v].push_back(u);
  }

  // Obilazak grafa u dubinu
  void DFS(int u)
  {
    // Kazemo da je cvor koji trenutno obradjujemo vec posecen
    visited[u] = true;

    // Trenutnom cvoru postavljamo i vreme obilaska i lower time na time
    times[u] = lower_times[u] = time;

    // Uvecavamo time za sledeci cvor
    time++;

    // Broj potomaka cvora na pocetku je 0
    int children = 0;

    // Uzimamo iteratore na pocetak i kraj kolekcije kako bismo prosli kroz sve susede
    // Ako obratimo paznju videcemo da uzimamo adjacency_list[u].begin() i adjacency_list[u].end(), odnosno uzimamo vector suseda cvora u i obradjujemo njih
    auto begin = adjacency_list[u].begin();
    auto end = adjacency_list[u].end();

    while (begin != end) {
      // Ako smo vec posetili cvor necemo ponovo u njega ici, trazimo neposecene cvorove. Za njih pozivamo DFS rekurzivno.
      // Ovde se krije i uslov izlaska iz rekurzije, jer kada nema vise cvorova koji nisu poseceni necemo ici dalje, tj necemo pozivati DFS ponovo
      // begin i end su iteratori (pokazivacke promenljive), pa da bismo dobili vrednost koju cuva begin moramo da ga dereferenciramo, i zato imamo *begin
      if (!visited[*begin]) {

        // Roditelj cvora koji cuva iterator je cvor u
        parents[*begin] = u;

        DFS(*begin);

        // Ako smo nasli na neposecenog suseda, znaci da je broj potomaka cvora v treba da se poveca za 1
        children++;

        // Ako imamo suseda ciji je lower time manji od lower time-a trenutnog cvora onda azuriramo i lower time trenutnog cvora
        lower_times[u] = lower_times[*begin] < lower_times[u] ? lower_times[*begin] : lower_times[u];

        // Ako je vreme tenutnog cvora manje od najranijeg trenutka kada sused *begin moze biti posecen, znaci da je jedini put do *begin preko u. Ako uklonimo tu granu\
        // graf postaje nepovezan, pa je ona most
        if (times[u] < lower_times[*begin])
          std::cout << u << " -> " << *begin << "\n";
      }
      // Ako je sused vec posecen, mozda je njegovo lower time manje od lower time-a cvora u, pa samim tim treba azurirati lower time cvora u
      else if (*begin != parents[u]) {
        lower_times[u] = lower_times[u] < lower_times[*begin] ? lower_times[u] : lower_times[*begin];
      }

      // Krecemo se kroz kolekciju
      begin++;
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
  // Vektor koji cuva cvorove roditelje za svaki od cvorova
  std::vector<int> parents;
  // Vektor koji cuva vremena posecivanja cvorova u DFS obilasku
  std::vector<int> times;
  // Vektor koji cuva lower times za sve cvorove. Lower time je zapravo minamlna vrednost time-a za sve susedne cvorove cvora u
  std::vector<int> lower_times;
  // Vektor koji cuva artikulacione tacke
  std::vector<int> articulation_points;
  // Promenljiva koja predstavlja vreme koje se dodeljuje svakom od cvorova
  int time;
};

int main ()
{
  Graph g(5);

  g.add_edge(0, 2);
  g.add_edge(0, 3);
  g.add_edge(1, 0);
  g.add_edge(2, 1);
  g.add_edge(3, 4);

  g.DFS(0);

  return 0;
}
