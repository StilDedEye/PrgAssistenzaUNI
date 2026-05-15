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
        Source/RequestHandlers/RequestFilter/requestOrganizer.h
        Source/RequestHandlers/RequestOrganizer/requestFilter.c
        Source/RequestHandlers/RequestOrganizer/requestFilter.h
        Source/RequestHandlers/RequestStats/requestStats.c
        Source/RequestHandlers/RequestStats/requestStats.h
        Source/Interface/InterfaceConstants.h
        Source/RequestHandlers/RequestFilter/requestOrganizer.c
        Source/Interface/InterfaceBuilder/InterfaceBuilder.c
        Source/Interface/InterfaceBuilder/InterfaceBuilder.h
        Source/Interface/MenuManager/menuManager.c
        Source/Interface/MenuManager/menuManager.h
)

# Stilded PROGRAMMA DI TEST PER L'INTERFACCIA
add_executable(TestSteeldead
        _Testing/steeldead/stildedTest.c
        ExternalLibraries/fort/fort.c
        ExternalLibraries/fort/fort.h
        Source/Interface/InterfaceConstants.h
        Source/Interface/InterfaceBuilder/InterfaceBuilder.c
        Source/Interface/InterfaceBuilder/InterfaceBuilder.h
        Source/Interface/MenuManager/menuManager.c
        Source/Interface/MenuManager/menuManager.h)

# PER ZAC: crea nella cartella _Testing/maxti un file chiamato {nomeFileTuoZac}.c
# SENZA COMMITTARLO E SENZA AGGIUNGERLO AL CMAKE
# e scrivici dentro i test che vuoi fare,
# poi aggiungi qui sotto questa riga cambiando {nomeFileTuoZac} con il nome del file che hai creato

# Poi crea nella cartella _Testing/steeldead un file chiamato stildedTest.c
# SENZA COMMITTARLO E SENZA AGGIUNGERLO AL CMAKE e basta, dovrebbe andare.

# Poi cancella questi commenti

# Ogni volta che ti serve una classe da mettere in test la aggiungi come percorso relativo qua sotto,
# tra le tonde

# Maxti PROGRAMMA DI TEST PER xxxxxxxx
add_executable(TestMaxti
        _Testing/maxti/{nomeFileTuoZac}.c
        ExternalLibraries/fort/fort.c
        ExternalLibraries/fort/fort.h)
