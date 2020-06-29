# INN 2 Gamebuino

## 1 Projekt Setup

### 1.1 Projekt compilieren & auf Gamebuino Meta uploaden

#### Arduino IDE

Eine Möglichkeit das Projekt im passenden Format zu erstellen, besteht darin, es in der Arduino IDE zu öffnen und unter **Sketch -> Upload** (Ctrl + U) auszuwählen.
Hierfür muss  
- unter Tools -> Boardmanager der Gamebuino Meta hinzugefügt und ausgewählt sein
- der Gamebuino am ausgewählten Port angeschlossen werden
 
Man kann das Projekt auch manuell auf den Gamebuino laden, indem man erst unter **Sketch -> Export Compiled Binary** (Ctrl + Alt + S) auswählt.
Das erstelle .bin file muss dann in einen Ordner mit gleichem Namen (case sensitive) verschoben werden. 
<br> Wird die Gamebuino Meta **SD Karte** verwendet, kann der folder einfach in d root der micro SD Karte verschoben werden.
Verwendet man eine andere, muss man darauf achten, dass die SD Karte FAT oder FAT32 formattiert ist. Außerdem muss die loader.bin von Gamebuino ebenfalls im Root liegen. 
(Verfügbar unter: https://github.com/Rodot/Games-META/tree/master/binaries )

### 1.2 Projekt via Emulator ausführen

Auch für den Gamebuino Meta Emulator wird ein .bin file benötigt (Erstellung siehe Punkt 1.1). Dieses findet sich auch im root dieses Repos.
Der Emulator ist unter https://gamebuino.com/creations/meta-emulator zu finden.
Zur Ausführung muss schlicht das .bin file unter dem Punkt *Upload Game* gedroppt werden.
Unter *Create your own keymapping* kann eine eigene Tastenbelegung ausgewählt werden.

## 2 Zielplattform

Das Spiel wurde für die Retro Konsole Gamebuino META entwickelt.
<br> https://gamebuino.com/gamebuino-meta
<br>
**Technische Details:**
- Microcontroller: ATSAMD21, 32bit ARM Cortex M0+, 256KB flash, 32KB RAM
- Display: 1.8" Diagonale, 80x64px RGB 16bit
- Battery: The 900mAh LiPo (etwa 16h Laufzeit)
- Light effects: 8 RGB LEDS
- Sound: Speaker (Klasse D audio amp, mit 10bit DAC)

## 3 Das Projekt

### Facts

**Rahmen**: Entwickelt im Rahmen der Lehrveranstaltung *Innovation Lab 2* des vierten Semesters Informatik auf der FH Technikum Wien.
<br>**Sprache**: C++
<br>
### 3.1 Kurzbeschreibung
Bei dem umgesetzten Spiel handelt es sich um einen Top-Down 2D Pixel Spiel im Stealth Genre.
<br> 
#### Story
Der spielbare Charakter ist ein Hacker, dessen Ziel es ist nach getaner Arbeit unbemerkt aus einem Bürokomplex zu entkommen.
Das Leveldesign verlangt vom Spieler ein taktisches Vorgehen. Er muss an Wachen vorbeischleichen, sie ablenken oder betäuben 
um an Schlüssel oder Rechner zu kommen, die seinen Weg freimachen. 
#### Gameplay
- Das **Ziel** jedes Levelbereichs ist an den Computer zu gelangen um den Ausgang (grüne Tür) zu entsperren und dann durch diesen zu entkommen.
- Wird man dabei vom Gegner erwischt, ist der Versuch gescheitert und das Level startet neu
- ausgerüstete Schlüssel entsperren rote Türen
- Interaktion mit dem Computer entsperrt grüne Ausgangstüren
- Bottles können auf den Gegner geworfen werden; wird er getroffen ist er einige Sekunden gestunned & kann sich nicht mehr bewegen.
- Traps (Geräuschfallen) können am Spielfeld platziert werden. Der Gegner geht dann den Geräuschen nach und kann so an einen beliebigen Platz auf der Map gelockt werden.
Doch Vorsicht ist geboten: Sieht er unterwegs den Spieler, wird er sofort die Verfolgung aufnehmen.

#### Steuerung

**Steuerkreuz:** movement<br>
**B:** Item umrüsten (Inventar)<br>
**A:** Aktion ausführen (ausgerüstetes Item verwenden, mit Computer interagieren)

