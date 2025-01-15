int pesqBinaria(int *vetor, int elemento){
int inicio = 0, fim = quantElem - 1, meio;
  while(inicio <= fim){
    meio = (int)(inicio+fim)/2;
    if (elemento == vetor[meio])
      return meio;
    else
      if(elemento< veto[meio])
        fim = meio - 1;
    else 
        inicio = meio + 1;
  }
  return -1;
}
