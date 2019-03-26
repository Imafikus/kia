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

  // Dodajemo granu u -> v i v -> u, posto je graf neusmeren, mozemo to ovako da oznacimo
  void add_edge(int u, int v)
  {
    // Sused cvora v je cvor u
    adjacency_list[v].push_back(u);
    // Sused cvora u je cvor v
    adjacency_list[u].push_back(v);
  }

  bool DFS(int u, int parent)
  {
    // Kazemo da je cvor koji trenutno obradjujemo vec posecen
    visited[u] = true;

    // Uzimamo iteratore na pocetak i kraj kolekcije kako bismo prosli kroz sve susede
    // Ako obratimo paznju videcemo da uzimamo adjacency_list[u].begin() i adjacency_list[u].end(), odnosno uzimamo vector suseda cvora u i obradjujemo njih
    auto begin = adjacency_list[u].begin();
    auto end = adjacency_list[u].end();

    while (begin != end) {
      // Slicno kao u usmerenom grafu, ako je cvor vidjen vec znaci da imamo ciklus. Kako je graf neusmeren, ovde ce se uvek doci do svih cvorova ako je graf povezan,
      // ne obracamo paznju na "trenutni put" jer je trenutni put onaj koji ce otici do svih cvorova, i ako ima ciklusa znacemo da on postoji ako hocemo da odemo u vec
      // poseceni cvor. Ono na sta treba obratiti paznju to je da ako imamo 0 -> 1 (neusmeren je graf, ali se krecemo do cvora 0 ka cvoru 1) sused od 0 je jedan, ali je
      // i sused od 1 0. Onda da nam ovaj slucaj ne bi pravi problem, za svaki cvor pamtimo "roditelja", tj cvor iz koga smo dosli do njega. Ako smo iz 0 dosli do 1,
      // onda znamo da je 0 sigurno vec vidjen cvor. I ako naidjemo na njega to znaci da nemamo ciklus. Ali ako naidjemo na cvor koji je posecen a nije roditelj to nam
      // oznacava ciklus
      if (visited[*begin]) {
        if (*begin != parent)
          return true;
      }
      // Ako odnekud dobijemo informaciju da imamo ciklus onda samo vratimo true kao tu informaciju
      else if (DFS(*begin, u)) {
        return true;
      }

      // Krecemo se kroz kolekciju
      begin++;
    }

    // Ako smo prosli sve covorve i nismo nasli ciklus (izasli u while petlji), onda vracamo indikator da ciklus ne postoji
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

 std::cout << g.DFS(0, -1) << std::endl;

  return 0;
}
