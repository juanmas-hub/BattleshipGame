#pragma once
#include <iostream>
#include "structs.hpp"


// Validations
bool lengthCheck(string input, int length) {
    return input.size() == length? false : true;
}

bool formatCheck(string input, int length) {
    for(int i = 0; i < length; i++) {
        switch (i % 2) {

        // Odd (0, 2) => A - J
        case 0:
            if(!isalpha(input[i])) return true;
            if(input[i] < 'A' || input[i] > 'J') return true;
            break;
        
        // Even (1, 3) => 0 - 9
        case 1:
            if(!isdigit(input[i])) return true;
            if(input[i] < '0' || input[i] > '9') return true;


        default:
            break;
        }
    }
    return false;
}

bool expresionCheck(string input){
   
    if (input[0] != input[2]) {
        return input[0] < input[2];
    }

    return input[1] < input[3];
}

bool sizeCheck(string input, int size) {
    int x1 = input[0] - 'A';
    int x2 = input[2] - 'A';
    int y1 = input[1] - '0';
    int y2 = input[3] - '0';

    if (x1 != x2 && y1 != y2) 
        return true;

    if (x1 == x2 && abs(y1 - y2) == size - 1)
        return false;

    if (y1 == y2 && abs(x1 - x2) == size - 1)
        return false;

    return true;
}

// Ship
bool intersectionCheck(Nodo<Ship>* shipList, string input) {
    int P1x = input[0] - 'A';
    int P2x = input[2] - 'A';
    int P1y = input[1] - '0';
    int P2y = input[3] - '0';
    Nodo<Ship>* aux = shipList;

    int P1P2[2] { P2x - P1x , P2y - P1y };

    while (aux != nullptr) {
        string shipPos = (aux->dato).pos;

        
        if (shipPos == input) {
            return true; // Ya existe un barco en la misma posición
        }

        int Q1x = shipPos[0] - 'A';
        int Q2x = shipPos[2] - 'A';
        int Q1y = shipPos[1] - '0';
        int Q2y = shipPos[3] - '0';

        int Q1Q2[2] { Q2x - Q1x, Q2y - Q1y };
        int P1Q1[2] { Q1x - P1x, Q1y - P1y };
        int P1Q2[2] { Q2x - P1x, Q2y - P1y };
        int Q1P1[2] { P1x - Q1x, P1y - Q1y };
        int Q1P2[2] { P2x - Q1x, P2y - Q1y };

        auto cross = [](int v1[2], int v2[2]) {
            return v1[0] * v2[1] - v1[1] * v2[0];
        };

        int cross1 = cross(P1P2, P1Q1);
        int cross2 = cross(P1P2, P1Q2);
        int cross3 = cross(Q1Q2, Q1P1);
        int cross4 = cross(Q1Q2, Q1P2);

        bool condition1 = (cross1 * cross2 < 0);
        bool condition2 = (cross3 * cross4 < 0);

        if (condition1 && condition2) {
            return true; // Hay una intersección
        }

        if (cross1 == 0 && cross2 == 0 && cross3 == 0 && cross4 == 0) {
            auto between = [](int a, int b, int c) {
                return min(a, b) <= c && c <= max(a, b);
            };
            if ((between(P1x, P2x, Q1x) && between(P1y, P2y, Q1y)) ||
                (between(P1x, P2x, Q2x) && between(P1y, P2y, Q2y)) ||
                (between(Q1x, Q2x, P1x) && between(Q1y, Q2y, P1y)) ||
                (between(Q1x, Q2x, P2x) && between(Q1y, Q2y, P2y))) {
                return true;
            }
        }

        aux = aux->sig;
    }

    return false;
}

// Attacks
bool repeatedAttackPos(Nodo<Attack>* attackPosList, string input){  // O(n) 
    Nodo<Attack>* aux = attackPosList;

    while( aux != nullptr) {
        if((aux->dato).pos == input) return true; // this position was already attacked
        aux = aux->sig;
    }
    return false; // this position has never been attacked
}

bool attackCheck(Nodo<Attack>* &currentAttack, Nodo<Ship>* opponentShips) {
    Nodo<Ship>* aux = opponentShips;

    int attackX = (currentAttack->dato).pos[0] - 'A'; // Columna del ataque
    int attackY = (currentAttack->dato).pos[1] - '0'; // Fila del ataque

    while (aux != nullptr) {
        Ship oppShip = aux->dato;
        int shipX1 = oppShip.pos[0] - 'A'; // Columna inicial de la nave
        int shipY1 = oppShip.pos[1] - '0'; // Fila inicial de la nave
        int shipX2 = oppShip.pos[2] - 'A'; // Columna final de la nave
        int shipY2 = oppShip.pos[3] - '0'; // Fila final de la nave

        if (shipY1 == shipY2) {
      
            if (attackY == shipY1 && attackX >= std::min(shipX1, shipX2) && attackX <= std::max(shipX1, shipX2)) {
                (currentAttack->dato).hitShipName = oppShip.name;
                return true; // Ataque exitoso
            }
        }

    
        if (shipX1 == shipX2) {
 
            if (attackX == shipX1 && attackY >= std::min(shipY1, shipY2) && attackY <= std::max(shipY1, shipY2)) {
                (currentAttack->dato).hitShipName = oppShip.name;
                return true; // Ataque exitoso
            }
        }

        aux = aux->sig;
    }

    (currentAttack->dato).hit = false;
    (currentAttack->dato).hitShipName = "It didn't hit";
    return false; // No impactó ninguna nave
}

