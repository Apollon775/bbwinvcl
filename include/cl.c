#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>

#include "cl.h"

#define BUF 255
#define BUFFER 256

/*
 Versucht eine Verbidnung zu einem Server auf dem Port 3306 aufzubauen
 Gibt -1 zurück wenn die Verbindung nicht hergestellt worden konnte
*/
int connectto(char *inetaddr)
{
    int sock;
    int size;
    struct sockaddr_in address;
    if(inetaddr == NULL)
    {
        inetaddr = "172.16.34.39";
    }
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
       return -1; 
    }

    inet_aton(inetaddr, &address.sin_addr);

    address.sin_family = AF_INET;
    address.sin_port = htons(3306);

    if(connect(sock, (struct sockaddr*) &address, sizeof(address)) != 0)
    {
        return -1;
    }

    return sock;

}

// Entfernt jeden Whitespace aus einem String bis zu einem definierten Termintaor
// und kopiert das Ergebnis in einen neuen String
// Gibt die Größe des Strings zurück als Integer wert zurück
int rmws(char *src, char terminator)
{
    char cpy[BUFFER];
    int line_len;
    unsigned int count = 0;

    if (src == NULL)
    {
        return -1;
    }
    for(int i = 0; i < BUFFER; ++i)
    {
        if (src[i] == '\n') 
        {
            line_len = i +1;
            break;
        }
    }

    for(int i = 0; i < line_len; ++i)
    {
        
        if(src[i] == terminator)
        {
            cpy[count] = '\0';
            break;
        }
        else if(!(isspace(src[i])))
        {
            cpy[count] = src[i];
            ++count;
        }

    }

    strcpy(src, cpy);
    return count;
}


//Öffnet /proc/cpuinfo und gibt den Moddell-Namen der CPU als String zurück
//Gibt einen Null-Pointer zurück falls es zu einem Fehler gekommen ist
char* read_cpuinfo()
{
    FILE* cpuinfo = fopen("/proc/cpuinfo","r");
    char str[BUFFER];
    char* finalstr = malloc(BUFFER);
    int i; 
    char buffer;
    int count = 0;

    if(cpuinfo == NULL)
    {
        printf("cpuinfo konnte nicht geöffnet werden");
        free(finalstr);
        return NULL;
    }

    while(fgets(str, BUFFER, cpuinfo))
    {
        if(!(strncmp(str, "model name", 10)))
        {
            rmws(str, '\n');
            printf("%s", str);

            rmws(str, '\n');
            for(int i = 0; i < strlen(str); ++i)
            {
                if(str[i] == ':')
                {
                    for(int ii = i + 1; ii < strlen(str); ++ii)
                    {
                        finalstr[count] = str[ii];
                        ++count;
                    }

                    finalstr[count] = '\0';
                    return finalstr;
                }
            }
        }
    }

    return finalstr;
}

char* read_addr()
{
    
}

char* read_mac()
{

}



char* read_kernel()
{
    FILE* version = fopen("/proc/version","r");
    char* str = malloc(BUFFER);
    char c;
    int count = 0;

    if(version == NULL)
    {
        free(str);
        return NULL;
    }

    while((c =fgetc(version)) != '(')
    {
        str[count] = c;
        ++count;
    }

    str[count] = '\0';
    return str;
}

// Öffnet die /etc/hostname und gibt den Hostname als String zurück
// Gibt einen Null-Pointer zurück falls es zu einem Fehler gekommen ist
char* read_hostname()
{
    FILE* hostname = fopen("/etc/hostname","r");
    char* str = malloc(BUFFER);
    char c;
    int count = 0;
    
    if(hostname == NULL)
    {
        free(str);
        return NULL;
    }

    while ((c = fgetc(hostname)) != '\n' )
    {
        str[count] = c;
        ++count;
    }

    str[count] = '\0';

    return str;

    #undef BUFFER 
}

//Initialiesiert einen Datenobjekt, dass an den Server übertragen werden soll
hostdata* hostdata_init()
{
    hostdata *data = malloc(sizeof(struct _hostdata));

    //TODO: Einfügen von guter Fehlerbehandlung
    data->name = read_hostname();
    data->cpu = read_cpuinfo();
    data->kernel = read_kernel();
/*
    if(data->name == NULL ||
        data->cpu == NULL ||
        data->kernel == NULL)
    {
        free(data->name);
        free(data->cpu);
        free(data->kernel);
        free(data);

        return NULL;
    }
*/
    return data;
}

int hostdata_del(hostdata *data)
{

}
