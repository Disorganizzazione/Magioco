#include "universal.h"
#include <stdlib.h>
#include <string.h>

//-----------------------------------------Choices
Choice_t* addChoice(Choice_List_t* List)
{
  Choice_t* C= calloc(1,sizeof(Choice_t));
  if(!C)
    alloc_error(__func__);
  if(!List->Last)
    List->Last= List->First= C;
  else
    {
      List->Last->Next= C;
      List->Last= C;
    }
  List->choices++;
  return C;
}

void select(Choice_List_t* List, char* text, short chosen)
{
  Choice_t* P= List->First;
  for(int x= 1; x < chosen; x++)
    P= P->Next;
  strcpy(text, P->text);
  deleteChoices(List);
}

void deleteChoices(Choice_List_t* List)
{
  Choice_t* Temp;
  while(List->First)
    {
      Temp= List->First;
      List->First= List->First->Next;
      free(Temp);
    }
  List->Last=NULL;
  List->choices=0;
}

//-----------------------------------------Items
Item_t* addItem(Item_List_t* List)
{
  Item_t *Item = calloc(1, sizeof(Item_t));

  if (!Item)
    alloc_error(__func__);
  if(!List->First)
    List->First = List->Last = Item;
  else
    {
      List->Last->Next = Item;
      List->Last = Item;
    }
  List->items++;
  return Item;
}

Item_t* searchItem(Item_List_t* List, char* name)
{
  Item_t* Ret= List->First;
  while(Ret)
    {
      if(!strcmp(Ret->Info.name, name))
        break;
      Ret= Ret->Next;
    }
  return Ret;
}

void move_Item_top()
{

}

void deleteItem(Item_List_t* List, Item_t* Item) //da usare solo con searchItem (unire?)
{
  Item_t* Ret= List->First;
  if(Ret==Item)
    {
      List->First= Ret->Next;
      free(Item);
      if(!List->First)
	List->Last= NULL;
    }
  else
    while(1)
      {  
	if(!Ret->Next)
	  {
	    fprintf(stderr,"Errore: oggetto non in lista (deleteItem)\n"); //OUTPUT
	    exit(EXIT_FAILURE); // non dovrebbe accadere se Item è reso da searchItem
	  }
	if(Ret->Next==Item)
	  {
	    Ret->Next= Ret->Next->Next;
	    if(!Ret->Next)
	      List->Last= Ret;
	    free(Item);
	    break;
	  }
	Ret= Ret->Next;
      }
  List->items--;
}

void deleteItems(Item_List_t* List)
{
  Item_t* Item;
  while(List->First)
    {
      Item = List->First;
      List->First = List->First->Next;
      free(Item);
    }
  List->Last= NULL;
  List->items = 0;
}

//-----------------------------------------Enemies
Enemy_t* addEnemy(Enemy_List_t* List)
{
  Enemy_t* Enemy = calloc(1, sizeof(Enemy_t));

  if(!Enemy)
    alloc_error(__func__);
  if(!List->First)
    List->First = List->Last = Enemy;
  else
    {
      List->Last->Next = Enemy;
      List->Last = Enemy;
    }
  List->enemies++;
  return Enemy;
}

Enemy_t* searchEnemy(Enemy_List_t* List, char* name)
{
  Enemy_t* Ret = List->First;
  while(Ret)
    {
      if(!strcmp(Ret->Info.name, name))
        break;
      Ret = Ret->Next;
    }
  return Ret;
}

void moveEnemy_bot(Enemy_List_t* List, Enemy_t* Enemy)
{
  if(Enemy==List->Last)
    return;
  if(Enemy==List->First)
    {
      List->First= Enemy->Next;
      List->Last->Next= Enemy;
      List->Last= Enemy;
      Enemy->Next= NULL;
    }
  //else
}

void deleteEnemy(Enemy_List_t* List, Enemy_t* Enemy)
{
  Enemy_t* Ret= List->First;
  if(Ret==Enemy)
    {
      List->First= Ret->Next;
      deleteActions(Enemy);
      free(Enemy);
      if(!List->First)
	List->Last= NULL;
    }
  else
    while(1)
      {  
	if(!Ret->Next)
	  {
	    fprintf(stderr,"Errore: nemico  non in lista (deleteEnemy)\n"); //OUTPUT
	    exit(EXIT_FAILURE); // non dovrebbe accadere se Item è reso da searchItem
	  }
	if(Ret->Next==Enemy)
	  {
	    Ret->Next= Ret->Next->Next;
	    if(!Ret->Next)
	      List->Last= Ret;
	    deleteActions(Enemy);
	    free(Enemy);
	    break;
	  }
	Ret= Ret->Next;
      }
  List->enemies--;
}


void deleteEnemies(Enemy_List_t* List)
{
  Enemy_t* Enemy;
  while(List->First)
    {
      Enemy = List->First;
      List->First = List->First->Next;
      deleteActions(Enemy);
      free(Enemy);
    }
  List->Last=NULL;
  List->enemies = 0;
}

//-----------------------------------------Actions
Action_t* addAction(Enemy_t* Enemy)
{
  Action_t* Action = calloc(1, sizeof(Action_t));

  if(!Action)
    alloc_error(__func__);
  if(!Enemy->First)
    Enemy->First = Enemy->Last = Action;
  else
    {
      Enemy->Last->Next = Action;
      Enemy->Last = Action;
    }
  Enemy->Info.actions++;
  return Action;
}

void deleteActions(Enemy_t* Enemy)
{
  Action_t* Action;
  while(Enemy->First)
    {
      Action = Enemy->First;
      Enemy->First = Enemy->First->Next;
      free(Action);
    }
  Enemy->Last=NULL;
  Enemy->Info.actions= 0;
}
