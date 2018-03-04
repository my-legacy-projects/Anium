# Anium

Cross-platform (as in I want to die) training software for Counter-Strike: Global Offensive

This project uses a few parts from AimTux, Fuzion, Cathook, blue and Nekohook.
Shoutout to aixxe, LWSS, nullifiedcat, F1ssi0n and Onee chan.

### Setup

Requirements:

* cmake
* C++17 compiler (MSVC, GCC, Clang)
* Shared library injector
* Dependencies for your operating system

To generate the project files:

* **Windows**: `cmake -G "Visual Studio 15" .`
* **Mac OS**: `cmake -G Xcode .`
* **Linux** `cmake .`

To build:

* **Windows**: Do it from within Visual Studio
* **Mac OS**: Do it from within Xcode
* **Linux**: `make -j$(nproc)`

Injection can be done by either `LD_PRELOAD`ing Anium or
injecting it with your favorite shared library injector.

### Continuous Integration

Windows | Mac OS | Linux
------- | ------ | ---------
VSTS | Travis CI | Circle CI
![VSTS](https://anium.visualstudio.com/_apis/public/build/definitions/d5ed15f5-b95d-4b52-bf62-fd3265ddf7d4/1/badge) | ![TravisCI](https://travis-ci.com/Marc3842h/Anium.svg?token=N3JdkxuzfFsy9B38kufx&branch=master) | ![CircleCI](https://img.shields.io/circleci/token/7d783390d7d066504d7ed0be0432dbed58e34324/project/github/Marc3842h/Anium/master.svg)
