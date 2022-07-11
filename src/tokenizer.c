#include <stdio.h>
#include <stdlib.h>


/* Return true (non-zero) if c is a whitespace characer
   ('\t' or ' ').  
Zero terminators are not printable (therefore false) */
int space_char(char c)
{
  if (c == ' ' || c == '\t') //Checks to see if char is a space
    return 1;
  return 0;
}

/* Return true (non-zero) if c is a non-whitespace 
   character (not tab or space).  
   Zero terminators are not printable (therefore false) */ 
int non_space_char(char c)
{
  if (c == ' ' || c == '\t' || c == '\0') //Checks to see if char is a non-space
    return 0;
  return 1;
}

/* Returns a pointer to the first character of the next 
   space-separated word in zero-terminated str.  Return a zero pointer if 
   str does not contain any words. */
char *word_start(char *str)
{
  while (space_char(*str) && *str != '\0')
    str++; //moves pointer to the first non space char after a space 
  return str; 
}

/* Returns a pointer terminator char following *word */
char *word_terminator(char *word)
{
  word = word_start(word);

  while(non_space_char(*word) && *word != '\0')
    word++; //moves pointer ot the first space char after a non-space char
  return word;
}

/* Counts the number of words in the string argument. */
int count_words(char *str)
{
  int counter;

  counter = 0;
  str = word_start(str);
  
  while(*str != '\0')
    {
      str = word_start(str);
      if (*str != '\0')
	counter++; //add to counter until \0 is reached which means we have reached the end and there are no more words
      str = word_terminator(str);
    }
  return counter;
}

/* Returns a fresly allocated new zero-terminated string 
   containing <len> chars from <inStr> */
char *copy_str(char *inStr, short len)
{
  char *cStr = (char*)malloc(sizeof(char)*(len+1)); //allocates memory for the copied string

  int i=0;
  while(i < len) //loop while i is less than the given length
    {
     cStr[i] = inStr[i]; //inserts whats in the string at the current index into new copy string
     i++;
   }
    cStr[len] = '\0'; //sets end of string to zero terminator 
    return cStr;
}

/* Returns a freshly allocated zero-terminated vector of freshly allocated 
   space-separated tokens from zero-terminated str.

   For example, tokenize("hello world string") would result in:
     tokens[0] = "hello"
     tokens[1] = "world"
     tokens[2] = "string" 
     tokens[3] = 0
*/
char **tokenize(char* str)
{
  int length = count_words(str); //stores the amount of words in string
  char **char_array; //create a new array
  char_array = (char**)malloc(sizeof(char*)*(length+1)); //allocates memory and adds 1 for '\0' (double array to hold pointers)
  int i = 0;
  while(i<length){ //while loop to copy each word from the string into the array
    str = word_start(str); //stores first char of string
    int stringLen = word_terminator(str) - str; //stores the length of the word in string 
    char_array[i] = copy_str(str, stringLen); 
    str = word_terminator(str); //sets str in blank 
    i++;
  }
  char_array[i] = NULL;
  return char_array;
}

/* Prints all tokens. */
void print_tokens(char **tokens)
{
  int i;
  for(i=0; tokens[i] != NULL; i++){
    printf("%s\n",tokens[i]);
  }
}

/* Frees all tokens and the vector containing themx. */
void free_tokens(char **tokens)
{
  int i;
  for(i = 0; tokens[i] != NULL; i++)
  {
    free(tokens[i]);
  }
  
  free(tokens[i]); //free memory
  free(tokens); //free memory
}
