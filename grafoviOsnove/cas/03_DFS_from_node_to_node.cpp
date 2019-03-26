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
    // Metod std::fill() prima iterator na pocetak kolekcije i kraj kolekcije i vrednost kojom treba popuniti celu kolekciju
    std::fill(visited.begin(), visited.end(), false);

    // Alociramo memoriju za V vectora, jer znamo da ce ih biti V, a svaki od njih cemo povecavati za po jedan element pomocu vector.push_back()
    adjacency_list.resize(V);

    // Postavljamo promenljivu found na false odnosno nismo uspeli da nadjemo cvor na samom pocetku pretrage
    found = false;
  }

  // Funkcija koja dodaje granu u -> v u graf
  void add_edge(int u, int v)
  {
    // Sused cvora u je cvor v
    adjacency_list[u].push_back(v);
  }

  // Pretraga u dubinu koja pamti sve cvorove kojima smo isli do ciljnog cvora. u je pocetni, v ciljni cvor,
 // vektor result cuva bas putanju od u do v kojom smo isli
  void DFS(int u, int v, std::vector<int> &result)
  {
    // Ako smo nasli cvor
    if (u == v) {
      // Ubacujemo u result i ciljni cvor
      result.push_back(v);
      // Kazemo da smo nasli cvor
      found = true;
      // Izlazimo iz rekurzije
      return ;
    }

    // Kazemo da je cvor koji trenutno obradjujemo vec posecen
    visited[u] = true;

    // Ubacujemo cvor u result, kako bismo pamtili put kojim smo isli
    result.push_back(u);

    // Uzimamo iteratore na pocetak i kraj kolekcije kako bismo prosli kroz sve susede
    // Ako obratimo paznju videcemo da uzimamo adjacency_list[u].begin() i adjacency_list[u].end(), odnosno uzimamo vector suseda cvora u i obradjujemo njih
    auto begin = adjacency_list[u].begin();
    auto end = adjacency_list[u].end();

    while (begin != end) {
      // Ako nismo vec posetili cvor ali i ako nismo nasli put idemo dalje, ako smo vec nasli put od u do v, sacuvan je u result i necemo dalje da idemo nigde
      if (!visited[*begin] && !found)
        DFS(*begin, v, result);

      // Krecemo se kroz kolekciju
      begin++;
    }
  }

  // Getter za promenljivu found
  bool get_found()
  {
    return found;
  }

private:
  // Lista susedstva. Imamo vector vector-a, sto znaci za svaki od cvorova [0,V) imamo po jednu listu koja cuva susede odgovarajuceg cvora
  std::vector<std::vector<int>> adjacency_list;
  // Broj cvorova grafa
  int V;
  // Lista posecenih cvorova. Da ne bismo ulazili u beskonacnu rekurziju ne zelimo da obilazimo cvorove koje smo vec obisli na putu kojim smo krenuli, zato cuvamo listu
  // posecenih cvorova
  std::vector<bool> visited;
  // Promenljiva koja nam govori da li smo pronasli ciljni cvor
  bool found;
};

int main ()
{
  int u, v;

  std::cin >> u >> v;

  Graph g(4);

  g.add_edge(0, 1);
  g.add_edge(0, 2);
  g.add_edge(1, 2);
  g.add_edge(2, 0);
  g.add_edge(2, 3);
  g.add_edge(3, 3);

  std::vector<int> result;

  g.DFS(u, v, result); //pokrecemo DFS bas iz cvora u

  // Ukoliko je found ostalo false znaci da nema puta od u do v
  if (!g.get_found())
    std::cout << "Nema puta!\n";
  // Inace ispisujemo put od u do v
  else {
    int i;
    for (i = 0; i < result.size() - 1; i++)
      std::cout << result[i] << " -> ";

    std::cout << result[i] << std::endl;
  }

  return 0;
}
