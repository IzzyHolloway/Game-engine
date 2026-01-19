ReadMe.txt
CPROG Programmeringsprojekt

Gruppnummer: [03]
Gruppmedlemmar: [William de Try: 0411050677,  
Sadra YaghoobzadehTari: 0306026311, 
Isabelle Holloway 0208316349]

--------------------------------------------------

1. Bygginstruktion

Projektet byggs med hjälp av make och kräver SDL samt biblioteken
SDL_image och SDL_ttf.

Förutsättningar:
- C++-kompilator med stöd för C++23
- make
- SDL
- SDL_image
- SDL_ttf

Bygga projektet:
1. Öppna en terminal i projektets rotkatalog.
2. Kör kommandot:
   make
3. Det körbara programmet skapas i katalogen:
   build/debug/

Projektet är testat på Linux, MacOS och Windows.
--------------------------------------------------

2. Köra programmet

Starta programmet genom att köra det kompilerade programmet i katalogen
build/debug/.

Exempel:
./build/debug/play

--------------------------------------------------

3. Resurser

Alla resurser ligger i katalogen resources/.

Sökvägar till resurser hanteras via den globala konstanten gResPath i
filen Constants.h.

Exempel:
- Bilder: resources/images/
- Ljud: resources/sounds/
- Typsnitt: resources/fonts/

--------------------------------------------------

4. Spelinstruktioner

Spelet är ett tvådimensionellt arkadspel av typen Breakout.

Styrning:
- Vänster piltangent eller A: flytta paddeln åt vänster
- Höger piltangent eller D: flytta paddeln åt höger
- Mellanslag: starta bollen

Mål:
Målet är att slå sönder alla bricks/brickor med bollen utan att förlora alla
liv.






