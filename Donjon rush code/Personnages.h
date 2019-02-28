#ifndef perso_h
#define perso_h

#include <iostream>
#include "Equipement.h"
#include "donjon.h"


using namespace std ;

class Personnages
{
public :
    //variable
    int pv ;
    int max_pv ;
    int esquive ;
    int chance ;
    int force ;
    int magie ;
    int defense_physique ;
    int defense_magique ;
    int degat_brut ;
    int slot_armes ;
    int slot_accessoires ;
    int slot_casques ;
    int slot_plastron ;
    int slot_bottes ;
    int slot_jambieres ;
    int slot_gantelets ;
    int slot_objets ;
    Equipement * sac[6] ;
    Equipement * stuff_arme[2] ;
    Equipement * stuff_accessoire[4] ;
    Equipement * stuff_casque[1] ;
    Equipement * stuff_plastron[1] ;
    Equipement * stuff_botte[1] ;
    Equipement * stuff_jambiere[1] ;
    Equipement * stuff_gantelets[1] ;
    string nom_personnage ;
    int position_x ;
    int position_y ;
    bool empoisonner ;
    string sprite_L1 ;
    string sprite_L2 ;
    string sprite_L3 ;
    string sprite_L4 ;
    string sprite_L5 ;
    string sprite_L6 ;
    string sprite_L7 ;
    string sprite_L8 ;
    string sprite_L9 ;
    string sprite_L10 ;
    string sprite_L11 ;
    string sprite_L12 ;
    string sprite_L13 ;
    string sprite_L14 ;
    string sprite_L15 ;
    string sprite_L16 ;
    string sprite_L17 ;
    string sprite_L18 ;

public:
    //methode
    void deplacer( int go , Piece *playground[10][10] ) ;
    void fuite( int go , Piece *playground[10][10] ) ;
    void combat( Personnages *ennemi , int fuir , Piece *playground[10][10] ) ;
    void recevoir_dommage( Personnages *attaquant , string type_dmg ) ;
    void attaque_normale( Personnages *cible ) ;
    void sorts( Personnages *cible ) ;
    bool mort() ;
    string barre_de_vie( string position ) ;
    void sprite_combat( Personnages *cible ) ;
    void utiliser_objet_combat( Personnages *cible , Piece *salles ) ;
    void utiliser_objet( Piece *salle , Personnages *cible ) ;
    void ramasser_objet( Piece *salle ) ;
    void poser_objet( Piece *salle ) ;
    void equiper( Piece *salle ) ;
    void modification_stats( int plus_ou_moins , int place_inventaire ) ;
    void caracteristiques_perso() ;
    void caracteristiques_objet() ;
    void inventaire( Piece *salle , Personnages *perso_fictif ) ;

public:
    //constructeur
    Personnages() ;
    ~Personnages(){} ;
} ;

class Moine : public Personnages
{
public :
    //variable

public :
    //constructeur
    Moine() ;
    Moine( int difficulter ) ;
    ~Moine(){} ;
} ;

class Guerrier : public Personnages
{
public :
    //variable


public :
    //constructeur
    Guerrier() ;
    Guerrier( int difficulter ) ;
    ~Guerrier(){} ;
} ;

class Sorciere : public Personnages
{
public :
    //variable


public :
    //constructeur
    Sorciere() ;
    Sorciere( int difficulter ) ;
    ~Sorciere(){} ;
} ;

class Amazone : public Personnages
{
public :
    //variable


public :
    //constructeur
    Amazone() ;
    Amazone( int difficulter ) ;
    ~Amazone(){} ;
} ;

#endif // perso_h
