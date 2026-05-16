//
// Created by andre on 15/05/2026.
//

#include "client.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct client {
    char *clientID;
    char *name;
};

//Costruttore Cliente
Client* create_client(const char *clientID, const char *name)
{
    if (clientID == NULL || name == NULL)
    {
        return NULL;
    }

    Client *client = malloc(sizeof(Client));
    if (client == NULL)
    {
        return NULL;
    }

    client -> clientID = NULL;
    client -> name = NULL;

    client->clientID = malloc(strlen(clientID) + 1);
    if (client->clientID == NULL)
    {
        destroy_client(client);
        return NULL;
    }
    strcpy(client->clientID, clientID);

    client->name = malloc(strlen(name) + 1);
    if (client->name == NULL)
    {
        destroy_client(client);
        return NULL;
    }
    strcpy(client->name, name);

    return client;
}

//Distruttore Cliente
void destroy_client(Client *client)
{
    if (client == NULL)
        return;

    free(client->clientID);
    free(client->name);
    free(client);
}

/*
 * -------------------
 * Getters
 * -------------------
 */

const char *get_client_id(Client *client)
{
    if (client == NULL)
        return NULL;
    return client->clientID;
}

const char *get_client_name(Client *client)
{
    if (client == NULL)
        return NULL;
    return client->name;
}

/*
* -------------------
* Setters
* -------------------
*/

void set_client_name(Client *client, const char *name)
{
    if (client == NULL)
        return;

    void *temp = realloc(client->name, strlen(name) + 1);
    if (temp != NULL)
    {
        client->name = temp;
        strcpy(client->name, name);
    }
}

