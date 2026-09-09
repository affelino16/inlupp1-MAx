#include <stdio.h>
#include "utils.h"

struct item {
    char *name;
    char *desc;
    int price;
    char *shelf;

};

typedef struct item item_t;

void print_item (item_t *item) {
    int price_int = (item->price)/100;
    int price_dec = (item->price) %100;
    printf("Name: %s\nDesc: %s\nPrice: %d.%d\nShelf: %s\n", 
        item->name, item->desc, price_int, price_dec, item->shelf);
}

item_t make_item (char *name, char *desc, int price, char *shelf) {
        item_t new_item = {.name = name, .desc = desc, .price = price, .shelf = shelf};
        return new_item;
    }
    
bool is_shelf(char *shelf) {
    int len = strlen(shelf);
    if (is_number(&shelf[0])) {
        return false;
    } else for (int i = 1 ; i < len; i++) {
        if (!is_number(&shelf[i])) {
            return false;
        }  else {
            return true;
        }
    }
}
char *ask_question_shelf(char *question) {
     answer_t shelf = ask_question(question, is_shelf,(convert_func *)strdup);
     return shelf.string_value;
}

item_t input_item(){
    char *name = ask_question_string("Define your item!\n\nName: ");
    char *desc = ask_question_string("Description: ");
    int price = ask_question_int("Price in Ören: ");
    char *shelf = ask_question_shelf("Shelf: ");
    item_t item = {.name = name, .desc = desc, .price = price, .shelf = shelf};
    return item;
}

char *magick(char *arr1[], char *arr2[], char* arr3[], int len) {
    char buf[255];
    int rand1 = random() % len;
    int rand2 = random() % len;
    int rand3 = random() % len;
    int i = 0; 
    int j = 0;
    while (arr1[rand1][j] != '\0') {
        buf[i] = arr1[rand1][j];
        i++;
        j++;
    } buf[i] ='-';
    j = 0;
    i++;  
    while (arr2[rand2][j] != '\0') {
        buf[i] = arr2[rand2][j];
        i++;
        j++;
    } buf[i] =' ';
    i++;
    j = 0;
    while (arr3[rand3][j] != '\0') {
        buf[i] = arr3[rand3][j];
        i++;
        j++;
    } buf[i] ='\0';
     return strdup(buf);
}

void list_db(item_t *items, int no_items) {
    for (int i = 0; i < no_items; i++) {
        printf("%d. %s\n", i + 1, items[i].name);
    }
}

item_t *edit_db(item_t *items, int no_items) {
    int index = ask_question_int("Vilken vara vill du ändra?") - 1;
    if (index < 0 || index > no_items) {
        printf("Den varan finns inte!\n");
        return items;
    } else print_item(&items[index]);
      items[index] = input_item();
      list_db(items, no_items);
      return items;
}


int main(int argc, char *argv[])
{
  char *array1[] = { "hej", "hallå", "scuba" }; // TODO: Lägg till!
  char *array2[] = { "då", "där","libre" }; // TODO: Lägg till!
  char *array3[] = {"kompis", "vän", "bror"}; // TODO: Lägg till!

  if (argc < 2)
  {
    printf("Usage: %s number\n", argv[0]);
  }
  else
  {
    item_t db[16]; // Array med plats för 16 varor
    int db_siz = 0; // Antalet varor i arrayen just nu

    int items = atoi(argv[1]); // Antalet varor som skall skapas

    if (items > 0 && items <= 16)
    {
      for (int i = 0; i < items; ++i)
      {
        // Läs in en vara, lägg till den i arrayen, öka storleksräknaren
        item_t item = input_item();
        db[db_siz] = item;
        ++db_siz;
      }
    }
    else
    {
      puts("Sorry, must have [1-16] items in database.");
      return 1; // Avslutar programmet!
    }

    for (int i = db_siz; i < 16; ++i)
      {
        char *name = magick(array1, array2, array3, 3); // TODO: Lägg till storlek
        char *desc = magick(array1, array2, array3, 3); // TODO: Lägg till storlek
        int price = random() % 200000;
        char shelf[] = { random() % ('Z'-'A') + 'A',
                         random() % 10 + '0',
                         random() % 10 + '0',
                         '\0' };
        item_t item = make_item(name, desc, price, strdup(shelf));

        db[db_siz] = item;
        ++db_siz;
      }

     // Skriv ut innehållet
     list_db(db,db_siz);
     edit_db(db,db_siz);
  }
  return 0;
}