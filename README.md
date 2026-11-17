# Tetris in C++ mit SFML 3

Ein komplettes Tetris in C++ mit SFML 3. Ich habe es als Lernprojekt für **objektorientierte Programmierung (OOP)** gemacht, während meiner Umschulung zum Fachinformatiker für Anwendungsentwicklung.

Das Ziel war nicht nur, dass das Spiel funktioniert. Ich wollte den Code **gut organisieren**: Aufgaben auf Klassen verteilen, Kapselung nutzen und `main.cpp` fast leer halten.

## Funktionen

- Alle 7 klassischen Steine, mit Drehung und *Wall Kicks*
- Schnelles Fallen (Pfeil unten) und sofortiges Fallen (Leertaste)
- Vorschau auf den nächsten Stein
- Punktestand und Highscore, der in einer Datei gespeichert wird
- Game-Over-Animation (das Spielfeld füllt sich und leert sich Zeile für Zeile)
- Musik und Soundeffekte

**Steuerung:** ← → bewegen · ↑ drehen · ↓ schneller fallen · Leertaste sofort fallen

## Architektur

| Klasse | Aufgabe |
|---|---|
| `Game` | Steuert alles: Hauptschleife, Eingabe, Update, Zeichnen und Spielende |
| `Board` | Logik des Spielfelds: Steine bewegen, drehen und festsetzen, Linien erkennen, Game-Over-Animation |
| `Parts` | Definiert die Matrizen der 7 Steine |
| `UI` | Texte auf dem Bildschirm: Punkte, Highscore, Next, Game Over, New Score |
| `Sounds` | Musik und Soundeffekte |

`main.cpp` erstellt nur ein `Game` und ruft `Run()` auf.

## Verwendete OOP-Konzepte

- **Kapselung:** Attribute sind `private`, die öffentliche Schnittstelle ist klein. `Game` zeigt nur `Game()` und `Run()`.
- **Komposition:** `Game` *hat* ein `Board`, eine `UI` und `Sounds`. Jede Klasse macht nur ihre eigene Aufgabe.
- **Vererbung und Polymorphie:** `Board` und `UI` erben von `sf::Drawable` und überschreiben `draw()` (`virtual` / `override`). So kann man sie mit `window.draw(objekt)` zeichnen.
- **Konstruktoren und Initialisierungslisten**, die in SFML 3 für `Text` und `Sound` nötig sind.
- **Trennung in `.hpp` / `.cpp`** und Schutz gegen doppeltes Einbinden mit `#pragma once`.
- **Eine Aufgabe pro Klasse:** Die Game-Over-Animation liegt in `Board`. `Game` fragt nur, ob sie fertig ist.

## Struktur

```
main.cpp
Game.hpp / Game.cpp
Board.hpp / Board.cpp
Parts.hpp / Parts.cpp
UI.hpp / UI.cpp
Sounds.hpp / Sounds.cpp
Footage/        (Schrift, Musik, Sounds und maxScore.txt)
```

## Kompilieren

```
g++ main.cpp Board.cpp Parts.cpp UI.cpp Game.cpp Sounds.cpp -o tetris.exe -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```

SFML 3 muss installiert sein. Das Programm bitte im Projektordner starten, weil die Pfade zu `Footage/` relativ sind.

## Was ich gelernt habe (und was schwer war)

Ich habe mich auf **Klassen, Funktionen und Architektur** konzentriert: Welche Aufgabe gehört zu welcher Klasse, wie sprechen die Klassen miteinander, und wie bleibt der Code übersichtlich.

Am schwierigsten waren die **verschachtelten `for`-Schleifen**, die das Spielfeld und die Matrizen der Steine durchlaufen (bewegen, drehen, Kollisionen prüfen, festsetzen). 
Ich habe sie umgesetzt und verstehe die Logik. Aber ich kann sie noch nicht allein von Grund auf neu schreiben. Das ist mein Punkt zum Üben.








<img width="716" height="637" alt="image" src="https://github.com/user-attachments/assets/f6799c90-341b-4ec6-8b3f-6b2eaaa258f8" />
<img width="712" height="639" alt="image" src="https://github.com/user-attachments/assets/5c0873b9-2ade-4c04-a8ab-2038edcbf6a4" />
<img width="712" height="631" alt="image" src="https://github.com/user-attachments/assets/f856663a-5319-4ae7-84dd-f8d7b7b940a2" />











# Tetris en C++ con SFML 3

Tetris completo hecho en C++ con SFML 3, como proyecto de aprendizaje de **programación orientada a objetos** durante mi formación como Fachinformatiker (Anwendungsentwicklung).

El objetivo no fue solo que el juego funcione, sino **organizarlo bien**: separar responsabilidades en clases, usar encapsulación y mantener `main.cpp` casi vacío.

## Características

- Las 7 piezas clásicas, con rotación y *wall kicks*
- Caída rápida (flecha abajo) y caída instantánea (barra espaciadora)
- Vista previa de la siguiente pieza
- Puntuación y récord guardado en archivo
- Animación de Game Over (el tablero se llena y se vacía fila a fila)
- Música y efectos de sonido

**Controles:** ← → mover · ↑ rotar · ↓ bajar rápido · Espacio caída instantánea

## Arquitectura

| Clase | Responsabilidad |
|---|---|
| `Game` | Orquesta todo: bucle principal, entrada, actualización, dibujo y fin de partida |
| `Board` | Lógica del tablero: mover, rotar y fijar piezas, detectar líneas, animación de Game Over |
| `Parts` | Define las matrices de las 7 piezas |
| `UI` | Textos en pantalla: puntuación, récord, Next, Game Over, New Score |
| `Sounds` | Música y efectos de sonido |

`main.cpp` solo crea un `Game` y llama a `Run()`.

## Conceptos de POO aplicados

- **Encapsulación:** atributos `private`, interfaz `public` mínima. `Game` solo expone `Game()` y `Run()`.
- **Composición:** `Game` *tiene* un `Board`, una `UI` y unos `Sounds`. Cada clase se encarga de lo suyo.
- **Herencia y polimorfismo:** `Board` y `UI` heredan de `sf::Drawable` y sobrescriben `draw()` (`virtual` / `override`), así se dibujan con `window.draw(objeto)`.
- **Constructores y listas de inicialización**, necesarios en SFML 3 para `Text` y `Sound`.
- **Separación `.hpp` / `.cpp`** y protección contra doble inclusión con `#pragma once`.
- **Responsabilidad única:** la animación de Game Over vive en `Board`, y `Game` solo pregunta si terminó.

## Estructura

```
main.cpp
Game.hpp / Game.cpp
Board.hpp / Board.cpp
Parts.hpp / Parts.cpp
UI.hpp / UI.cpp
Sounds.hpp / Sounds.cpp
Footage/        (fuente, música, sonidos y maxScore.txt)
```

## Compilar

```
g++ main.cpp Board.cpp Parts.cpp UI.cpp Game.cpp Sounds.cpp -o tetris.exe -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```

Hace falta SFML 3 instalado. Ejecutar desde la carpeta del proyecto, porque las rutas a `Footage/` son relativas.

## Lo que aprendí (y lo que me costó)

Me centré en **clases, funciones y arquitectura**: decidir qué responsabilidad le toca a cada clase, cómo se comunican y cómo mantener el código ordenado.

La parte más difícil fueron los **bucles `for` anidados** que recorren el tablero y las matrices de las piezas (mover, rotar, comprobar colisiones, fijar). 
Los implementé y entiendo su lógica, pero todavía me cuesta mucho reproducirlos desde cero sin ayuda. Es mi punto a reforzar. Son un dolor de huevos.
