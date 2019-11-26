#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>

#include <sys/stat.h>
#include <ifaddrs.h>
#include <netpacket/packet.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "ifdata.h"
#include "cl.h"


// Benutzt das Sysfs um die Physikalische Adresse aus Linux-Systemen auszulesen.
char** read_physical(int *size)
{
    FILE* addrFile;
    int ifCount = 0;
    char **dirpath;
    char *path = "/sys/class/net";

    DIR *dp;
    struct dirent *dir;
    struct stat filestat;
    int dircount = 0;

    char c;
    char **addr;
    int strcount = 0;


    if ((dp = opendir(path)) ==NULL)
        return NULL; 
    
    while((dir = readdir(dp)) != NULL)
    {
        stat(dir->d_name, &filestat);
        if( S_ISDIR(filestat.st_mode))
            if(!( strcmp(dir->d_name, "lo")))
            {
               ++ifCount;
            }
    }

    dirpath = (char**)calloc(ifCount, BUFFER);

    while((dir = readdir(dp)) != NULL)
    {
        stat(dir->d_name, &filestat);
        if( S_ISDIR(filestat.st_mode))
            if(!( strcmp(dir->d_name, "lo")))
            {
                dirpath[dircount] = strcat(strcat(path,"/"), dir->d_name);
                ++dircount;
            }
    }

    addr = (char**)calloc(ifCount, BUFFER);

    for (int i = 0; i < ifCount; ++i)
    {
        addrFile = fopen(dirpath[i], "r");

        while((c =fgetc(addrFile)) != EOF)
        {
            addr[i][strcount] = c;
            ++strcount;
        }

        addr[strcount] = (char*)'\0';

        fclose(addrFile);
    }
    
    *size = ifCount;

    closedir(dp);

    return addr;
}


char *readifname(struct ifaddrs* ifaddr)
{
    int i = 0;
    char *name = (char*)malloc(BUFFER);
    
    if (ifaddr) 
    {
        if (ifaddr->ifa_name)
            strcpy(name, ifaddr->ifa_name);
    }

    return name;
}


char *readifphysical(struct ifaddrs* ifaddr)
{
    int i = 0;
    char *physical = (char*)malloc(BUFFER);
    
    if (ifaddr) 
    {
        struct sockaddr_ll *s = (struct sockaddr_ll*)ifaddr->ifa_addr;
        for (i = 0; i < s->sll_halen; ++i)
        {
            sprintf(physical, "%s%02x%c",(i==0)?"":physical, s->sll_addr[i] ,(i+1!=s->sll_halen)?':':'\0');
        }

    }

    return physical;
}


char *readifip(struct ifaddrs* ifaddr)
{
    int i = 0;
    char *ip = (char*)malloc(BUFFER);
    
    if (ifaddr->ifa_addr && ifaddr ->ifa_addr->sa_family == AF_INET)
    { 
            struct sockaddr_in *in = (struct sockaddr_in*) (ifaddr->ifa_addr);
            inet_ntop(AF_INET, &(in->sin_addr), ip, BUFFER);  
    } 
    else if(ifaddr->ifa_addr && ifaddr ->ifa_addr->sa_family == AF_INET6) 
    {
        struct sockaddr_in *in = (struct sockaddr_in*) (ifaddr->ifa_addr);
            inet_ntop(AF_INET6, &(in->sin_addr), ip, BUFFER);  
    } 
    else
    {
        free(ip);
        ip = NULL;
    }
    return ip;
}


char *readifipv6()
{

}


int countif(struct ifaddrs *ifaddr)
{
    struct ifaddrs *ifa = NULL;
    int count = 0;

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        if ((ifa) && (ifa->ifa_addr->sa_family == AF_INET))
        {
            ++count;
        }
    }

    return count;
}


ifdata_t** ifdata_init()
{
    int ifCount, pointer = 0; 
    ifdata_t **ifArray;

    struct ifaddrs *ifaddr = NULL; 
    struct ifaddrs *ifa = NULL;

    if (getifaddrs(&ifaddr) == -1)
    {
        perror("getifaddrs()");
    }

    ifCount = countif(ifaddr);

    ifArray = (ifdata_t**)calloc(ifCount, sizeof(ifdata_t*));

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        if ((ifa) && (ifa->ifa_addr->sa_family == AF_INET))
        {
            ifArray[pointer] = (ifdata_t*)malloc(sizeof(ifdata_t));    
            ifArray[pointer]->name = readifname(ifa);
            ifArray[pointer]->ipv4 = readifip(ifa);
            ifArray[pointer]->ipv6 = "Not yet implemented";
            ifArray[pointer]->type = "Not yet implemented";
            ++pointer;
        }

    }

    pointer = 0;

     for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        if ((ifa) && (ifa->ifa_addr->sa_family == AF_PACKET))
        {
            for (size_t i = 0; ifArray[i] != NULL; ++i)
            {
                if (!strcmp(ifa->ifa_name, ifArray[i]->name))
                {
                    ifArray[i]->physical =readifphysical(ifa);
                }
            }
            ++pointer;
        }

    }
  
    freeifaddrs(ifaddr);
    return ifArray;
}


void ifdata_del(ifdata_t *data)
{
    if (data->ipv4)
        free(data->ipv4);
    //free(data->ipv6);
    if (data->name)
        free(data->name);
    if(data->physical)
        free(data->physical);
    //free(data->type);
    if(data)
        free(data);
}