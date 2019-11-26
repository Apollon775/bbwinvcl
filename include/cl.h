#pragma once

#include <stdlib.h>
#include "ifdata.h"

#define BUFFER 256


//Die Daten die an den Server geschickt werden
struct _hostdata
{
    char *name;
    char *kernel;
    char *user;
    char *cpu;
    ifdata_t **interfaces;
};

typedef struct _hostdata hdata_t;

int connectto(char *inetaddr, int port);

char* read_hostname();

hdata_t* hdata_init();

int send_data(int sock_fd, hdata_t *data);

void hdata_del(hdata_t *data);


