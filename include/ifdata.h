#pragma once

struct _interfacedata
{
    char *physical;
    char *ipv4;
    char *ipv6;
    char *name;
    char *type;
};

typedef struct _interfacedata ifdata_t;


//Gibt eine array mit dynamischen Structs ide Infomrationen zu den einzelnen Interfaces befindet
//(loopback interface ausgeschlossen)
ifdata_t **ifdata_init();

void ifdata_del(ifdata_t *data);