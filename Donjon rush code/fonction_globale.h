#ifndef fonc_glob_h
#define fonc_glob_h

#include <iostream>


using namespace std ;



int spam_endl( int nb_saut ) ;
string spam_space( int nb_space ) ;
string intToString( int z ) ;
int logo() ;
void init_plateau_jeu( Piece *playground[10][10] ) ;
string affichage_donjon( Piece *playground[10][10] , Personnages *ut ) ;
void verification_type_equipement( Personnages *ut , int choix_equipement , int *compteur_accessoire , int *compteur_arme ) ;
void placement_ia( Personnages *ia1 , Personnages *ia2 , Personnages *ia3 ) ;
void verification_place_sol( Personnages *ut , Piece *salles , string type_objet , int emplacement_sac ) ;
void ramassage_objet( Personnages *ut , Piece *salles , int place_libre , int choix_objet ) ;
void utilisation_objet( Personnages *ut , int place_objet , Personnages *ennemi , Piece *salle ) ;


#endif //fonc_glob_h
