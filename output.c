#include "universal.h"
#include <stdlib.h>
#include <string.h>

#define CENTER(TEXT) for(int x= (strlen(TEXT)+1)/2; x< width/2-2; x++) printf(" "); printf("%s\n",TEXT);
#define CHOSE(TEXT, SELECTED, WIDTH) for(int x= strlen(TEXT)/2; x< WIDTH/2-4; x++) printf(" "); printf("%c%s%c\n",SELECTED?'[':' ',TEXT,SELECTED?']':' ');

extern Data_t Local;
extern _Bool buffered;
extern short width;

void next_page()
{
  system("clear");
}

void print_intro()
{
  puts("");
  CENTER("  __  __                   __                       ");
  CENTER(" /  \\/  \\    ____    ____ /\\_\\   ____   ___   ____  ");
  CENTER("/\\ \\__/\\ \\  /  _ \\  / __ \\\\/_/  / __ \\ / __\\ / __ \\ ");
  CENTER("\\ \\ \\_/ \\ \\/\\ \\_\\ \\/\\ \\_\\ \\/\\ \\/\\ \\_\\ \\\\ \\__/\\ \\_\\ \\");
  CENTER(" \\ \\_\\ \\ \\ \\ \\__/\\_\\ \\__/\\ \\ \\_\\ \\____/ \\___\\ \\____/");
  CENTER("  \\/_/  \\/_/\\/_/\\/_/\\/\\____/\\/_/\\/___/ \\/___/\\/___/ ");
  CENTER("                     \\/___/                         ");
  puts("");
  CENTER("Premere 'a' per continuare");
  CENTER("Premere 'q' per uscire");
}

void print_menu()
{
  CENTER(" Menù ");
  puts("");
  CENTER("Usare le frecce direzionali");
  CENTER("per muoversi");
  puts("");
  CHOSE("Continua",Local.chosen==1,width);
  CHOSE("Nuova partita",Local.chosen==2,width);
  CHOSE("Imp. grafiche",Local.chosen==3,width);
  CHOSE("Elimina salv.",Local.chosen==4,width);
}

void print_center(char* text)
{
  CENTER(text);
}

void print_imp()
{
  CENTER("Impostazioni");
  puts("");
  CENTER("Usare le frecce direzionali");
  CENTER("per cambiare la larghezza");
  puts("");
  CENTER("Premere 'a' per salvare");
  CENTER("Premere 'q' per default");
  puts("");
  for(int x=0; x<width; x++)
    printf("*");
  puts("");
}

void print_quit(short* chosen)
{
  CENTER("Quit Menù");
  puts("");
  CENTER("Premere 'q' per annullare");
  puts("");
  CHOSE("Salva",*chosen==1,width);
  CHOSE("Menù",*chosen==2,width);
  CHOSE("Esci",*chosen==3,width);
}

void print_gameover()
{
  CENTER("Game Over");
  puts("");
  CENTER("Premere 'q' per uscire");
  CENTER("Premere 'a' per continuare");
}

void print_Choices(Choice_List_t* List, short chosen)
{
  CENTER(List->text);
  puts("");
  Choice_t* Temp= List->First; 
  for(int x= 1; x <= List->choices; x++)
    {
      CHOSE(Temp->text,x==chosen,width);
      Temp= Temp->Next;
    }
}

void print_name(char* name)
{
  CENTER("Nome");
  puts("");
  CENTER(name);
  puts("");
  CENTER("Premere '.' per confermare");
  CENTER("Premere '-' per cancellare");  
}

void print_Enemies()
{ 
  Enemy_t* Enemy= Local.Battle.First;
  for (int x=1; x<=Local.Battle.enemies; x++)
    {
      CHOSE(Enemy->Info.name, Local.enemy_chosen==x, 0);
      printf("HP ");
      for (int y=0; y<Enemy->Info.health; y++)
        printf("*");
      for (int z=0; z<Enemy->Info.defence; z++)
        printf(")");
      puts("\n");
      Enemy= Enemy->Next;
    }
}

void print_stats()
{
  for(int x= strlen(Local.name)+2; x < width; x++)
    printf(" ");
  CHOSE(Local.name, Local.enemy_chosen==Local.Battle.enemies+1, 0);
  for(int x= 3+Local.health+Local.defence; x< width; x++)
    printf(" ");
  for(int y=0; y<Local.defence; y++)
    printf("(");
  for (int x=0; x<Local.health; x++)
    printf("*");
  printf(" HP");
  puts("\n");
}

void print_Items()
{ 
  Item_t* Tmp= Local.Bag.First;
  if(!Local.Bag.items && !Local.defending)
    puts("Non hai oggetti");
  else
    {
      puts("Scegli:");
      for(int x= 1; x <= Local.Bag.items; x++)
        {
          for(int x= strlen(Tmp->Info.name)/2; x< width/2-7; x++) 
            printf(" "); 
          printf("%c%s%c  %s: %d\n"
                 , Local.item_chosen==x?'[':' '
                 , Tmp->Info.name
                 , Local.item_chosen==x?']':' '
                 , Tmp->Info.type=='u' ? "res" : "qnt"
                 , Tmp->Info.uses
                 );
          Tmp= Tmp->Next;
        }
      if(Local.defending)
        {
          for(int x= strlen(Local.Defending.name)/2; x< width/2-7; x++) 
            printf(" ");
          printf("%c%s%c  %s: %d"
                 , Local.item_chosen==Local.Bag.items+1?'[':' '
                 , Local.Defending.name
                 , Local.item_chosen==Local.Bag.items+1?']':' '
                 , Local.Defending.type=='u' ? "res" : "qnt"
                 , Local.Defending.uses
                 );
          printf("  ((difesa))\n");
        }
    }
}

void print_Uses(Item_t* Item)
{
  printf("Scelto:");
  CHOSE(Item->Info.name,0,(width-12));
  puts("");
  CHOSE(">> Usa <<",Local.use_chosen==1,width);
  CHOSE("<< Lancia",Local.use_chosen==2,width);
  CHOSE("(( Blocca",Local.use_chosen==3,width);
}

void print_sel(Item_t* Item)
{
  printf("%s", Local.use_chosen==1? ">> Usa <<": "<< Lancia");
  CHOSE(Item->Info.name,0,(width-16));
}

void print_Action(Enemy_t* Enemy)
{
  Action_t* Action= Enemy->First;
  printf("%s: %s\n", Enemy->Info.name, Action->Info.text);
  switch(Action->Info.type)
    {
    case'm':
      puts("Attacco ravvicinato");
      if(Local.ranged)
        printf("%s è fuori portata\n", Local.name);
      else if(Local.defending)
        {
          printf("%s: si difende con %s\n", Local.name, Local.Defending.name);
          if(Local.Defending.type=='p')
            printf("%s distrutti\n", Local.Defending.name);
        }
      break;
    case'r':
      puts("Attacco a distanza");
      if(Local.defending)
        {
          if(Local.Defending.defvalue < Action->Info.value)
            printf("%s non basta a fermare il colpo\n", Local.Defending.name);
          else
            {
              printf("%s ferma il colpo\n", Local.Defending.name);
              if(Local.Defending.type=='p')
                printf("%s persi\n", Local.Defending.name);
            }
        }
      break;
    case'd':
      puts("Si difende");
    }

  if(Enemy==enemy_sel())
    {
      Item_t* Item;
      Item= item_sel();
      puts("");
      if(!Local.ranged)
        {
          printf("%s: usa %s su %s\n", Local.name, Item->Info.name, Enemy->Info.name);
          if(Action->Info.type=='r')
            printf("%s è fuori portata\n", Enemy->Info.name);
        }
      else
        {
          printf("%s: lancia %s contro %s\n", Local.name, Item->Info.name, Enemy->Info.name);
          if(Enemy->Info.defence)
            printf("%s è difeso", Enemy->Info.name);
        }
    }
}
