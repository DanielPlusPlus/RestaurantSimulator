# Restaurant Simulator / Symulator Restauracji

## EN

### Overview
Restaurant Simulator is a 2D restaurant simulator. The user selects parameters such as the number of chefs, the number of waiters, the number of tables, and sets the simulation time. The simulation is then run using probability distributions appropriate to the nature of the events. After it ends, the calculated statistics are displayed and also saved to a file.

### Screenshots
![Main menu](screenshots/menu_screen.png)
![Simulation](screenshots/simulation_screen.png)
![Summary](screenshots/summary_screen.png)

### Technologies
- C++
- SFML 2.6.2
- CMake

### How to Run
1. Configure the project with CMake.
2. Build the `RestaurantSimulator` target.
3. Run the executable from the build directory.

Example (Windows, PowerShell):
```powershell
cmake -S . -B build
cmake --build build --config Release
./build/RestaurantSimulator.exe
```

### Project Structure
```
.
├── assets/              # graphics and fonts
├── include/             # class/struct headers
├── src/                 # implementations
├── external/            # dependencies (SFML)
├── build/               # CMake build output
├── screenshots/         # screenshots
└── README.md            # this file
```

## PL

### Opis
Restaurant Simulator to dwuwymiarowy symulator restauracji. Użytkownik wybiera parametry takie jak: liczba kucharzy, liczba kelnerów, liczba stołów oraz ustala czas symulacji. Następnie uruchamiana jest ona uruchamiana z użyciem rozkładów prawdopodobieństwa, zgodnymi z charakterem zdarzeń. Po jej zakończeniu wyświetlone zostają wyliczone statystyki, a także zostają one zapisane do pliku.

### Screeny
![Menu glowne](screenshots/menu_screen.png)
![Symulacja](screenshots/simulation_screen.png)
![Podsumowanie](screenshots/summary_screen.png)

### Technologie
- C++
- SFML 2.6.2
- CMake

### Uruchomienie
1. Skonfiguruj projekt przez CMake.
2. Zbuduj target `RestaurantSimulator`.
3. Uruchom plik wykonywalny z katalogu build.

Przyklad (Windows, PowerShell):
```powershell
cmake -S . -B build
cmake --build build --config Release
./build/RestaurantSimulator.exe
```

### Struktura projektu
```
.
├── assets/              # zasoby graficzne i fonty
├── include/             # naglowki klas i struktur
├── src/                 # implementacje
├── external/            # zaleznosci (SFML)
├── build/               # katalog generowany przez CMake
├── screenshots/         # zrzuty ekranu
└── README.md            # ten plik
```

---