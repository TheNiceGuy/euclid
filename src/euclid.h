#ifndef EUCLID_INCLUDE_H
#define EUCLID_INCLUDE_H

#define PRECISION 5

int get_val(char sym);
char get_sym(unsigned int val);
int is_base(char* num, int base);
int is_prime(int num);
char* conv_whole(char* num, int in, int out);
char* conv_frac(char* num, int in, int out);
char* conv(char* num, int in, int out);
int pgcd(int a, int b);

#endif
