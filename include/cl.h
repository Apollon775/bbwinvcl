#include <stdlib.h>

//Die Daten die an den Server geschickt werden
struct _hostdata
{
    char *name;
    char *kernel;
    char *cpu;
/*
    char *physical; 
    char *in_addr;
*/
};

typedef struct _hostdata hostdata;

int connectto(char *inetaddr);

hostdata* hostdata_init();




