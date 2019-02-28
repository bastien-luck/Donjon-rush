#ifndef dj_cpp
#define dj_cpp

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




Piece::Piece()
{
    chance_loot_premier_slot = 1 + rand()%100 ;
    chance_loot_second_slot = 1 + rand()%100 ;
    chance_loot_troisieme_slot = 1 + rand()%100 ;
    chance_loot_quatrieme_slot = 1 + rand()%100 ;
    chance_loot_sixieme_slot = 1 + rand()%100 ;
    type_arme_loot = rand()%16 ;
    type_armure_loot = rand()%15 ;
    type_accessoire_loot = rand()%5 ; //à amélioré
    type_piege_loot = rand()%3 ;
    type_poison_et_tp_loot = rand()%5 ;
    type_parchemin_loot = rand()%4 ;
    icon_arme_et_armure = " " ;
    icon_accessoire = " " ;
    icon_potion = " " ;
    icon_piege = " " ;
    icon_poison_et_tp_et_parchemin = " " ;
    icon_perso_et_piege_actif = " " ;
    nom_arme_et_armure = "" ;
    nom_accessoire = "" ;
    nom_potion = "" ;
    nom_poison_et_tp_et_parchemin = "" ;
    nom_piege = "" ;
    nom_piege_actif = "" ;
    passage_perso_utiliser = "non" ;
    espace_premier_slot = "vide" ;
    espace_second_slot = "vide" ;
    espace_troisieme_slot = "vide" ;
    espace_quatrieme_slot = "vide" ;
    espace_sixieme_slot = "vide" ;
    piece_du_coffre = false ;
    numero_objet_premier_slot = 0 ;
    numero_objet_second_slot = 0 ;
    numero_objet_troisieme_slot = 0 ;
    numero_objet_quatrieme_slot = 0 ;
    numero_objet_sixieme_slot = 0 ;

    if ( chance_loot_premier_slot <= 50 )
    {
        espace_premier_slot = "plein" ;
        switch ( type_arme_loot )
        {
            case 0 :
                {
                    numero_objet_premier_slot = 1 ;
                    nom_arme_et_armure = "epee de fer" ;
                    icon_arme_et_armure = "G" ;
                    break ;
                }
            case 1 :
                {
                    numero_objet_premier_slot = 2 ;
                    nom_arme_et_armure = "epee enflammee" ;
                    icon_arme_et_armure = "G" ;
                    break ;
                }
            case 2 :
                {
                    numero_objet_premier_slot = 3 ;
                    nom_arme_et_armure = "targe" ;
                    icon_arme_et_armure = "G" ;
                    break ;
                }
            case 3 :
                {
                    numero_objet_premier_slot = 4 ;
                    nom_arme_et_armure = "rempart" ;
                    icon_arme_et_armure = "G" ;
                    break ;
                }
            case 4 :
                {
                    numero_objet_premier_slot = 5 ;
                    nom_arme_et_armure = "epee lourde de fer" ;
                    icon_arme_et_armure = "G" ;
                    break ;
                }
            case 5 :
                {
                    numero_objet_premier_slot = 6 ;
                    nom_arme_et_armure = "epee lourde enflammee" ;
                    icon_arme_et_armure = "G" ;
                    break ;
                }
            case 6 :
                {
                    numero_objet_premier_slot = 7 ;
                    nom_arme_et_armure = "sceptre d'archimage" ;
                    icon_arme_et_armure = "S" ;
                    break ;
                }
            case 7 :
                {
                    numero_objet_premier_slot = 8 ;
                    nom_arme_et_armure = "baton de combat" ;
                    icon_arme_et_armure = "S" ;
                    break ;
                }
            case 8 :
                {
                    numero_objet_premier_slot = 9 ;
                    nom_arme_et_armure = "necronomicon" ;
                    icon_arme_et_armure = "S" ;
                    break ;
                }
            case 9 :
                {
                    numero_objet_premier_slot = 10 ;
                    nom_arme_et_armure = "boule de divination" ;
                    icon_arme_et_armure = "S" ;
                    break ;
                }
            case 10 :
                {
                    numero_objet_premier_slot = 11 ;
                    nom_arme_et_armure = "baguette rapide" ;
                    icon_arme_et_armure = "S" ;
                    break ;
                }
            case 11 :
                {
                    numero_objet_premier_slot = 12 ;
                    nom_arme_et_armure = "baguette de premier secour" ;
                    icon_arme_et_armure = "S" ;
                    break ;
                }
            case 12 :
                {
                    numero_objet_premier_slot = 13 ;
                    nom_arme_et_armure = "lance aiguisee" ;
                    icon_arme_et_armure = "A" ;
                    break ;
                }
            case 13 :
                {
                    numero_objet_premier_slot = 14 ;
                    nom_arme_et_armure = "harpon" ;
                    icon_arme_et_armure = "A" ;
                    break ;
                }
            case 14 :
                {
                    numero_objet_premier_slot = 15 ;
                    nom_arme_et_armure = "sarbacane empoisonnee" ;
                    icon_arme_et_armure = "A" ;
                    break ;
                }
            case 15 :
                {
                    numero_objet_premier_slot = 16 ;
                    nom_arme_et_armure = "bolas de chasse" ;
                    icon_arme_et_armure = "A" ;
                    break ;
                }
            default :
                break ;
        }
    }
    else
    {
        espace_premier_slot = "plein" ;
        switch( type_armure_loot )
        {
            case 0 :
                {
                    numero_objet_premier_slot = 17 ;
                    nom_arme_et_armure = "heaume de fer" ;
                    icon_arme_et_armure = "C" ;
                    break ;
                }
            case 1 :
                {
                    numero_objet_premier_slot = 18 ;
                    nom_arme_et_armure = "chapeau magique" ;
                    icon_arme_et_armure = "C" ;
                    break ;
                }
            case 2 :
                {
                    numero_objet_premier_slot = 19 ;
                    nom_arme_et_armure = "bandana" ;
                    icon_arme_et_armure = "C" ;
                    break ;
                }
            case 3 :
                {
                    numero_objet_premier_slot = 20 ;
                    nom_arme_et_armure = "plastron de fer" ;
                    icon_arme_et_armure = "P" ;
                    break ;
                }
            case 4 :
                {
                    numero_objet_premier_slot = 21 ;
                    nom_arme_et_armure = "armure de gladiateur" ;
                    icon_arme_et_armure = "P" ;
                    break ;
                }
            case 5 :
                {
                    numero_objet_premier_slot = 22 ;
                    nom_arme_et_armure = "robe de mage" ;
                    icon_arme_et_armure = "P" ;
                    break ;
                }
            case 6 :
                {
                    numero_objet_premier_slot = 23 ;
                    nom_arme_et_armure = "bottes en fer" ;
                    icon_arme_et_armure = "B" ;
                    break ;
                }
            case 7 :
                {
                    numero_objet_premier_slot = 24 ;
                    nom_arme_et_armure = "souliers du voyageur" ;
                    icon_arme_et_armure = "B" ;
                    break ;
                }
            case 8 :
                {
                    numero_objet_premier_slot = 25 ;
                    nom_arme_et_armure = "chaussons enchanteur" ;
                    icon_arme_et_armure = "B" ;
                    break ;
                }
            case 9 :
                {
                    numero_objet_premier_slot = 26 ;
                    nom_arme_et_armure = "jambiere de soldat" ;
                    icon_arme_et_armure = "J" ;
                    break ;
                }
            case 10 :
                {
                    numero_objet_premier_slot = 27 ;
                    nom_arme_et_armure = "jambiere de serenitee" ;
                    icon_arme_et_armure = "J" ;
                    break ;
                }
            case 11 :
                {
                    numero_objet_premier_slot = 28 ;
                    nom_arme_et_armure = "jambiere de peau" ;
                    icon_arme_et_armure = "J" ;
                    break ;
                }
            case 12 :
                {
                    numero_objet_premier_slot = 29 ;
                    nom_arme_et_armure = "poing du dragon" ;
                    icon_arme_et_armure = "g" ;
                    break ;
                }
            case 13 :
                {
                    numero_objet_premier_slot = 30 ;
                    nom_arme_et_armure = "gantelets imperial" ;
                    icon_arme_et_armure = "g" ;
                    break ;
                }
            case 14 :
                {
                    numero_objet_premier_slot = 31 ;
                    nom_arme_et_armure = "gants de soie" ;
                    icon_arme_et_armure = "g" ;
                    break ;
                }
            default :
                break ;
        }
    }
    if ( chance_loot_second_slot >= 25 && chance_loot_second_slot <= 75 )
    {
        espace_second_slot = "plein" ;
        switch ( type_accessoire_loot )
        {
            case 0 :
                {
                    numero_objet_second_slot = 1 ;
                    nom_accessoire = "masque a gaz" ;
                    icon_accessoire = "A" ;
                    break ;
                }
            case 1 :
                {
                    numero_objet_second_slot = 2 ;
                    nom_accessoire = "crucifix" ;
                    icon_accessoire = "A" ;
                    break ;
                }
            case 2 :
                {
                    numero_objet_second_slot = 3 ;
                    nom_accessoire = "ceinture" ;
                    icon_accessoire = "A" ;
                    break ;
                }
            case 3 :
                {
                    numero_objet_second_slot = 4 ;
                    nom_accessoire = "bracelets" ;
                    icon_accessoire = "A" ;
                    break ;
                }
            case 4 :
                {
                    numero_objet_second_slot = 5 ;
                    nom_accessoire = "brassard" ;
                    icon_accessoire = "A" ;
                    break ;
                }
        }
    }
    if ( chance_loot_troisieme_slot >= 0 && chance_loot_troisieme_slot <= 25 )
    {
        numero_objet_troisieme_slot = 1 ;
        espace_troisieme_slot = "plein" ;
        nom_potion = "petite potion" ;
        icon_potion = "p" ;
    }
    else if ( chance_loot_troisieme_slot >= 45 && chance_loot_troisieme_slot <= 55 )
    {
        numero_objet_troisieme_slot = 2 ;
        espace_troisieme_slot = "plein" ;
        nom_potion = "moyenne potion" ;
        icon_potion = "m" ;
    }
    else if ( chance_loot_troisieme_slot >= 75 && chance_loot_troisieme_slot <= 80 )
    {
        numero_objet_troisieme_slot = 3 ;
        espace_troisieme_slot = "plein" ;
        nom_potion = "grande potion" ;
        icon_potion = "g" ;
    }
    if ( chance_loot_quatrieme_slot >= 50 && chance_loot_quatrieme_slot <= 70 )
    {
        espace_quatrieme_slot = "plein" ;
        switch ( type_poison_et_tp_loot ) // 2 fois plus de chance de tombé sur les poisons
                {
                case 0 :
                case 1 :
                    {
                        numero_objet_quatrieme_slot = 1 ;
                        nom_poison_et_tp_et_parchemin = "fiole de poison" ;
                        icon_poison_et_tp_et_parchemin = "F" ;
                        break ;
                    }
                case 2 :
                case 3 :
                    {
                        numero_objet_quatrieme_slot = 2 ;
                        nom_poison_et_tp_et_parchemin = "enduit empoisonne" ;
                        icon_poison_et_tp_et_parchemin = "E" ;
                        break ;
                    }
                case 4 :
                    {
                        numero_objet_quatrieme_slot = 3 ;
                        nom_poison_et_tp_et_parchemin = "cle de teleportation" ;
                        icon_poison_et_tp_et_parchemin = "V" ;
                        break ;
                    }

                 }
    }
    else if ( chance_loot_quatrieme_slot <= 22 )
    {
        espace_quatrieme_slot = "plein" ;
        switch( type_parchemin_loot )
        {
            case 0 :
                {
                    numero_objet_quatrieme_slot = 4 ;
                    nom_poison_et_tp_et_parchemin = "parchemin bulant" ;
                    icon_poison_et_tp_et_parchemin = "S" ;
                    break ;
                }
            case 1 :
                {
                    numero_objet_quatrieme_slot = 5 ;
                    nom_poison_et_tp_et_parchemin = "parchemin de soin" ;
                    icon_poison_et_tp_et_parchemin = "S" ;
                    break ;
                }
            case 2 :
                {
                    numero_objet_quatrieme_slot = 6 ;
                    nom_poison_et_tp_et_parchemin = "parchemin de puissance" ;
                    icon_poison_et_tp_et_parchemin = "S" ;
                    break ;
                }
            case 3 :
                {
                    numero_objet_quatrieme_slot = 7 ;
                    nom_poison_et_tp_et_parchemin = "parchemin tellurique" ;
                    icon_poison_et_tp_et_parchemin = "S" ;
                    break ;
                }
        }
    }
    if ( chance_loot_sixieme_slot >= 23 && chance_loot_sixieme_slot <= 47 )
    {
        espace_sixieme_slot = "plein" ;
        switch ( type_piege_loot )
        {
            case 0 :
                {
                    numero_objet_sixieme_slot = 1 ;
                    nom_piege = "piege runique" ;
                    icon_piege = "T" ;
                    break ;
                }
            case 1 :
                {
                    numero_objet_sixieme_slot = 2 ;
                    nom_piege = "arbalette piegee" ;
                    icon_piege = "T" ;
                    break ;
                }
            case 2 :
                {
                    numero_objet_sixieme_slot = 3 ;
                    nom_piege = "piege incapacitant" ;
                    icon_piege = "T" ;
                    break ;
                }
        }
    }
} ;

#endif // dj_cpp
