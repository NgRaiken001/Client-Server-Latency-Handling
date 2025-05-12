# ⏱️ Client-Server Latency Compensation in C++

A prototype implementation of **latency compensation techniques** for real-time multiplayer games, using custom C++ networking code. This system aims to reduce perceived lag and desynchronization in client-server communication using interpolation, client-side prediction, and lag compensation.

---

## 🎮 Why Latency Handling Matters

In fast-paced multiplayer games, **network delay (ping/lag)** can break player immersion. Techniques like **client-side prediction** and **server reconciliation** help smooth gameplay and improve responsiveness—even on unstable connections.

---

## 🧠 Features

- 🧮 **Client-Side Prediction**: Client simulates immediate input response before server confirmation.
- 🔁 **Server Reconciliation**: Client rewinds and re-applies missed inputs after receiving server state.
- 🔧 **Lag Compensation**: Server uses historical player states to resolve hits fairly despite latency.
- 🔄 **Interpolation**: Smooths remote player positions based on known delay.
- 🔌 Built using raw **C++ socket programming**.

---

## 🛠️ Tech Stack

- **C++17**
- **TCP/UDP Sockets** (POSIX or Winsock)
- Custom serialization of state data
- Time-stamping & input buffering

---

## 📁 Project Structure

```plaintext
/LatencyHandling/
│
├── Server.cpp          # Manages authoritative state & lag compensation
├── Client.cpp          # Handles prediction and input buffering
├── InputBuffer.hpp     # Stores client-side input history
├── StateSnapshot.hpp   # Maintains historical server states
├── TimeUtils.hpp       # Timestamping and latency simulation
