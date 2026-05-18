cmake_minimum_required(VERSION 4.2)
project(PrgAssistenzaUNI C)

set(CMAKE_C_STANDARD 11)

add_executable(PrgAssistenzaUNI Source/main.c
        ExternalLibraries/fort/fort.c
        ExternalLibraries/fort/fort.h
        Source/Entities/Client/client.c
        Source/Entities/Client/client.h
        Source/Entities/Request/request.c
        Source/Entities/Request/request.h
        Source/FileManger/Reader/fileReader.c
        Source/FileManger/Reader/fileReader.h
        Source/FileManger/Writer/fileWriter.c
        Source/FileManger/Writer/fileWriter.h
        Source/Constants/constants.h
        Source/RequestHandlers/RequestOrganizer/requestOrganizer.h
        Source/RequestHandlers/RequestFilter/requestFilter.c
        Source/RequestHandlers/RequestFilter/requestFilter.h
        Source/RequestHandlers/RequestStats/requestStats.c
        Source/RequestHandlers/RequestStats/requestStats.h
        Source/Interface/interfaceConstants.h
        Source/RequestHandlers/RequestOrganizer/requestOrganizer.c
        Source/Interface/InterfaceBuilder/InterfaceBuilder.c
        Source/Interface/InterfaceBuilder/InterfaceBuilder.h
        Source/Interface/MenuManager/menuManager.c
        Source/Interface/MenuManager/menuManager.h
        Source/Entities/RequestList/requestList.c
        Source/Entities/RequestList/requestList.h
        Source/Utilities/util.c
        Source/Utilities/util.h
)

# Stilded PROGRAMMA DI TEST PER L'INTERFACCIA
add_executable(TestSteeldead
        _Testing/steeldead/stildedTest.c
        ExternalLibraries/fort/fort.c
        ExternalLibraries/fort/fort.h
        Source/Interface/interfaceConstants.h
        Source/Interface/InterfaceBuilder/InterfaceBuilder.c
        Source/Interface/InterfaceBuilder/InterfaceBuilder.h
        Source/Interface/MenuManager/menuManager.c
        Source/Interface/MenuManager/menuManager.h
        Source/Entities/Client/client.c
        Source/Entities/Client/client.h
        Source/Entities/Request/request.c
        Source/Entities/Request/request.h
        Source/Constants/constants.h
        Source/Entities/RequestList/requestList.c
        Source/Entities/RequestList/requestList.h
        Source/Utilities/util.c
        Source/Utilities/util.h
        Source/RequestHandlers/RequestOrganizer/requestOrganizer.h
        Source/RequestHandlers/RequestOrganizer/requestOrganizer.c)


# Maxti PROGRAMMA DI TEST PER xxxxxxxx
add_executable(TestMaxti
        _Testing/maxti/maxtiTest.c
        ExternalLibraries/fort/fort.c
        ExternalLibraries/fort/fort.h
        Source/Interface/interfaceConstants.h
        Source/Interface/InterfaceBuilder/InterfaceBuilder.c
        Source/Interface/InterfaceBuilder/InterfaceBuilder.h
        Source/Interface/MenuManager/menuManager.c
        Source/Interface/MenuManager/menuManager.h
        Source/Entities/Client/client.c
        Source/Entities/Client/client.h
        Source/Entities/Request/request.c
        Source/Entities/Request/request.h
        Source/Constants/constants.h
        Source/Entities/RequestList/requestList.c
        Source/Entities/RequestList/requestList.h
        Source/Utilities/util.c
        Source/Utilities/util.h
        Source/RequestHandlers/RequestOrganizer/requestOrganizer.h
        Source/RequestHandlers/RequestOrganizer/requestOrganizer.c
        Source/RequestHandlers/RequestFilter/requestFilter.c
        Source/RequestHandlers/RequestFilter/requestFilter.h
        Source/RequestHandlers/RequestStats/requestStats.c
        Source/RequestHandlers/RequestStats/requestStats.h
)
