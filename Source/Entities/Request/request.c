//
// Created by andre on 15/05/2026.
//

#include "request.h"
#include "../Client/client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct request {
    char *requestID;
    Client *client;
    Device device;
    Priority priority;
    RequestStatus status;
    char *description;
    double estimatedCost;
    double finalCost;
    struct tm creationDate;
};

//Costruttore Richiesta
Request* create_request(const char *requestID, Client *client, Device device, Priority priority,
    const char *description, double estimatedCost, double finalCost, struct tm creationDate)
{
    if (requestID == NULL || client == NULL || description == NULL)
    {
        return NULL;
    }

    Request *request = malloc(sizeof(Request));
    if (request == NULL)
    {
        return NULL;
    }

    request->requestID = NULL;
    request->client = client;
    request->description = NULL;
    request->device = device;
    request->priority = priority;
    request->status = PENDING;
    request->estimatedCost = estimatedCost < 0 && estimatedCost != VAL_UNDEFINED ? 0 : estimatedCost;
    request->finalCost = finalCost < 0 && finalCost != VAL_UNDEFINED ? 0 : finalCost;
    request->creationDate = creationDate;

    request->requestID = malloc(strlen(requestID) + 1);
    if (request->requestID == NULL)
    {
        destroy_request(request);
        return NULL;
    }
    strcpy(request->requestID, requestID);

    request->description = malloc(strlen(description) + 1);
    if (request->description == NULL)
    {
        destroy_request(request);
        return NULL;
    }
    strcpy(request->description, description);

    return request;
}

//Distruttore Richiesta
void destroy_request(Request *request)
{
    if (request == NULL)
        return;

    free(request -> requestID);
    free(request -> description);
    free(request);
}

/*
 * -------------------
 * Getters
 * -------------------
 */

const char* get_request_id(const Request *request)
{
    if (request == NULL)
        return NULL;

    return request->requestID;
}

Client* get_request_client(const Request *request)
{
    if (request == NULL)
        return NULL;

    return request->client;
}

Device get_request_device(const Request *request)
{
    if (request == NULL)
        return 0;

    return request->device;
}

Priority get_request_priority(const Request *request)
{
    if (request == NULL)
        return 0;

    return request->priority;
}

RequestStatus get_request_status(const Request *request)
{
    if (request == NULL)
        return 0;

    return request->status;
}

const char* get_request_description(const Request *request)
{
    if (request == NULL)
        return NULL;

    return request->description;
}

double get_request_estimated_cost(const Request *request)
{
    if (request == NULL)
        return VAL_UNDEFINED;

    return request->estimatedCost;
}

double get_request_final_cost(const Request *request)
{
    if (request == NULL)
        return VAL_UNDEFINED;

    return request->finalCost;
}

struct tm get_request_creation_date(const Request *request)
{
    const struct tm empty = {0};

    if (request == NULL)
        return empty;

    return request->creationDate;
}

/*
 * -------------------
 * Setters
 * -------------------
 */

void set_request_client(Request *request, Client *client)
{
    if (request == NULL || client == NULL)
        return;

    request->client = client;
}

void set_request_device(Request *request, Device device)
{
    if (request == NULL)
        return;

    request->device = device;
}

void set_request_priority(Request *request, Priority priority)
{
    if (request == NULL)
        return;

    request->priority = priority;
}

void set_request_status(Request *request, RequestStatus status)
{
    if (request == NULL)
        return;

    request->status = status;
}

void set_request_description(Request *request, const char *description)
{
    if (request == NULL || description == NULL)
        return;

    void *temp = realloc(request->description, strlen(description) + 1);
    if (temp != NULL)
    {
        request->description = temp;
        strcpy(request->description, description);
    }
}

void set_request_estimated_cost(Request *request, double estimatedCost)
{
    if (request == NULL)
        return;

    request->estimatedCost = estimatedCost;
}

void set_request_final_cost(Request *request, double finalCost)
{
    if (request == NULL)
        return;

    request->finalCost = finalCost;
}

void set_request_creation_date(Request *request, struct tm creationDate)
{
    if (request == NULL)
        return;

    request->creationDate = creationDate;
}


