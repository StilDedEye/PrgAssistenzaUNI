//
// Created by andre on 15/05/2026.
//

#include "requestFilter.h"
#include "../../Entities/RequestList/requestList.h"
#include "../../Entities/Request/request.h"
#include "../../Entities/Client/client.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

RequestList* filter_requests(RequestList* requestList, filterCriteria criteria, void* filterValue)
{
    if (requestList == NULL)
        return NULL;

    RequestList* filteredList = malloc(sizeof(RequestList));
    if (filteredList == NULL)
        return NULL;

    init_request_list(filteredList);

    for (int i = 0; i < requestList->count; i++)
    {
        Request* request = requestList->requests[i];
        if (criteria(request, filterValue))
        {
            add_request(filteredList, request);
        }
    }

    return filteredList;
}

/*
 * ------------------------
 * Ricerca richiesta per ID
 * ------------------------
 */

RequestList* search_by_request_id(RequestList* requestList, char* requestID)
{
    if (requestList == NULL || requestID == NULL)
        return NULL;

    RequestList* filteredList = malloc(sizeof(RequestList));
    if (filteredList == NULL)
        return NULL;

    init_request_list(filteredList);

    int left = 0;
    int right = requestList->count - 1;

    while (left <= right)
    {
        int middle = left + (right - left) / 2;
        Request* currentRequest = requestList->requests[middle];

        if (currentRequest == NULL || get_request_id(currentRequest) == NULL)
        {
            return NULL;
        }

        int comparison = strcmp(get_request_id(currentRequest), requestID);

        if (comparison == 0)
            add_request(filteredList, currentRequest);

        if (comparison < 0)
            left = middle + 1;
        else
            right = middle - 1;
    }

    return filteredList;
}

/*
 * ------------------------
 * Criteri di Filtraggio
 * ------------------------
 */

bool filter_by_status(Request* request, void *filterValue)
{
    if (request == NULL || filterValue == NULL)
        return false;

    RequestStatus filterStatus = *(RequestStatus*)filterValue;
    return get_request_status(request) == filterStatus;

}

bool filter_by_priority(Request* request, void *filterValue)
{
    if (request == NULL || filterValue == NULL)
        return false;

    Priority filterPriority = *(Priority*)filterValue;
    return get_request_priority(request) == filterPriority;
}

bool filter_by_device(Request* request, void *filterValue)
{
    if (request == NULL || filterValue == NULL)
        return false;

    Device filterDevice = *(Device*)filterValue;
    return get_request_device(request) == filterDevice;
}

bool filter_by_client_name(Request* request, void *filterValue)
{
    if (request == NULL || filterValue == NULL)
        return false;

    char* filterName = (char*)filterValue;
    Client* client = get_request_client(request);
    if (client == NULL)
        return false;

    return strcmp(get_client_name(client), filterName) == 0;
}

bool filter_by_client_id(Request* request, void *filterValue)
{
    if (request == NULL || filterValue == NULL)
        return false;

    Client* client = get_request_client(request);
    if (client == NULL)
        return false;

    return strcmp(get_client_id(client), filterValue) == 0;
}

bool filter_by_request_id(Request* request, void *filterValue)
{
    if (request == NULL || filterValue == NULL)
        return false;

    char* requestId = (char*)filterValue;
    return strcmp(get_request_id(request), requestId) == 0;
}
