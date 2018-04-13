/*
This is a demo c programm to create a queue and moderate it. 

List

Platform: 
- GCC Version: (Apple LLVM version 9.0.0 (clang-900.0.39.2) Target: x86_64-apple-darwin16.7.0) 
- Online Complier (https://www.onlinegdb.com/online_c_compiler)
Author: Tim
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node *next;
}node;

typedef struct {
  int count;
  node* head;
} ListHead;

ListHead *CreateList() {
  ListHead *myLH = (ListHead *) malloc (sizeof (ListHead));
  // Empty list is created.
  // Element counter is set to zero
  myLH->count = 0;
  // Top should address NULL as it is an empty list
  myLH->head = NULL;
  return myLH;
}

void Insert(ListHead *myList, int data) {
  if (myList->count == 0) {
    node *pNew = (node *) malloc(sizeof(node));
    pNew->data = data;
    pNew->next = NULL;
    myList->head = pNew;
    myList->count++;
  }
  else {
    if (data <= myList->head->data) {
      node *pNew = (node *) malloc(sizeof(node));
      pNew->data = data;
      pNew->next = myList->head;
      myList->head = pNew;
      myList->count++;
    }
    else {
      // create node
      // GENERAL CASE
      node *pNew = (node *) malloc(sizeof(node));
      pNew->data = data;
      myList->count++;

      node *pPre = (node *) malloc(sizeof(node)), *pCur = myList->head;

      do {
        pPre = pCur;
        pCur = pCur->next;
        if (pCur == NULL) break;

      } while (pCur->data < data);

      pPre->next = pNew;
      pNew->next = pCur;
    
    }
  }
}

// delete spercific data in the list

int Delete(ListHead *myList, int data) {
  node *pPre = (node *) malloc(sizeof(node)), *pCur = myList->head, *pDel = (node *) malloc(sizeof(node));
  // number of times found
  int rv = 0;
  do {
    if (pCur->data == data) {
      rv++;
      if (pPre == NULL) 
        myList->head = pCur->next;
      else 
        pPre->next = pCur->next;
      
      myList->count--;
      pDel = pCur;
      pCur = pCur->next;
      free (pDel);
    }
    else
    {
      pPre = pCur;
      pCur = pCur->next;
    }

  } while (pCur != NULL);

  return rv;
}

// list count
int GetListCount(ListHead *myList){
  return myList-> count;
}
// empty list
int IsEmpty(ListHead *myList){
  return GetListCount(myList)<=0;
}

// list search
int Search (ListHead *myList, int target){
  node *pCur = myList->head;
  

  while (pCur != NULL)
  {
      if (pCur->data == target)
        return 1;

      pCur = pCur->next;
  }
  return 0;
}

int RetrieveList(ListHead *myList, int target){
  node *pCur = myList->head;
  node *pDel = myList->head;
  int dataOut =0;
  

  while (pCur != NULL)
  {
      if (pCur->data == target){
        dataOut= pCur->data;
        pDel = pCur;
        pCur = pCur->next;

        // myList->count--;
        // free(pDel);
        return dataOut;
      }else{
        pCur = pCur->next;
      }
      
  }
  return dataOut;
}

void Empty(ListHead *myList){

  if (! IsEmpty(myList)){
    node *pCur = myList->head;
    node *pDel = myList->head;
    while (pCur != NULL){
      myList->count--;
      pDel = pCur;
      pCur = pCur->next;
      free (pDel);
    }
    myList-> head = NULL;
  }
}




void PrintList(ListHead *myList) {
  if (! IsEmpty(myList)){
    node *pCur = myList->head;
    for (int k = 0; k < myList->count; k++) {
      printf("%d \n", pCur->data);
      pCur = pCur->next;
    }
  }else{
    printf("List is empty \n");
  }
}

int main()
{
  //An empty List is created and a pointer to the head is returned
  ListHead *myList = CreateList();

  Insert(myList, 23);
  Insert(myList, 11);
  Insert(myList, 27);
  Insert(myList, 0);
  Insert(myList, 99);
  Insert(myList, 0);
  Insert(myList, 1);
  Insert(myList, 99);
  Insert(myList, 89);
  Insert(myList, 39);

  PrintList(myList);


  int result = Search(myList,   89);

  printf(" finding 89 result: %d \n", result );

  int dataOut = RetrieveList(myList, 1);
  printf(" retrieve  %d \n", dataOut );

  // int deleted = Delete(myList, 89);

  // if (deleted){
  //   printf("The value 89 was found %d times \n", deleted);
  // }
  // else
  //   printf("Not found \n");

  Empty(myList);


  PrintList(myList);

  // VS will need next line to hold the Terminal Window before 
  // disposing it when Code is done running.
  system("pause");

  // It is a good programming practice to define returning
  // value of funtion main to 'int' on C and C++
  return 0;
}
