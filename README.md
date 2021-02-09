# PacMan_v1.0

<p align="center">
  <img src="https://user-images.githubusercontent.com/49727204/107409434-744e4c00-6b0c-11eb-8846-99dcf3d2e388.gif">
</p>

## PL

### O grze

Gra polega na zebraniu jak największej ilości punktów rozmieszczonych w labiryncie. Graczowi przeszkadzają duchy które za nim podążają. W przypadku natknięcia na ducha graczowi odejmowane są życia. Na starcie gry gracz ma 3 życia. 

### O projekcie

Celem projektu było odtworzenie tytułowej gry PacMan wraz z dodaniem dodatkowej możliwości grania wieloosobowego z wykorzystaniem protokołu TCP. Implementacja algorytm znajdowania drogi A*(A star) w celu wyznaczania trasy duchów do gracza. Projekt został wykonany w oparciu o framework Qt. 

### Instrukcja 

Po uruchomieniu aplikacji użytkownikowi wyświetla się menu z następującymi opcjami:

Single Player - rozpoczęcie gry jednoosobowej

Multi Player - wybór gry wieloosobowej. Po kliknięciu tej opcji ukaże się menu w którym są następujące opcje: Host Game oraz Join Game

Host Game - Opcja pozwalająca na zostanie Hostem gry. W tym trybie można oczekiwać na połączenie się innych graczy którzy wybrali opcję Join Game.

Join Game  - Opcja pozwalająca na podłączenie się do gry stworzonej przez Hosta.
Po wybraniu tej opcji należy podać IP hosta a następnie wybrać opcje connect oraz tryb w jakim chce się uczestniczyć w grze.

Sound - opcja pozwalająca na włączenie/wyłączenie dźwięków gry

Quit - wyłączenie aplikacji

Przyciski:
W - ruch w górę
A - ruch w lewo
S - ruch w dół
D - ruch w prawo

## ENG

### About game

PacMan is a game in which the main objective is to collect points in the maze. The player is disrupted by ghosts who are pursuing him. If any of the ghosts catch him, the player loses a life. At the start, the player has three lives.  

### About project

The main aim of the project was to remake the cult game Pacman with an additional option of the multiplayer mode using the TCP protocol. Implementation pathfinding algorithm A* (A star) which is used to set route from ghost to player. The project was made on the Qt framework.

### Manual

After launching the app you will see the main menu with options listed below.

Single Player - start the single-player game  

Multi Player - After choosing this option player will have to choose if he would like to become a host or to join a host.  

Host Game - This option allows you to create a multiplayer game and connect other players to you.  

Join Game - This option allows you to connect to a game created by a host. The player will have to pass the host IP and confirm it by pressing connect button. After connecting he will have to decide in which mode he will take part during the game - as a spectator or a player.

Sound - turn on/off sound

Quit - exit app

Buttons:
W - move up
A - move left
S - move down
D - move rigth

