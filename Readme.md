# 🎮 Quoridor Game - Client-Server Project

## 📌 About the Project  
This project is my **second-semester bachelor's assignment** for the **Programming** course at the **University of Tehran - Computer Science Department**.  
It is an implementation of the **Quoridor board game**, built using a **client-server architecture** in **C++**.

The project demonstrates basic concepts of network communication and game logic. It uses the lightweight and powerful `httplib.h` library to handle HTTP-based communication between the client and server.

---

## 🛠 Technologies Used
- **Language:** C++
- **Architecture:** Client–Server
- **Networking Library:** httplib.h

---

## 🚀 Features
- Basic game logic of the Quoridor board game  
- Client-server communication using HTTP  
- Modular code structure for easier understanding  
- Simple and clean implementation for educational purposes, with comments in the code to help better understanding

---

## 📦 How to Run

### 1. Clone the Repository

### 2. Run the Game Using Makefile

You can run the game in your terminal with the provided 'Makefile':
```bash
make
```

Here’s the content of the 'Makefile' used to compile the server and client:
```bash
main: server.cpp client.cpp
	g++ -std=c++11 -o server server.cpp -lpthread -I.
	g++ -std=c++11 -o client client.cpp -lpthread -I.
```

### 3. Start the Server

```bash
./server
```

### 4- Run the Client for each player

```bash
./client
```

---

## 🙋‍♂️ Author

**Ali Hoseini**  
Computer Science Student  
University of Tehran – Computer Science Department  

**Email:** [alihoseini2002@gmail.com]
**Project Term:** Second Semester  
**Course:** Programming
