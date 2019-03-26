#include <iostream>
#include <vector>
#include <algorithm>

// Klasa kojom cemo predstavljati graf
class Graph
{
public:
  // Konstruktor za graf koji samo prima broj cvorova grafa
  Graph(int V)
  {
    // Broj cvorova grafa je jednak prosledjenom argumentu
    this->V = V;

    // Alociramo memoriju za V vectora, 
	// jer znamo da ce ih biti V, a svaki od njih cemo povecavati za po jedan element pomocu vector.push_back()
    adjacency_list.resize(V);

    // Alociramo mesto za V bool vrednosti koje ce cuvati posecene cvorove
    visited.resize(V);
    // Na pocetku nijedan cvor nije posecen
    /********* C++ deo *********/
    // Metod std::fill() prima iterator na pocetak kolekcije i kraj kolekcije i vrednost kojom treba popuniti celu kolekciju
    std::fill(visited.begin(), visited.end(), false);

    // Alociramo mesto za V int vrednosti koje ce cuvati boje cvorova
    colors.resize(V);
    // Na pocetku je boja svih cvorova -1
    /********* C++ deo *********/
    // Metod std::fill() prima iterator na pocetak kolekcije i kraj kolekcije i vrednost kojom treba popuniti celu kolekciju
    std::fill(colors.begin(), colors.end(), -1);
  }

  // Funkcija koja dodaje granu u -> v u graf
  void add_edge(int u, int v)
  {
    // Sused cvora u je cvor v
    adjacency_list[u].push_back(v);
  }

  // DFS ce nam ovde vracati bool. Ako je graf bipartitan vracace true inace false
  bool DFS(int u, int color)
  {
    // Kazemo da je cvor koji trenutno obradjujemo vec posecen
    visited[u] = true;

    // Dodeljujemo pocetnom cvoru jednu boju. Boje su iz skupa [0,1]
    colors[u] = color;

    // Uzimamo iteratore na pocetak i kraj kolekcije kako bismo prosli kroz sve susede
    // Ako obratimo paznju videcemo da uzimamo adjacency_list[u].begin() i adjacency_list[u].end(), 
	// odnosno uzimamo vector suseda cvora u i obradjujemo njih
    auto begin = adjacency_list[u].begin();
    auto end = adjacency_list[u].end();

    while (begin != end) {
      // Ukoliko se desi da cvor koji zelimo da posetimo vec ima dodeljenu boju i da je ta boja ista kao i kod cvora v,
     //	 to znaci da imamo 2 suseda koja imaju istu boju,
      // tj. pripadaju istoj particiji, te onda vracamo false, jer smo sigurni da nam graf u tom slucaju nije bipartitan
      if (colors[*begin] == colors[u]) {
        return false;
      }

      // Ako smo vec posetili cvor necemo ponovo u njega ici, trazimo neposecene cvorove. Za njih pozivamo DFS rekurzivno, i to sa drugom bojom. Ako je u imao boju 0, svi
      // njegovi susedi treba da imaju 1 i obratno
      // Ovde se krije i uslov izlaska iz rekurzije, jer kada nema vise cvorova koji nisu poseceni necemo ici dalje, tj necemo pozivati DFS ponovo
      // begin i end su iteratori (pokazivacke promenljive), pa da bismo dobili vrednost koju cuva begin moramo da ga dereferenciramo, i zato imamo *begin
      if (!visited[*begin]) {
        // Ukoliko nam se iz nekog od rekurzivnih poziva vraca false, pa imamo dokaz da graf nije bipartitan, i odmah vracamo false, nema potrebe dalje bilo sta proveravati
        if (!DFS(*begin, !color))
          return false;
      }
      // Krecemo se kroz kolekciju
      begin++;
    }

    // Ukoliko dodjemo do ovde znaci da nismo nasli nigde da graf nije bipartitan pa vracamo true
    return true;
  }

private:
  // Lista susedstva. Imamo vector vector-a, sto znaci za svaki od cvorova [0,V) imamo po jednu listu koja cuva susede odgovarajuceg cvora
  std::vector<std::vector<int>> adjacency_list;
  // Broj cvorova grafa
  int V;
  // Lista posecenih cvorova. Da ne bismo ulazili u beskonacnu rekurziju ne zelimo da obilazimo cvorove koje smo vec obisli na putu kojim smo krenuli, zato cuvamo listu
  // posecenih cvorova
  std::vector<bool> visited;
  // Vektor koji nam cuva samo boju za svaki od cvorova
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


  std::cout << g.DFS(0, 0) << "\n";

  return 0;
}
