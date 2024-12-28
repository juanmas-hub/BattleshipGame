#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cmath>
#include "structs.hpp"
#include "validations.hpp"
using namespace std;



// Linked List manegment 

template <typename T>
Nodo<T>* addLast(Nodo<T>*& list, T &newData) {
    Nodo<T>* nuevo = new Nodo<T>;
    nuevo->sig = nullptr;
    nuevo->dato = newData;

    if (list == nullptr) {
        list = nuevo;
        return nuevo;
    } else {
        Nodo<T>* aux = list;
        while (aux->sig != nullptr) {
            aux = aux->sig;
        }
        aux->sig = nuevo;
        return nuevo;
    }
    
}

ostream& operator<<(ostream& os, Ship s) {
    os << "Name: " << s.name << endl;
    os << "Pos: " << s.pos << endl;
    os << "Size: " << s.size << endl;
}

template <typename T>
void clear(Nodo<T>*& list) {
    while (list != nullptr) {
        Nodo<T>* aux = list;
        list = list->sig;
        delete aux;
    }
}

template <typename T>
void printList(Nodo<T>* list) {
    Nodo<T>* aux = list;
    while (aux != nullptr) {
        cout << aux->dato << " -> ";
        aux = aux->sig;
    }
    cout << "nullptr" << endl;
}


// Load
Nodo<Ship>* askSetUp(Nodo<Ship>* &shipList, string shipNames[], int shipSizes[]) {
    string input; // 4+1 because of: '\0'

    for (int i = 0; i < 4; i++) {
        cout << "Introduce the " << shipNames[i] << " position: ";
        cin >> input;

        // Validar longitud de la entrada
        if (lengthCheck(input, 4)) {
            cout << "Invalid input length. Please enter exactly 4 characters." << endl;
            i = i - 1;
            continue;
        }

        // Validar formato: letra-número-letra-número
        if (formatCheck(input, 4)) {
            cout << "Invalid format. Use letter-number-letter-number." << endl;
            i--;
            continue;
        }

        if (!expresionCheck(input)) {
            cout << "Select the tail and then the front." << endl;
            i--;
            continue;
        }

        if (sizeCheck(input, shipSizes[i])) {
            cout << "The " << shipNames[i] << " doesn't fit because of its size/position." << endl;
            i--;
            continue;
        }

        if (intersectionCheck(shipList, input)) {
            cout << "The " << shipNames[i] << " intersects another ship." << endl;
            i--;
            continue;
        }

        // Agregar a la lista
        Ship actualShip = {input, shipNames[i], shipSizes[i]};
        addLast(shipList, actualShip);
        
        
    }
    return shipList;
}

Nodo<Attack>* askAttackPos(Nodo<Attack>* &attackList, char name){
    bool ok = true;
    string input; // 2+1 because of: '\0'
    Attack attack;
    Nodo<Attack>* aux;

    while(ok) {
        cout << "Player " << name << ", where do u wanna shot?: "; cin >> input;

        if ( lengthCheck(input, 2) || formatCheck(input, 2) || repeatedAttackPos(attackList, input) ) {
            cout << "Please, enter a valid position" << endl;

        } else {
            
            attack.pos = input;
            aux = addLast(attackList, attack);
            ok = false;
        }
    }
    return aux;
}

void fillTable(char (&table)[10][10],int rows, int columns){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            table[i][j] = '~';
        }
    }
}

void addShips(char (&table)[10][10], Nodo<Ship>* ships){
    Nodo<Ship>* aux = ships;
    
    while(aux != nullptr){
        string pos = (aux->dato).pos;
        int x1 = pos[0] - 'A';
        int y1 = pos[1] - '0';
        int x2 = pos[2] - 'A';
        int y2 = pos[3] - '0';

        // Asegurar que x1, y1 son siempre los menores
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);

        switch( x1 - x2 ){
            // x1 == x2 (Horizontal)
            case 0:
                for(int i = y1; i <= y2; i++){
                    table[i][x1] = 'S';
                }
                break;
            
            // y1 == y2 (Vertical)
            default:
                for(int i = x1; i <= x2; i++){
                    table[y1][i] = 'S';
                }
                break;
        }
        
        aux = aux->sig;
    }
}



void addShot(char (&table)[10][10], string pos, char shot){
    table[pos[1] - '0'][pos[0] - 'A'] = shot;
}