//
// Created by andre on 15/05/2026.
//

#include "requestStats.h"
#include "../../Entities/Request/request.h"
#include "../../Entities/RequestList/requestList.h"
#include "../../Interface/InterfaceBuilder/interfaceBuilder.h"
#include "../../RequestHandlers/RequestFilter/requestFilter.h"

void get_average_cost(RequestList *requestList, double avgByType[], size_t typesNumber, statsCriteria statsCriteria)
{
    if (requestList == NULL || requestList->count == 0 || statsCriteria == NULL)
        return;

    for (size_t i = 0; i < typesNumber; i++)
    {
        RequestList *filteredList = filter_requests(requestList, statsCriteria, &i);

        if (filteredList == NULL || filteredList->count == 0)
        {
            avgByType[i] = 0;
            continue;
        }

        double sum = 0;
        for (size_t j = 0; j < filteredList->count; j++)
        {
            double request_final_cost = get_request_final_cost(filteredList->requests[j]);
            if (request_final_cost != VAL_UNDEFINED)
            {
                sum += request_final_cost;
            } else
            {
                sum += get_request_estimated_cost(filteredList->requests[j]);
            }
        }

        avgByType[i] = sum / filteredList->count;

        destroy_request_list(filteredList);
    }
}

void get_max_cost(RequestList *requestList, double maxByType[], size_t typesNumber, statsCriteria statsCriteria)
{
    if (requestList == NULL || requestList->count == 0 || statsCriteria == NULL)
        return;

    for (size_t i = 0; i < typesNumber; i++)
    {
        RequestList *filteredList = filter_requests(requestList, statsCriteria, &i);

        if (filteredList == NULL || filteredList->count == 0)
        {
            maxByType[i] = VAL_UNDEFINED;
            continue;
        }

        double max;

        for (size_t j = 0; j < filteredList->count; j++)
        {
            double request_final_cost = get_request_final_cost(filteredList->requests[j]);
            double cost_to_consider = (request_final_cost != VAL_UNDEFINED) ? request_final_cost : get_request_estimated_cost(filteredList->requests[j]);

            if (j == 0) max = cost_to_consider;

            if (cost_to_consider > max)
            {
                max = cost_to_consider;
            }
        }

        maxByType[i] = max;
        destroy_request_list(filteredList);
    }
}

void get_min_cost(RequestList *requestList, double minByType[], size_t typesNumber, statsCriteria statsCriteria)
{
    if (requestList == NULL || requestList->count == 0 || statsCriteria == NULL)
        return;

    for (size_t i = 0; i < typesNumber; i++)
    {
        RequestList *filteredList = filter_requests(requestList, statsCriteria, &i);

        if (filteredList == NULL || filteredList->count == 0)
        {
            minByType[i] = VAL_UNDEFINED;
            continue;
        }

        double min = 0;

        for (size_t j = 0; j < filteredList->count; j++)
        {
            double request_final_cost = get_request_final_cost(filteredList->requests[j]);
            double cost_to_consider = (request_final_cost != VAL_UNDEFINED) ? request_final_cost : get_request_estimated_cost(filteredList->requests[j]);

            if (j == 0) min = cost_to_consider;

            if (cost_to_consider < min)
            {
                min = cost_to_consider;
            }
        }

        minByType[i] = min;
        destroy_request_list(filteredList);
    }
}
