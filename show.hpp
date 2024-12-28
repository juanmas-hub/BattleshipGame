#pragma once
#include <iostream>
#include "structs.hpp"
using namespace std;



void showPlayerTables(Player player) {
    cout << endl;
    cout << "Inferior jugador " << player.name << "               " << "Superior jugador " << player.name << endl;
    for( int i = 0; i < rows; i++ ) {

        
        for( int j = 0; j < columns; j++ ) {   
            cout << player.tableInf[i][j] << " ";
        }

        cout << "             ";

        for( int j = 0; j < columns; j++ ) {   
            cout << player.tableSup[i][j] << " ";
        }
        
        cout << endl;
    }
}

/*void showAllTables(char ainf[10][10], char asup[10][10], char binf[10][10], char bsup[10][10]){
    cout << endl;
    cout << "Inferior A" << "               " << "Superior A" << "                     " << "Inferior B" << "               " << "Superior B" << endl;
    for(int i = 0; i < rows; i++){  // Recorre las filas
        for(int j = 0; j < columns; j++){   // Recorre las columnas del jugador a, tablero inferior
            cout << ainf[i][j] << " ";
        }
        cout << "     ";
        for(int j = 0; j < columns; j++){ // Recorre las columnas del jugador a, tablero superior
            cout << asup[i][j] << " ";
        }
        cout << "           ";
        for(int j = 0; j < columns; j++){ // Recorre las columnas del jugador b, tablero inferior
            cout << binf[i][j] << " ";
        }
        cout << "     ";
        for(int j = 0; j < columns; j++){ // Recorre las columnas del jugador b, tablero superior
            cout << bsup[i][j] << " ";
        }
        cout << endl;
    }
}*/