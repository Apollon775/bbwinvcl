#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "cl.h"
#include "ifdata.h"

int main (int argc, char **argv)
{
    int sock;
    hdata_t *data = hdata_init();
    int size;



    if ((sock = connectto(NULL, 6661)) < 0)
    {
       printf("Verbindung mit dem Server konnte nicht aufgenommen werden\n");
       return EXIT_FAILURE;
    }

    if(send_data(sock, data))
    {
        printf("send() error");
    }

    hdata_del(data);

}