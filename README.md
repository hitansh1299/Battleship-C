# **Battleships in C** 
Implementation of the two player game battleships using C over TCP/IP

## Table of Contents

- [How to Play](#how-to-play)
- [TCP/IP Communication](#tcpip-communication)
- [Installation](#installation)
- [Project Structure](#project-structure)
- [License](#license)

## How to Play

### Overview

Battleships in C is a two-player game where each player tries to sink the opponent's fleet by guessing the coordinates of their ships. Players place ships on a grid, and during their turn, they input coordinates to fire at their opponent's grid.

### Game Setup

1. **Grid**: The game grid is typically 10x10.
2. **Ships**: Each player has a fleet of ships (Aircraft Carrier, Battleship, Cruiser, Submarine, and Destroyer). Ships are placed on the grid either horizontally or vertically.
3. **Objective**: The objective is to sink all the opponent’s ships before they sink yours.

### Gameplay

- Players take turns to guess the coordinates of the opponent’s ships.
- The game marks each hit and miss, and provides real-time updates of both players' boards.
- A hit is made if the guessed coordinates match the location of any part of the opponent's ship.
- A ship is sunk when all of its parts are hit.

### Commands

- **Placing Ships**: Players choose ship positions by entering grid coordinates.
- **Firing at Opponent**: Enter the coordinates (e.g., `B3`) to fire a shot at the opponent’s grid.

### Endgame

The game continues until one player sinks all the opponent’s ships. The player who sinks all ships first is declared the winner.

## TCP/IP Communication

Battleship-C utilizes TCP/IP communication to allow two players to play the game over a network. This is achieved using sockets to send and receive data between a server and a client.

### How It Works

1. **Server Setup**: One player acts as the server and waits for a connection from the other player.
   - The server listens on a specific port and accepts incoming client connections.
   - The game is set up by calling the `server.c` module, which establishes the connection.

2. **Client Connection**: The other player acts as a client and connects to the server.
   - The client connects to the server using the server’s IP address and port.

3. **Data Transmission**:
   - **Turn-based communication**: On each player's turn, data such as shot coordinates, hit/miss results, and board updates are sent from one player to the other.
   - **Synchronous gameplay**: Both players’ game states are synchronized by exchanging messages over TCP/IP, ensuring that both boards are updated correctly after each turn.
   - The `server.c` and `client.c` files handle all the communication logic using Windows sockets.

4. **Socket Communication**:
   - The server binds to a specific port and waits for client connections using the `accept()` function.
   - Once connected, both the client and server send and receive data using `send()` and `recv()` functions.
   - The game continues with back-and-forth communication between the two players.

### Networking Flow

- **Server**: 
  - Starts first and waits for the client to connect.
  - Manages communication once connected and ensures that the turns are synchronized.

- **Client**: 
  - Connects to the server using its IP address and port.
  - Sends coordinates for its guesses and receives feedback from the server about hits or misses.

By using TCP/IP, Battleship-C allows for remote multiplayer gameplay, demonstrating practical implementation of socket programming and network communication in a C-based game.

## Installation

Follow these steps to compile and run Battleship-C:

1. **Clone the repository**:
   ```bash
   git clone https://github.com/hitansh1299/Battleship-C.git
   cd Battleship-C
   ```

2. **Compile the game**:
   You can compile the game using `gcc` (ensure you have all required libraries installed).
   ```bash
   gcc -o battleship main.c game.c gameUtils.c menu.c server.c setup.c view.c -lws2_32
   ```

3. **Run the server**:
   One player must run the server first:
   ```bash
   ./battleship --server
   ```

4. **Run the client**:
   The other player connects to the server:
   ```bash
   ./battleship --client <server_ip>
   ```

## Project Structure

- `main.c`: The entry point of the game, handles the main game loop.
- `game.c`: Contains the core game logic, including setup and player turns.
- `gameUtils.c`: Helper functions for managing the game board and ships.
- `menu.c`: Manages the game menu and user interaction.
- `server.c`: Implements the server-side socket communication.
- `setup.c`: Manages the initial setup phase, including ship placement.
- `view.c`: Handles the display of the game boards and results.

## License

This project is licensed under the MIT License. See the [LICENSE](./LICENSE) file for details.
