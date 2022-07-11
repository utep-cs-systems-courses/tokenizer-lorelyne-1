#include <stdlib.h>
#include <stdio.h>
#include "history.h"
#include "tokenizer.h"
/* Initialize the inked list to keep the history. */
List *init_history(){

  List *history = malloc(sizeof(List)); //Creates a new linked list and allocates the memory for it
  
  history->root = NULL; //Root is initiallized to NULL
  return history;
}

/* Add a history item to the end of the lsit.
   List* list - the linked list
   char* str - the string to store
*/
//Adds new strings to the end of the linked list
void add_history(List *list, char *str)
{
 Item *item = malloc(sizeof(Item));
  
  //Will be use for the ID of the Item
  int count = 0;
  
  if(list -> root == NULL){ //If the root is NULL we set the new item as root
    list -> root = item;
  }
  else{ //else find the next free space in the list using while loop
    struct s_Item *temp = list -> root;
    count++;
    while(temp -> next != NULL){
      count++;
      temp = temp -> next;
    }
    temp -> next = item; //Once end is found, set item at the end
  }
  
  item -> id = count;
  int length = 0;
  while(*str != '\0'){
    length++;
    str++;
  }
  
  str = str - length;
  //Copy the string into the Item str
  item -> str = copy_str(str, length);
  //Set the next space to NULL
  item -> next = NULL;
}

/* Retrieve the string stored in the node where Item->id == id.
   List* list - the linked list
   int id - the id of the Item to find */
char *get_history(List *list, int id)
{
  struct s_Item *temp = list -> root; //Helps iterate thriugh list
  while(temp != NULL && id != 0){ //Move through list id amount of times
    temp = temp -> next;
    id--;
  }
  if(temp == NULL){ //if item is null and id is not 0 then item doesn't exist
    printf("ID not in history\n");
  }
  else{ //else return string of that item
    return temp -> str;
  }
}
/*Print the entire contents of the list*/
void print_history(List *list)
{
  struct s_Item *temp = list -> root;
  while(temp != NULL){
    printf("[%i] %s\n", temp -> id, temp -> str); //Print the whole history list
    temp = temp -> next;
  }
}
/*Free the history list and the strings it references. */
void free_history(List * list)
{
  struct s_Item *temp = list -> root;
  struct s_Item *temp_2;
  while(temp != NULL){
    temp_2 = temp -> next;
    free(temp -> str);
    free(temp);
    temp = temp_2;
  }
  free(list);
  list -> root = NULL;
}

