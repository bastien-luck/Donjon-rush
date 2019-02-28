#ifndef perso_cpp
#define perso_cpp

#include <iostream>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <sstream>
#include "windows.h"
//#include "gestion_fenetre.h"
#include "Personnages.h"
#include "Equipement.h"
#include "donjon.h"
#include "fonction_globale.h"

using namespace std ;

Personnages::Personnages()
{
    nom_personnage = "" ;
    degat_brut = 0 ;
    empoisonner = false ;
} ;

void Personnages::deplacer( int go , Piece *playground[10][10] )
{
    while((this->position_x==0&&go==52) || (this->position_x==9&&go==54) || (this->position_y==0&&go==56) || (this->position_y==9&&go==50))
    {
        go = _getch() ;
    }

    if ( playground[this->position_y][this->position_x]->icon_perso_et_piege_actif != "!" )
    {
        playground[this->position_y][this->position_x]->icon_perso_et_piege_actif = " " ;
    }

    if ( go == 52 )
    {
        this->position_x -- ;
    }
    else if ( go == 54 )
    {
        this->position_x ++ ;
    }
    else if ( go == 56 )
    {
        this->position_y -- ;
    }
    else if ( go == 50 )
    {
        this->position_y ++ ;
    }

    playground[this->position_y][this->position_x]->icon_perso_et_piege_actif = "X" ;
    playground[this->position_y][this->position_x]->passage_perso_utiliser = "oui" ;
}

void Personnages::fuite( int go , Piece *playground[10][10] )
{
    playground[this->position_y][this->position_x]->icon_perso_et_piege_actif = " " ;

    if ( go == 54 )
    {
        this->position_x -- ;
    }
    else if ( go == 52 )
    {
        this->position_x ++ ;
    }
    else if ( go == 50 )
    {
        this->position_y -- ;
    }
    else if ( go == 56 )
    {
        this->position_y ++ ;
    }

    playground[this->position_y][this->position_x]->icon_perso_et_piege_actif = "X" ;
}

void Personnages::combat( Personnages *ennemi , int fuir , Piece *playground[10][10] )
{
    int action_combat ;
    int tour_combat = 0 ;
    int start = 0 ;
    cout << spam_space( 10 ) << "vous venez de tomber contre " << ennemi->nom_personnage ;
    spam_endl( 4 ) ;
    do //combat
    {
        spam_endl( 5 ) ;
        this->sprite_combat( ennemi ) ;
        if ( start == 0 )
        {
            tour_combat = 1 ;
            start = 1 ;
        }
        if ( tour_combat == 1 )
        {
            action_combat = _getch() ;
            while ( action_combat != 49 && action_combat != 50 && action_combat != 51 && action_combat != 52 )
            {
                action_combat = _getch() ;
            }
            spam_endl( 20 ) ;
            switch ( action_combat )
            {
                case 49 :
                        this->attaque_normale( ennemi ) ;
                        break ;
                case 50 :
                        this->sorts( ennemi ) ;
                        break ;
                case 51 :
                        this->utiliser_objet_combat( ennemi , playground[this->position_y][position_x] ) ;
                        break ;
                case 52 :
                        this->fuite( fuir , playground ) ;
                        break ;
            }
            tour_combat = 2 ;
        }
        else if ( tour_combat == 2 )
        {
            Sleep( 2000 ) ;
            spam_endl( 20 ) ;
            if ( ennemi->force > ennemi->magie )
            {
                ennemi->attaque_normale( this ) ;
            }
            else
            {
                ennemi->sorts( this ) ;
            }
            tour_combat = 1 ;
            if ( ennemi->empoisonner == true )
            {
                ennemi->pv -= 2 ;
                cout << "        " << ennemi->nom_personnage << " souffre du poison : - " << 2 << " pv" << endl ;
            }
        }
    }while ( action_combat != 52 && ennemi->mort() != true && this->mort() != true ) ;
}

void Personnages::recevoir_dommage( Personnages *attaquant , string type_dmg )
{
    int chance_esquive = rand()%101 ;
    int chance_critique = rand()%101 ;
    if ( this->esquive < chance_esquive )
    {
        if ( type_dmg == "physique" )
        {
            if ( attaquant->chance > chance_critique )
            {
                this->pv -= attaquant->force + attaquant->degat_brut ;
                cout << endl << "        " << "c\'est un coup critique !" << endl << "        " << this->nom_personnage << " viens de perdre plusieurs dents : -" << attaquant->force + attaquant->degat_brut  << " pv" << endl ;
            }
            else if ( attaquant->force > this->defense_physique || attaquant->degat_brut != 0 )
            {
                this->pv -= attaquant->degat_brut ;
                this->pv -= attaquant->force + attaquant->degat_brut - this->defense_physique ;
                cout << endl << "        " << this->nom_personnage << " n\'a pas aimer ce coup : -" << attaquant->force + attaquant->degat_brut - this->defense_physique << " pv" << endl ;
                if ( attaquant->force < this->defense_physique )
                {
                    cout << endl << "        " << this->nom_personnage << " n\'a pas aimer ce coup : -" << attaquant->degat_brut  << " pv" << endl ;
                }
            }
            else
            {
                cout << endl << "        " << this->nom_personnage << " est aussi dur que de la pierre " << endl ;
            }
        }
        else if ( type_dmg == "magique" )
        {
            if ( attaquant->chance > chance_critique )
            {
                this->pv -= attaquant->magie ;
                cout << endl << "        " << "c\'est un coup critique !" << endl << "        " << this->nom_personnage << " tremble de nombreux spasmes : -" << attaquant->magie << " pv" << endl ;

            }
            else if ( attaquant->magie > this->defense_magique )
            {
                this->pv -= attaquant->magie - this->defense_magique ;
                cout << endl << "        " << this->nom_personnage << " se fait electrocuter : -" << attaquant->magie - this->defense_magique << " pv" << endl ;
            }
            else
            {
                cout << endl << "        " << this->nom_personnage << " n\'a meme pas eu un coup de chaud " << endl ;
            }
        }
    }
    else
    {
        cout << endl << "        " << this->nom_personnage << " esquive avec brio l\'attaque de " << attaquant->nom_personnage << endl ;
    }
}

void Personnages::attaque_normale( Personnages *cible )
{
    string degat = "physique" ;
    cout << endl << "        " << this->nom_personnage << " fout une baigne a " << cible->nom_personnage << endl ;
    cible->recevoir_dommage( this , degat ) ;
}

void Personnages::sorts( Personnages *cible )
{
    string degat = "magique" ;
    cout << endl << "        " << this->nom_personnage << " lance une boule de feu sur " << cible->nom_personnage << endl ;
    cible->recevoir_dommage( this , degat ) ;
}

bool Personnages::mort()
{
    if ( this->pv <=0 )
    {
        spam_endl( 4 ) ;
        cout << "        " << this->nom_personnage << " est mort" ;
        this->position_x = -1 ;
        return true ;
    }
    else
    {
        return false ;
    }
}

string Personnages::barre_de_vie( string position )
{
    string temps = "" ;
    if ( position == "haut" )
    {
        for ( int i = 0 ; i < 21 ; i++ )
            {
                temps += "_" ;
            }
    }
    if ( position == "milieu" )
    {
        int nb = 0 ;
        for ( int i = 0 ; i < 21 ; i++ )
            {
                if ( i > 12 )
                {
                    if ( ( ( this->pv )*21/( this->max_pv ) ) < i )
                    {
                        temps += " " ;
                    }
                    else
                    {
                        temps += "è" ;
                    }
                }
                else if ( i < 8 )
                {
                    if ( ( ( this->pv )*21/( this->max_pv ) ) < i )
                    {
                        temps += " " ;
                    }
                    else
                    {
                        temps += "è" ;
                    }
                }
                else if ( nb == 0 )
                {
                    if ( this->pv <10 )
                    {
                        temps += " " ;
                    }
                    nb = 1 ;
                    temps += intToString( this->pv ) + "/" + intToString( this->max_pv ) ;
                }
            }
    }
    if ( position == "milieux" )
    {
        for ( int i = 1 ; i < 22 ; i++ )
            {
                if ( ( ( this->pv )*21/( this->max_pv ) ) < i )
                {
                    temps += " " ;
                }
                else
                {
                    temps += "è" ;
                }
            }
    }
    if ( position == "bas" )
    {
        for ( int i = 0 ; i < 21 ; i++ )
            {
                temps += "\"" ;
            }
    }
    return temps ;
}

void Personnages::sprite_combat( Personnages *cible )
{
    string combat = "" ;
    combat += spam_space( 21-this->nom_personnage.size()/2 ) + this->nom_personnage + spam_space( 79-this->nom_personnage.size()/2-cible->nom_personnage.size()/2 ) + cible->nom_personnage + "\n" ;
    combat += spam_space( 11 ) + this->barre_de_vie( "haut" ) + spam_space( 59 ) + cible->barre_de_vie( "haut" ) + "\n" ;
    combat += spam_space( 10 ) +  "(" + this->barre_de_vie( "milieux" ) + ")" + spam_space( 57 ) + "(" + cible->barre_de_vie( "milieux" ) + ")" + "\n" ;
    combat += spam_space( 10 ) + "(" + this->barre_de_vie( "milieu" ) + ")" + spam_space( 57 ) + "(" + cible->barre_de_vie( "milieu" ) + ")" + "\n" ;
    combat += spam_space( 10 ) + "(" + this->barre_de_vie( "milieux" ) + ")" + spam_space( 57 ) + "(" + cible->barre_de_vie( "milieux" ) + ")" + "\n" ;
    combat += spam_space( 11 ) + this->barre_de_vie( "bas" ) + spam_space( 59 ) + cible->barre_de_vie( "bas" ) + "\n" ;
    combat += this->sprite_L1 + spam_space( 40 ) + cible->sprite_L1 + "\n" ;
    combat += this->sprite_L2 + spam_space( 40 ) + cible->sprite_L2 + "\n" ;
    combat += this->sprite_L3 + spam_space( 40 ) + cible->sprite_L3 + "\n" ;
    combat += this->sprite_L4 + spam_space( 40 ) + cible->sprite_L4 + "\n" ;
    combat += this->sprite_L5 + spam_space( 40 ) + cible->sprite_L5 + "\n" ;
    combat += this->sprite_L6 + spam_space( 40 ) + cible->sprite_L6 + "\n" ;
    combat += this->sprite_L7 + spam_space( 40 ) + cible->sprite_L7 + "\n" ;
    combat += this->sprite_L8 + spam_space( 40 ) + cible->sprite_L8 + "\n" ;
    combat += this->sprite_L9 + spam_space( 40 ) + cible->sprite_L9 + "\n" ;
    combat += this->sprite_L10 + spam_space( 40 ) + cible->sprite_L10 + "\n" ;
    combat += this->sprite_L11 + spam_space( 40 ) + cible->sprite_L11 + "\n" ;
    combat += this->sprite_L12 + spam_space( 40 ) + cible->sprite_L12 + "\n" ;
    combat += this->sprite_L13 + spam_space( 40 ) + cible->sprite_L13 + "\n" ;
    combat += this->sprite_L14 + spam_space( 40 ) + cible->sprite_L14 + "\n" ;
    combat += this->sprite_L15 + spam_space( 40 ) + cible->sprite_L15 + "\n" ;
    combat += this->sprite_L16 + spam_space( 40 ) + cible->sprite_L16 + "\n" ;
    combat += this->sprite_L17 + spam_space( 40 ) + cible->sprite_L17 + "\n" ;
    combat += this->sprite_L18 + spam_space( 40 ) + cible->sprite_L18 + "\n" ;
    combat += "\n\n\n\n\n\n\n\n\n\n" ;
    combat += "\n" + spam_space( 12 ) + "1 : attaque normale" + "\n" ;
    combat += "\n" + spam_space( 12 ) + "2 : sort" + "\n" ;
    combat += "\n" + spam_space( 12 ) + "3 : utiliser objet" + "\n" ;
    combat += "\n" + spam_space( 12 ) + "4 : fuir" + "\n" ;
    cout << combat ;
}


void Personnages::utiliser_objet_combat( Personnages *cible , Piece *salles )
{
    int a ;
    string e_1 = "vide" ;
    string e_2 = "vide" ; // réduction taille condition while
    string e_3 = "vide" ;
    string e_4 = "vide" ;
    string e_5 = "vide" ;
    string e_6 = "vide" ;
    e_1 = this->sac[0]->nom_equipement ;
    e_2 = this->sac[1]->nom_equipement ;
    e_3 = this->sac[2]->nom_equipement ;
    if ( this->slot_objets > 3 )
    {
        e_4 = this->sac[3]->nom_equipement ;
        if ( this->slot_objets > 5 )
        {
            e_5 = this->sac[4]->nom_equipement ;
            e_6 = this->sac[5]->nom_equipement ;
        }
    }
    spam_endl( 20 ) ;
    string combat = "" ;
    combat += spam_space( 21-this->nom_personnage.size()/2 ) + this->nom_personnage + spam_space( 79-this->nom_personnage.size()/2-cible->nom_personnage.size()/2 ) + cible->nom_personnage + "\n" ;
    combat += spam_space( 11 ) + this->barre_de_vie( "haut" ) + spam_space( 59 ) + cible->barre_de_vie( "haut" ) + "\n" ;
    combat += spam_space( 10 ) +  "(" + this->barre_de_vie( "milieux" ) + ")" + spam_space( 57 ) + "(" + cible->barre_de_vie( "milieux" ) + ")" + "\n" ;
    combat += spam_space( 10 ) + "(" + this->barre_de_vie( "milieu" ) + ")" + spam_space( 57 ) + "(" + cible->barre_de_vie( "milieu" ) + ")" + "\n" ;
    combat += spam_space( 10 ) + "(" + this->barre_de_vie( "milieux" ) + ")" + spam_space( 57 ) + "(" + cible->barre_de_vie( "milieux" ) + ")" + "\n" ;
    combat += spam_space( 11 ) + this->barre_de_vie( "bas" ) + spam_space( 59 ) + cible->barre_de_vie( "bas" ) + "\n" ;
    combat += this->sprite_L1 + spam_space( 40 ) + cible->sprite_L1 + "\n" ;
    combat += this->sprite_L2 + spam_space( 40 ) + cible->sprite_L2 + "\n" ;
    combat += this->sprite_L3 + spam_space( 40 ) + cible->sprite_L3 + "\n" ;
    combat += this->sprite_L4 + spam_space( 40 ) + cible->sprite_L4 + "\n" ;
    combat += this->sprite_L5 + spam_space( 40 ) + cible->sprite_L5 + "\n" ;
    combat += this->sprite_L6 + spam_space( 40 ) + cible->sprite_L6 + "\n" ;
    combat += this->sprite_L7 + spam_space( 40 ) + cible->sprite_L7 + "\n" ;
    combat += this->sprite_L8 + spam_space( 40 ) + cible->sprite_L8 + "\n" ;
    combat += this->sprite_L9 + spam_space( 40 ) + cible->sprite_L9 + "\n" ;
    combat += this->sprite_L10 + spam_space( 40 ) + cible->sprite_L10 + "\n" ;
    combat += this->sprite_L11 + spam_space( 40 ) + cible->sprite_L11 + "\n" ;
    combat += this->sprite_L12 + spam_space( 40 ) + cible->sprite_L12 + "\n" ;
    combat += this->sprite_L13 + spam_space( 40 ) + cible->sprite_L13 + "\n" ;
    combat += this->sprite_L14 + spam_space( 40 ) + cible->sprite_L14 + "\n" ;
    combat += this->sprite_L15 + spam_space( 40 ) + cible->sprite_L15 + "\n" ;
    combat += this->sprite_L16 + spam_space( 40 ) + cible->sprite_L16 + "\n" ;
    combat += this->sprite_L17 + spam_space( 40 ) + cible->sprite_L17 + "\n" ;
    combat += this->sprite_L18 + spam_space( 40 ) + cible->sprite_L18 + "\n" ;
    combat += "\n\n\n\n\n\n\n\n\n" ;
    combat += spam_space( 12 ) + "objets dans l'inventaire :" + "\n\n" ;
    combat += spam_space( 12 ) + "1 : " + this->sac[0]->nom_equipement + "\n" ;
    combat += spam_space( 12 ) + "2 : " + this->sac[1]->nom_equipement + "\n" ;
    combat += spam_space( 12 ) + "3 : " + this->sac[2]->nom_equipement + "\n" ;
    if ( this->slot_objets > 3 )
    {
        combat += spam_space( 12 ) + "4 : " + this->sac[3]->nom_equipement + "\n" ;
        if ( this->slot_objets == 6 )
        {
            combat += spam_space( 12 ) + "5 : " + this->sac[4]->nom_equipement + "\n" ;
            combat += spam_space( 12 ) + "6 : " + this->sac[5]->nom_equipement + "\n" ;
        }
        else
        {
            combat += "\n\n" ;
        }
    }
    else
    {
        combat += "\n" ;
    }
    cout << combat << endl ;
    a = _getch() ;
    while ( ( ( a != 32 && a != 49 && a != 50 && a != 51 && a != 52 && a != 53 && a != 54 ) || ( a == 49 && e_1 == "vide" ) || ( a == 50 && e_2 == "vide" ) || ( a == 51 && e_3 == "vide" ) || ( a == 52 && e_4 == "vide" ) || ( a == 53 && e_5 == "vide" ) || ( a == 54 && e_6 == "vide" ) ) )
    {
        a = _getch() ;
    }
    spam_endl( 20 ) ;
    switch ( a )
    {
        case 49 :
            utilisation_objet( this , 0 , cible , salles ) ;
            break ;
        case 50 :
            utilisation_objet( this , 1 , cible , salles ) ;
            break ;
        case 51 :
            utilisation_objet( this , 2 , cible , salles ) ;
            break ;
        case 52 :
            utilisation_objet( this , 3 , cible , salles ) ;
            break ;
        case 53 :
            utilisation_objet( this , 4 , cible , salles ) ;
            break ;
        case 54 :
            utilisation_objet( this , 5 , cible , salles ) ;
            break ;
    }
}

void Personnages::utiliser_objet( Piece *salle , Personnages *cible )
{
    int a ;
    int place ;
    string e_1 = "vide" ;
    string e_2 = "vide" ; // réduction taille condition while
    string e_3 = "vide" ;
    string e_4 = "vide" ;
    string e_5 = "vide" ;
    string e_6 = "vide" ;
    do
    {
        e_1 = this->sac[0]->nom_equipement ;
        e_2 = this->sac[1]->nom_equipement ;
        e_3 = this->sac[2]->nom_equipement ;
        if ( this->slot_objets > 3 )
        {
            e_4 = this->sac[3]->nom_equipement ;
            if ( this->slot_objets > 5 )
            {
                e_5 = this->sac[4]->nom_equipement ;
                e_6 = this->sac[5]->nom_equipement ;
            }
        }
        spam_endl( 10 ) ;
        place = 1 ;
        cout << spam_space( 10 ) << "objet equiper :" ;
        spam_endl( 2 ) ;
        cout << spam_space( 10 ) << "armes :" << endl ;
        for ( int i = 0 ; i < this->slot_armes ; i++ )
        {
            cout << spam_space( 10 ) << this->stuff_arme[i]->nom_equipement << endl ;
        }
        cout << endl << spam_space( 10 ) << "accessoires :" << endl ;
        for ( int j = 0 ; j < this->slot_accessoires ; j++ )
        {
            cout << spam_space( 10 ) << this->stuff_accessoire[j]->nom_equipement << endl ;
        }
        cout << endl << spam_space( 10 ) << "casque :" << endl ;
        for ( int k = 0 ; k < this->slot_casques ; k++ )
        {
            cout << spam_space( 10 ) << this->stuff_casque[k]->nom_equipement << endl ;
        }
        cout << endl << spam_space( 10 ) << "plastron :" << spam_space( 43 ) << "retour : espace" << endl ;
        for ( int l = 0 ; l < this->slot_plastron ; l++ )
        {
            cout << spam_space( 10 ) << this->stuff_plastron[l]->nom_equipement << endl ;
        }
        cout << endl << spam_space( 10 ) << "bottes :" << endl ;
        for ( int m = 0 ; m < this->slot_bottes ; m++ )
        {
            cout << spam_space( 10 ) << this->stuff_botte[m]->nom_equipement << endl ;
        }
        cout << endl << spam_space( 10 ) << "jambiere :" << endl ;
        for ( int n = 0 ; n < this->slot_jambieres ; n++ )
        {
            cout << spam_space( 10 ) << this->stuff_jambiere[n]->nom_equipement << endl ;
        }
        cout << endl << spam_space( 10 ) << "gantelets :" << endl ;
        for ( int o = 0 ; o < this->slot_gantelets ; o++ )
        {
            cout << spam_space( 10 ) << this->stuff_gantelets[o]->nom_equipement << endl ;
        }
        spam_endl( 5 ) ;
        cout << endl << spam_space( 10 ) << "inventaire :" << spam_space( 41 ) << "quel objet voulez vous utiliser ? " ;
        spam_endl( 2 ) ;
        for ( int p = 0 ; p < this->slot_objets ; p++ )
        {
            cout << spam_space( 10 ) << place << " : " << this->sac[p]->nom_equipement << endl ;
            place ++ ;
        }
        spam_endl( 5 ) ;
        cout << spam_space( 10 ) + "objet dans la piece :" << endl << endl << spam_space( 10 ) + salle->nom_arme_et_armure ;
        cout << endl  << spam_space( 10 ) + salle->nom_accessoire << endl << spam_space( 10 ) + salle->nom_potion << endl ;
        cout << spam_space( 10 ) + salle->nom_poison_et_tp_et_parchemin << endl << spam_space( 10 ) + salle->nom_piege ;
        spam_endl( 5 ) ;
        a = _getch() ;
        while ( a != 32 && ( ( a != 49 && a != 50 && a != 51 && a != 52 && a != 53 ) || ( a == 49 && e_1 == "vide" ) || ( a == 50 && e_2 == "vide" ) || ( a == 51 && e_3 == "vide" ) || ( a == 52 && e_4 == "vide" ) || ( a == 53 && e_6 == "vide" ) ) )
        {
            a = _getch() ;
        }
        switch ( a )
        {
            case 49 :
                utilisation_objet( this , 0 , cible , salle ) ;
                break ;
            case 50 :
                utilisation_objet( this , 1 , cible , salle ) ;
                break ;
            case 51 :
                utilisation_objet( this , 2 , cible , salle ) ;
                break ;
            case 52 :
                utilisation_objet( this , 3 , cible , salle ) ;
                break ;
            case 53 :
                utilisation_objet( this , 4 , cible , salle ) ;
                break ;
            case 54 :
                utilisation_objet( this , 5 , cible , salle ) ;
                break ;
            default :
                break ;
        }
    }while ( a != 32 ) ;
}

void Personnages::ramasser_objet( Piece *salle )
{
    int emplacement_libre ;
    int a ;
    string e_1 ;
    string e_2 ; // réduction taille condition while
    string e_3 ;
    string e_4 ;
    string e_6 ;
    do
    {
        e_1 = salle->espace_premier_slot ;
        e_2 = salle->espace_second_slot ;
        e_3 = salle->espace_troisieme_slot ;
        e_4 = salle->espace_quatrieme_slot ;
        e_6 = salle->espace_sixieme_slot ;
        emplacement_libre = 10 ;
        spam_endl( 10 ) ;
        cout << spam_space( 10 ) << "objet equiper :" ;
        spam_endl( 2 ) ;
        cout << spam_space( 10 ) << "armes :" << endl ;
        for ( int i = 0 ; i < this->slot_armes ; i++ )
        {
            cout << spam_space( 10 ) << this->stuff_arme[i]->nom_equipement << endl ;
        }
        cout << endl << spam_space( 10 ) << "accessoires :" << endl ;
        for ( int j = 0 ; j < this->slot_accessoires ; j++ )
        {
            cout << spam_space( 10 ) << this->stuff_accessoire[j]->nom_equipement << endl ;
        }
        cout << endl << spam_space( 10 ) << "casque :" << endl ;
        for ( int k = 0 ; k < this->slot_casques ; k++ )
        {
            cout << spam_space( 10 ) << this->stuff_casque[k]->nom_equipement << endl ;
        }
        cout << endl << spam_space( 10 ) << "plastron :" << spam_space( 43 ) << "retour : espace" << endl ;
        for ( int l = 0 ; l < this->slot_plastron ; l++ )
        {
            cout << spam_space( 10 ) << this->stuff_plastron[l]->nom_equipement << endl ;
        }
        cout << endl << spam_space( 10 ) << "bottes :" << endl ;
        for ( int m = 0 ; m < this->slot_bottes ; m++ )
        {
            cout << spam_space( 10 ) << this->stuff_botte[m]->nom_equipement << endl ;
        }
        cout << endl << spam_space( 10 ) << "jambiere :" << endl ;
        for ( int n = 0 ; n < this->slot_jambieres ; n++ )
        {
            cout << spam_space( 10 ) << this->stuff_jambiere[n]->nom_equipement << endl ;
        }
        cout << endl << spam_space( 10 ) << "gantelets :" << endl ;
        for ( int o = 0 ; o < this->slot_gantelets ; o++ )
        {
            cout << spam_space( 10 ) << this->stuff_gantelets[o]->nom_equipement << endl ;
        }
        spam_endl( 5 ) ;
        cout << endl << spam_space( 10 ) << "inventaire :" ;
        spam_endl( 2 ) ;
        for ( int p = 0 ; p < this->slot_objets ; p++ )
        {
            cout << spam_space( 10 ) << this->sac[p]->nom_equipement << endl ;
        }
        spam_endl( 5 ) ;
        cout << spam_space( 10 ) + "objet dans la piece :" << spam_space( 32 ) << "quel objet voulez vous ramasser ?" << endl ;
        cout << endl << spam_space( 10 ) + "1 : " + salle->nom_arme_et_armure << endl  << spam_space( 10 ) + "2 : " ;
        cout << salle->nom_accessoire << endl << spam_space( 10 ) + "3 : " + salle->nom_potion << endl << spam_space( 10 ) ;
        cout << "4 : " + salle->nom_poison_et_tp_et_parchemin << endl << spam_space( 10 ) + "5 : " + salle->nom_piege ;
        spam_endl( 5 ) ;
        a = _getch() ;
        while ( ( ( a != 32 && a != 49 && a != 50 && a != 51 && a != 52 && a != 53 ) || ( a == 49 && e_1 == "vide" ) || ( a == 50 && e_2 == "vide" ) || ( a == 51 && e_3 == "vide" ) || ( a == 52 && e_4 == "vide" ) || ( a == 53 && e_6 == "vide" ) ) )
        {
            a = _getch() ;
        }
        for ( int d = 0 ; d < this->slot_objets ; d ++ )
            {
                if ( this->sac[d]->nom_equipement == "vide" )
                {
                    emplacement_libre = d ;
                    break ;
                }
            }
        if ( emplacement_libre != 10 )
        {
            switch ( a )
            {
                case 49 :
                    ramassage_objet( this , salle , emplacement_libre , 1 ) ;
                    break ;
                case 50 :
                    ramassage_objet( this , salle , emplacement_libre , 2 ) ;
                    break ;
                case 51 :
                    ramassage_objet( this , salle , emplacement_libre , 3 ) ;
                    break ;
                case 52 :
                    ramassage_objet( this , salle , emplacement_libre , 4 ) ;
                    break ;
                case 53 :
                    ramassage_objet( this , salle , emplacement_libre , 5 ) ;
                    break ;
                default :
                    break ;
            }
        }
    }while ( a != 32 ) ;
}

void Personnages::poser_objet( Piece *salle )
{
    int a ;
    int place ;
    string e_1 = "vide" ;
    string e_2 = "vide" ; // réduction taille condition while
    string e_3 = "vide" ;
    string e_4 = "vide" ;
    string e_5 = "vide" ;
    string e_6 = "vide" ;
    do
    {
        e_1 = this->sac[0]->nom_equipement ;
        e_2 = this->sac[1]->nom_equipement ;
        e_3 = this->sac[2]->nom_equipement ;
        if ( this->slot_objets > 3 )
        {
            e_4 = this->sac[3]->nom_equipement ;
            if ( this->slot_objets > 5 )
            {
                e_5 = this->sac[4]->nom_equipement ;
                e_6 = this->sac[5]->nom_equipement ;
            }
        }
        spam_endl( 10 ) ;
        place = 1 ;
        cout << spam_space( 10 ) << "objet equiper :" ;
        spam_endl( 2 ) ;
        cout << spam_space( 10 ) << "armes :" << endl ;
        for ( int i = 0 ; i < this->slot_armes ; i++ )
        {
            cout << spam_space( 10 ) << this->stuff_arme[i]->nom_equipement << endl ;
        }
        cout << endl << spam_space( 10 ) << "accessoires :" << endl ;
        for ( int j = 0 ; j < this->slot_accessoires ; j++ )
        {
            cout << spam_space( 10 ) << this->stuff_accessoire[j]->nom_equipement << endl ;
        }
        cout << endl << spam_space( 10 ) << "casque :" << endl ;
        for ( int k = 0 ; k < this->slot_casques ; k++ )
        {
            cout << spam_space( 10 ) << this->stuff_casque[k]->nom_equipement << endl ;
        }
        cout << endl << spam_space( 10 ) << "plastron :" << spam_space( 43 ) << "retour : espace" << endl ;
        for ( int l = 0 ; l < this->slot_plastron ; l++ )
        {
            cout << spam_space( 10 ) << this->stuff_plastron[l]->nom_equipement << endl ;
        }
        cout << endl << spam_space( 10 ) << "bottes :" << endl ;
        for ( int m = 0 ; m < this->slot_bottes ; m++ )
        {
            cout << spam_space( 10 ) << this->stuff_botte[m]->nom_equipement << endl ;
        }
        cout << endl << spam_space( 10 ) << "jambiere :" << endl ;
        for ( int n = 0 ; n < this->slot_jambieres ; n++ )
        {
            cout << spam_space( 10 ) << this->stuff_jambiere[n]->nom_equipement << endl ;
        }
        cout << endl << spam_space( 10 ) << "gantelets :" << endl ;
        for ( int o = 0 ; o < this->slot_gantelets ; o++ )
        {
            cout << spam_space( 10 ) << this->stuff_gantelets[o]->nom_equipement << endl ;
        }
        spam_endl( 5 ) ;
        cout << endl << spam_space( 10 ) << "inventaire :" << spam_space( 41 ) << "quel objet voulez vous poser ?" ;
        spam_endl( 2 ) ;
        for ( int p = 0 ; p < this->slot_objets ; p++ )
        {
            cout << spam_space( 10 ) << place << " : " << this->sac[p]->nom_equipement << endl ;
            place ++ ;
        }
        spam_endl( 5 ) ;
        cout << spam_space( 10 ) + "objet dans la piece :" << endl << endl << spam_space( 10 ) + salle->nom_arme_et_armure ;
        cout << endl  << spam_space( 10 ) + salle->nom_accessoire << endl << spam_space( 10 ) + salle->nom_potion << endl ;
        cout << spam_space( 10 ) + salle->nom_poison_et_tp_et_parchemin << endl << spam_space( 10 ) + salle->nom_piege ;
        spam_endl( 5 ) ;
        a = _getch() ;
        while ( ( ( a != 32 && a != 49 && a != 50 && a != 51 && a != 52 && a != 53 && a != 54 ) || ( a == 49 && e_1 == "vide" ) || ( a == 50 && e_2 == "vide" ) || ( a == 51 && e_3 == "vide" ) || ( a == 52 && e_4 == "vide" ) || ( a == 53 && e_5 == "vide" ) || ( a == 54 && e_6 == "vide" ) ) )
        {
            a = _getch() ;
        }
        switch ( a )
        {
            case 49 :
                verification_place_sol( this , salle , this->sac[0]->type_equipement , 0 ) ;
                break ;
            case 50 :
                verification_place_sol( this , salle , this->sac[1]->type_equipement , 1 ) ;
                break ;
            case 51 :
                verification_place_sol( this , salle , this->sac[2]->type_equipement , 2 ) ;
                break ;
            if ( this->slot_objets > 3 )
            {
                case 52 :
                    verification_place_sol( this , salle , this->sac[3]->type_equipement , 3 ) ;
                    break ;
                if ( this->slot_objets > 6 )
                {
                    case 53 :
                        verification_place_sol( this , salle , this->sac[4]->type_equipement , 4 ) ;
                        break ;
                    case 54 :
                        verification_place_sol( this , salle , this->sac[5]->type_equipement , 5 ) ;
                        break ;
                }
            }
            default :
                break ;
        }
    }while ( a != 32 ) ;
}

void Personnages::equiper( Piece *salle )
{
    int a ;
    int place ;
    int place_arme = 0 ;
    int place_accessoire = 0 ;
    string e_1 = "vide" ;
    string e_2 = "vide" ; // réduction taille condition while
    string e_3 = "vide" ;
    string e_4 = "vide" ;
    string e_5 = "vide" ;
    string e_6 = "vide" ;
    do
    {
        e_1 = this->sac[0]->nom_equipement ;
        e_2 = this->sac[1]->nom_equipement ;
        e_3 = this->sac[2]->nom_equipement ;
        if ( this->slot_objets > 3 )
        {
            e_4 = this->sac[3]->nom_equipement ;
            if ( this->slot_objets > 5 )
            {
                e_5 = this->sac[4]->nom_equipement ;
                e_6 = this->sac[5]->nom_equipement ;
            }
        }
        spam_endl( 10 ) ;
        place = 1 ;
        cout << spam_space( 10 ) << "objet equiper :" ;
        spam_endl( 2 ) ;
        cout << spam_space( 10 ) << "armes :" << endl ;
        for ( int i = 0 ; i < this->slot_armes ; i++ )
        {
            cout << spam_space( 10 ) << this->stuff_arme[i]->nom_equipement << endl ;
        }
        cout << endl << spam_space( 10 ) << "accessoires :" << endl ;
        for ( int j = 0 ; j < this->slot_accessoires ; j++ )
        {
            cout << spam_space( 10 ) << this->stuff_accessoire[j]->nom_equipement << endl ;
        }
        cout << endl << spam_space( 10 ) << "casque :" << endl ;
        for ( int k = 0 ; k < this->slot_casques ; k++ )
        {
            cout << spam_space( 10 ) << this->stuff_casque[k]->nom_equipement << endl ;
        }
        cout << endl << spam_space( 10 ) << "plastron :" << spam_space( 43 ) << "fermer inventaire : espace" << endl ;
        for ( int l = 0 ; l < this->slot_plastron ; l++ )
        {
            cout << spam_space( 10 ) << this->stuff_plastron[l]->nom_equipement << endl ;
        }
        cout << endl << spam_space( 10 ) << "bottes :" << endl ;
        for ( int m = 0 ; m < this->slot_bottes ; m++ )
        {
            cout << spam_space( 10 ) << this->stuff_botte[m]->nom_equipement << endl ;
        }
        cout << endl << spam_space( 10 ) << "jambiere :" << endl ;
        for ( int n = 0 ; n < this->slot_jambieres ; n++ )
        {
            cout << spam_space( 10 ) << this->stuff_jambiere[n]->nom_equipement << endl ;
        }
        cout << endl << spam_space( 10 ) << "gantelets :" << endl ;
        for ( int o = 0 ; o < this->slot_gantelets ; o++ )
        {
            cout << spam_space( 10 ) << this->stuff_gantelets[o]->nom_equipement << endl ;
        }
        spam_endl( 5 ) ;
        cout << endl << spam_space( 10 ) << "inventaire :" << spam_space( 41 ) << "quel objet voulez vous equiper ?" ;
        spam_endl( 2 ) ;
        for ( int p = 0 ; p < this->slot_objets ; p++ )
        {
            cout << spam_space( 10 ) << place << " : " << this->sac[p]->nom_equipement << endl ;
            place ++ ;
        }
        spam_endl( 5 ) ;
        cout << spam_space( 10 ) + "objet dans la piece :" << endl << endl << spam_space( 10 ) + salle->nom_arme_et_armure ;
        cout << endl  << spam_space( 10 ) + salle->nom_accessoire << endl << spam_space( 10 ) + salle->nom_potion << endl ;
        cout << spam_space( 10 ) + salle->nom_poison_et_tp_et_parchemin << endl << spam_space( 10 ) + salle->nom_piege ;
        spam_endl( 5 ) ;
        a = _getch() ;
        while ( ( ( a != 32 && a != 49 && a != 50 && a != 51 && a != 52 && a != 53 && a != 54 ) || ( a == 49 && e_1 == "vide" ) || ( a == 50 && e_2 == "vide" ) || ( a == 51 && e_3 == "vide" ) || ( a == 52 && e_4 == "vide" ) || ( a == 53 && e_5 == "vide" ) || ( a == 54 && e_6 == "vide" ) ) )
        {
            a = _getch() ;
        }
        if ( a != 32 )
        {
            this->modification_stats( 1 , a-49 ) ;
            switch ( a )
            {
                case 49 :
                    verification_type_equipement( this , 0 , &place_accessoire , &place_arme ) ;
                    break ;
                case 50 :
                    verification_type_equipement( this , 1 , &place_accessoire , &place_arme ) ;
                    break ;
                case 51 :
                    verification_type_equipement( this , 2 , &place_accessoire , &place_arme ) ;
                    break ;
                if ( this->slot_objets > 3 )
                {
                    case 52 :
                        verification_type_equipement( this , 3 , &place_accessoire , &place_arme ) ;
                        break ;
                    if ( this->slot_objets == 6 )
                    {
                        case 53 :
                            verification_type_equipement( this , 4 , &place_accessoire , &place_arme ) ;
                            break ;
                        case 54 :
                            verification_type_equipement( this , 5 , &place_accessoire , &place_arme ) ;
                            break ;
                    }
                }
                default :
                    break ;
            }
            this->modification_stats( -1 , a-49 ) ;
        }
    }while ( a != 32 ) ;
}

void Personnages::modification_stats( int plus_ou_moins , int place_inventaire )
{
    switch ( plus_ou_moins )
    {
        case -1 :
            this->max_pv += plus_ou_moins * ( this->sac[place_inventaire]->pv ) ;
            this->pv += plus_ou_moins * ( this->sac[place_inventaire]->pv ) ;
            this->force += plus_ou_moins * ( this->sac[place_inventaire]->force ) ;
            this->magie += plus_ou_moins * ( this->sac[place_inventaire]->magie ) ;
            this->defense_magique += plus_ou_moins * ( this->sac[place_inventaire]->defense_magique ) ;
            this->defense_physique += plus_ou_moins * ( this->sac[place_inventaire]->defense_physique ) ;
            this->esquive += plus_ou_moins * ( this->sac[place_inventaire]->esquive ) ;
            this->chance += plus_ou_moins * ( this->sac[place_inventaire]->chance ) ;
            this->degat_brut += plus_ou_moins * ( this->sac[place_inventaire]->degats_brut ) ;
            break ;
        case 1 :
            this->max_pv += plus_ou_moins * ( this->sac[place_inventaire]->pv ) ;
            this->pv += plus_ou_moins * ( this->sac[place_inventaire]->pv ) ;
            this->force += plus_ou_moins * ( this->sac[place_inventaire]->force ) ;
            this->magie += plus_ou_moins * ( this->sac[place_inventaire]->magie ) ;
            this->defense_magique += plus_ou_moins * ( this->sac[place_inventaire]->defense_magique ) ;
            this->defense_physique += plus_ou_moins * ( this->sac[place_inventaire]->defense_physique ) ;
            this->esquive += plus_ou_moins * ( this->sac[place_inventaire]->esquive ) ;
            this->chance += plus_ou_moins * ( this->sac[place_inventaire]->chance ) ;
            this->degat_brut += plus_ou_moins * ( this->sac[place_inventaire]->degats_brut ) ;
            break ;
    }
}

void Personnages::caracteristiques_perso()
{
    spam_endl( 20 ) ;
    cout << spam_space( 20 ) << "personnage : " << this->nom_personnage ;
    spam_endl( 4 ) ;
    cout << this->sprite_L1 << spam_space( 10 ) << "points de vie : " << this->pv << "/" << this->max_pv << endl ;
    cout << this->sprite_L2 << endl ;
    cout << this->sprite_L3 << endl ;
    cout << this->sprite_L4 << spam_space( 10 ) << "force : " << this->force << endl ;
    cout << this->sprite_L5 << spam_space( 10 ) << "force brute : " << this->degat_brut << endl ;
    cout << this->sprite_L6 << endl ;
    cout << this->sprite_L7 << spam_space( 10 ) << "magie : " << this->magie << endl ;
    cout << this->sprite_L8 << endl ;
    cout << this->sprite_L9 << endl ;
    cout << this->sprite_L10 << spam_space( 10 ) << "defense physique : " << this->defense_physique << endl ;
    cout << this->sprite_L11 << endl ;
    cout << this->sprite_L12 << endl ;
    cout << this->sprite_L13 << spam_space( 10 ) << "defense magique : " << this->defense_magique << endl ;
    cout << this->sprite_L14 << endl ;
    cout << this->sprite_L15 << endl ;
    cout << this->sprite_L16 << spam_space( 10 ) << "chance d\'esquive : " << this->esquive << "/100" << endl ;
    cout << this->sprite_L17 << endl ;
    cout << this->sprite_L18 << spam_space( 10 ) << "chance de critique : " << this->chance << "/100" << endl ;
    spam_endl( 8 ) ;
    cout << spam_space( 30 ) << "retour : espace" ;
    spam_endl( 8 ) ;
    while ( _getch() != 32 )
    {

    }
}

void Personnages::caracteristiques_objet()
{
    int choix_objet ;
    int place_sac = 0 ;
    do
    {
        spam_endl( 20 ) ;
        if ( choix_objet != 32 )
        {
            cout << spam_space( 20 )  << this->sac[place_sac]->nom_equipement << endl ;
            cout << endl << spam_space( 20 ) << "pv suplementaire : " << this->sac[place_sac]->pv << endl ;
            cout << endl << spam_space( 20 ) << "degat physique : " << this->sac[place_sac]->force << endl ;
            cout << endl << spam_space( 20 ) << "degat brut : " << this->sac[place_sac]->degats_brut << endl ;
            cout << endl << spam_space( 20 ) << "degat magique : " << this->sac[place_sac]->magie << endl ;
            cout << endl << spam_space( 20 ) << "defense physique : " << this->sac[place_sac]->defense_physique << endl ;
            cout << endl << spam_space( 20 ) << "defense magique : " << this->sac[place_sac]->defense_magique << endl ;
            cout << endl << spam_space( 20 ) << "chance d\'esquive : " << this->sac[place_sac]->esquive << endl ;
            cout << endl << spam_space( 20 ) << "chance de critique : " << this->sac[place_sac]->chance << endl ;
            spam_endl( 5 ) ;
            cout << endl << spam_space( 10 ) << "inventaire :" << spam_space( 30 ) << "retour : espace" ;
            spam_endl( 2 ) ;
            for ( int p = 0 ; p < this->slot_objets ; p++ )
            {
                cout << spam_space( 10 ) << p+1 << " : " << this->sac[p]->nom_equipement << endl ;
            }
        }
        spam_endl( 10 ) ;
        choix_objet = _getch() ;
        while ( ( choix_objet != 32 && choix_objet != 49 && choix_objet != 50 && choix_objet != 51 && choix_objet != 52 && choix_objet != 53 && choix_objet != 54  ) || this->slot_objets+48 < choix_objet )
        {
            choix_objet = _getch() ;
        }
        switch ( choix_objet )
        {
            case 49 :
                place_sac = 0 ;
                break ;
            case 50 :
                place_sac = 1 ;
                break ;
            case 51 :
                place_sac = 2 ;
                break ;
            if ( this->slot_objets > 3 )
            {
                case 52 :
                    place_sac = 3 ;
                    break ;
                if ( this->slot_objets == 6 )
                {
                    case 53 :
                        place_sac = 4 ;
                        break ;
                    case 54 :
                        place_sac = 5 ;
                        break ;
                }
            }
        }
    }while ( choix_objet != 32 ) ;
}

void Personnages::inventaire( Piece *salle , Personnages *perso_fictif )
{
    int action_inventaire ;
    do
    {
        spam_endl( 10 ) ;
        cout << spam_space( 10 ) << "objet equiper :" ;
        spam_endl( 2 ) ;
        cout << spam_space( 10 ) << "armes :" << spam_space( 46 ) << "utiliser : u" << endl ;
        for ( int i = 0 ; i < this->slot_armes ; i++ )
        {
            cout << spam_space( 10 ) << this->stuff_arme[i]->nom_equipement << endl ;
        }
        cout << endl << spam_space( 10 ) << "accessoires :" << spam_space( 40 ) << "poser par terre : t" << endl ;
        for ( int j = 0 ; j < this->slot_accessoires ; j++ )
        {
            cout << spam_space( 10 ) << this->stuff_accessoire[j]->nom_equipement << endl ;
        }
        cout << endl << spam_space( 10 ) << "casque :" << spam_space( 45 ) << "equiper : e" << endl ;
        for ( int k = 0 ; k < this->slot_casques ; k++ )
        {
            cout << spam_space( 10 ) << this->stuff_casque[k]->nom_equipement << endl ;
        }
        cout << endl << spam_space( 10 ) << "plastron :" << spam_space( 43 ) << "ramasser : r" << endl ;
        for ( int l = 0 ; l < this->slot_plastron ; l++ )
        {
            cout << spam_space( 10 ) << this->stuff_plastron[l]->nom_equipement << endl ;
        }
        cout << endl << spam_space( 10 ) << "bottes :" << spam_space( 45 ) << "statistiques du personnage : c" << endl ;
        for ( int m = 0 ; m < this->slot_bottes ; m++ )
        {
            cout << spam_space( 10 ) << this->stuff_botte[m]->nom_equipement << endl ;
        }
        cout << endl << spam_space( 10 ) << "jambiere :" << spam_space( 43 ) << "statistiques objet : s" << endl ;
        for ( int n = 0 ; n < this->slot_jambieres ; n++ )
        {
            cout << spam_space( 10 ) << this->stuff_jambiere[n]->nom_equipement << endl ;
        }
        cout << endl << spam_space( 10 ) << "gantelets :" << spam_space( 42 ) << "fermer inventaire : espace" << endl ;
        for ( int o = 0 ; o < this->slot_gantelets ; o++ )
        {
            cout << spam_space( 10 ) << this->stuff_gantelets[o]->nom_equipement << endl ;
        }
        spam_endl( 5 ) ;
        cout << endl << spam_space( 10 ) << "inventaire :" ;
        spam_endl( 2 ) ;
        for ( int p = 0 ; p < this->slot_objets ; p++ )
        {
            cout << spam_space( 10 ) << this->sac[p]->nom_equipement << endl ;
        }
        spam_endl( 5 ) ;
        cout << spam_space( 10 ) + "objet dans la piece :" << endl << endl << spam_space( 10 ) + salle->nom_arme_et_armure ;
        cout << endl  << spam_space( 10 ) + salle->nom_accessoire << endl << spam_space( 10 ) + salle->nom_potion << endl ;
        cout << spam_space( 10 ) + salle->nom_poison_et_tp_et_parchemin << endl << spam_space( 10 ) + salle->nom_piege ;
        spam_endl( 5 ) ;
        action_inventaire = _getch() ;
        while ( action_inventaire != 32 && action_inventaire != 99 && action_inventaire != 101 && action_inventaire != 114 && action_inventaire != 115 && action_inventaire != 116 && action_inventaire != 117 )
        {
            action_inventaire = _getch() ;
        }
        if ( action_inventaire == 99 )
        {
            this->caracteristiques_perso() ;
        }
        else if ( action_inventaire == 101 )
        {
            for ( int a = 0 ; a < this->slot_objets ; a ++ )
            {
                if ( this->sac[a]->nom_equipement != "vide" )
                {
                    this->equiper( salle ) ;
                    break ;
                }
            }
        }
        else if ( action_inventaire == 114 )
        {
            for ( int b = 0 ; b < this->slot_objets ; b ++ )
            {
                if ( this->sac[b]->nom_equipement == "vide" )
                {
                    this->ramasser_objet( salle ) ;
                    break ;
                }
            }
        }
        else if (action_inventaire == 115 )
        {
            for ( int c = 0 ; c < this->slot_objets ; c ++ )
            {
                if ( this->sac[c]->nom_equipement != "vide" )
                {
                    this->caracteristiques_objet() ;
                    break ;
                }
            }
        }
        else if ( action_inventaire == 116 )
        {
            for ( int d = 0 ; d < this->slot_objets ; d ++ )
            {
                if ( this->sac[d]->nom_equipement != "vide" )
                {
                    this->poser_objet( salle ) ;
                    break ;
                }
            }
        }
        else if ( action_inventaire == 117 )
        {
            for ( int e = 0 ; e < this->slot_objets ; e ++ )
            {
                if ( this->sac[e]->type_equipement_objet == "objet" )
                {
                    this->utiliser_objet( salle , perso_fictif ) ;
                    break ;
                }
            }
        }
    }while ( action_inventaire != 32 ) ;
}

Moine::Moine()
{
    //initialisation du personnage de type moine
    pv = 20 ;
    max_pv = 20 ;
    esquive = 25 ;
    chance = 25 ;
    force = 2 ;
    magie = 3 ;
    defense_physique = 1 ;
    defense_magique = 2 ;
    slot_armes = 0 ;
    slot_accessoires = 4 ;
    slot_casques = 0 ;
    slot_plastron = 0 ;
    slot_bottes = 0 ;
    slot_jambieres = 1 ;
    slot_gantelets = 1 ;
    slot_objets = 4 ;
    for ( int i = 0 ; i < slot_objets ; i++ )
    {
        sac[i] = new Vide() ;
    }
    for ( int j = 0 ; j < slot_armes ; j++ )
    {
        stuff_arme[j] = new Vide() ;
    }
    for ( int j = 0 ; j < slot_accessoires ; j++ )
    {
        stuff_accessoire[j] = new Vide() ;
    }
    for ( int j = 0 ; j < slot_casques ; j++ )
    {
        stuff_casque[j] = new Vide() ;
    }
    for ( int j = 0 ; j < slot_plastron ; j++ )
    {
        stuff_plastron[j] = new Vide() ;
    }
    for ( int j = 0 ; j < slot_bottes ; j++ )
    {
        stuff_botte[j] = new Vide() ;
    }
    for ( int j = 0 ; j < slot_jambieres ; j++ )
    {
        stuff_jambiere[j] = new Vide() ;
    }
    for ( int j = 0 ; j < slot_gantelets ; j++ )
    {
        stuff_gantelets[j] = new Vide() ;
    }
    nom_personnage = "moine" ;
    position_x = 0 ;
    position_y = 0 ;
    sprite_L1 =  spam_space( 21 ) + "m" + spam_space( 19 ) ;
    sprite_L2 =  spam_space( 21 ) + "m" + spam_space( 19 ) ;
    sprite_L3 =  spam_space( 21 ) + "m" + spam_space( 19 ) ;
    sprite_L4 =  spam_space( 21 ) + "m" + spam_space( 19 ) ;
    sprite_L5 =  spam_space( 21 ) + "m" + spam_space( 19 ) ;
    sprite_L6 =  spam_space( 21 ) + "m" + spam_space( 19 ) ;
    sprite_L7 =  spam_space( 21 ) + "m" + spam_space( 19 ) ;
    sprite_L8 =  spam_space( 21 ) + "m" + spam_space( 19 ) ;
    sprite_L9 =  spam_space( 21 ) + "m" + spam_space( 19 ) ;
    sprite_L10 = spam_space( 21 ) + "m" + spam_space( 19 ) ;
    sprite_L11 = spam_space( 21 ) + "m" + spam_space( 19 ) ;
    sprite_L12 = spam_space( 21 ) + "m" + spam_space( 19 ) ;
    sprite_L13 = spam_space( 21 ) + "m" + spam_space( 19 ) ;
    sprite_L14 = spam_space( 21 ) + "m" + spam_space( 19 ) ;
    sprite_L15 = spam_space( 21 ) + "m" + spam_space( 19 ) ;
    sprite_L16 = spam_space( 21 ) + "m" + spam_space( 19 ) ;
    sprite_L17 = spam_space( 21 ) + "m" + spam_space( 19 ) ;
    sprite_L18 = spam_space( 21 ) + "m" + spam_space( 19 ) ;
} ;

Moine::Moine( int difficulter )
{
    pv = difficulter * 6 + 20 ;
    max_pv = difficulter * 6 + 20 ;
    esquive = difficulter * 10 + 25 ;
    chance = difficulter * 10 + 25 ;
    force = difficulter * 2 + 2 ;
    magie = difficulter * 2 + 3 ;
    defense_physique = difficulter * 2 + 1 ;
    defense_magique = difficulter * 2 + 2 ;
    nom_personnage = "moine" ;
    position_x = 0 ;
    position_y = 0 ;
    sprite_L1 =  spam_space( 21 ) + "m" + spam_space( 19 ) ;
    sprite_L2 =  spam_space( 21 ) + "m" + spam_space( 19 ) ;
    sprite_L3 =  spam_space( 21 ) + "m" + spam_space( 19 ) ;
    sprite_L4 =  spam_space( 21 ) + "m" + spam_space( 19 ) ;
    sprite_L5 =  spam_space( 21 ) + "m" + spam_space( 19 ) ;
    sprite_L6 =  spam_space( 21 ) + "m" + spam_space( 19 ) ;
    sprite_L7 =  spam_space( 21 ) + "m" + spam_space( 19 ) ;
    sprite_L8 =  spam_space( 21 ) + "m" + spam_space( 19 ) ;
    sprite_L9 =  spam_space( 21 ) + "m" + spam_space( 19 ) ;
    sprite_L10 = spam_space( 21 ) + "m" + spam_space( 19 ) ;
    sprite_L11 = spam_space( 21 ) + "m" + spam_space( 19 ) ;
    sprite_L12 = spam_space( 21 ) + "m" + spam_space( 19 ) ;
    sprite_L13 = spam_space( 21 ) + "m" + spam_space( 19 ) ;
    sprite_L14 = spam_space( 21 ) + "m" + spam_space( 19 ) ;
    sprite_L15 = spam_space( 21 ) + "m" + spam_space( 19 ) ;
    sprite_L16 = spam_space( 21 ) + "m" + spam_space( 19 ) ;
    sprite_L17 = spam_space( 21 ) + "m" + spam_space( 19 ) ;
    sprite_L18 = spam_space( 21 ) + "m" + spam_space( 19 ) ;
} ;

Guerrier :: Guerrier()
{
    //initialisation du personnage de type guerrier
    pv = 15 ;
    max_pv = 15 ;
    esquive = 30 ;
    chance = 10 ;
    force = 5 ;
    magie = 1 ;
    defense_physique = 3 ;
    defense_magique = 0 ;
    slot_armes = 2 ;
    slot_accessoires = 0 ;
    slot_casques = 1 ;
    slot_plastron = 1 ;
    slot_bottes = 1 ;
    slot_jambieres = 1 ;
    slot_gantelets = 1 ;
    slot_objets = 3 ;
    for ( int i = 0 ; i < slot_objets ; i++ )
    {
        sac[i] = new Vide() ;
    }
    for ( int j = 0 ; j < slot_armes ; j++ )
    {
        stuff_arme[j] = new Vide() ;
    }
    for ( int j = 0 ; j < slot_accessoires ; j++ )
    {
        stuff_accessoire[j] = new Vide() ;
    }
    for ( int j = 0 ; j < slot_casques ; j++ )
    {
        stuff_casque[j] = new Vide() ;
    }
    for ( int j = 0 ; j < slot_plastron ; j++ )
    {
        stuff_plastron[j] = new Vide() ;
    }
    for ( int j = 0 ; j < slot_bottes ; j++ )
    {
        stuff_botte[j] = new Vide() ;
    }
    for ( int j = 0 ; j < slot_jambieres ; j++ )
    {
        stuff_jambiere[j] = new Vide() ;
    }
    for ( int j = 0 ; j < slot_gantelets ; j++ )
    {
        stuff_gantelets[j] = new Vide() ;
    }
    nom_personnage = "guerrier " ;
    position_x = 0 ;
    position_y = 0 ;
    sprite_L1 =  "                                        " ;
    sprite_L2 =  "         .                              " ;
    sprite_L3 =  "        / \\                             " ;
    sprite_L4 =  "        | |         wwww                " ;
    sprite_L5 =  "        | |        /n n \\               " ;
    sprite_L6 =  "        |.|       (  ^   )              " ;
    sprite_L7 =  "        |.|        \\ -- /               " ;
    sprite_L8 =  "        |:|      (--====--)             " ;
    sprite_L9 =  "        |:|    / /\\======/\\ \\ |`-,__,-'|" ;
    sprite_L10 = "      '--8--'_/ /  \\====/  \\ \\|        |" ;
    sprite_L11 = "        3|P____/   |====|   \\ |  )  (  |" ;
    sprite_L12 = "         O        /oooooo\\   \\| ((,,)) |" ;
    sprite_L13 = "                 (   /\\   )   | '|vv|' |" ;
    sprite_L14 = "                 |   )(   |    \\  Y.Y  /" ;
    sprite_L15 = "                 [_  ][  _]     \\  ~  / " ;
    sprite_L16 = "                 __||  ||__      \\,_,/  " ;
    sprite_L17 = "                (    ][    )            " ;
    sprite_L18 = "                                        " ;
} ;

Guerrier :: Guerrier( int difficulter )
{
    pv = difficulter * 6 + 15 ;
    max_pv = difficulter * 6 + 15 ;
    esquive = difficulter * 10 + 30 ;
    chance = difficulter * 10 + 10 ;
    force = difficulter * 2 + 5 ;
    magie = difficulter * 2 + 1 ;
    defense_physique = difficulter * 2 + 3 ;
    defense_magique = difficulter * 2 + 0 ;
    nom_personnage = "guerrier " ;
    position_x = 0 ;
    position_y = 0 ;
    sprite_L1 =  "                                        " ;
    sprite_L2 =  "         .                              " ;
    sprite_L3 =  "        / \\                             " ;
    sprite_L4 =  "        | |         wwww                " ;
    sprite_L5 =  "        | |        /n n \\               " ;
    sprite_L6 =  "        |.|       (  ^   )              " ;
    sprite_L7 =  "        |.|        \\ -- /               " ;
    sprite_L8 =  "        |:|      (--====--)             " ;
    sprite_L9 =  "        |:|    / /\\======/\\ \\ |`-,__,-'|" ;
    sprite_L10 = "      '--8--'_/ /  \\====/  \\ \\|        |" ;
    sprite_L11 = "        3|P____/   |====|   \\ |  )  (  |" ;
    sprite_L12 = "         O        /oooooo\\   \\| ((,,)) |" ;
    sprite_L13 = "                 (   /\\   )   | '|vv|' |" ;
    sprite_L14 = "                 |   )(   |    \\  Y.Y  /" ;
    sprite_L15 = "                 [_  ][  _]     \\  ~  / " ;
    sprite_L16 = "                 __||  ||__      \\,_,/  " ;
    sprite_L17 = "                (    ][    )            " ;
    sprite_L18 = "                                        " ;
} ;

Sorciere :: Sorciere()
{
    //initialisation du personnage de type sorciere
    pv = 10 ;
    max_pv = 10 ;
    esquive = 15 ;
    chance = 10 ;
    force = 1 ;
    magie = 5 ;
    defense_physique = 0 ;
    defense_magique = 3 ;
    slot_armes = 2 ;
    slot_accessoires = 1 ;
    slot_casques = 1 ;
    slot_plastron = 1 ;
    slot_bottes = 1 ;
    slot_jambieres = 0 ;
    slot_gantelets = 0 ;
    slot_objets = 4 ;
    for ( int i = 0 ; i < slot_objets ; i++ )
    {
        sac[i] = new Vide() ;
    }
    for ( int j = 0 ; j < slot_armes ; j++ )
    {
        stuff_arme[j] = new Vide() ;
    }
    for ( int j = 0 ; j < slot_accessoires ; j++ )
    {
        stuff_accessoire[j] = new Vide() ;
    }
    for ( int j = 0 ; j < slot_casques ; j++ )
    {
        stuff_casque[j] = new Vide() ;
    }
    for ( int j = 0 ; j < slot_plastron ; j++ )
    {
        stuff_plastron[j] = new Vide() ;
    }
    for ( int j = 0 ; j < slot_bottes ; j++ )
    {
        stuff_botte[j] = new Vide() ;
    }
    for ( int j = 0 ; j < slot_jambieres ; j++ )
    {
        stuff_jambiere[j] = new Vide() ;
    }
    for ( int j = 0 ; j < slot_gantelets ; j++ )
    {
        stuff_gantelets[j] = new Vide() ;
    }
    nom_personnage = "sorciere " ;
    position_x = 0 ;
    position_y = 0 ;
    sprite_L1 =  spam_space( 21 ) + "s" + spam_space( 19 ) ;
    sprite_L2 =  spam_space( 21 ) + "s" + spam_space( 19 ) ;
    sprite_L3 =  spam_space( 21 ) + "s" + spam_space( 19 ) ;
    sprite_L4 =  spam_space( 21 ) + "s" + spam_space( 19 ) ;
    sprite_L5 =  spam_space( 21 ) + "s" + spam_space( 19 ) ;
    sprite_L6 =  spam_space( 21 ) + "s" + spam_space( 19 ) ;
    sprite_L7 =  spam_space( 21 ) + "s" + spam_space( 19 ) ;
    sprite_L8 =  spam_space( 21 ) + "s" + spam_space( 19 ) ;
    sprite_L9 =  spam_space( 21 ) + "s" + spam_space( 19 ) ;
    sprite_L10 = spam_space( 21 ) + "s" + spam_space( 19 ) ;
    sprite_L11 = spam_space( 21 ) + "s" + spam_space( 19 ) ;
    sprite_L12 = spam_space( 21 ) + "s" + spam_space( 19 ) ;
    sprite_L13 = spam_space( 21 ) + "s" + spam_space( 19 ) ;
    sprite_L14 = spam_space( 21 ) + "s" + spam_space( 19 ) ;
    sprite_L15 = spam_space( 21 ) + "s" + spam_space( 19 ) ;
    sprite_L16 = spam_space( 21 ) + "s" + spam_space( 19 ) ;
    sprite_L17 = spam_space( 21 ) + "s" + spam_space( 19 ) ;
    sprite_L18 = spam_space( 21 ) + "s" + spam_space( 19 ) ;
} ;

Sorciere :: Sorciere( int difficulter )
{
    pv = difficulter * 6 + 10 ;
    max_pv = difficulter * 6 + 10 ;
    esquive = difficulter * 10 + 15 ;
    chance = difficulter * 10 + 10 ;
    force = difficulter * 2 + 1 ;
    magie = difficulter * 2 + 5 ;
    defense_physique = difficulter * 2 + 0 ;
    defense_magique = difficulter * 2 + 3 ;
    nom_personnage = "sorciere " ;
    position_x = 0 ;
    position_y = 0 ;
    sprite_L1 =  spam_space( 21 ) + "s" + spam_space( 19 ) ;
    sprite_L2 =  spam_space( 21 ) + "s" + spam_space( 19 ) ;
    sprite_L3 =  spam_space( 21 ) + "s" + spam_space( 19 ) ;
    sprite_L4 =  spam_space( 21 ) + "s" + spam_space( 19 ) ;
    sprite_L5 =  spam_space( 21 ) + "s" + spam_space( 19 ) ;
    sprite_L6 =  spam_space( 21 ) + "s" + spam_space( 19 ) ;
    sprite_L7 =  spam_space( 21 ) + "s" + spam_space( 19 ) ;
    sprite_L8 =  spam_space( 21 ) + "s" + spam_space( 19 ) ;
    sprite_L9 =  spam_space( 21 ) + "s" + spam_space( 19 ) ;
    sprite_L10 = spam_space( 21 ) + "s" + spam_space( 19 ) ;
    sprite_L11 = spam_space( 21 ) + "s" + spam_space( 19 ) ;
    sprite_L12 = spam_space( 21 ) + "s" + spam_space( 19 ) ;
    sprite_L13 = spam_space( 21 ) + "s" + spam_space( 19 ) ;
    sprite_L14 = spam_space( 21 ) + "s" + spam_space( 19 ) ;
    sprite_L15 = spam_space( 21 ) + "s" + spam_space( 19 ) ;
    sprite_L16 = spam_space( 21 ) + "s" + spam_space( 19 ) ;
    sprite_L17 = spam_space( 21 ) + "s" + spam_space( 19 ) ;
    sprite_L18 = spam_space( 21 ) + "s" + spam_space( 19 ) ;
} ;

Amazone :: Amazone()
{
    //initialisation du personnage de type amazone
    pv = 12 ;
    max_pv = 12 ;
    esquive = 35 ;
    chance = 15 ;
    force = 4 ;
    magie = 2 ;
    defense_physique = 2 ;
    defense_magique = 1 ;
    slot_armes = 1 ;
    slot_accessoires = 3 ;
    slot_casques = 0 ;
    slot_plastron = 0 ;
    slot_bottes = 1 ;
    slot_jambieres = 1 ;
    slot_gantelets = 1 ;
    slot_objets = 6 ;
    for ( int i = 0 ; i < slot_objets ; i++ )
    {
        sac[i] = new Vide() ;
    }
    for ( int j = 0 ; j < slot_armes ; j++ )
    {
        stuff_arme[j] = new Vide() ;
    }
    for ( int j = 0 ; j < slot_accessoires ; j++ )
    {
        stuff_accessoire[j] = new Vide() ;
    }
    for ( int j = 0 ; j < slot_casques ; j++ )
    {
        stuff_casque[j] = new Vide() ;
    }
    for ( int j = 0 ; j < slot_plastron ; j++ )
    {
        stuff_plastron[j] = new Vide() ;
    }
    for ( int j = 0 ; j < slot_bottes ; j++ )
    {
        stuff_botte[j] = new Vide() ;
    }
    for ( int j = 0 ; j < slot_jambieres ; j++ )
    {
        stuff_jambiere[j] = new Vide() ;
    }
    for ( int j = 0 ; j < slot_gantelets ; j++ )
    {
        stuff_gantelets[j] = new Vide() ;
    }
    nom_personnage = "amazone" ;
    position_x = 0 ;
    position_y = 0 ;
    sprite_L1 =  "               www                      " ;
    sprite_L2 =  "              /n n\\        /\\           " ;
    sprite_L3 =  "              |/^\\|       /  \\          " ;
    sprite_L4 =  "              | , |       ^||^          " ;
    sprite_L5 =  "               \\_/         ||           " ;
    sprite_L6 =  "               _U_         ||           " ;
    sprite_L7 =  "             /`   `''-----'P3           " ;
    sprite_L8 =  "            / |. .|''-----'||           " ;
    sprite_L9 =  "            \\'|   |        ||           " ;
    sprite_L10 = "             \\|   |        ||           " ;
    sprite_L11 = "              E   |        ||           " ;
    sprite_L12 = "             /#####\\       ||           " ;
    sprite_L13 = "             /#####\\       ||           " ;
    sprite_L14 = "               |||         ||           " ;
    sprite_L15 = "               |||         ||           " ;
    sprite_L16 = "               |||         ||           " ;
    sprite_L17 = "               |||         ||           " ;
    sprite_L18 = "              molom        Ll           " ;
} ;

Amazone :: Amazone( int difficulter )
{
    pv = difficulter * 6 + 12 ;
    max_pv = difficulter * 6 + 12 ;
    esquive = difficulter * 10 + 35 ;
    chance = difficulter * 10 + 15 ;
    force = difficulter * 2 + 4 ;
    magie = difficulter * 2 + 2 ;
    defense_physique = difficulter * 2 + 2 ;
    defense_magique = difficulter * 2 + 1 ;
    position_x = 0 ;
    position_y = 0 ;
    nom_personnage = "amazone" ;
    sprite_L1 =  "               www                      " ;
    sprite_L2 =  "              /n n\\        /\\           " ;
    sprite_L3 =  "              |/^\\|       /  \\          " ;
    sprite_L4 =  "              | , |       ^||^          " ;
    sprite_L5 =  "               \\_/         ||           " ;
    sprite_L6 =  "               _U_         ||           " ;
    sprite_L7 =  "             /`   `''-----'P3           " ;
    sprite_L8 =  "            / |. .|''-----'||           " ;
    sprite_L9 =  "            \\'|   |        ||           " ;
    sprite_L10 = "             \\|   |        ||           " ;
    sprite_L11 = "              E   |        ||           " ;
    sprite_L12 = "             /#####\\       ||           " ;
    sprite_L13 = "             /#####\\       ||           " ;
    sprite_L14 = "               |||         ||           " ;
    sprite_L15 = "               |||         ||           " ;
    sprite_L16 = "               |||         ||           " ;
    sprite_L17 = "               |||         ||           " ;
    sprite_L18 = "              molom        Ll           " ;
} ;

#endif // perso_cpp
