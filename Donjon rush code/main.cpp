#ifndef main_cpp
#define main_cpp

#include <iostream>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <sstream>
#include "gestion_fenetre.h"
#include "Personnages.h"
#include "Equipement.h"
#include "donjon.h"
#include "fonction_globale.h"

using namespace std;

class Personnages ;
class Moine ;
class Guerrier ;
class Sorciere ;
class Amazone ;


int main()
{
    srand(time(NULL)) ;
    modif_fenetre() ;
    int action_terrain = 0 ;
    int choix_perso ;
    int menu ;
    int page ;
    int input ;
    int choix_difficulter ;
    Piece *plateau_jeu[10][10] ;
    Personnages *perso_utiliser ;
    Personnages *perso_ia1 ;
    Personnages *perso_ia2 ;
    Personnages *perso_ia3 ;
    Personnages *pantin = new Personnages() ;

/// 1° partie : menu du début de jeu..........................................................................................................
    do
    {
        page = 0 ;
        spam_endl( 3 ) ;
        logo() ;
        spam_endl( 3 ) ;
        cout << spam_space( 78 ) << "DONJON RUSH" ;
        spam_endl( 4 ) ;
        cout << spam_space( 54 ) << "Nouvelle partie = 1   Continuer partie = 2   Tutoriel = 3" ;
        spam_endl( 34 ) ;
        menu = _getch() ;
        while ( menu != 49  &&  menu != 50  &&  menu != 51 )
        {
            menu = _getch() ;
        }
        switch ( menu )
            {
            case 50 :
                choix_perso = 49 ;
                choix_difficulter = 49 ;
                break ;
            case 51 :
                cout << endl ;
                do
                {
                    switch ( page )
                    {
                        case 0 :
                            cout << spam_space( 33 ) << "Le but du jeu est de trouver la salle du coffre qui fait gagner des objets et de l\'experience." << endl << endl ;
                            break ;
                        case 1 :
                            cout << spam_space( 46 ) << "Vous commencez dans la case dans l\'angle en haut a gauche du donjon." << endl ;
                            cout << endl << spam_space( 52 ) << "Pour vous deplacer utilisez les fleches du pave numerique." << endl ;
                            break ;
                        case 2 :
                            cout << endl << spam_space( 33 ) << "Quand vous entrer dans une piece vous pouvez voir les differents objets et personnage presents." << endl << endl ;
                            break ;
                        case 3 :
                            cout << spam_space( 39 ) << "Si un autre personnage est present dans la piece, vous etes oblige de l\'attaquer." << endl ;
                            cout << endl << spam_space( 39 ) << "Le combat se termine a la mort de un des deux combattants ou lors de votre fuite." << endl ;
                            cout << endl << spam_space( 39 ) << "Les degats qui vous sont infliges pendant les combats diminuent vos points de vie." ;
                            break ;
                        case 4 :
                            cout << "        Il vous est possible de ramasser des objets presents dans la piece pour les mettre dans votre sac dont la taille varie en fonction du personnages choisi." << endl ;
                            cout << endl << spam_space( 32 ) << "Vous pouvez aussi deposer des objets, les utiliser, ou poser dans la piece des objets de type pieges." << endl ;
                            cout << endl << spam_space( 49 ) << "Vous ne pouvez neanmoins placer que un seul piege par piece." ;
                            break ;
                        case 5 :
                            cout << spam_space( 36 ) << "Vous pouvez decider de terminer votre tour a n\'importe quel moment sauf lors d\'un combat." << endl << endl ;
                            break ;
                        case 6 :
                            cout << spam_space( 32 ) << "Vous etes maintenant pret pour commencer l\'aventure et trouver la salle du coffre, bonne chance !" << endl << endl ;
                            break ;
                        case 7 :
                            cout << spam_space( 74 ) << "______" << endl ;
                            cout << spam_space( 73 ) << "|112233|" << endl ;
                            cout << spam_space( 73 ) << "|112233|" << endl ;
                            cout << spam_space( 73 ) << "|445566|" << endl ;
                            cout << spam_space( 73 ) << "|445566|" << endl ;
                            cout << spam_space( 73 ) << "|      |" << endl ;
                            cout << spam_space( 73 ) << "|______|" ;
                            spam_endl( 4 ) ;
                            cout << spam_space( 32 ) << "les emplacements comprenants : les 1 representent les armes et les armures" << endl ;
                            cout << spam_space( 63 ) << "les 2 representent les accessoires" << endl ;
                            cout << spam_space( 63 ) << "les 3 representent les objets" << endl ;
                            cout << spam_space( 63 ) << "les 4 representent les parchemins, les poisons et les cles de teleportation" << endl ;
                            cout << spam_space( 63 ) << "les 5 representent la position de votre personnage" << endl ;
                            cout << spam_space( 63 ) << "les 6 representent les pieges" << endl ;
                            break ;
                        default :
                            break ;
                    }
                    spam_endl( 31 ) ;
                    if ( page == 0 )
                    {
                        spam_endl( 10 ) ;
                        cout << "Menu : 4" ;
                        cout << spam_space( 149 ) << "Suivant : 6" ;
                    }
                    else if ( page == 7 )
                    {
                        cout << "Precedent : 4" ;
                        cout << spam_space( 147 ) << "Menu : 6" ;
                    }
                    else
                    {
                        spam_endl( 10 ) ;
                        cout << "Precedent : 4" ;
                        cout << spam_space( 144 ) << "Suivant : 6" ;
                    }
                    cout << spam_space( 70 ) << "retour : espace" ;
                    input = _getch();
                    while ( input != 32 && input != 52 && input != 54 )
                    {
                        input = _getch() ;
                    }
                    if ( input == 54 )
                    {
                        page ++ ;
                    }
                    if ( input == 52 )
                    {
                        page -- ;
                    }
                    spam_endl( 13 ) ;
                }while ( input != 32 && page != -1 && page != 8 ) ;
                break ;
            case 49 :
                do
                {
                    cout << endl << spam_space( 18 ) << "Quel personnage choisissez vous ?" << endl ;
                    cout << endl << spam_space( 18 ) << "1 : Moine" << endl ;
                    cout << endl << spam_space( 18 ) << "2 : Guerrier" << endl ;
                    cout << endl << spam_space( 18 ) << "3 : Sorciere" << endl ;
                    cout << endl << spam_space( 18 ) << "4 : Amazone" << endl ;
                    spam_endl( 5 ) ;
                    cout << spam_space( 18 ) << "retour : espace" ;
                    spam_endl( 25 ) ;
                    choix_perso = _getch() ;
                    while ( choix_perso != 32 && choix_perso != 49 && choix_perso != 50 && choix_perso != 51 && choix_perso != 52 )
                    {
                        choix_perso = _getch() ;
                    }
                    if ( choix_perso != 32 )
                    {
                        spam_endl( 19 ) ;
                        cout << "                  Quel mode de jeu choisissez vous ?" << endl ;
                        cout << endl << "                  1 : vagabond" << endl ;
                        cout << endl << "                  2 : aventurier" << endl ;
                        cout << endl << "                  3 : chercheur de tresor confirmer" << endl ;
                        spam_endl( 5 ) ;
                        cout << spam_space( 18 ) << "retour : espace" ;
                        spam_endl( 25 ) ;
                        choix_difficulter = _getch() ;
                        while ( choix_difficulter != 32 && choix_difficulter != 49 && choix_difficulter != 50 && choix_difficulter != 51 )
                        {
                            choix_difficulter = _getch() ;
                        }
                    }
                }while ( choix_perso != 32 && choix_difficulter != 49 && choix_difficulter != 50 && choix_difficulter != 51 ) ;
                break ;
            }
    } while ( choix_difficulter != 49 && choix_difficulter != 50 && choix_difficulter != 51 && menu != 50 ) ;

/// 2° partie : création du jeu ..............................................................................................................

    init_plateau_jeu( plateau_jeu ) ;
    switch ( choix_difficulter )
    {
        case 49 :
            choix_difficulter = 0 ;
            break ;
        case 50 :
            choix_difficulter = 1 ;
            break ;
        case 51 :
            choix_difficulter = 2 ;
            break ;
    }
    switch ( choix_perso )
    {
        case 49 :
                perso_utiliser = new Moine() ;
                perso_ia1 = new Guerrier( choix_difficulter ) ;
                perso_ia2 = new Sorciere( choix_difficulter ) ;
                perso_ia3 = new Amazone( choix_difficulter ) ;
                break ;
        case 50 :
                perso_ia1 = new Moine( choix_difficulter ) ;
                perso_utiliser = new Guerrier() ;
                perso_ia2 = new Sorciere( choix_difficulter ) ;
                perso_ia3 = new Amazone( choix_difficulter ) ;
                break ;
        case 51 :
                perso_ia2 = new Moine( choix_difficulter ) ;
                perso_ia1 = new Guerrier( choix_difficulter ) ;
                perso_utiliser = new Sorciere() ;
                perso_ia3 = new Amazone( choix_difficulter ) ;
                break ;
        case 52 :
                perso_ia3 = new Moine( choix_difficulter ) ;
                perso_ia1 = new Guerrier( choix_difficulter ) ;
                perso_ia2 = new Sorciere( choix_difficulter ) ;
                perso_utiliser = new Amazone() ;
                break ;
    }
    placement_ia( perso_ia1 , perso_ia2 , perso_ia3 ) ;

/// 3° partie : gameplay .....................................................................................................................

    do //tour par tour
    {
        spam_endl( 10 ) ;
        cout << affichage_donjon( plateau_jeu , perso_utiliser ) <<  endl << spam_space( 39 ) << "inventaire : i" << endl ;
        cout << spam_space( 39 ) << "passer son tour : p " ;
        spam_endl( 9 ) ;

        action_terrain = _getch() ;
        while ( action_terrain != 50 && action_terrain != 52 && action_terrain != 54 && action_terrain != 56 && action_terrain != 105 && action_terrain != 112 )
        {
            action_terrain = _getch() ;
        }

        perso_utiliser->deplacer( action_terrain , plateau_jeu ) ;

        spam_endl( 30 ) ;

        if ( action_terrain == 105 )
        {
            perso_utiliser->inventaire( plateau_jeu[perso_utiliser->position_y][perso_utiliser->position_x] , pantin ) ;
        }

        else
        {
            if ( plateau_jeu[perso_utiliser->position_y][perso_utiliser->position_x]->nom_piege_actif == "piege runique" )
            {
                cout << "vous etes tomber sur un piege runique : - " << 8 - perso_utiliser->defense_magique << " pv" ;
                perso_utiliser->pv -= 8 - perso_utiliser->defense_magique ;
                plateau_jeu[perso_utiliser->position_y][perso_utiliser->position_x]->nom_piege_actif = "" ;
            }
            else if ( plateau_jeu[perso_utiliser->position_y][perso_utiliser->position_x]->nom_piege_actif == "arbalete piegee" )
            {
                cout << "vous etes tomber sur une arbalette piegee : - " << 8 - perso_utiliser->defense_physique << " pv" ;
                perso_utiliser->pv -= 8 - perso_utiliser->defense_physique ;
                plateau_jeu[perso_utiliser->position_y][perso_utiliser->position_x]->nom_piege_actif = "" ;
            }
        }

        if ( perso_utiliser->position_x == perso_ia1->position_x && perso_utiliser->position_y == perso_ia1->position_y )
        {
            perso_utiliser->combat( perso_ia1 , action_terrain , plateau_jeu ) ;
        }
        if ( perso_utiliser->position_x == perso_ia2->position_x && perso_utiliser->position_y == perso_ia2->position_y )
        {
            perso_utiliser->combat( perso_ia2 , action_terrain , plateau_jeu ) ;
        }
        if ( perso_utiliser->position_x == perso_ia3->position_x && perso_utiliser->position_y == perso_ia3->position_y )
        {
            perso_utiliser->combat( perso_ia3 , action_terrain , plateau_jeu ) ;
        }
    }while ( perso_utiliser->mort() == false && plateau_jeu[perso_utiliser->position_y][perso_utiliser->position_x]->piece_du_coffre != true ) ;
    if ( perso_utiliser->mort() == true )
    {
        spam_endl( 27 ) ;
        cout << spam_space( 75 ) << "GAME OVER" ;
        spam_endl( 26 ) ;
    }
    else
    {
        spam_endl( 27 ) ;
        cout << spam_space( 60 ) << "                      /|\\" << endl ;
        cout << spam_space( 60 ) << "                      \\|/" << endl ;
        cout << spam_space( 60 ) << "                    . ' ` ." << endl ;
        cout << spam_space( 60 ) << "*             *  . '   *    ` .  *             *" << endl ;
        cout << spam_space( 60 ) << "` \\          / \\'     / \\      `/ \\          / '" << endl ;
        cout << spam_space( 60 ) << " `  \\       /   \\    /   \\     /   \\       /  '" << endl ;
        cout << spam_space( 60 ) << "  `   \\   ./     \\  /     \\   /     \\.   /   '" << endl ;
        cout << spam_space( 60 ) << "   `    \\'/       \\/       \\ /       \\`/    '" << endl ;
        cout << spam_space( 60 ) << "    `_____________________________________ '" << endl ;
        cout << spam_space( 60 ) << "     _____________________________________" << endl ;
        cout << spam_space( 60 ) << "     _____________________________________" << endl ;
        cout << spam_space( 60 ) << "     |                                   |" << endl ;
        cout << spam_space( 60 ) << "     *     *     *     *     *     *     *" << endl ;
        cout << spam_space( 60 ) << "     |___________________________________|" << endl ;
        cout << spam_space( 60 ) << "     _____________________________________" << endl ;
        spam_endl( 5 ) ;
        cout << spam_space( 80 ) << "BRAVO !" << endl ;
        cout << spam_space( 75 ) << "vous avez gagnez !" << endl ;
        spam_endl( 20 ) ;
    }

    /*delete perso_ia1 ;
    delete perso_ia2 ;
    delete perso_ia3 ;
    delete perso_utiliser ;
    delete plateau_jeu ;
    delete pantin ;*/

    return 0 ;
}
#endif // main_cpp
