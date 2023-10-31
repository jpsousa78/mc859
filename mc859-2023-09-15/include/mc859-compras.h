#ifndef COMPRAS_DEFINE
#define COMPRAS_DEFINE

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

void erro(int i,string s) {cout << "Erro " << i << ": "<< s << endl;}
void erro(int i) {cout << "Erro " << i << "." << endl;}


typedef vector<int> IntVector;
typedef Digraph::NodeMap<vector<int>> DNodePriceMap;

class Compras_Entrada {
public:
  Compras_Entrada(string filename);
  Compras_Entrada(void);
  void ImprimeFormatoArquivo(void);
  long long int custoaresta(Arc a,int peso);
  void esvaziasolucao(void); // faz sequencia de no's da solucao ficar vazia
  void inserelojasolucao(DNode No); // insere um no' no fim da solucao atual
  bool verificasolucao(void); // 
  long long int custosolucao(void);
  void imprimesolucao(void);
  bool visualizasolucao(void);
  Digraph g;
  DNode Deposito;
  DNodeStringMap vname;
  DNodePosMap px;
  DNodePosMap py;
  ArcIntMap dist;
  ArcIntMap fatorpeso;
  int nnodes;
  int narcs;
  int nitens;
  IntVector peso;
  DNodePriceMap preco; // preco[v][i] indica o preco do item i no vertice v
  int nnodesequence; // number of nodes in the sequence solution
  vector <DNode> nodesequence = vector <DNode>(MAXNODES); // sequencia de lojas (sem considerar deposito)
  vector <DNode> lojaitem = vector <DNode>(MAXITENS); // loja onde o item foi comprado
};

Compras_Entrada::Compras_Entrada(string filename) :
  vname(this->g),
  px(this->g),
  py(this->g),
  dist(this->g),
  fatorpeso(this->g),
  preco(this->g)
{
  string depname;
  ifstream inputfile;

  inputfile.open(filename);
  //--------------------------------------------
  StringTable TabHeader(1,inputfile);
  if (!TabHeader.first("nnodes",this->nnodes))
    cout << "Erro: Erro no formato do arquivo " << filename << ": nnodes." << endl;
  if (!TabHeader.first("narcs",this->narcs))
    cout << "Erro: Erro no formato do arquivo " << filename << ": narcs." << endl;
  if (!TabHeader.first("nitens",this->nitens))
    cout << "Erro: Erro no formato do arquivo " << filename << ": nitens." << endl;
  if (!TabHeader.first("deposito",depname))
    cout << "Erro: Erro no formato do arquivo " << filename << ": deposito." << endl;
  cout << "Deposito eh o no' " << depname << endl;
  //--------------------------------------------
  StringTable TabItens(this->nitens,inputfile);
  vector <int> v_item(nitens);
  this->peso.resize(nitens);
  TabItens.readcolumn("item",v_item);
  TabItens.readcolumn("peso",peso);
  //--------------------------------------------
  StringTable TabNodes(this->nnodes,inputfile);
  vector <string> v_name(this->nnodes);
  vector <int> v_posx(this->nnodes);
  vector <int> v_posy(this->nnodes);
  vector <int> v_preco(this->nnodes);
  TabNodes.readcolumn("vname",v_name);
  TabNodes.readcolumn("posx",v_posx);
  TabNodes.readcolumn("posy",v_posy);
  DNode v[this->nnodes];
  this->Deposito=INVALID;
  for (int i=0;i<this->nnodes;i++) {
    v[i]=this->g.addNode();
    this->vname[v[i]] = v_name[i];
    if (this->vname[v[i]]==depname) this->Deposito = v[i];
    this->px[v[i]] = v_posx[i];
    this->py[v[i]] = v_posy[i];
  }
  if (this->Deposito==INVALID){
    cout<<"Erro: Nao encontrou no' "<<depname<<" referente ao deposito."<<endl;
    exit(1);}
  for (DNodeIt v(this->g); v!=INVALID; ++v) this->preco[v].resize(nitens);
  for (int j=0;j<this->nitens;j++) {
    TabNodes.readcolumn("preco_"+IntToString(j),v_preco);
    for (int i=0;i<this->nnodes;i++) {
      //cout << "It. item " << j << "; No " << vname[v[i]] << endl;
      this->preco[v[i]][j] = v_preco[i];
    }
  }
  //--------------------------------------------
  StringTable TabArcos(this->narcs,inputfile);
  vector <string> v_origem(this->narcs);
  vector <string> v_destino(this->narcs);
  vector <int> v_dist(this->narcs);
  vector <int> v_fatorpeso(this->narcs);
  TabArcos.readcolumn("origem",v_origem);
  TabArcos.readcolumn("destino",v_destino);
  TabArcos.readcolumn("dist",v_dist);
  TabArcos.readcolumn("fatorpeso",v_fatorpeso);
  for (int i=0;i<this->narcs;i++){
    DNode origem=INVALID,destino=INVALID;
    for (DNodeIt u(this->g);u!=INVALID;++u) 
      if (this->vname[u]==v_origem[i]) {origem=u;break;}
    for (DNodeIt u(this->g);u!=INVALID;++u) 
      if (this->vname[u]==v_destino[i]) {destino=u;break;}
    Arc a=this->g.addArc(origem,destino);
    this->dist[a] = v_dist[i];
    this->fatorpeso[a] = v_fatorpeso[i];
  }
}


Compras_Entrada::Compras_Entrada(void) :
  vname(this->g),
  px(this->g),
  py(this->g),
  dist(this->g),
  fatorpeso(this->g),
  preco(this->g)
{
}


void Compras_Entrada::ImprimeFormatoArquivo(void)
{
  //---------------------------------------------------------------
  cout << "#\n";
  cout << "# Projeto para encontrar rota para compras.\n";
  cout << "#\n";
  cout << "#\n";
  cout << "#----------- Cabecalho com informacoes iniciais ----------\n";
  cout << "nnodes nitens narcs deposito\n";
  cout << this->nnodes << " " << this->nitens << " " << this->narcs << " " << this->vname[this->Deposito] << endl;
  //---------------------------------------------------------------
  cout << "#\n";
  cout << "#----------- Lista de itens e seus pesos ----------\n";
  cout << "item" << " peso" << endl ;
  for (int i=0;i<this->nitens;i++) cout << i << " " << this->peso[i] << endl;
  //---------------------------------------------------------------
  cout << "#\n";
  cout << "#----------- Lista de lojas, suas coordenadas e precos dos itens ----------\n";
  cout << "vname" << " posx posy " ;
  for (int j=0;j<this->nitens;j++) cout << "preco_"+IntToString(j) << " ";
  cout << endl;
  for (DNodeIt v(this->g);v!=INVALID;++v) {
    cout << this->vname[v] << " " << this->px[v] << " " << this->py[v] << " ";
    for (int j=0;j<this->nitens;j++) cout << this->preco[v][j] << " ";
    cout << endl;
  }
  //---------------------------------------------------------------
  cout << "#\n";
  cout << "#----------- Grafo formado pelas lojas ----------\n";
  cout << "origem destino dist fatorpeso" << endl;
  for (ArcIt e(this->g);e!=INVALID;++e) {
    cout << this->vname[this->g.source(e)] << " " << this->vname[this->g.target(e)] << " " << this->dist[e] << " " << this->fatorpeso[e] << endl;
  }
}

long long int Compras_Entrada::custoaresta(Arc a,int peso)
{
  return((long long int) this->dist[a] + this->fatorpeso[a]*peso);
}
void Compras_Entrada::esvaziasolucao(void)
{
  this->nnodesequence = 0;
}
void Compras_Entrada::inserelojasolucao(DNode No)
{
  this->nodesequence[this->nnodesequence] = No;
  this->nnodesequence++;
}

bool Compras_Entrada::verificasolucao(void)
{
  DNode No,v;
  int ok;
  DNodeBoolMap Visitado(this->g);
  cout<<"Deposito: "<<this->vname[this->Deposito]<<endl<<endl;
  if (this->nnodesequence<2){
    cout<<"Erro: Solucao deve ter pelo menos dois no's."<<endl;return(false);}
  if (this->nodesequence[0]!=this->Deposito){
    cout<<"Erro: Primeiro no' da solucao deve ser o deposito."<<endl;
    cout<<this->vname[this->nodesequence[0]]<<" e "<<this->vname[this->Deposito]<<endl;
    return(false);}
  if (this->nodesequence[this->nnodesequence-1]!=this->Deposito){
    cout<<"Erro: Ultimo no' da solucao deve ser o deposito."<<endl;return(false);}
  for (DNodeIt v(this->g);v!=INVALID;++v) Visitado[v]=false;
  for (int j=0;j<this->nnodesequence-1;j++) {
    Visitado[this->nodesequence[j]] = true;
    ok = 0;
    for (OutArcIt a(this->g,this->nodesequence[j]);a!=INVALID;++a) {
      if (this->g.target(a)==this->nodesequence[j+1]) { // achou aresta que liga no's
	ok = 1;	break; }}
    if (!ok){
      cout<<"Erro: Nao encontrou arco da loja "<<
	this->vname[nodesequence[j]] << " para a loja " <<
	this->vname[nodesequence[j+1]]<<"."<<endl;
      return(false);}
  }
  for (int i=0;i<this->nitens;i++) {
    if (!Visitado[this->lojaitem[i]]) {
      cout<<"Erro: Loja do item "<<i<<" nao esta' na solucao."<<endl; return(false);}
  }
  return(true);
}

long long int Compras_Entrada::custosolucao(void)
{
  int ok;
  long long int custocorrente,pesocorrente;
  pesocorrente=0;
  custocorrente=0;
  for (int j=0;j<this->nnodesequence-1;j++) {
    ok = 0;
    for (OutArcIt a(this->g,this->nodesequence[j]);a!=INVALID;++a) {
      if (this->g.target(a)==this->nodesequence[j+1]) { // achou aresta que liga no's
	ok = 1;
	custocorrente += this->custoaresta(a,pesocorrente);
	break;
      }}
    if (!ok){
      cout<<"Erro: Nao encontrou arco da loja "<<
	this->vname[nodesequence[j]] << " para a loja " <<
	this->vname[nodesequence[j+1]]<<"."<<endl;
      exit(2);}
    for (int i=0;i<this->nitens;i++) {
      if (this->nodesequence[j+1]==this->lojaitem[i]) {
	// a partir de No, o peso de i deve ser considerado
	pesocorrente += this->peso[i];
	// cout << "    Item comprado na loja "<< this->vname[this->lojaitem[i]] << ": " << i << endl;
      }
    }

  }
  return(custocorrente);
}

void Compras_Entrada::imprimesolucao(void)
{
  for (int j=0;j<this->nnodesequence;j++) {
    cout << "Itens da Loja: " << this->vname[this->nodesequence[j]] <<": ";
    for (int i=0;i<this->nitens-1;i++){
      if (this->lojaitem[i]==this->nodesequence[j])
	cout<< i << ", ";
    }
    cout<<endl;
  }
  return;
}


bool Compras_Entrada::visualizasolucao(void)
{
  if (!this->verificasolucao()) {
    cout<<"Erro: Erro na solucao. Nao e' possivel visualizar a solucao."<<endl;}
  DigraphAttributes G(this->g,this->vname,this->px,this->py);
  G.SetDigraphAttrib("splines=false");
  G.SetDefaultDNodeAttrib("color=Gray style=filled width=0.2 height=0.2 fixedsize=true");
  for (DNodeIt v(this->g);v!=INVALID;++v) G.SetColor(v,"Gray");//vertices em cinza.
  for (ArcIt a(this->g);a!=INVALID;++a) G.SetColor(a,"Invis");// todos arcos de invisivel

  // Pinta arcos da solucao, em azul.
  for (int j=0;j<this->nnodesequence-1;j++) {
    G.SetColor(this->nodesequence[j],"Red");//vertices da solucao em vermelho.
    for (OutArcIt a(this->g,this->nodesequence[j]);a!=INVALID;++a) {
      if (this->g.target(a)==this->nodesequence[j+1]) {
	G.SetColor(a,"Blue");}}// arcos da solucao.
  }
  G.SetColor(this->Deposito,"Yellow");//deposito em amarelo
  G.SetDigraphAttrib("label=\"Rota de compras com custo "+
		     LongLongIntToString(this->custosolucao())+"\"");
  G.View();
}

#endif
