#include <iostream>
#include <cmath>
#include "show.hpp"
#include "load.hpp"
#include "validations.hpp"

using namespace std;




int main(){
    Player playerA;
    Player playerB;
    playerA.name = 'A';
    playerB.name = 'B';
    Player players[2] = { playerA, playerB };

    
    for(int i = 0; i < 2; i++){
        

        fillTable(players[i].tableInf, rows, columns);
        fillTable(players[i].tableSup, rows, columns);

        // Data upload
        cout << "Player " << players[i].name << endl;

        players[i].ships = askSetUp(players[i].ships, shipNames, shipSizes);
        addShips(players[i].tableInf, players[i].ships);

 
        showPlayerTables(players[i]);
    }

    
    // Gameloop
    bool gameover = false;
    
        int current = 0;
        int opponent = 1;

    while(!gameover){
        
        

        Nodo<Attack>* attackptr = askAttackPos( players[current].attacks, players[current].name );

        
        bool hit = attackCheck( attackptr, players[opponent].ships );

        

        if( hit ){
            
            cout << "Nice shot! " << endl;
            
            ( attackptr->dato ).hit = true;
            addShot( players[current].tableSup, ( attackptr->dato ).pos, impact );
            showPlayerTables(players[opponent]);


            // stats
            players[current].attackCount++;
            players[current].impactsCount++;
            players[opponent].shipsSizesCount--;

            if(players[opponent].shipsSizesCount == 0){
                gameover = true;
                cout << "The player " << players[current].name << " wins!!!";
                showPlayerTables(players[current]);
                showPlayerTables(players[opponent]);
            }

        } else {

            cout << "It was close!" << endl;
            

            ( attackptr->dato ).hit = false;
            addShot( players[current].tableSup, ( attackptr->dato ).pos, fail );
            showPlayerTables(players[opponent]);

            // stats
            players[current].attackCount++;
            players[current].failsCount++;
        }
        

        if(current == 0) {
            current = 1;
            opponent = 0;
        } 
        else {
            current = 0;
            opponent = 1;
        }
    }
    
    
    return 0;
}