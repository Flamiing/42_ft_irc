# 💬 ft_irc

An **IRC server** implemented in **C++98** as part of the **42 School** curriculum.
It handles multiple clients using `poll(2)`, parses IRC-style commands, manages channels, modes, and user states, and communicates using the standard IRC text protocol.

---

## 📘 Table of Contents

1. [Introduction](#-introduction)
2. [Project Overview](#-project-overview)
3. [How It Works](#-how-it-works)
4. [Architecture & Responsibilities](#-architecture--responsibilities)
5. [Command Handling](#-command-handling)
6. [Program Flow](#-program-flow)
7. [Error Handling & Limits](#-error-handling--limits)
8. [Compilation](#-compilation)
9. [Usage](#-usage)
10. [Project Structure](#-project-structure)
11. [Credits](#-credits)

---

## 🧠 Introduction

**ft_irc** is a small IRC server compatible with common IRC clients.

It focuses on:

* Socket programming and networking (IPv4, TCP, `poll`)
* Handling multiple clients and connections
* Parsing and routing IRC commands
* Managing users, channels, and modes
* Robust error handling and resource management

The final binary is called **`ircserv`**. 

---

## 📦 Project Overview

At a high level, the server:

* Listens on a given **TCP port** with a **password**
* Accepts multiple client connections (limited by `MAX_CLIENTS`) 
* Keeps track of:

  * Connected **clients** (`std::map<int, Client>`) 
  * Open **channels** (`std::vector<Channel>`) 
* Uses `poll(2)` to multiplex I/O over all sockets 
* Parses IRC-style messages into a `Command` object and dispatches them to the correct handler  

The server is configured at runtime via CLI arguments:

```text
./ircserv <port> <password>
```

If the arguments are invalid, usage is printed and the program exits. 

---

## ⚙️ How It Works

### 🧵 Entry Point

The `main` function:

1. Checks that exactly **two arguments** are passed (`<port> <password>`)
2. Validates the port using `parsePort`
3. Validates the password length (`<= 30`) 
4. Constructs a `Server` with the given port and password
5. Calls `server.runServer()` inside a try/catch block 

```cpp
if (argc != 3)
    return howToUse();

int         port;
std::string password(argv[2]);
std::string portStr(argv[1]);
if (!parsePort(portStr, port))
    return printError(BAD_PORT, NORMAL);
if (password.size() > 30)
    return printError(PASS_TOO_LONG, NORMAL);

Server server(port, password);
server.runServer();
```

---

### 🧱 Server Initialization

The `Server` class stores the main server state:

* Port and password 
* Listening socket and `sockaddr_in` address 
* Map of clients (`socket -> Client`) 
* Vector of `pollfd` structures (`_pollFds`) for multiplexing 
* Vector of channels (`channels`) 
* `mapCommand` → maps command strings (e.g. `"JOIN"`) to handler functions  

`runServer()`:

* Calls `_setupSever()` to:

  * Initialize `mapCommand`
  * Create the listening socket (AF_INET, SOCK_STREAM)
  * Set up the server address (INADDR_ANY, given port) 
* Sets `SO_REUSEADDR` on the socket
* Binds and listens with a backlog of `MAX_CLIENTS` 
* Logs that the server is listening and then calls `_handleClientConnections()` 

---

## 🧩 Architecture & Responsibilities

### 🧷 Server

Defined in `Server.hpp`, the `Server` class:

* Manages lifecycle:

  * `runServer()` to start the loop 
  * `closeAllSockets()` to gracefully shut down 
* Provides getters for:

  * Port, IP, password
  * Client and channel lookups (e.g. `getClientByNickname`, `getChannelByName`) 
* Channel management:

  * `addChannel`, `connectToChannel`, `disconnectClientFromChannels`, `kickFromChannel`, `partFromChannel` 
* Ban logic:

  * `isBanned(Client&, std::string& channel)` 
* Internal helpers (private):

  * `_handleClientConnections()`, `_handleClients()`
  * `_newClient()`, `_handleClientRequest()`
  * `_processMessage()` and `_processBuffer()` for message parsing 

---

### 👤 Client

`Client` encapsulates the state of each connected user:

* Socket descriptor `_socket`
* Nickname (`_nickname` / `_wrongNickname`), username, full name 
* Authentication flags:

  * `_passAuth`, `_userAuth`, `_nickAuth`, `_auth` 
* Operator status: `_isOperator` 
* Joined channels (`_joinedChannels`) 
* Away state and message (`isAway`, `awayMessage`) 
* Buffer for partial reads `buffer`

This allows the server to track a full IRC user state and enforce registration order (PASS → NICK → USER).

---

### #️⃣ Channel

`Channel` represents an IRC channel:

* Name, topic, key, user limit  
* Creation time (`creationTime`) set at construction using `getCurrentTime()` 
* Lists of:

  * Operators (`_operators`)
  * Users allowed to speak (`_canTalk`)
  * Online users (`_onlineUsers`)
  * Banned users (`_bannedUsers`) 
* Mode management:

  * Internal maps for modes, with and without parameters (`modes`, `modesWithParams`, `modesWithoutParams`) 

Specialized files like `ChannelModes.cpp`, `ChannelBan.cpp`, and mode handlers (`oMode.cpp`, `kMode.cpp`, `lMode.cpp`, `bMode.cpp`, etc.) implement IRC channel mode logic. 

---

## 🧾 Command Handling

### 🔁 Command Dispatch

Commands are encapsulated by the `Command` class:

* Holds pointers to `Server`, `Client`, and a reply buffer (`std::string *buffer`) 
* Stores:

  * Raw line (`raw`)
  * Raw command text (`rawCmd`)
  * Parsed command name (`cmd`)
  * Tokenized message vector (`message`) 

`Server::initMapCommand()` fills a map from command string to a function pointer: 

* `PASS`, `USER`, `NICK`
* Channel commands: `JOIN`, `INVITE`, `TOPIC`, `PART`, `LIST`, `NAMES`, `KICK`
* Messaging: `PRIVMSG`, `NOTICE`, `AWAY`
* Server control: `OPER`, `DIE`
* Others: `QUIT`, `MODE`

### 🧠 Processing Logic

`processCommand()` coordinates authentication and dispatch: 

* If the command is `PASS`, it always goes to `PASS` handler first
* `USER` and `NICK` require `passAuth == true` before being accepted 
* `PONG` is ignored (handled elsewhere or used just to keep connection alive) 
* Other commands go through `processGeneralCommands()` which:

  * Looks up the command in `mapCommand`
  * If the client is authenticated (`getAuth()`), invokes the handler
  * Otherwise, writes an appropriate `ERR_NOTREGISTERED` reply, or `ERR_UNKNOWNCOMMAND` if not mapped 

This ensures a proper **IRC registration sequence** and correct error codes.

---

## 🔄 Program Flow

High-level flow:

```text
1. Start server
   - Parse CLI args: <port> <password>
   - Validate input and initialize Server object

2. Setup listening socket
   - socket()
   - setsockopt(SO_REUSEADDR)
   - bind()
   - listen(MAX_CLIENTS)

3. Event loop (poll)
   - Accept new connections
   - Read from client sockets
   - Accumulate data in client buffers
   - Split into IRC messages and construct Command objects
   - Dispatch commands via processCommand()

4. Sending replies
   - Command handlers build reply strings into client buffers
   - Server writes replies using send() / write()

5. Shutdown
   - closeAllSockets()
   - Free resources and exit
```

`closeAllSockets()` iterates over `_pollFds`, logs disconnections, closes all client sockets and finally the listening socket. 

---

## 🚨 Error Handling & Limits

Some constraints and constants:

* `MAX_CLIENTS = 10` → control the maximum number of concurrent clients 
* `BUFFER_LIMIT = 512` for message buffering 

On errors during setup (socket, setsockopt, bind, listen), `runServer()` prints a descriptive error (via `printError`) and exits:   

Runtime errors:

* `printError` is used for validation issues like:

  * Invalid port (`BAD_PORT`)
  * Password too long (`PASS_TOO_LONG`) 
* Command-level errors result in appropriate IRC numeric replies:

  * `ERR_UNKNOWNCOMMAND`
  * `ERR_NOTREGISTERED` 

The main function also catches `std::exception` and prints it, exiting with code 1 on unhandled exceptions. 

---

## 🛠️ Compilation

The project is built via the **Makefile** in the root directory: 

* Target binary: **`ircserv`**
* Compiler: `c++` with flags:

  * `-Wall -Wextra -Werror -std=c++98 -g3 -fsanitize=address` 

Main rules: 

```sh
make        # builds ircserv
make clean  # removes object files (obj/)
make fclean # clean + remove ircserv
make re     # rebuild everything
```

There are also helper targets:

* `exe` → builds and runs `ircserv` with default `PORT=2042`, `PASS=pass`  
* `net` → opens `nc -c localhost 2042` (simple client) 
* `net1` → executes `user.sh` (scripted client) 

---

## ▶️ Usage

### Basic Run

```sh
./ircserv <port> <password>
```

Example:

```sh
./ircserv 6667 mysecretpass
```

or using the Makefile helper:

```sh
make exe      # runs with default ARG1=2042 ARG2=pass
```

You can then connect using any IRC client, e.g.:

```sh
irc localhost 6667
# or using netcat:
nc localhost 6667
```

*(Adjust to the actual port and password you use.)*

---

## 📁 Project Structure

Based on the Makefile source list and folders: 

```text
.
├── inc/
│   ├── Server.hpp
│   ├── Client.hpp
│   ├── Channel.hpp
│   ├── Command.hpp
│   ├── commands.hpp
│   ├── errors.hpp
│   ├── generalUtils.hpp
│   ├── colors.hpp
│   └── ...
├── src/
│   ├── main/
│   │   └── main.cpp
│   ├── server/
│   │   ├── Server.cpp
│   │   ├── ServerRun.cpp
│   │   ├── ServerClientConnections.cpp
│   │   ├── ServerProcessMessage.cpp
│   │   ├── ServerChannelConnection.cpp
│   │   ├── ServerChannelDisconnection.cpp
│   │   ├── ServerClientDisconnection.cpp
│   │   ├── ServerChannels.cpp
│   │   ├── ServerGeneral.cpp
│   │   └── ServerGetters.cpp
│   ├── client/
│   │   ├── Client.cpp
│   │   ├── ClientChannels.cpp
│   │   ├── ClientGetters.cpp
│   │   ├── ClientOperator.cpp
│   │   └── ClientSetter.cpp
│   ├── channel/
│   │   ├── Channel.cpp
│   │   ├── ChannelConnection.cpp
│   │   ├── ChannelDisconnection.cpp
│   │   ├── ChannelMethods.cpp
│   │   ├── ChannelGeneral.cpp
│   │   ├── ChannelGetters.cpp
│   │   ├── ChannelSetters.cpp
│   │   ├── ChannelModes.cpp
│   │   ├── ChannelBan.cpp
│   │   └── channelUtils.cpp
│   ├── command/
│   │   ├── Command.cpp (if present)
│   │   ├── processCommand.cpp
│   │   ├── passCommand.cpp
│   │   ├── userCommand.cpp
│   │   ├── nickCommand.cpp
│   │   ├── joinCommand.cpp
│   │   ├── partCommand.cpp
│   │   ├── quitCommand.cpp
│   │   ├── operCommand.cpp
│   │   ├── kickCommand.cpp
│   │   ├── privmsgCommand.cpp
│   │   ├── noticeCommand.cpp
│   │   ├── topicCommand.cpp
│   │   ├── inviteCommand.cpp
│   │   ├── listCommand.cpp
│   │   ├── namesCommand.cpp
│   │   ├── awayCommand.cpp
│   │   ├── modeCommand.cpp
│   │   ├── oMode.cpp, kMode.cpp, lMode.cpp, ...
│   │   └── dieCommand.cpp
│   ├── utils/
│   │   ├── parsePort.cpp
│   │   ├── printError.cpp
│   │   ├── splitString.cpp
│   │   ├── trimSpaces.cpp
│   │   ├── toUpperCase.cpp
│   │   ├── getMessage.cpp
│   │   ├── getCurrentTime.cpp
│   │   └── numberToString.cpp
│   └── ...
├── Makefile
└── README.md
```

---

## 👤 Credits

Project developed by **guilmira** and **Me** for **42 School**.

