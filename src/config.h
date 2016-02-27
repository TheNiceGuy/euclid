#ifndef INCLUDE_CONFIG_H
#define INCLUDE_CONFIG_H

#undef TRUE
#undef FALSE

#define SUCCESS 0
#define FAILED  1

#define TRUE  1
#define FALSE 0

#define BUFF 10
#define ERR -1

#ifndef __LINUX__
    #define clear(); system("cls");
#else
    #define clear(); system("clear");
#endif

#endif
