//
// Created by aless on 16/05/2026.
//

#include "requestList.h"
#include "../Request/request.h"
#include "../Client/client.h"

#include <stdlib.h>
#include <string.h>


void request_list_init(RequestList* requestList)
{
    requestList->count = 0;
    requestList->capacity = 0;
    requestList->requests = NULL;
}

int add_request(RequestList* requestList, Request* request)
{
    if (requestList == NULL || request == NULL)
        return -1;

    if (requestList->count >= requestList->capacity)
    {
        int newCapacity = (requestList->capacity == 0) ? 4 : requestList->capacity * 2;
        Request **newRequests = realloc(requestList->requests, newCapacity * sizeof(Request*));
        if (newRequests == NULL)
            return -1;

        requestList->requests = newRequests;
        requestList->capacity = newCapacity;
    }

    requestList->requests[requestList->count] = request;
    requestList->count++;

    return 0;
}
