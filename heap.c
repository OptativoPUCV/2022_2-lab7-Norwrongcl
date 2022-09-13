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
  heapElem* aux= (heapElem*)malloc(sizeof(heapElem));
  pq->heapArray[0]= pq->heapArray[pq->size];
  pq->size--;
  int asize= 0;
  int younga= (2*asize)+ 1;
  int olda= (2*asize)+ 2; 
  while (asize < pq->size){
    if (pq->heapArray[asize].priority < pq->heapArray[younga].priority && pq->heapArray[younga].priority > pq->heapArray[olda].priority){
      *aux= pq->heapArray[asize];
      pq->heapArray[asize]= pq->heapArray[younga];
      pq->heapArray[younga]= *aux;
      asize= younga;
      younga= (2*asize)+ 1;
      olda= (2*asize)+ 2;
    }
    else if (pq->heapArray[asize].priority < pq->heapArray[olda].priority && pq->heapArray[olda].priority > pq->heapArray[younga].priority){
      *aux= pq->heapArray[asize];
      pq->heapArray[asize]= pq->heapArray[olda];
      pq->heapArray[olda]= *aux;

      asize= olda;
      younga= (2*asize)+ 1;
      olda= (2*asize)+ 2;
    }
    else break;
   }
}

Heap* createHeap(){
	Heap* new= (Heap*)malloc(sizeof(Heap));
  new->size= 0;
  new->capac= 3;
  new->heapArray= (heapElem*)malloc(3*sizeof(heapElem));
  return new;
}
