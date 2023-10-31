
// Project and Analysis of Algorithms
// Flávio Keidi Miyazawa
// Problems with connectivity: Generate Triangulated Digraph 
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <lemon/list_graph.h>
#include "mygraphlib.h"
#include <string>
#include "myutils.h"
#include <lemon/concepts/digraph.h>
#include <lemon/preflow.h>
using namespace lemon;
#define MAXNODES 1000
#define MAXITENS 1000
#define MAXPESO 100
#define MAXPRECO 1000
#define MAXDIST 1000


//typedef int IntVectorType[MAXITENS];
typedef struct IntVectorType {int x[MAXITENS];} IntVectorType;
typedef Digraph::NodeMap<IntVectorType> DNodePriceMap;

class Compras_Entrada {
public:
  Compras_Entrada(Digraph &graph,
		  DNodeStringMap &vvname,
		  DNodePosMap &posx,
		  DNodePosMap &posy,
		  ArcIntMap &edist,
		  int &number_nodes,
		  int &number_arcs,
		  int &number_itens,
		  IntVectorType &peso_item, // peso de cada item
		  DNodePriceMap &preco_item // preco[v][i] indica o preco do item i no vertice v
		  );
  Digraph &g;
  DNodeStringMap &vname;
  DNodePosMap &px;
  DNodePosMap &py;
  ArcIntMap &dist;
  int &nnodes;
  int &narcs;
  int &nitens;
  IntVectorType &peso;
  DNodePriceMap &preco; // preco[v][i] indica o preco do item i no vertice v
};

Compras_Entrada::Compras_Entrada(Digraph &graph,
		  DNodeStringMap &vvname,
		  DNodePosMap &posx,
		  DNodePosMap &posy,
		  ArcIntMap &edist,
		  int &number_nodes,
		  int &number_arcs,
		  int &number_itens,
		  IntVectorType &peso_item, // peso de cada item
		  DNodePriceMap &preco_item // preco[v][i] indica o preco do item i no vertice v
				 ):
  g(graph),vname(vvname),px(posx),py(posy),dist(edist),nnodes(number_nodes),narcs(number_arcs),nitens(number_itens),peso(peso_item),preco(preco_item) {
}
void Imprime_Compras_Entrada(Compras_Entrada &C)
{
  //---------------------------------------------------------------
  cout << "nnodes nitens narcs\n";
  cout << C.nnodes << " " << C.nitens << " " << C.narcs << endl;
  //---------------------------------------------------------------
  cout << "item" << " peso" << endl ;
  for (int i=0;i<C.nitens;i++) cout << i << " " << C.peso.x[i] << endl;
  //---------------------------------------------------------------
  cout << "vname" << " posx posy " ;
  for (int j=0;j<C.nitens;j++) cout << "preco_"+IntToString(j) << " ";
  cout << endl;
  for (DNodeIt v(C.g);v!=INVALID;++v) {
    cout << C.vname[v] << " " << C.px[v] << " " << C.py[v] << " ";
    for (int j=0;j<C.nitens;j++) cout << C.preco[v].x[j] << " ";
    cout << endl;
  }
  //---------------------------------------------------------------
  cout << "origem destino dist" << endl;
  for (ArcIt e(C.g);e!=INVALID;++e) {
    cout << C.vname[C.g.source(e)] << " " << C.vname[C.g.target(e)] << " " << C.dist[e] << endl;
  }
}


void Heuristica(Compras_Entrada &C)
{
  cout << "\n\nImplementar a Heuristica\n\n" << endl;
}


int main(int argc, char *argv[]) 
{
  int seed;
  int box_width,box_height;
  Digraph g;  // graph declaration
  DNodeStringMap vname(g);  // name of graph nodes
  DNodePosMap px(g),py(g);  // xy-coodinates for each node
  ArcIntMap dist(g);   // edge weights
  IntVectorType peso;
  DNodePriceMap preco(g); // preco[v][i] indica  
  int nnodes,nitens,narcs;
  double edge_factor;
  DNode V[MAXNODES];

  // double cutoff;   // used to prune non promissing branches (of the B&B tree)
  //cout << "argc = " << argc << endl;
  if (argc!=2) {cout<<"Usage: "<< argv[0]<<" <filename>"<< endl;exit(0);}

  ifstream inputfile;
  inputfile.open(argv[1]);
  //--------------------------------------------
  StringTable TabHeader(1,inputfile);
  nnodes=TabHeader.firstint("nnodes");
  narcs=TabHeader.firstint("narcs");
  nitens=TabHeader.firstint("nitens");
  //--------------------------------------------
  StringTable TabItens(nitens,inputfile);
  vector <int> v_item(nitens);
  vector <int> v_peso(nitens);
  TabItens.readcolumn("item",v_item);
  TabItens.readcolumn("peso",v_peso);
  for (int i=0;i<nitens;i++) peso.x[v_item[i]] = v_peso[i];
  //--------------------------------------------
  StringTable TabNodes(nnodes,inputfile);
  vector <string> v_name(nnodes);
  vector <int> v_posx(nnodes);
  vector <int> v_posy(nnodes);
  vector <int> v_preco(nnodes);
  TabNodes.readcolumn("vname",v_name);
  TabNodes.readcolumn("posx",v_posx);
  TabNodes.readcolumn("posy",v_posy);
  DNode v[nnodes];
  for (int i=0;i<nnodes;i++) {
    v[i]=g.addNode();
    vname[v[i]] = v_name[i];
    px[v[i]] = v_posx[i];
    py[v[i]] = v_posy[i];
  }
  for (int j=0;j<nitens;j++) {
    TabNodes.readcolumn("preco_"+IntToString(j),v_preco);
    for (int i=0;i<nnodes;i++) preco[v[i]].x[j] = v_preco[i];
  }
  //--------------------------------------------
  StringTable TabArcos(narcs,inputfile);
  vector <string> v_origem(narcs);
  vector <string> v_destino(narcs);
  vector <int> v_dist(narcs);
  TabArcos.readcolumn("origem",v_origem);
  TabArcos.readcolumn("destino",v_destino);
  TabArcos.readcolumn("dist",v_dist);
  for (int i=0;i<narcs;i++){
    DNode origem=INVALID,destino=INVALID;
    for (DNodeIt u(g);u!=INVALID;++u) 
      if (vname[u]==v_origem[i]) {origem=u;break;}
    for (DNodeIt u(g);u!=INVALID;++u) 
      if (vname[u]==v_destino[i]) {destino=u;break;}
    Arc a=g.addArc(origem,destino);
    dist[a] = v_dist[i];
  }
  Compras_Entrada C(g,vname,px,py,dist,nnodes,narcs,nitens,peso,preco);
  Imprime_Compras_Entrada(C);
  Heuristica(C);
  return 0;
}

