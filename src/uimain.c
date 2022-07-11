#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "history.h"

#define SIZE 100
/*
  This method is called from the main when the user wants to tokenize something.
  It first takes the string and adds it to the history and then it tokenizes it. 
  At the end the tokens are freed.
 */
void goto_tokens(char *input, List *list)
{
  printf("Please provide a phrase you would like to tokenize.\n");
  printf("> ");
  fgets(input,1000,stdin);
  add_history(list, input);
  char **tokens = tokenize(input);
  print_tokens(tokens);
  free_tokens(tokens);
}

/*
  This method is called from the main when the user wants to see the history of past
  commands. It first prints the history so the user can choose what index they want to 
  tokenize. Then the string at the index chosen is tokenize. Finally the tokens are freed.
 */
void goto_history(char *input, List *list)
{
  print_history(list);
  printf("Please provide a number from the history above.\n");
  putchar('>');
  fgets(input,100,stdin);
  char *str = get_history(list, atoi(input));
  printf("String at %i: %s\n",atoi(input), str);
  char **tokens = tokenize(str);
  print_tokens(tokens);
  free_tokens(tokens);
}

/*
  This is the main. Here is where I ask the user if they want to tokenize, view history
  ot exit the program. If 't' is typed, I call the goto_tokens() method that passes a Linked
  List and a character array used for the input. If 'h' is typed, I call the goto_history()
  method that receives also a Linked List and a character array. If 'q' is typed, we exit the
  program, else prompt the user with "Command does not exist".
 */
int main()
{
  //Set the size of the input
  char input[1000];

  //Create a new List 
  List *list = init_history();
 
  while(1){
    printf("Welcome to my Tokenizer. Enter 't' to Tokenize, 'h' to see the History, and 'q' to Exit.\n");
    putchar('$');
    fgets (input,1000,stdin);
    if (*input == 't'){
      goto_tokens(input, list);
    }
    else if (*input == 'h'){
      goto_history(input, list);
    }
    else if (*input == 'q'){
      free_history(list);
      exit(1);
    }
    else{
      printf("Invalid command. Please try again.\n");
    }
  }
}

/*

int main()
{
  char userInput[100];

  //Part A: Building a Simple UI
  printf("Please input something\n");
  printf("$ ");
  fgets(userInput, 100, stdin);
  printf("%s\n", userInput);
  
}

*/
