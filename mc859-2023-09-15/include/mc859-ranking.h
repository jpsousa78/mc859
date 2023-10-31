#ifndef RANKING_DEFINE
#define RANKING_DEFINE

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
#define MAXK 18
#define MAXDIST 10000

void erro(int i,string s) {cout << "Erro " << i << ": "<< s << endl;}
void erro(int i) {cout << "Erro " << i << "." << endl;}


typedef vector<int> IntVector;
typedef Digraph::NodeMap<vector<int>> DNodePriceMap;

class Ranking_Entrada {
public:
  Ranking_Entrada(string filename);
  Ranking_Entrada(void);
  void ImprimeFormatoArquivo(void);
  void inserenaparte(DNode v,int t);
  bool verificasolucao(void); // 
  int custosolucao(void);
  void imprimesolucao(void);
  bool visualizasolucao(void);
  int k;
  Digraph g;
  DNodeStringMap vname;
  DNodePosMap px;
  DNodePosMap py;
  ArcIntMap antes;
  ArcIntMap igual;
  ArcIntMap depois;
  int nnodes;
  int narcs;
  DNodeIntMap solucao; // parte que pertence o vertice
};

Ranking_Entrada::Ranking_Entrada(string filename):
  vname(this->g),
  px(this->g),
  py(this->g),
  antes(this->g),
  igual(this->g),
  depois(this->g),
  solucao(this->g)
{
  ifstream inputfile;

  inputfile.open(filename);
  //--------------------------------------------
  StringTable TabHeader(1,inputfile);
  if (!TabHeader.first("k",this->k))
    cout << "Erro: Erro no formato do arquivo " << filename << ": k" << endl;
  if (!TabHeader.first("nnodes",this->nnodes))
    cout << "Erro: Erro no formato do arquivo " << filename << ": nnodes" << endl;
  if (!TabHeader.first("narcs",this->narcs))
    cout << "Erro: Erro no formato do arquivo " << filename << ": narcs" << endl;
  //--------------------------------------------
  StringTable TabNodes(this->nnodes,inputfile);
  vector <string> v_name(this->nnodes);
  vector <int> v_posx(this->nnodes);
  vector <int> v_posy(this->nnodes);
  TabNodes.readcolumn("vname",v_name);
  TabNodes.readcolumn("posx",v_posx);
  TabNodes.readcolumn("posy",v_posy);
  DNode v[this->nnodes];
  for (int i=0;i<this->nnodes;i++) {
    v[i]=this->g.addNode();
    this->vname[v[i]] = v_name[i];
    this->px[v[i]] = v_posx[i];
    this->py[v[i]] = v_posy[i];
  }

  //--------------------------------------------
  StringTable TabArcos(this->narcs,inputfile);
  vector <string> v_origem(this->narcs);
  vector <string> v_destino(this->narcs);
  vector <int> v_antes(this->narcs);
  vector <int> v_igual(this->narcs);
  vector <int> v_depois(this->narcs);
  TabArcos.readcolumn("origem",v_origem);
  TabArcos.readcolumn("destino",v_destino);
  TabArcos.readcolumn("antes",v_antes);
  TabArcos.readcolumn("igual",v_igual);
  TabArcos.readcolumn("depois",v_depois);
  for (int i=0;i<this->narcs;i++){
    DNode origem=INVALID,destino=INVALID;
    for (DNodeIt u(this->g);u!=INVALID;++u) 
      if (this->vname[u]==v_origem[i]) {origem=u;break;}
    for (DNodeIt u(this->g);u!=INVALID;++u) 
      if (this->vname[u]==v_destino[i]) {destino=u;break;}
    Arc a=this->g.addArc(origem,destino);
    this->antes[a] = v_antes[i];
    this->igual[a] = v_igual[i];
    this->depois[a] = v_depois[i];
  }
  for (DNodeIt v(this->g);v!=INVALID;++v) this->solucao[v] = -1;// nao tem parte ainda.
}


Ranking_Entrada::Ranking_Entrada(void) :
  vname(this->g),
  px(this->g),
  py(this->g),
  antes(this->g),
  igual(this->g),
  depois(this->g),
  solucao(this->g)
{
}


void Ranking_Entrada::ImprimeFormatoArquivo(void)
{
  //---------------------------------------------------------------
  cout << "#\n";
  cout << "# Projeto para encontrar ranking de produtos em k partes.\n";
  cout << "#\n";
  cout << "#\n";
  cout << "#----------- Cabecalho com informacoes iniciais ----------\n";
  cout << "k nnodes narcs\n";
  cout << this->k << " " << this->nnodes << " " << this->narcs << endl;
  //---------------------------------------------------------------
  cout << "#\n";
  cout << "#----------- Lista de no's e suas coordenadas ----------\n";
  cout << "vname posx posy " << endl ;
  for (DNodeIt v(this->g);v!=INVALID;++v) {
    cout << this->vname[v] << " " << this->px[v] << " " << this->py[v] << endl;}
  //---------------------------------------------------------------
  cout << "#\n";
  cout << "#--- Pares (u,v) e custos se u e' colocado antes (resp. igual, depois) que parte de v ---\n";
  cout << "origem destino antes igual depois" << endl;
  for (ArcIt e(this->g);e!=INVALID;++e) {
    cout << this->vname[this->g.source(e)] << " " << this->vname[this->g.target(e)] << " " << this->antes[e] << " " << this->igual[e] << " "<<this->depois[e] << endl;
  }
}

void Ranking_Entrada::inserenaparte(DNode v,int t)
{  this->solucao[v] = t; }

bool Ranking_Entrada::verificasolucao(void)
{
  DNode No,v;
  int ok;
  ok=true;
  for (DNodeIt v(this->g);v!=INVALID;++v) {
    if ((this->solucao[v]<0) || (this->solucao[v]>=this->k)){
      cout << "Erro: Produto "<<this->vname[v]<<
	" classificado com parte invalida: "<<this->solucao[v]<<endl;
      ok=false;}}
  return(ok);
}

int Ranking_Entrada::custosolucao(void)
{
  int custo;
  custo=0;
  for (ArcIt a(this->g);a!=INVALID;++a) {
    if (this->solucao[this->g.source(a)] < this->solucao[this->g.target(a)])
      custo += this->antes[a];
    else if (this->solucao[this->g.source(a)] > this->solucao[this->g.target(a)])
      custo += this->depois[a];
    else custo += this->igual[a];
  }
  return(custo);
}

DNodeIntMap *sol;
int compareDNode(DNode a,DNode b){return ((*sol)[a]-(*sol)[b]);}
void Ranking_Entrada::imprimesolucao(void)
{
  vector <DNode> V(this->nnodes);
  int i;
  i=0;
  for (DNodeIt v(this->g);v!=INVALID;++v) {V[i] = v;i++;}
  sol=&this->solucao;
  sort(V.begin(),V.end(),compareDNode);
  for (int i=0;i<this->nnodes;i++)
    cout<<"No "<<this->vname[V[i]]<<" parte "<<this->solucao[V[i]]<<endl;
  return;
}

bool Ranking_Entrada::visualizasolucao(void)
{
  if (!this->verificasolucao()) {
    cout<<"Erro: Erro na solucao. Nao e' possivel visualizar a solucao."<<endl;}
  if (this->k > SizeVisualDistinctColor()) {
    cout << "Erro: Numero de partes muito maior que o numero de cores distintas armazenadas.\n";
    return(false);
  }
  DigraphAttributes G(this->g,this->vname,this->px,this->py);
  G.SetDigraphAttrib("splines=false");
  G.SetDefaultDNodeAttrib("color=Gray style=filled width=0.2 height=0.2 fixedsize=true");
  for (ArcIt a(this->g);a!=INVALID;++a) G.SetColor(a,"Invis");// todos arcos de invisivel
  for (DNodeIt v(this->g);v!=INVALID;++v)
    G.SetColor(v,ColorName(ith_VisualDistinctColor(this->solucao[v])));
  G.SetDigraphAttrib("label=\"Cada cor distinta representa uma parte. Custo da solucao "+
		     IntToString(this->custosolucao())+"\"");
  G.View();
  return(true);
}

#endif
