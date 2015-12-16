#include "struct.h"
#include <stdio.h>

//battle

//event
void select(short chosen, Choice_List* List);
void deleteEvents(void);
void addEvent(void);

//input
void press_a(void); //ferma il programma fino a che non si preme 'a'
_Bool choice(short* chosen, short choices); // rende 1 se viene premuto 'a' se effettua un cambiamento al valore chosed o allo stato rende 0

//management
void addAction(Enemy_t* Enemy, char* text, char type, short value);
void addEnemy(char* name, short health, short defence);
void addItem(Item_List* List, char* name, char type, int usev, unsigned short trwv, unsigned short defv, int uses);
Item_t* searchItem(char* id, Item_List* List);

//output
void print_Enemies();
void print_Items();
void print_Events(); //choice_t e choice_list
void print_Stat (); //Nome vita e difesa giocatore 

//text
void readevent();
void printtext(FILE*);
void move(char,FILE*);
char* sstring(FILE*,char);
void controle(FILE*,char,char);
void readchoices(FILE*);
void isearch();