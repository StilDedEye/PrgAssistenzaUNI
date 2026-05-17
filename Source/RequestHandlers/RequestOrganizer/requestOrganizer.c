//
// Created by andre on 15/05/2026.
//

#include "requestOrganizer.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../../Entities/Request/request.h"
#include "../../Entities/RequestList/requestList.h"

void merge(Request **arr, size_t left, size_t mid, size_t right,
    bool (*criteria)(Request*, Request*, int), int order)
{
    // Dimensione delle due metà da unire: [left..mid] e [mid+1..right]
    size_t l_size = mid - left + 1;
    size_t r_size = right - mid;

    // Copie temporanee delle due sotto-sequenze da confrontare e fondere
    Request **left_arr = malloc(sizeof(Request*) * l_size);
    Request **right_arr = malloc(sizeof(Request*) * r_size);

    if (left_arr == NULL || right_arr == NULL)
    {
        free(left_arr);
        free(right_arr);
        return;
    }

    for (size_t i = 0; i < l_size; i++)
        left_arr[i] = arr[left + i];

    for (size_t i = 0; i < r_size; i++)
        right_arr[i] = arr[mid + 1 + i];

    // Confronta gli elementi delle due metà e riscrive l'array originale in ordine crescente
    size_t i = 0, j = 0, k = left;
    while (i < l_size && j < r_size)
    {
        if (criteria(left_arr[i], right_arr[j], order))
        {
            arr[k++] = left_arr[i++];
        }
        else
        {
            arr[k++] = right_arr[j++];
        }
    }

    // Copia gli eventuali elementi rimasti nella metà sinistra
    while (i < l_size)
        arr[k++] = left_arr[i++];
    // Copia gli eventuali elementi rimasti nella metà destra
    while (j < r_size)
        arr[k++] = right_arr[j++];

    free(left_arr);
    free(right_arr);
}

void merge_sort(Request **arr, size_t left, size_t right,
    bool (*criteria)(Request*, Request*, int), int order)
{
    if (left < right)
    {
        // Divide ricorsivamente il segmento a metà finché non resta un solo elemento
        size_t mid = left + (right - left) / 2;

        merge_sort(arr, left, mid, criteria, order);
        merge_sort(arr, mid + 1, right, criteria, order);
        // Ricompone le due metà già ordinate
        merge(arr, left, mid, right, criteria, order);
    }
}

void request_list_sort(RequestList *requestList,
    bool (*criteria)(Request*, Request*, int), int order)
{
    // Non c'è nulla da ordinare se la lista è nulla, vuota o composta da un solo elemento
    if (requestList == NULL || requestList->requests == NULL || requestList->count < 2)
        return;

    // Avvia il merge sort sull'intero array di richieste
    merge_sort(requestList->requests, 0, requestList->count - 1, criteria, order);
}

/*
 * ------------------------
 * Ordine di Ordinamento
 * ------------------------
 */

bool sorting_order_control(bool result, int order)
{
    if (order == CRESCENT_SORTING)
    {
        return result;
    }
    else if (order == DESCENT_SORTING)
    {
        return !result;
    }
    return false;
}

/*
 * ------------------------
 * Criteri di Ordinamento
 * ------------------------
 */

bool sort_by_client_name(Request *req1, Request *req2, int order)
{
    if (req1 == NULL || req2 == NULL)
        return false;

    const char *req1_client_name = get_client_name(get_request_client(req1));
    const char *req2_client_name = get_client_name(get_request_client(req2));

    if (req1_client_name == NULL || req2_client_name == NULL)
        return false;

    // strcmp ritorna int <= se la prima stringa viene prima della seconda
    if ((strcmp(req1_client_name, req2_client_name) <= 0))
    {
        // req1 viene prima di req2
        return sorting_order_control(true, order);
    } else
    {
        // req2 viene prima di req1
        return sorting_order_control(false, order);
    }
}

bool sort_by_estimated_cost(Request *req1, Request *req2, int order)
{
    if (req1 == NULL || req2 == NULL)
        return false;

    const double req1_estimated_cost = get_request_estimated_cost(req1);
    const double req2_estimated_cost = get_request_estimated_cost(req2);

    if (req1_estimated_cost <= req2_estimated_cost)
    {
        return sorting_order_control(true, order);
    } else
    {
        return sorting_order_control(false, order);
    }
}

bool sort_by_priority(Request *req1, Request *req2, int order)
{
    if (req1 == NULL || req2 == NULL)
        return false;

    const Priority req1_priority = get_request_priority(req1);
    const Priority req2_priority = get_request_priority(req2);

    if (req1_priority <= req2_priority)
    {
        return sorting_order_control(true, order);
    } else
    {
        return sorting_order_control(false, order);
    }
}