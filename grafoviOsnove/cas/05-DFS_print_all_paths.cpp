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

  }

  // Funkcija koja dodaje granu u -> v u graf
  void add_edge(int u, int v)
  {
    // Sused cvora u je cvor v
    adjacency_list[u].push_back(v);
  }

  // DFS koji prima pocetni krajnji cvor i vektor u koji ce se smestati rezultat, odnosno putanju od u do v
  // Obratiti paznju da NE SME biti slato kao referenca, 
  // jer cemo onda stalno menjati isti vektor, a nama zapravo treba za svaki put odvojen vector
  void DFS(int u, int v, std::vector<int> result)
  {
    // Ako smo dosli do cilja, dodajemo i njega u result i ispisujemo put od u do v
    if (u == v) {
      result.push_back(v);
      int i;
      for (i = 0; i < result.size() - 1; i++)
        std::cout << result[i] << " -> ";

      std::cout << result[i] << std::endl;

      // Kraj rekurzije
      return ;
    }

    // Kazemo da je cvor koji trenutno obradjujemo vec posecen
    visited[u] = true;

    // Ubacujemo cvor u result, kako bismo pamtili put kojim smo isli
    result.push_back(u);

    // Uzimamo iteratore na pocetak i kraj kolekcije kako bismo prosli kroz sve susede
    // Ako obratimo paznju videcemo da uzimamo adjacency_list[u].begin() i adjacency_list[u].end(), 
	//odnosno uzimamo vector suseda cvora u i obradjujemo njih
    auto begin = adjacency_list[u].begin();
    auto end = adjacency_list[u].end();

    while (begin != end) {
      // Ako smo vec posetili cvor necemo ponovo u njega ici, trazimo neposecene cvorove. 
	  // Za njih pozivamo DFS rekurzivno.
      // Ovde se krije i uslov izlaska iz rekurzije, jer kada nema vise cvorova koji nisu poseceni necemo ici dalje, 
	   //tj. necemo pozivati DFS ponovo
      // begin i end su iteratori (pokazivacke promenljive), pa da bismo dobili vrednost koju cuva begin moramo da ga dereferenciramo, i zato imamo *begin
      if (!visited[*begin])
        DFS(*begin, v, result);

      // Krecemo se kroz kolekciju
      begin++;
    }

    // Ovo je neophodan uslov, jer mi zelimo zapravo da nadjemo sve putanje od u do v, tako da kada se zavrsi deo putanje kroz jedan cvor on treba da postane neposecen
    // jer mozda postoji drugi put koji ide kroz taj cvor
    visited[u] = false;
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
  int u, v;

  std::cin >> u >> v;

  Graph g(4);

  g.add_edge(0, 1);
  g.add_edge(0, 2);
  g.add_edge(0, 3);
  g.add_edge(2, 0);
  g.add_edge(2, 1);
  g.add_edge(1, 3);

  std::vector<int> result;

  g.DFS(u, v, result);

  return 0;
}
