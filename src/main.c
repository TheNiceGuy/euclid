#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "euclid.h"
#include "config.h"

void printn(char* num, int b, int a) {
    int i;

    for(i = 0; num[i] != '.'; i++);
    for(b -= i; b > 0; b--)
        printf(" ");
    printf("%s", num);
}

int get_int(char* string, int min, int max) {
    int input;

    do {
        printf("%s [%d, %d] : ", string, min, max);
        scanf("%d", &input);
    } while(input < min || input > max);

    return input;
}

char* get_Str(char* string, char* buff) {
    while(getchar() != '\n');
    printf("%s", string);

    if (fgets(buff, BUFF, stdin) == NULL)
        return NULL;

    if(buff[strlen(buff)-1] != '\n')
        while(getchar() != '\n');

    buff[strlen(buff)-1] = '\0';
    return buff;
}

void get_enter() {
    char key;

    printf("\nAppuyer sur <entré> pour continuer...");

    while ((key = getchar()) != '\n' && key != EOF);
    getchar();
}

void menu_conv() {
    char num[BUFF];
    char* base;
    int in, out;

    clear();
    get_Str("Veuillez le nombre à convertir : " , num);
    in = get_int("Base initiale", 2, 16);
    out = get_int("Base finale", 2, 16);

    base = conv(num, in, out);
    if(base == NULL) {
        printf("\nLe nombre est invalide.\n");
        get_enter();
        return;
    }

    printf("\nNombre de départ : %s\n", num);
    printf(  "   Base initiale : %d\n", in);
    printf(  "     Base finale : %d\n", out);
    printf(  "Nombre convertit : %s\n", base);
    get_enter();

    free(base);
}

void menu_pgcd() {
    int a, b, c;

    clear();
    a = get_int("Veuillez entrer le premier nombre", -9999, 9999);
    b = get_int("Veuillez entrer le deuxième nombre", -9999, 9999);
    c = pgcd(a, b);

    printf("\nLe plus grand commun diviseur entre %d et %d est %d.\n", a, b, c);
    get_enter();
}

void menu_prime() {
    int p;

    clear();
    p = get_int("Veuillez entrer un nombre", -9999, 9999);

    if(is_prime(p))
        printf("\n%d est un nombre premier.\n", p);
    else
        printf("\n%d n'est pas un nombre premier.\n", p);
    get_enter();
}

void menu_ex() {
    char buffer[BUFF];
    char* str;
    int i;

    clear();
    printf("Voici une table de conversion.\n\n");
    printf("       Binaire"
           "      Octal"
           "   Decimal"
           "       Hex"
           "\n");

    for(i = -25; i <= 25; i++) {
        snprintf(buffer, BUFF, "%d.%d", i, abs(i));
        str = conv(buffer, 10, 2);
        printn(str, 9, 4);
        free(str);

        printf(" ");
        str = conv(buffer, 10, 8);
        printn(str, 5, 4);
        free(str);

        printf(" ");
        str = conv(buffer, 10, 10);
        printn(str, 4, 4);
        free(str);

        printf(" ");
        str = conv(buffer, 10, 16);
        printn(str, 4, 4);
        free(str);

        printf("\n");
    }
    get_enter();

    clear();
    printf("Voici une liste de nombre premier en bas de 5000.\n\n");
    for(i = 1; i <= 5000; i++)
        if(is_prime(i))
            printf("%d ", i);
    printf("\n");
    get_enter();
}


int main() {
    int exit = FALSE;

    do {
        clear();
        printf("Que voulez-vous effectuer?\n\n");
        printf("[0] Conversion\n");
        printf("[1] PGCD\n");
        printf("[2] Tester un nombre premier\n");
        printf("[3] Exemples\n");
        printf("[4] Quitter\n");

        switch(get_int("Veuillez faire votre choix", 0, 4)) {
            case 0:
                menu_conv();
                break;
            case 1:
                menu_pgcd();
                break;
            case 2:
                menu_prime();
                break;
            case 3:
                menu_ex();
                break;
            case 4:
                exit = TRUE;
                break;
        }
    } while(!exit);

    return 0;
}
