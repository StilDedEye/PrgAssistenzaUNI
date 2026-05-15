cmake_minimum_required(VERSION 4.2)
project(PrgAssistenzaUNI C)

set(CMAKE_C_STANDARD 11)

add_executable(PrgAssistenzaUNI Source/main.c
        test.c
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
        Source/RequestHandlers/RequestFilter/requestOrganizer.cpp
        Source/RequestHandlers/RequestFilter/requestOrganizer.h
        Source/RequestHandlers/RequestOrganizer/requestFilter.c
        Source/RequestHandlers/RequestOrganizer/requestFilter.h
        Source/RequestHandlers/RequestStats/requestStats.c
        Source/RequestHandlers/RequestStats/requestStats.h)
