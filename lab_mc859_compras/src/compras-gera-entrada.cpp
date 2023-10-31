
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
  int nnodes,narcs,nitens=1000;
  double edge_factor;
  DNode V[MAXNODES];

  // double cutoff;   // used to prune non promissing branches (of the B&B tree)
  //cout << "argc = " << argc << endl;
  if (argc!=5) {cout<<"Usage: "<< argv[0]<<" <seed> <number_of_nodes_in_graph> <number_of_itens> <edge_factor>"<< endl;exit(0);}

  seed = atoi(argv[1]);
  srand48(seed);
  nnodes = atoi(argv[2]);
  nitens = atoi(argv[3]);
  if (nnodes>MAXNODES) {
    cout << "ERROR: maximum number of nodes is " << MAXNODES << endl;
    exit(1);
  }
  narcs = nnodes*(nnodes-1);
  if (nitens>MAXITENS) {
    cout << "ERROR: maximum number of itens is " << MAXITENS << endl;
    exit(1);
  }
  edge_factor = atof(argv[4]); // a factor between 0 and 1.
  box_width = 10000;// todos vertices tem coordenadas x,y em {0,...,10000}
  box_height = 10000;

  for (int i=0;i<nitens;i++) peso.x[i] = (int) (1.0 + drand48()*MAXPESO);
  
  for (int i=0;i<nnodes;i++) {
    DNode v=g.addNode();
    V[i] = v;
    vname[v] = IntToString(i);
    for (int j=0;j<nitens;j++) preco[v].x[j] = (int) (1.0 + drand48()*MAXPRECO);
    px[v] = (int) (1.0+drand48()*box_width);
    py[v] = (int) (1.0+drand48()*box_height);
    }
  for (int i=0;i<nnodes;i++) {
    for (int j=0;j<nnodes;j++) {
      if (i!=j) {
	Arc a=g.addArc(V[i],V[j]);
	dist[a] = (int) (MAXDIST*sqrt(pow(px[V[i]]-px[V[j]],2)+pow(py[V[i]]-py[V[j]],2)));
	// Coloca alguma variacao nas distancias
	dist[a] = (int) (1.0 + 0.9*dist[a]  +  drand48()*0.1*dist[a]);
      }
    }
  }
  Compras_Entrada C(g,vname,px,py,dist,nnodes,narcs,nitens,peso,preco);
  Imprime_Compras_Entrada(C);
  return 0;
}

