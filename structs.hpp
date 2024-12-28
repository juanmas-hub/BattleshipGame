#include <iostream>
#pragma once
using namespace std;

// Datos
const int rows = 10;
const int columns = 10;
const int AC_SIZE = 5;  // Aircraft Carrier size
const int BS_SIZE = 4;  // Battleship size
const int SM_SIZE = 3;  // Submarine size
const int DT_SIZE = 2;  // Destroyer size
string shipNames[] = {"Aircraft Carrier(5)", "Battleship(4)", "Submarine(3)", "Destroyer(2)"};
int shipSizes[] = {AC_SIZE, BS_SIZE, SM_SIZE, DT_SIZE};
const char water = '~';
const char ship = 'S';
const char impact = 'X';
const char fail = 'O';


template<typename T> 
struct Nodo{
    Nodo<T>* sig = nullptr;
    T dato; 
};



struct Ship {
    string pos;
    string name;
    int size;
};

struct Attack {
    string pos;
    bool hit; 
    string hitShipName; // if hit = true

};

struct Player{
    char name;
    int shipsSizesCount = AC_SIZE + BS_SIZE + SM_SIZE + DT_SIZE;
    int attackCount = 0;
    int impactsCount = 0;
    int failsCount = 0;
    char tableInf[rows][columns];
    char tableSup[rows][columns];
    Nodo<Attack>* attacks = nullptr;
    Nodo<Ship>* ships = nullptr;
};