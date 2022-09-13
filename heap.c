#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
}Heap;

void* heap_top(Heap* pq){
  if (pq->size == 0) return NULL;
  return (void*) pq->heapArray[0].data;
}

void heap_push(Heap* pq, void* data, int priority){
  if (pq->size == pq->capac){
    pq->capac= (pq->capac*2)+ 1;
    pq->heapArray= realloc(pq->heapArray, pq->capac*sizeof(heapElem));
  }
  pq->heapArray[pq->size].data= data;
  pq->heapArray[pq->size].priority= priority;
  int asize= pq->size;
  int adadsize= ((pq->size-1)/2);
  heapElem* aux= (heapElem*) malloc (sizeof(heapElem));
  while (asize > 0){
    if (pq->heapArray[asize].priority > pq->heapArray[adadsize].priority){
      *aux= pq->heapArray[adadsize];
      pq->heapArray[adadsize]= pq->heapArray[asize];
      pq->heapArray[asize]= *aux;
    }
    asize= adadsize;
    adadsize= (asize-1)/2;
  }
  pq->size++;
}

void heap_pop(Heap* pq){ 
  int size= pq->size;
  int apt= pq->heapArray[size-1].priority;
  void *adata= pq->heapArray[size-1].data;

  pq->heapArray[size].priority= pq->heapArray[0].priority;
  pq->heapArray[size].data= pq->heapArray[0].data;
  pq->heapArray[0].priority= apt;
  pq->heapArray[0].data= adata;
  pq->size= pq->size-1;
  while (int i=0 < pq->size){
    int indexch1= (i*2)+ 1;
    int indexch2= (i*2)+ 2;
    int apt2= pq->heapArray[i].priority;
    void *adata2= pq->heapArray[i].data;
		
    if (indexch1 > pq->size) pq->heapArray[indexch1].priority= 0;
    if (indexch2 > pq->size) pq->heapArray[indexch2].priority= 0;
    if (pq->heapArray[indexch1].priority > pq->heapArray[indexch2].priority){
      if (pq->heapArray[indexch1].priority > pq->heapArray[i].priority){
          pq->heapArray[i].priority= pq->heapArray[indexch1].priority;
          pq->heapArray[i].data= pq->heapArray[indexch1].data;
          pq->heapArray[indexch1].priority= apt2;
          pq->heapArray[indexch1].data= adata2;
          i= indexch1; 
      }
      else break;
    }
    else if (pq->heapArray[indexch2].priority > pq->heapArray[indexch1].priority){
      if (pq->heapArray[indexch2].priority > pq->heapArray[i].priority){
          pq->heapArray[i].priority= pq->heapArray[indexch2].priority;
          pq->heapArray[i].data= pq->heapArray[indexch2].data;

          pq->heapArray[indexch2].priority= apt2;
          pq->heapArray[indexch2].data= adata2;
          i= indexch2; 
      } 
      else break;
    }
    else break;
    }
  }
}

Heap* createHeap(){
	Heap* new= (Heap*)malloc(sizeof(Heap));
  new->size= 0;
  new->capac= 3;
  new->heapArray= (heapElem*)malloc(3*sizeof(heapElem));
  return new;
}
