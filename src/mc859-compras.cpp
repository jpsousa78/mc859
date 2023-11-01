
// Project and Analysis of Algorithms
// Prof: Fl�vio Keidi Miyazawa
// Student: Joao Paulo de Sousa Brito
#include <mc859-compras.h>

// CODIGO OFICIAL SOH A PARTIR DA LINHA ~177
// ATE LA EH NA MAIOR PARTE LIXO/CODIGO RUIM

void TrocaDNode(DNode &a, DNode &b)
{
  DNode aux;
  aux = a;
  a = b;
  b = aux;
}

// SOLUCAO INICIAL RUIM
void Heuristica(Compras_Entrada &C)
{
  vector<int> LojaEscolhida(MAXITENS);
  int menorpreco, nit;
  long long int valorsolucaoatual, valorsolucaonova;
  DNodeBoolMap TemItemComprado(C.g);
  DNode No;
  for (DNodeIt v(C.g); v != INVALID; ++v)
    TemItemComprado[v] = false;
  for (int i = 0; i < C.nitens; i++)
  {
    menorpreco = INT_MAX;
    No = INVALID;
    for (DNodeIt v(C.g); v != INVALID; ++v)
    {
      // cout << "Preco do item "<<i<<" na loja "<<C.vname[v]<<": "<<C.preco[v][i]<<endl;
      if (C.preco[v][i] < menorpreco)
      {
        No = v;
        menorpreco = C.preco[v][i];
      }
    }
    if (No == INVALID)
    {
      cout << "Erro: Nao eh possivel comprar item " << i << "." << endl;
      exit(3);
    }
    C.lojaitem[i] = No;
    TemItemComprado[No] = true;
    // cout << "Item "<< i <<" comprado na loja "<< C.vname[C.lojaitem[i]] <<
    //   " por " << C.preco[C.lojaitem[i]][i] << "." << endl;
  }
  C.esvaziasolucao();
  // Primeiro noh da solucao eh o deposito.
  C.inserelojasolucao(C.Deposito);
  // Insere na solucao todas lojas onde comprou algo
  for (DNodeIt v(C.g); v != INVALID; ++v)
    if (TemItemComprado[v])
      C.inserelojasolucao(v);
  // Ultimo noh da solucao eh o deposito.
  C.inserelojasolucao(C.Deposito);

  // Tenta melhor a solucao atual com uma busca local probabilistica ingenua
  nit = 10000;
  // repete nit vezes: Troca dois no's quaisquer. Se troca nao melhorou, volta atras.
  valorsolucaoatual = C.custosolucao();
  for (int i = 0; i < nit; i++)
  {
    if (i % (nit / 10) == 0)
      cout << "It. " << i << " de " << nit << endl;
    int ia, ib;
    ia = 1 + (int)(drand48() * (C.nnodesequence - 2));
    ib = 1 + (int)(drand48() * (C.nnodesequence - 2));
    // if ((ia==ib)||(ia<1)||(ia>C.nnodesequence-2)||(ib<1)||(ib>C.nnodesequence-2)) continue;
    TrocaDNode(C.nodesequence[ia], C.nodesequence[ib]);
    valorsolucaonova = C.custosolucao();
    if (valorsolucaoatual < valorsolucaonova)
    {
      TrocaDNode(C.nodesequence[ia], C.nodesequence[ib]);
    }
    else
    {
      valorsolucaoatual = valorsolucaonova;
    }
  }
  // C.imprimesolucao();
  if (!C.verificasolucao())
  {
    cout << "Erro: Nao construiu solucao valida na fase 2." << endl;
    exit(1);
  }
}

// NAO VAI USAR MAS TEM CONTEXTO DENTRO QUE DA PRA REUTILIZAR //
void CaminhoMaisCurto(Compras_Entrada &C)
{
  /* MENORES PRECOS */
  int menorpreco, nfaltantes;
  DNode No;
  DNodeBoolMap TemItemComprado(C.g);
  for (DNodeIt v(C.g); v != INVALID; ++v)
    TemItemComprado[v] = false;
  for (int i = 0; i < C.nitens; i++)
  {
    menorpreco = INT_MAX;
    No = INVALID;
    for (DNodeIt v(C.g); v != INVALID; ++v)
    {
      // cout << "Preco do item "<<i<<" na loja "<<C.vname[v]<<": "<<C.preco[v][i]<<endl;
      if (C.preco[v][i] < menorpreco)
      {
        No = v;
        menorpreco = C.preco[v][i];
      }
    }
    if (No == INVALID)
    {
      cout << "Erro: Nao eh possivel comprar item " << i << "." << endl;
      exit(3);
    }
    C.lojaitem[i] = No;
    TemItemComprado[No] = true;
    /* FIM - MENORES PRECOS - FIM */
  }

  C.esvaziasolucao();
  // Primeiro noh da solucao eh o deposito.
  C.inserelojasolucao(C.Deposito);
  // Isso aqui soh insere todas as lojas com item sem ordem,
  // sem criterio e sem saber se tem conexao com o no seguinte
  for (DNodeIt v(C.g); v != INVALID; ++v)
    if (TemItemComprado[v])
      C.inserelojasolucao(v);
  // Ultimo tambem eh deposito
  C.inserelojasolucao(C.Deposito);
}

// ESSE ERASE TA QUEBRADO //
ArcIntMap erase(Arc a);

// NAO VAI USAR MAS TEM CONTEXTO DENTRO QUE DA PRA REUTILIZAR //
void CicloMinimo(Compras_Entrada &C)
{
  DNodeIt v(C.g), currentNode;
  int min_cycle = INT_MAX;
  int E = C.narcs;
  ArcIntMap &arcs = C.dist;
  for (int i = 0; i < E; i++)
  {
    // info do no atual
    DNode currentNode = C.nodesequence[i];
    OutArcIt fromArc(C.g, C.nodesequence[i]);
    InArcIt toArc(C.g, C.nodesequence[i+1]);

    // pegar aresta pra "remover"
    int distancia = C.dist[fromArc];
    C.dist[fromArc] = MAXDIST;

    // nova menor distancia
    Dijkstra<Digraph, ArcIntMap> Dij(C.g, C.dist);
    Dij.run(C.nodesequence[i], C.nodesequence[i+1]);
    int distance = Dij.dist(C.nodesequence[i+1]);

    min_cycle = min(min_cycle, distance + e.weight);

    // "devolver" aresta depois
    C.dist[fromArc] = distancia;
    ++v;
  }

  // return shortest cycle
  return min_cycle;
}

void BuscaLocal()
{
  // - compare solution matrix cells
  // - if found better solution with < dist, switch paths

}

void Solution(Compras_Entrada &C)
{
  // RODAR VIZINHO MAIS PROXIMO PRA DISTANCIA
  //  -- INVERTER A ORDEM (DISTANCIAS MENORES FICAM NO FINAL)
  //
  // RODAR VERSAO MODIFICADA DO VIZINHO MAIS PROXIMO
  // SOH QUE PRA PRIORIZAR OS FATORES MENORES "~mais proximos~"
  //  -- INVERTER A ORDEM (FATORES MENORES FICAM NO FINAL)
  //
  // ? APLICAR OTIMIZACAO COMPRANDO MAIS DE UM ITEM NA MESMA LOJA ?
  // 
  // RODAR BUSCA LOCAL
}

int main(int argc, char *argv[])
{
  // cout << "argc = " << argc << endl;
  if (argc != 2)
  {
    cout << "Usage: " << argv[0] << " <filename>" << endl
         << endl
         << "Example:" << endl
         << "\t" << argv[0] << " " << getpath(argv[0]) + "../instances/mc859-compras_1_100_100_0" << endl;
    exit(0);
  }

  Compras_Entrada C(argv[1]);
  // C.ImprimeFormatoArquivo();

  Heuristica(C);

  if (!C.verificasolucao())
  {
    cout << "Erro: Ocorreu erro na producao de uma solucao." << endl;
  }
  else
  {
    cout << "Custo da solucao obtida eh " << C.custosolucao() << endl;
  }
  C.imprimesolucao();
  C.visualizasolucao();
  return 0;
}
