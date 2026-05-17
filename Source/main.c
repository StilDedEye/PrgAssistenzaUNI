
#include "Entities/RequestList/requestList.h"
#include "Interface/MenuManager/menuManager.h"

RequestList data();

int main(void)
{
    // TODO Lettura da file
    RequestList requestList = data();

    init_menu(&requestList);

}

// TEMP FUNCTION
RequestList data()
{
    struct tm testDate = {0};
    testDate.tm_year = 2026 - 1900;
    testDate.tm_mon = 4;
    testDate.tm_mday = 16;
    testDate.tm_hour = 10;
    testDate.tm_min = 30;
    testDate.tm_sec = 0;

    Client *testClients[] = {
        create_client("CL-1", "Mario Rossi"),
        create_client("CL-2", "Maria Bianchi"),
        create_client("CL-3", "Giovanni Blu"),
        create_client("CL-4", "Laura Gialli"),
    };

    Request *testRequests[] = {
        create_request("RQ-1", testClients[0], SMARTPHONE, HIGH, "Display cracked", VAL_UNDEFINED, VAL_UNDEFINED, testDate),
        create_request("RQ-2", testClients[1], LAPTOP, MEDIUM, "Battery drains quickly", 18544.24, 85.4, testDate),
        create_request("RQ-3", testClients[2], TABLET, LOW, "Slow performance", 50.0, -1.0, testDate),
        create_request("RQ-4", testClients[3], PRINTER, HIGH, "Won't boot", 150.0, VAL_UNDEFINED, testDate),
        NULL
    };

    RequestList requestList;
    init_request_list(&requestList);

    add_request(&requestList, testRequests[0]);
    add_request(&requestList, testRequests[1]);
    add_request(&requestList, testRequests[2]);
    add_request(&requestList, testRequests[3]);
    return requestList;
}