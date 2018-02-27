# Anium

Cross-platform (as in I want to die) training software for Counter-Strike: Global Offensive

This project uses a few parts from AimTux, Fuzion, Cathook, blue and Nekohook.
Shoutout to LWSS, nullifiedcat, F1ssi0n and Onee chan.

### Setup

Requirements:

* cmake
* C++17 compiler (MSVC, GCC, Clang)
* Shared library injector
* Dependencies for your operating system

To generate the project files:

* **Windows**: `cmake -G "Visual Studio 15" .`
* ***nix** `cmake .`

To build:

* **Windows**: Do it from within Visual Studio
* ***nix**: `make -j$(nproc)`

Injection can be done by either `LD_PRELOAD`ing Anium or
injecting it with your favorite shared library injector.
