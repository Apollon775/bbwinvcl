#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include "cl.h"


int main (int argc, char **argv)
{
    int sock;
    hostdata* data = hostdata_init();

    printf("%s\n", data->name);
    printf("%s\n", data->kernel);
    printf("%s\n",data->cpu);


    if ((sock = connectto(NULL)) < 0)
    {
       printf("Verbindung mit dem Server konnte nicht aufgenommen werden\n");
       return EXIT_FAILURE;
    }

    free(data);

}