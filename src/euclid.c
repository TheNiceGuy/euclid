#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "euclid.h"
#include "config.h"

int get_val(char sym) {
    switch(sym) {
        /* Pour les chiffres de 0 à 9. */
        default:
        case '0' ... '9':
            return sym-'0';

        /* Pour les chiffres de A à F. */
        case 'A' ... 'F':
            return sym-'7';
    }
}

char get_sym(unsigned int val) {
    switch(val) {
        /* Pour les chiffres de 0 à 9. */
        default:
        case 0 ... 9:
            return val+'0';

        /* Pour les chiffres de A à F. */
        case 0xA ... 0xF:
            return val+'7';
    }
}

int is_base(char* num, int base) {
    int len = strlen(num);
    int dec = FALSE;
    int i;

    /* On regarde chaque caractère. */
    for(i = 0; i < len; i++) {
        /* On s'assure qu'un seul point est présent. */
        if(num[i] == '.' && !dec) {
            dec = TRUE;
            continue;
        }

        /* On s'assure que le symbole existe dans la base. */
        if(get_val(num[i]) < 0 || get_val(num[i]) >= base)
            return FALSE;
    }

    return TRUE;
}

int is_prime(int num) {
    int* sieve;
    int i, j;

    /* On alloue la mémoire pour le cribble d'Eratosthène. */
    sieve = malloc((num+1)*sizeof(int));
    if(sieve == NULL)
        return FALSE;

    /* On assume tout les nombres étant premier. */
    memset(sieve, TRUE, (num+1)*sizeof(int));

    /* On calcule le cribble d'Eratothène. */
    for(i = 2; i <= num; i++) {
        if(!sieve[i])
            continue;

        for(j = 1; i*j <= num; j++)
            sieve[i*j] = FALSE;

        if(i == num) {
            free(sieve);
            return TRUE;
        }
    }

    free(sieve);
    return FALSE;
}

char* conv_whole(char* num, int in, int out) {
    char* result;
    int len = strlen(num);
    int i, tmp, size;
    int base10 = 0;

    /* On convertit le nombre en base 10. */
    for(i = 0; i < len; i++)
        base10 += get_val(num[len-i-1])*pow(in, i);

    /* On calcule la taille du résultat. */
    for(tmp = base10, i = 0; tmp != 0; i++)
        tmp /= out;
    size = i;

    /* On alloue la mémoire du résultat. */
    result = malloc((size+1)*sizeof(char));
    result[size] = '\0';

    /* On convertit finalement vers la base voulue. */
    for(i = 0; i < size; i++) {
        result[size-i-1] = get_sym(base10%out);
        base10 /= out;
    }

    return result;
}

char* conv_frac(char* num, int in, int out) {
    char* result;
    int len = strlen(num);
    int i, size;
    float base10 = 0;

    /* On convertit le nombre en base 10. */
    for(i = 1; i <= len; i++)
        base10 += get_val(num[i-1])*pow(in, -i);

    size = PRECISION;

    /* On alloue la mémoire du résultat. */
    result = malloc(size*sizeof(char));
    result[size-1] = '\0';

    /* On convertit finalement vers la base voulue. */
    for(i = 0; i < size-1; i++) {
        base10 *= out;
        result[i] = get_sym((int)base10);
        base10 -= (int)base10;
    }

    return result;
}

char* conv(char* num, int in, int out) {
    char* result;
    char* whole;
    char* frac;
    char* ptr;
    int len = strlen(num);
    int dec = FALSE;
    int neg = FALSE;
    int size[2];
    int i;

    /* On regarde si le chiffre est négatif. */
    if(num[0] == '-') {
        neg = TRUE;
        num++;
    }

    /* On s'assure que le nombre est valide. */
    if(!is_base(num, in))
        return NULL;

    /* On obtient la position du point décimale. */
    for(i = 0; i < len; i++) {
        if(num[i] == '.') {
            dec = TRUE;
            break;
        }
    }

    /* On obtient la partie entière. */
    whole = malloc((i+1)*sizeof(char));
    memcpy(whole, num, i);
    whole[i] = '\0';

    /* On obtient la partie fractionnaire. */
    frac = malloc((len-i+1)*sizeof(char));
    memcpy(frac, &num[i+1], len-i);
    frac[len-i] = '\0';

    /* On convertit la partie entière. */
    ptr = whole;
    whole = conv_whole(whole, in, out);
    free(ptr);

    /* On convertit la partie fractionnaire. */
    ptr = frac;
    if(dec)
        frac = conv_frac(frac, in, out);
    else
        frac = conv_frac("0000", in, out);
    free(ptr);

    /* On calcule la taille des parties. */
    size[0] = strlen(whole);
    size[1] = strlen(frac);

    /*On alloue la mémoire pour le résultat final. */
    if(neg) {
        result = malloc((size[0]+size[1]+3)*sizeof(char));

        /* On ajoute le moins si le nombre est négatif. */
        result[0] = '-';
        result++;
    } else {
        result = malloc((size[0]+size[1]+3)*sizeof(char));
    }

    /* On ajoute le point décimal et la termination. */
    result[size[0]] = '.';
    result[size[0]+size[1]+1] = '\0';

    /* On combine les résultats. */
    memcpy(result, whole, size[0]);
    memcpy(&result[size[0]+1], frac, size[1]);

    /* On libère la mémoire. */
    free(whole);
    free(frac);

    /* On affiche le moins, si le chiffre est négatif. */
    if(neg)
        result--;

    return result;
}

int pgcd(int a, int b) {
    /* On s'assure qu'un nombre n'est pas nulle. */
    if(a == 0 && b == 0)
        return ERR;

    /* Le pgcd de 1 ou 2 nombres négatifs est équivalent à leur valeur absolue. */
    a = abs(a);
    b = abs(b);

    /* On calcule le pgcd. */
    while(a != b)
        if(a < b)
            b -= a;
        else
            a -= b;

    return a;
}
