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

bool search_by_request_id(Request* request, void *filterValue)
{
    if (request == NULL || filterValue == NULL)
        return false;

    char* requestId = (char*)filterValue;
    return strcmp(get_request_id(request), requestId) == 0;
}
