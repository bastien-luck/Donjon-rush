#ifndef dj_h
#define dj_h

#include <iostream>
#include "Equipement.h"

class Personnages ;
class Moine ;
class Guerrier ;
class Sorciere ;
class Amazone ;
class Piege ;


using namespace std ;


class Piece //: Donjon
{
public :
    //variable
    int chance_loot_premier_slot ;
    int chance_loot_second_slot ;
    int chance_loot_troisieme_slot ;
    int chance_loot_quatrieme_slot ;
    int chance_loot_sixieme_slot ;
    int type_arme_loot ;
    int type_armure_loot ;
    int type_accessoire_loot ;
    int type_poison_et_tp_loot ;
    int type_parchemin_loot ;
    int type_piege_loot ;
    string icon_arme_et_armure ;
    string icon_accessoire ;
    string icon_potion ;
    string icon_poison_et_tp_et_parchemin ;
    string icon_perso_et_piege_actif ;
    string icon_piege ;
    string nom_arme_et_armure ;
    string nom_accessoire ;
    string nom_potion ;
    string nom_poison_et_tp_et_parchemin ;
    string nom_piege ;
    string nom_piege_actif ;
    string passage_perso_utiliser ;
    string espace_premier_slot ;
    string espace_second_slot ;
    string espace_troisieme_slot ;
    string espace_quatrieme_slot ;
    string espace_sixieme_slot ;
    bool piece_du_coffre ;
    int numero_objet_premier_slot ;
    int numero_objet_second_slot ;
    int numero_objet_troisieme_slot ;
    int numero_objet_quatrieme_slot ;
    int numero_objet_sixieme_slot ;

public :
    //méthodes
    Piege trap ;
    Equipement loot() ;

public :
    //constructeur
    Piece() ;
    ~Piece(){} ;
} ;


#endif // dj_h
