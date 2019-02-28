#ifndef fonc_glob_cpp
#define fonc_glob_cpp

#include <iostream>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <sstream>
//#include "gestion_fenetre.h"
#include "Personnages.h"
#include "Equipement.h"
#include "donjon.h"
#include "fonction_globale.h"

using namespace std;

int spam_endl( int nb_saut )
{
    for ( int i = 0 ; i < nb_saut ; i++ )
    {
        cout << endl ;
    }
    return 0 ;
}

string spam_space( int nb_space )
{
    string temp = "" ;
    for ( int i = 0 ; i < nb_space ; i++ )
    {
        temp += " " ;
    }
    return temp ;
}

string intToString( int z ) //converti un int en string
{
     ostringstream oss ;
     oss << z ;
     return oss.str() ;
}

int logo()
{
    cout << spam_space( 51 ) << "                              .___.                                " << endl ;
    cout << spam_space( 51 ) << "          /)               ,-^     ^-.                             " << endl ;
    cout << spam_space( 51 ) << "         //               /           \\                           " << endl ;
    cout << spam_space( 51 ) << ".-------| |--------------/  __     __  \\-------------------.__    " << endl ;
    cout << spam_space( 51 ) << "|WMWMWMW| |>>>>>>>>>>>>> | />>\\   />>\\ |>>>>>>>>>>>>>>>>>>>>>>:> " << endl ;
    cout << spam_space( 51 ) << "`-------| |--------------| \\__/   \\__/ |-------------------'^^   " << endl ;
    cout << spam_space( 51 ) << "         \\\\               \\    /|\\    /                        " << endl ;
    cout << spam_space( 51 ) << "          \\)               \\   \\_/   /                          " << endl ;
    cout << spam_space( 51 ) << "                            |       |                              " << endl ;
    cout << spam_space( 51 ) << "                            |+H+H+H+|                              " << endl ;
    cout << spam_space( 51 ) << "                            \\       /                             " << endl ;
    cout << spam_space( 51 ) << "                             ^-----^                               " << endl ;
    return 0 ;
}

void init_plateau_jeu( Piece *playground[10][10] )
{
    int pos_y_fin = rand()%10 ;
    int pos_x_fin = rand()%10 ;
    for ( int i = 0 ; i < 10 ; i++ )
    {
        for ( int j = 0 ; j < 10 ; j++ )
        {
            playground[i][j] = new Piece() ;
        }
    }
    playground[0][0]->icon_perso_et_piege_actif = "X" ;
    playground[0][0]->passage_perso_utiliser = "oui" ;
    playground[pos_y_fin][pos_x_fin]->piece_du_coffre = true ;
}

string affichage_donjon( Piece *playground[10][10] , Personnages *ut )
{
    string dj = "" ;
    for ( int i = 0 ; i <= 30 ; i++ )
    {
        dj += spam_space( 10 ) ;
        for ( int j = 0 ; j < 10 ; j++ )
        {
            switch ( i )
            {
                case 0 :
                case 3 :
                case 6 :
                case 9 :
                case 12 :
                case 15 :
                case 18 :
                case 21 :
                case 24 :
                case 27 :
                case 30 :
                    if ( j == 0 )
                    {
                        if ( i == 0 )
                        {
                            dj += " _______________________________________"  ;
                        }
                        else
                        {
                            dj += "|___|___|___|___|___|___|___|___|___|___" ;
                        }
                    }
                    break ;
                case 1 :
                case 4 :
                case 7 :
                case 10 :
                case 13 :
                case 16 :
                case 19 :
                case 22 :
                case 25 :
                case 28 :
                    if ( playground[i*10/30][j]->passage_perso_utiliser == "oui" )
                    {
                        dj += "|" + playground[i*10/30][j]->icon_arme_et_armure + playground[i*10/30][j]->icon_accessoire + playground[i*10/30][j]->icon_potion ;
                    }
                    else
                    {
                        dj += "|   " ;
                    }
                    break ;
                case 2 :
                case 5 :
                case 8 :
                case 11 :
                case 14 :
                case 17 :
                case 20 :
                case 23 :
                case 26 :
                case 29 :
                    if ( playground[i*10/30][j]->passage_perso_utiliser == "oui" )
                    {
                        dj += "|" + playground[i*10/30][j]->icon_poison_et_tp_et_parchemin + playground[i*10/30][j]->icon_perso_et_piege_actif + playground[i*10/30][j]->icon_piege ;
                    }
                    else
                    {
                        dj += "|   " ;
                    }
                    break ;
            }
        }
        if ( i != 0 )
        {
            dj += "|" + spam_space( 6 ) ;
        }
        switch ( i )
        {
            case 1 :
                dj += "objet dans la piece :" ;
                break ;
            case 5 :
                if ( playground[ut->position_y][ut->position_x]->icon_arme_et_armure != " " )
                {
                    dj += playground[ut->position_y][ut->position_x]->nom_arme_et_armure ;
                }
                break ;
            case 9 :
                if ( playground[ut->position_y][ut->position_x]->icon_accessoire != " " )
                {
                    dj += playground[ut->position_y][ut->position_x]->nom_accessoire ;
                }
                break ;
            case 13 :
                if ( playground[ut->position_y][ut->position_x]->icon_potion != " " )
                {
                    dj += playground[ut->position_y][ut->position_x]->nom_potion ;
                }
                break ;
            case 17 :
                if ( playground[ut->position_y][ut->position_x]->icon_poison_et_tp_et_parchemin != " " )
                {
                    dj += playground[ut->position_y][ut->position_x]->nom_poison_et_tp_et_parchemin ;
                }
                break ;
            case 21 :
                if ( playground[ut->position_y][ut->position_x]->icon_piege != " " )
                {
                    dj += playground[ut->position_y][ut->position_x]->nom_piege ;
                }
                break ;
        }
        dj+= "\n" ;
    }
    return dj ;
}

void verification_type_equipement( Personnages *ut , int choix_equipement , int *compteur_accessoire , int *compteur_arme )
{
    if ( *compteur_arme < 0 || *compteur_arme > ut->slot_armes-1 )
    {
        *compteur_arme = 0 ;
    }
    if ( *compteur_accessoire < 0 || *compteur_accessoire > ut->slot_accessoires-1 )
    {
        *compteur_accessoire = 0 ;
    }
    Equipement *stockage ;
    Equipement *stockage_bis ;
    if ( ut->sac[choix_equipement]->place_arme == 1 && ut->slot_armes >= 1 )
    {
        stockage = ut->stuff_arme[*compteur_arme] ;
        ut->stuff_arme[*compteur_arme] = ut->sac[choix_equipement] ;
        ut->sac[choix_equipement] = stockage ;
        *compteur_arme  = *compteur_arme + 1 ;
    }
    else if ( ut->sac[choix_equipement]->place_arme == 2 && ut->slot_armes == 2 )
    {
        for ( int i = 0 ; i < ut->slot_objets ; i ++ )
        {
            if ( ut->sac[i]->nom_equipement == "vide" || ut->stuff_arme[0]->nom_equipement == "vide" || ut->stuff_arme[1]->nom_equipement == "vide" )
            {
                stockage = ut->stuff_arme[0] ;
                ut->stuff_arme[0] = ut->sac[choix_equipement] ;
                ut->sac[choix_equipement] = stockage ;
                if ( ut->stuff_arme[1]->nom_equipement != "vide" )
                {
                    stockage_bis = ut->stuff_arme[1] ;
                    ut->stuff_arme[1] = ut->sac[i] ;
                    ut->sac[i] = stockage_bis ;
                }
                *compteur_arme = 0 ;
                break ;
            }
        }
    }
    else if ( ut->sac[choix_equipement]->type_equipement == "accessoire" && ut->slot_accessoires != 0 )
    {
        stockage = ut->stuff_accessoire[*compteur_accessoire] ;
        ut->stuff_accessoire[*compteur_accessoire] = ut->sac[choix_equipement] ;
        ut->sac[choix_equipement] = stockage ;
        *compteur_accessoire = *compteur_accessoire + 1 ;
    }
    else if ( ut->sac[choix_equipement]->sous_type_equipement == "casque" && ut->slot_casques != 0 )
    {
        stockage = ut->stuff_casque[0] ;
        ut->stuff_casque[0] = ut->sac[choix_equipement] ;
        ut->sac[choix_equipement] = stockage ;
    }
    else if ( ut->sac[choix_equipement]->sous_type_equipement == "plastron" && ut->slot_plastron != 0 )
    {
        stockage = ut->stuff_plastron[0] ;
        ut->stuff_plastron[0] = ut->sac[choix_equipement] ;
        ut->sac[choix_equipement] = stockage ;
    }
    else if ( ut->sac[choix_equipement]->sous_type_equipement == "bottes" && ut->slot_bottes != 0 )
    {
        stockage = ut->stuff_botte[0] ;
        ut->stuff_botte[0] = ut->sac[choix_equipement] ;
        ut->sac[choix_equipement] = stockage ;
    }
    else if ( ut->sac[choix_equipement]->sous_type_equipement == "jambieres" && ut->slot_jambieres != 0 )
    {
        stockage = ut->stuff_jambiere[0] ;
        ut->stuff_jambiere[0] = ut->sac[choix_equipement] ;
        ut->sac[choix_equipement] = stockage ;
    }
    else if ( ut->sac[choix_equipement]->nom_equipement == "poings du dragon" )
    {
        if ( ut->nom_personnage == "moine" )
        {
            stockage = ut->stuff_gantelets[0] ;
            ut->stuff_gantelets[0] = ut->sac[choix_equipement] ;
            ut->sac[choix_equipement] = stockage ;
        }
    }
    else if ( ut->sac[choix_equipement]->sous_type_equipement == "gantelets" && ut->slot_gantelets != 0 )
    {
        stockage = ut->stuff_gantelets[0] ;
        ut->stuff_gantelets[0] = ut->sac[choix_equipement] ;
        ut->sac[choix_equipement] = stockage ;
    }
}

void placement_ia( Personnages *ia1 , Personnages *ia2 , Personnages *ia3 )
{
    while ( ia1->position_x == 0 && ia1->position_y == 0 )
    {
        ia1->position_x = rand()%10 ;
        ia1->position_y = rand()%10 ;
    }
    while ( ia2->position_x == 0 && ia2->position_y == 0 )
    {
        ia2->position_x = rand()%10 ;
        ia2->position_y = rand()%10 ;
    }
    while ( ia3->position_x == 0 && ia3->position_y == 0 )
    {
        ia3->position_x = rand()%10 ;
        ia3->position_y = rand()%10 ;
    }
}

void verification_place_sol( Personnages *ut , Piece *salles , string type_objet , int emplacement_sac )
{
    if ( ( type_objet == "arme" || type_objet == "armure" ) && salles->espace_premier_slot == "vide" )
    {
        salles->icon_arme_et_armure = ut->sac[emplacement_sac]->icon_arme_et_armure ;
        salles->nom_arme_et_armure = ut->sac[emplacement_sac]->nom_equipement ;
        salles->espace_premier_slot = "plein" ;
        salles->numero_objet_premier_slot = ut->sac[emplacement_sac]->numero_objet_premier_slot ;
        delete ut->sac[emplacement_sac] ;
        ut->sac[emplacement_sac] = new Vide() ;
    }
    else if ( type_objet == "accessoire" && salles->espace_second_slot == "vide" )
    {
        salles->icon_accessoire = ut->sac[emplacement_sac]->icon_accessoire ;
        salles->nom_accessoire = ut->sac[emplacement_sac]->nom_equipement ;
        salles->espace_second_slot = "plein" ;
        salles->numero_objet_second_slot = ut->sac[emplacement_sac]->numero_objet_second_slot ;
        delete ut->sac[emplacement_sac] ;
        ut->sac[emplacement_sac] = new Vide() ;
    }
    else if ( type_objet == "potion" && salles->espace_troisieme_slot == "vide" )
    {
        salles->icon_potion = ut->sac[emplacement_sac]->icon_potion ;
        salles->nom_potion = ut->sac[emplacement_sac]->nom_equipement ;
        salles->espace_troisieme_slot = "plein" ;
        salles->numero_objet_troisieme_slot = ut->sac[emplacement_sac]->numero_objet_troisieme_slot ;
        delete ut->sac[emplacement_sac] ;
        ut->sac[emplacement_sac] = new Vide() ;
    }
    else if ( ( type_objet == "parchemin" || type_objet == "cle teleportation" || type_objet == "poison") && salles->espace_quatrieme_slot == "vide" )
    {
        salles->icon_poison_et_tp_et_parchemin = ut->sac[emplacement_sac]->icon_poison_et_tp_et_parchemin ;
        salles->nom_poison_et_tp_et_parchemin = ut->sac[emplacement_sac]->nom_equipement ;
        salles->espace_quatrieme_slot = "plein" ;
        salles->numero_objet_quatrieme_slot = ut->sac[emplacement_sac]->numero_objet_quatrieme_slot ;
        delete ut->sac[emplacement_sac] ;
        ut->sac[emplacement_sac] = new Vide() ;
    }
    else if ( type_objet == "piege" && salles->espace_sixieme_slot == "vide" )
    {
        salles->icon_piege = ut->sac[emplacement_sac]->icon_piege ;
        salles->nom_piege = ut->sac[emplacement_sac]->nom_equipement ;
        salles->espace_sixieme_slot = "plein" ;
        salles->numero_objet_sixieme_slot = ut->sac[emplacement_sac]->numero_objet_sixieme_slot ;
        delete ut->sac[emplacement_sac] ;
        ut->sac[emplacement_sac] = new Vide() ;
    }
}

void ramassage_objet( Personnages *ut , Piece *salles , int place_libre , int choix_objet )
{
    if ( choix_objet == 1 )
    {
        salles->icon_arme_et_armure = " " ;
        salles->espace_premier_slot = "vide" ;
        salles->nom_arme_et_armure = "" ;
        switch ( salles->numero_objet_premier_slot )
        {
            case 1 :
                ut->sac[place_libre] = new Epee_une_main_classique() ;
                break ;
            case 2 :
                ut->sac[place_libre] = new Epee_une_main_elementaire() ;
                break ;
            case 3 :
                ut->sac[place_libre] = new Petit_bouclier() ;
                break ;
            case 4 :
                ut->sac[place_libre] = new Grand_bouclier() ;
                break ;
            case 5 :
                ut->sac[place_libre] = new Epee_deux_mains_classique() ;
                break ;
            case 6 :
                ut->sac[place_libre] = new Epee_deux_mains_elementaire() ;
                break ;
            case 7 :
                ut->sac[place_libre] = new Sceptre_d_incantation() ;
                break ;
            case 8 :
                ut->sac[place_libre] = new Sceptre_de_combat() ;
                break ;
            case 9 :
                ut->sac[place_libre] = new Livre() ;
                break ;
            case 10 :
                ut->sac[place_libre] = new Boule_magique() ;
                break ;
            case 11 :
                ut->sac[place_libre] = new Baguette_de_mobilite() ;
                break ;
            case 12 :
                ut->sac[place_libre] = new Baguette_de_soin() ;
                break ;
            case 13 :
                ut->sac[place_libre] = new Lance_fine() ;
                break ;
            case 14 :
                ut->sac[place_libre] = new Lance_d_accro() ;
                break ;
            case 15 :
                ut->sac[place_libre] = new Sarbacane() ;
                break ;
            case 16 :
                ut->sac[place_libre] = new Bolas() ;
                break ;
            case 17 :
                ut->sac[place_libre] = new Heaume() ;
                break ;
            case 18 :
                ut->sac[place_libre] = new Chapeau() ;
                break ;
            case 19 :
                ut->sac[place_libre] = new Serre_tete() ;
                break ;
            case 20 :
                ut->sac[place_libre] = new Armure_lourde() ;
                break ;
            case 21 :
                ut->sac[place_libre] = new Armure_legere() ;
                break ;
            case 22 :
                ut->sac[place_libre] = new Robe() ;
                break ;
            case 23 :
                ut->sac[place_libre] = new Bottes_lourdes() ;
                break ;
            case 24 :
                ut->sac[place_libre] = new Chaussures() ;
                break ;
            case 25 :
                ut->sac[place_libre] = new Chaussons() ;
                break ;
            case 26 :
                ut->sac[place_libre] = new Jambieres_lourdes() ;
                break ;
            case 27 :
                ut->sac[place_libre] = new Jambieres_moyennes() ;
                break ;
            case 28 :
                ut->sac[place_libre] = new Jambieres_legeres() ;
                break ;
            case 29 :
                ut->sac[place_libre] = new Gantelets_offensifs() ;
                break ;
            case 30 :
                ut->sac[place_libre] = new Gantelets_lourds() ;
                break ;
            case 31 :
                ut->sac[place_libre] = new Gantelets_legers() ;
                break ;
        }
        salles->numero_objet_premier_slot = 0 ;
    }
    else if ( choix_objet == 2 )
    {
        salles->icon_accessoire = " " ;
        salles->espace_second_slot = "vide" ;
        salles->nom_accessoire = "" ;
        switch ( salles->numero_objet_second_slot )
        {
            case 1 :
                ut->sac[place_libre] = new Masque_a_gaz() ;
                break ;
            case 2 :
                ut->sac[place_libre] = new Crucifix() ;
                break ;
            case 3 :
                ut->sac[place_libre] = new Ceinture() ;
                break ;
            case 4 :
                ut->sac[place_libre] = new Bracelets() ;
                break ;
            case 5 :
                ut->sac[place_libre] = new Brassard() ;
                break ;

        }
        salles->numero_objet_second_slot = 0 ;
    }
    else if ( choix_objet == 3 )
    {
        salles->icon_potion = " " ;
        salles->espace_troisieme_slot = "vide" ;
        salles->nom_potion = "" ;
        switch ( salles->numero_objet_troisieme_slot )
        {
            case 1 :
                ut->sac[place_libre] = new Petites_potions() ;
                break ;
            case 2 :
                ut->sac[place_libre] = new Moyennes_potions() ;
                break ;
            case 3 :
                ut->sac[place_libre] = new Grandes_potions() ;
                break ;
        }
        salles->numero_objet_troisieme_slot = 0 ;
    }
    else if ( choix_objet == 4 )
    {
        salles->icon_poison_et_tp_et_parchemin = " " ;
        salles->espace_quatrieme_slot = "vide" ;
        salles->nom_poison_et_tp_et_parchemin = "" ;
        switch ( salles->numero_objet_quatrieme_slot )
        {
            case 1 :
                ut->sac[place_libre] = new Fioles() ;
                break ;
            case 2 :
                ut->sac[place_libre] = new Enduit() ;
                break ;
            case 3 :
                ut->sac[place_libre] = new Cle_teleportation() ;
                break ;
            case 4 :
                ut->sac[place_libre] = new Feu() ;
                break ;
            case 5 :
                ut->sac[place_libre] = new Soin() ;
                break ;
            case 6 :
                ut->sac[place_libre] = new Buff() ;
                break ;
            case 7 :
                ut->sac[place_libre] = new Terre() ;
                break ;
        }
        salles->numero_objet_quatrieme_slot = 0 ;
    }
    else if ( choix_objet == 5 )
    {
        salles->icon_piege = " " ;
        salles->espace_sixieme_slot = "vide" ;
        salles->nom_piege = "" ;
        switch ( salles->numero_objet_sixieme_slot )
        {
            case 1 :
                ut->sac[place_libre] = new Runes() ;
                break ;
            case 2 :
                ut->sac[place_libre] = new Tourelles() ;
                break ;
            case 3 :
                ut->sac[place_libre] = new Changement_etat() ;
                break ;
        }
        salles->numero_objet_sixieme_slot = 0 ;
    }
}

void utilisation_objet( Personnages *ut , int place_objet , Personnages *ennemi , Piece *salle )
{
    int chance_critique = rand()%101 ;
    bool objet_utiliser = false ;
    if ( ut->sac[place_objet]->type_equipement == "potion" )
    {
        if ( ut->pv + ut->sac[place_objet]->pv < ut->max_pv )
        {
            cout << "        " << "vous recuperez " << ut->sac[place_objet]->pv << " pv" ;
            ut->pv += ut->sac[place_objet]->pv ;
        }
        else
        {
            cout << "        " << "vous recuperez " << ut->max_pv - ut->pv << " pv" ;
            ut->pv = ut->max_pv ;
        }
        objet_utiliser = true ;
    }
    else if ( ut->sac[place_objet]->type_equipement == "parchemin" )
    {
        if ( ut->sac[place_objet]->type_degat == "soin" )
        {
            objet_utiliser = true ;
            spam_endl( 10 ) ;
            if ( ut->pv + ut->magie + ut->sac[place_objet]->magie < ut->max_pv )
            {
                cout << "        " << "vous recuperez " << ut->sac[place_objet]->magie << " pv" ;
                ut->pv += ut->magie + ut->sac[place_objet]->magie ;
            }
            else
            {
                cout << "        " << "vous recuperez " << ut->max_pv - ut->pv << " pv" ;
                ut->pv = ut->max_pv ;
            }
        }
        else if ( ut->sac[place_objet]->type_degat == "physique" && ennemi->nom_personnage != "" )
        {
            objet_utiliser = true ;
            if ( ut->chance > chance_critique )
            {
                ennemi->pv -= ut->magie + ut->sac[place_objet]->magie ;
                cout << endl << "        " << "c\'est un coup critique !" << endl << "        " << ennemi->nom_personnage << " se fait ecraser par un gros rocher : -" << ut->magie + ut->sac[place_objet]->magie << " pv" << endl ;
            }
            else if ( ut->magie + ut->sac[place_objet]->magie > ennemi->defense_physique )
            {
                ennemi->pv -= ut->magie + ut->sac[place_objet]->magie - ennemi->defense_physique ;
                cout << endl << "        " << ennemi->nom_personnage << " se fait marteller par une pluie de pierre : -" << ut->magie + ut->sac[place_objet]->magie - ennemi->defense_physique << " pv" << endl ;
            }
            else
            {
                cout << endl << "        " << ennemi->nom_personnage << " est immuniser contre la chute de pierre " << endl ;
            }
        }
        else if ( ut->sac[place_objet]->type_degat == "magique" && ennemi->nom_personnage != "" )
        {
            objet_utiliser = true ;
            spam_endl( 10 ) ;
            if ( ennemi->chance > chance_critique )
            {
                ennemi->pv -= ut->magie + ut->sac[place_objet]->magie ;
                cout << endl << "        " << "c\'est un coup critique !" << endl << "        " << ennemi->nom_personnage << " est bruler au troisieme degres : -" << ut->magie + ut->sac[place_objet]->magie << " pv" << endl ;

            }
            else if ( ut->magie > ennemi->defense_magique )
            {
                ennemi->pv -= ut->magie + ut->sac[place_objet]->magie - ennemi->defense_magique ;
                cout << endl << "        " << ennemi->nom_personnage << " est fortement bruler : -" << ut->magie + ut->sac[place_objet]->magie - ennemi->defense_magique << " pv" << endl ;
            }
            else
            {
                cout << endl << "        " << ennemi->nom_personnage << " n\'a meme pas eu un coup de chaud " << endl ;
            }
        }
        else if ( ut->sac[place_objet]->type_degat == "buff" && ennemi->nom_personnage != "" )
        {
            objet_utiliser = true ;
            spam_endl( 10 ) ;
            switch ( rand()%4 )
            {
                case 0 :
                    ut->force += 1 ;
                    cout << "        " << "vous gagnez en force" ;
                    break ;
                case 1 :
                    ut->magie += 1 ;
                    cout << "        " << "vous gagnez en magie" ;
                    break ;
                case 2 :
                    ut->defense_physique += 1 ;
                    cout << "        " << "vous gagnez en defense physique" ;
                    break ;
                case 3 :
                    ut->defense_magique += 1 ;
                    cout << "        " << "vous gagnez en defense magique" ;
                    break ;
            }
        }
    }
    else if ( ut->sac[place_objet]->type_equipement == "piege" && ennemi->nom_personnage == "" )
    {
        objet_utiliser = true ;
        salle->icon_perso_et_piege_actif = "!" ;
        salle->nom_piege_actif = ut->sac[place_objet]->nom_equipement ;
    }
    else if ( ut->sac[place_objet]->type_equipement == "poison" && ennemi->nom_personnage != "" )
    {
        spam_endl( 10 ) ;
        cout << "        " << ut->nom_personnage << " empoisonne " << ennemi->nom_personnage << " en l\'aspergeant de poison" << endl ;
        ennemi->empoisonner = true ;
        objet_utiliser = true ;
    }
    if ( objet_utiliser == true )
    {
        delete ut->sac[place_objet] ;
        ut->sac[place_objet] = new Vide() ;
    }
}

#endif //fonc_glob_cpp
