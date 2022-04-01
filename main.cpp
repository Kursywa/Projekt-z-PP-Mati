#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<locale.h>
#include<string.h>
#include<cstring>

using namespace std;
static int aaa = 0;
struct ObiektWypozyczenia{
    int  ID;
    char NazwaObiektu[30];
    char ImieAutora[30];
    char NazwiskoAutora[30];
    char Kategoria[13];
    struct DataWypozyczenia{
        int rok;
        int miesiac;
        int dzien;
    }daty;
    char ImieWypozyczajacego[30];
    char NazwiskoWypozyczajacego[30];
    char StanWypozyczenia[12];
    struct ObiektWypozyczenia *next;
    struct ObiektWypozyczenia *prev;
}obiekty
;
//globalne konstrukcje
struct ObiektWypozyczenia *head = NULL;
struct ObiektWypozyczenia *tmp;
int *elem;
//globalne zmienne
char nazwa[30];
char wypozyczony[] = "wypozyczony";
//deklarowanie funkcji
void Dodaj();
void wyswietl();
int dlugosc();
void usun(int ID);
void usun( char nazwa[] );
void free_element( ObiektWypozyczenia *elem );
void edytuj(int ID);
void edytuj(char nazwa[]);
void edit_structure();
void wypozycz(int ID);
void wypozycz(char nazwa[]);
void borrow_structure();

int main(){
    setlocale(LC_CTYPE, "Polish");
    //declaring variables
    struct ObiektWypozyczenia;

    char menu;
    int decision, ID;
    //menu prompt (might put it in function)
    menu:
    printf("Prosze podac znak z nizej podanych:\n");
    printf("1) Dodaj nowy obiekt (przez obiekt rozumiemy ksiazke/film/gre planszowa)\n2) Usun obiekt\n3) Edytuj dane obieku\n4) Zmien status obiektu\n");
    printf("5) Wyszukaj obiekt po nazwie lub ID\n6) Wyswietl baze po nazwach obiektow\n7) Wyswietl obiekty wypozyczone\n8) Zapisz do pliku\n9) Odczytaj z pliku\nX) Zakoncz program\n");
    printf("W) wyswietl liste czytelnikow\n");
    scanf(" %c", &menu);
    //menu code
    switch(menu)
    {
    case '1': // dodaj nowy obiekt
        Dodaj();
        goto menu;
        break;

    case '2': //usun


        printf("deleting by ID (1) or name (2)? ");
        scanf(" %d",&decision);
        if(decision == 1){
            printf("which ID to be deleted?\n");
            scanf(" %d",&ID);
            usun(ID);
        }
        if(decision == 2){
            printf("type the name of the object you want to delete:  ");
            scanf(" %s",&nazwa);
            usun(nazwa[30]);
        }
        goto menu;
        break;

    case '3': //edit

        printf("Edytowac obiekt po ID (1) czy nazwie (2)?: ");
        scanf(" %d",&decision);
        if(decision == 1){
            printf("Ktore ID ma być zedytowane?: ");
            scanf(" %d",&ID);
            edytuj(ID);
        }
        if(decision == 2){
            printf("Wpisz nazwe obiektu, ktory chcesz zedytowac: ");
            scanf(" %s",&nazwa);
            edytuj(nazwa[30]);
        }
        goto menu;
        break;

    case '4': // zmien status na wypozyczony

            printf("Zmienic status obiektu po ID (1) czy nazwie (2)?: ");
            scanf(" %d",&decision);
            if(decision == 1){
                printf("ID obiektu do wypozyczenia: ");
                scanf(" %d",&ID);
                wypozycz(ID);
            }
            if(decision == 2){
                printf("nazwa obiektu, ktory chcesz wypozyczyc: ");
                scanf(" %s",&nazwa);
                wypozycz(nazwa[30]);
            }
        goto menu;
        break;

    case '5': //wyswietl baze po nazwie lub ID

        goto menu;
        break;

    case '6': //Wyświetl bazę po nazwach obiektów
        wyswietl();
        goto menu;
        break;





    case 'w':
    case 'W':
        printf("Lista czytelnikow: \n");
        tmp = head;
        while(tmp != NULL && tmp->ImieWypozyczajacego != NULL) {
            printf("imie czytelnika: %s\tnazwisko czytelnika: %s\n",tmp->ImieWypozyczajacego,tmp->NazwiskoWypozyczajacego);
            tmp = tmp->next;
        }
        if(tmp = NULL){
            printf("\n");
        }
    goto menu;
    break;

    case 'X':
    case 'x':
        return 0;
        break;

    default:
        printf("nieprawidlowy znak funkcji!\n");
        goto menu;
    }





}


void Dodaj() // musi dostawac pierwszy wolny ID
{
    dodajobiekt:
    //struct ObiektWypozyczenia *tmp;
    tmp = (struct ObiektWypozyczenia*)malloc(sizeof(struct ObiektWypozyczenia));
    /*Dodaj nową obiekt: funkcja tworzy nowy obiekt książkę, film lub grę planszową, wcześniej pytając o nazwę
(tytuł), kategorię i dane autora. Program automatycznie przypisuje pierwszy wolny ID do nowego obiektu,
który następnie dodawany jest na koniec listy (lub jako pierwszy element, gdy lista jest jeszcze pusta). Po
dodaniu nowego obiektu program pyta, czy ma wrócić do głównego menu, czy dodać nowy obiekt.*/
    printf("Podaj tytul obiektu: ");
    scanf(" %s",tmp->NazwaObiektu);
    printf("\nPodaj Podaj kategorie obiektu(ksiazka/film/gra planszowa: ");
    scanf(" %s",tmp->Kategoria);
    printf("\nPodaj Imie, a nastepnie nazwisko autora:\n");
    scanf(" %s",tmp->ImieAutora);
    scanf(" %s",tmp->NazwiskoAutora);

    /* tmp->StanWypozyczenia = '';
    tmp->ImieWypozyczajacego = null;
    tmp->NazwiskoWypozyczajacego = null; */
    //jezu jak przypisac to ID
    tmp->ID = aaa++;

    tmp->next = NULL;
    tmp->prev = NULL;

    //warunki
    if(head == NULL){
        head = tmp;
    }
    else{
        struct ObiektWypozyczenia *p;
        p = head;
        while(p->next != NULL){
            p = p->next;
        }
        p->next = tmp;
        tmp->prev = p;
    }

    char decyzja;
    printf("Dodac kolejny obiekt? Y/N \n");
    scanf(" %c",&decyzja);
    if(decyzja == 'y' || decyzja == 'Y'){
        goto dodajobiekt;
    }
}
/* Wyświetl bazę po nazwach (tytułach): funkcja wyświetla bazę po nazwach obiektów (tytułach) z zachowaniem
informacji o danych autora i kategorii obiektu.*/
void wyswietl()
{
    tmp = head;
    //struct ObiektWypozyczenia *tmp = head; //wskaznik element do iterowania
    //int len = dlugosc(head);
            if(tmp == NULL){
                printf("brak listy do wyswietlenia!\n\n");
            }
            while(tmp != NULL){
                printf("ID: %d\n", tmp->ID);
                printf("Nazwa obiektu: %s\n", tmp->NazwaObiektu);
                printf("Kategoria: %s\n", tmp->Kategoria);
                printf("Imie autora %s\n", tmp->ImieAutora);
                printf("Nazwisko autora: %s\n", tmp->NazwiskoAutora);
                printf("Stan wypozyczenia: %s\n",tmp->StanWypozyczenia);
                printf("Imie wypozyczajacego: %s\n",tmp->ImieWypozyczajacego);
                printf("Nazwisko wypozyczajacego: %s\n\n", tmp->NazwiskoWypozyczajacego);

                tmp = tmp->next;
            }
}
/* Usuń obiekt: funkcja najpierw program pyta czy usuwanie ma być po ID czy po nazwie (tytule). Następnie
prosi o odpowiednie dane (ID lub nazwa (tytuł)) i usuwa obiekt z listy. Gdy obiektu o podanym ID/nazwie
(tytule) nie ma w ogóle na liście - wyświetla odpowiedni komunikat i wraca do głównego menu. */

   void free_element( ObiektWypozyczenia *elem ) {

    if(strcmp(tmp->StanWypozyczenia,"wypozyczony") == 0) {
        printf("Dany obiekt jest juz wypozyczony! Nie mozna go usunac.\n\n");
    }
    else{

    ObiektWypozyczenia *prev = elem->prev;
    ObiektWypozyczenia *next = elem->next;

    if( prev != NULL ) {
        prev->next = next;
    }
    if( next != NULL ) {
        next->prev = prev;
    }
    // Special case just in case head is the element being removed we don't want
    // to invalidate its pointer by freeing it, so set it to the next element
    if( elem == head ) {
        head = next;
    }
    free( elem );
    }
}

// Remove by ID
void usun(int ID){
    tmp = head;
    while( tmp != NULL ) {
        if( tmp->ID == ID ) {
            free_element( tmp );
            return;
        }
        tmp = tmp->next;
    }
}

// Remove by name
void usun( char nazwa[] ) {
    tmp = head;
    while( tmp != NULL ) {
        if( strcmp( nazwa, tmp->NazwaObiektu ) == 0 ) {
            free_element( tmp );
            return;
        }
        tmp = tmp->next;
    }
}

void edit_structure(){
    printf("Podaj nowy tytul obiektu: ");
    scanf(" %s",tmp->NazwaObiektu);
    printf("\nPodaj nowa kategorie obiektu(ksiazka/film/gra planszowa: ");
    scanf(" %s",tmp->Kategoria);
    printf("\nPodaj nowe Imie, a nastepnie nowe nazwisko autora:\n");
    scanf(" %s",tmp->ImieAutora);
    scanf(" %s",tmp->NazwiskoAutora);

}

//edit by ID
void edytuj(int ID){
    tmp = head;
    while( tmp != NULL ) {
        if( tmp->ID == ID ) {
                if(strcmp(tmp->StanWypozyczenia,"wypozyczony") == 0){

                }
                else{
                edit_structure();
                return;
                }
        }
        tmp = tmp->next;
}
}

//edit by name
void edytuj(char nazwa[]){
    tmp = head;
    while( tmp != NULL ) {
        if( strcmp( nazwa, tmp->NazwaObiektu ) == 0 ) {
                edit_structure();
                return;
        }
        tmp = tmp->next;
}
}

void wypozycz(int ID){
    tmp = head;
    while( tmp != NULL ) {
        if( tmp->ID == ID ) {
                borrow_structure();
                return;
        }
        tmp = tmp->next;
}
}

void wypozycz(char nazwa[]){
    tmp = head;
    while( tmp != NULL ) {
        if( strcmp( nazwa, tmp->NazwaObiektu ) == 0 ) {
                borrow_structure();
                return;
        }
        tmp = tmp->next;
}
}

void borrow_structure(){
    printf("podaj imie wypozyczajacego: ");
    scanf(" %s", tmp->ImieWypozyczajacego);
    printf("podaj nazwisko wypozyczajacego: ");
    scanf(" %s",tmp->NazwiskoWypozyczajacego);
    printf(" wpisz date wypozyczenia (dzien/miesiac/rok): ");
    scanf(" %d", &tmp->daty.dzien);
    scanf(" %d", &tmp->daty.miesiac);
    scanf(" %d", &tmp->daty.rok);
    strcpy(tmp->StanWypozyczenia,"wypozyczony");
}

int dlugosc(){
    struct ObiektWypozyczenia* tmp = head;
    int count = 0;
    while(tmp != NULL){
        count++;
        tmp = tmp->next;
    }
    return count;
}

/*
char *strcpy(
   char *strDestination,
   const char *strSource
);
wchar_t *wcscpy(
   wchar_t *strDestination,
   const wchar_t *strSource
);
unsigned char *_mbscpy(
   unsigned char *strDestination,
   const unsigned char *strSource
);
*/
