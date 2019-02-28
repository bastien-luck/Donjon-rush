#ifndef equipement_cpp
#define equipement_cpp

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

Equipement::Equipement()
{
    type_equipement = "" ;
    pv = 0 ;
    esquive = 0 ;
    chance = 0 ;
    force = 0 ;
    magie = 0 ;
    defense_physique = 0 ;
    defense_magique = 0 ;
    nom_equipement = "" ;
    type_degat = "" ;
    degats_brut = 0 ;
    place_arme = 0 ;
    icon_arme_et_armure = " " ;
    icon_accessoire = " " ;
    icon_potion = " " ;
    icon_poison_et_tp_et_parchemin = " " ;
    icon_piege = " " ;
    numero_objet_premier_slot = 0 ;
    numero_objet_second_slot = 0 ;
    numero_objet_troisieme_slot = 0 ;
    numero_objet_quatrieme_slot = 0 ;
    numero_objet_sixieme_slot = 0 ;
} ;

Vide::Vide()
{
    type_equipement = "" ;
    nom_equipement = "vide" ;
    type_degat = "physique" ;
}

Armes::Armes()
{
    type_equipement = "arme" ;
} ;

Epee_une_main::Epee_une_main()
{
    icon_arme_et_armure = "G" ;
} ;

Epee_une_main_classique::Epee_une_main_classique()
{
    chance = 10 ;
    force = 2 ;
    nom_equipement = "epee de fer" ;
    type_degat = "physique" ;
    place_arme = 1 ;
    numero_objet_premier_slot = 1 ;
} ;

Epee_une_main_elementaire::Epee_une_main_elementaire()
{
    chance = 10 ;
    force = 1 ;
    magie = 1 ;
    nom_equipement = "epee enflammee" ;
    type_degat = "magique" ;
    place_arme = 1 ;
    numero_objet_premier_slot = 2 ;
} ;

Bouclier::Bouclier()
{
    icon_arme_et_armure = "G" ;
} ;

Petit_bouclier::Petit_bouclier()
{
    pv = 5 ;
    defense_physique = 1 ;
    defense_magique = 1 ;
    nom_equipement = "targe" ;
    place_arme = 1 ;
    numero_objet_premier_slot = 3 ;
} ;

Grand_bouclier::Grand_bouclier()
{
    pv = 10 ;
    esquive = -20 ;
    defense_physique = 3 ;
    defense_magique = 2 ;
    nom_equipement = "rempart" ;
    place_arme = 1 ;
    numero_objet_premier_slot = 4 ;
} ;

Epee_deux_mains::Epee_deux_mains()
{
    icon_arme_et_armure = "G" ;
} ;

Epee_deux_mains_classique::Epee_deux_mains_classique()
{
    pv = 5 ;
    esquive = -10 ;
    force = 5 ;
    defense_physique = 2 ;
    nom_equipement = "epee lourde de fer" ;
    type_degat = "physique" ;
    place_arme = 2 ;
    numero_objet_premier_slot = 5 ;
} ;

Epee_deux_mains_elementaire::Epee_deux_mains_elementaire()
{
    pv = 5 ;
    esquive = -10 ;
    force = 3 ;
    magie = 3 ;
    defense_magique = 1 ;
    nom_equipement = "epee lourde enflammee" ;
    type_degat = "magique" ;
    place_arme = 2 ;
    numero_objet_premier_slot = 6 ;
} ;

Sceptre::Sceptre()
{
    icon_arme_et_armure = "S" ;
} ;

Sceptre_d_incantation::Sceptre_d_incantation()
{
    chance = 25 ;
    magie = 6 ;
    nom_equipement = "sceptre d'archimage" ;
    type_degat = "magique" ;
    place_arme = 2 ;
    numero_objet_premier_slot = 7 ;
} ;

Sceptre_de_combat::Sceptre_de_combat()
{
    pv = 6 ;
    esquive = 5 ;
    force = 3 ;
    defense_physique = 3 ;
    defense_magique = 1 ;
    nom_equipement = "baton de combat" ;
    type_degat = "physique" ;
    place_arme = 2 ;
    numero_objet_premier_slot = 8 ;
} ;

Objet_magique::Objet_magique()
{
    icon_arme_et_armure = "S" ;
} ;

Livre::Livre()
{
    magie = 2 ;
    defense_physique = 2 ;
    nom_equipement = "necronomicon" ;
    type_degat = "physique" ;
    degats_brut = 1 ;
    place_arme = 1 ;
    numero_objet_premier_slot = 9 ;
} ;
Boule_magique::Boule_magique()
{
    esquive = 20 ;
    magie = 1 ;
    defense_physique = 1 ;
    defense_magique = 1 ;
    nom_equipement = "boule de divination" ;
    type_degat = "def" ;
    place_arme = 1 ;
    numero_objet_premier_slot = 10 ;
} ;

Baguette::Baguette()
{
    icon_arme_et_armure = "S" ;
} ;

Baguette_de_mobilite::Baguette_de_mobilite()
{
    esquive = 15 ;
    chance = 5 ;
    magie = 2 ;
    nom_equipement = "baguette rapide" ;
    type_degat = "magique" ;
    place_arme = 1 ;
    numero_objet_premier_slot = 11 ;
} ;

Baguette_de_soin::Baguette_de_soin()
{
    pv = 2 ;
    esquive = 5 ;
    magie = 3 ;
    nom_equipement = "baguette de premier secour" ;
    type_degat = "soin" ;
    place_arme = 1 ;
    numero_objet_premier_slot = 12 ;
} ;

Lance::Lance()
{
    icon_arme_et_armure = "A" ;
} ;

Lance_fine::Lance_fine()
{
    esquive = 5 ;
    chance = 15 ;
    force = 2 ;
    nom_equipement = "lance aiguisee" ;
    type_degat = "physique" ;
    degats_brut = 4 ;
    place_arme = 1 ;
    numero_objet_premier_slot = 13 ;
} ;

Lance_d_accro::Lance_d_accro()
{
    pv = 5 ;
    chance = 15 ;
    force = 4 ;
    nom_equipement = "harpon" ;
    type_degat = "debuff" ;
    place_arme = 1 ;
    numero_objet_premier_slot = 14 ;
} ;

Arme_de_jet::Arme_de_jet()
{
    icon_arme_et_armure = "A" ;
} ;

Sarbacane::Sarbacane()
{
    force = 2 ;
    defense_physique = 2 ;
    defense_magique = 1 ;
    nom_equipement = "sarbacane empoisonnee" ;
    type_degat = "poison" ;
    place_arme = 1 ;
    numero_objet_premier_slot = 15 ;
} ;

Bolas::Bolas()
{
    esquive = 15 ;
    force = 4 ;
    nom_equipement = "bolas de chasse" ;
    type_degat = "physique" ;
    degats_brut = 4 ;
    place_arme = 1 ;
    numero_objet_premier_slot = 16 ;
} ;

Armures::Armures()
{
    type_equipement = "armure" ;
} ;

Casque::Casque()
{
    icon_arme_et_armure = "C" ;
    sous_type_equipement = "casque" ;
} ;

Heaume::Heaume()
{
    pv = 2 ;
    defense_physique = 1 ;
    defense_magique = 1 ;
    nom_equipement = "heaume de fer" ;
    type_degat = "null" ;
    numero_objet_premier_slot = 17 ;
} ;

Chapeau::Chapeau()
{
    chance = 5 ;
    magie = 1 ;
    defense_physique = 1 ;
    nom_equipement = "chapeau magique" ;
    type_degat = "null" ;
    numero_objet_premier_slot = 18 ;
} ;

Serre_tete::Serre_tete()
{
    pv = 5 ;
    esquive = 5 ;
    chance = 5 ;
    force = 1 ;
    nom_equipement = "bandana" ;
    type_degat = "null" ;
    numero_objet_premier_slot = 19 ;
} ;

Plastron::Plastron()
{
    icon_arme_et_armure = "P" ;
    sous_type_equipement = "plastron" ;
} ;

Armure_lourde::Armure_lourde()
{
    pv = 5 ;
    esquive = -20 ;
    defense_physique = 3 ;
    defense_magique = 3 ;
    nom_equipement = "plastron fer" ;
    type_degat = "null" ;
    numero_objet_premier_slot = 20 ;
} ;

Armure_legere::Armure_legere()
{
    pv = 5 ;
    esquive = 5 ;
    chance = 10 ;
    force = 1 ;
    defense_physique = 2 ;
    nom_equipement = "armure de gladiateur" ;
    type_degat = "null" ;
    numero_objet_premier_slot = 21 ;
} ;

Robe::Robe()
{
    pv = 5 ;
    esquive = -5 ;
    magie = 2 ;
    defense_physique = 1 ;
    defense_magique = 2 ;
    nom_equipement = "robe de mage" ;
    type_degat = "null" ;
    numero_objet_premier_slot = 22 ;
} ;

Bottes::Bottes()
{
    icon_arme_et_armure = "B" ;
    sous_type_equipement = "bottes" ;
} ;

Bottes_lourdes::Bottes_lourdes()
{
    esquive = -5 ;
    force = 1 ;
    defense_physique = 2 ;
    nom_equipement = "bottes en fer" ;
    type_degat = "null" ;
    numero_objet_premier_slot = 23 ;
} ;

Chaussures::Chaussures()
{
    pv = 2 ;
    esquive = 5 ;
    chance = 5 ;
    defense_physique = 1 ;
    defense_magique = 1 ;
    nom_equipement = "souliers du voyageur" ;
    type_degat = "null" ;
    numero_objet_premier_slot = 24 ;
} ;

Chaussons::Chaussons()
{
    pv = 2 ;
    magie = 1 ;
    defense_physique = 1 ;
    defense_magique = 2 ;
    nom_equipement = "chaussons enchanteur" ;
    type_degat = "null" ;
    numero_objet_premier_slot = 25 ;
} ;

Jambieres::Jambieres()
{
    icon_arme_et_armure = "J" ;
    sous_type_equipement = "jambieres" ;
} ;

Jambieres_lourdes::Jambieres_lourdes()
{
    pv = 5 ;
    force = 1 ;
    defense_physique = 2 ;
    defense_magique = 2 ;
    nom_equipement = "jambiere de soldat" ;
    type_degat = "null" ;
    numero_objet_premier_slot = 26 ;
} ;

Jambieres_moyennes::Jambieres_moyennes()
{
    pv = 3 ;
    esquive = 5 ;
    chance = 10 ;
    force = 1 ;
    defense_physique = 2 ;
    defense_magique = 2 ;
    nom_equipement = "jambiere de serenitee" ;
    type_degat = "null" ;
    numero_objet_premier_slot = 27 ;
} ;

Jambieres_legeres::Jambieres_legeres()
{
    pv = 2 ;
    esquive = 10 ;
    defense_physique = 1 ;
    defense_magique = 1 ;
    nom_equipement = "jambiere de peau" ;
    type_degat = "null" ;
    numero_objet_premier_slot = 28 ;
} ;

Gantelets::Gantelets()
{
    icon_arme_et_armure = "g" ;
    sous_type_equipement = "gantelets" ;
} ;

Gantelets_offensifs::Gantelets_offensifs()
{
    pv = 5 ;
    esquive = 5 ;
    chance = 15 ;
    force = 4 ;
    defense_physique = 2 ;
    nom_equipement = "poings du dragon" ;
    type_degat = "null" ;
    numero_objet_premier_slot = 29 ;
} ;

Gantelets_lourds::Gantelets_lourds()
{
    pv = 2 ;
    force = 1 ;
    defense_physique = 2 ;
    defense_magique = 1 ;
    nom_equipement = "gantelets imperial" ;
    type_degat = "null" ;
    numero_objet_premier_slot = 30 ;
} ;

Gantelets_legers::Gantelets_legers()
{
    pv = 2 ;
    chance = 5 ;
    magie = 1 ;
    defense_physique = 1 ;
    defense_magique = 2 ;
    nom_equipement = "gants de soie" ;
    type_degat = "null" ;
    numero_objet_premier_slot = 31 ;
} ;

Accessoires::Accessoires()
{
    icon_accessoire = "A" ;
    type_equipement = "accessoire" ;
} ;

Masque_a_gaz::Masque_a_gaz()
{
    pv = 1 ;
    nom_equipement = "masque a gaz" ;
    type_degat = "null" ;
    numero_objet_second_slot = 1 ;
} ;

Crucifix::Crucifix()
{
    nom_equipement = "crucifix" ;
    type_degat = "null" ;
    chance = 5 ;
    magie = 2 ;
    numero_objet_second_slot = 2 ;
} ;

Ceinture::Ceinture()
{
    nom_equipement = "ceinture" ;
    type_degat = "null" ;
    defense_physique = 2 ;
    pv = 2 ;
    numero_objet_second_slot = 3 ;
} ;

Bracelets::Bracelets()
{
    nom_equipement = "bracelets" ;
    type_degat = "null" ;
    defense_magique = 2 ;
    chance = 5 ;
    numero_objet_second_slot = 4 ;
} ;

Brassard::Brassard()
{
    icon_accessoire = "A" ;
    nom_equipement = "brassard" ;
    type_degat = "null" ;
    defense_magique = 1 ;
    defense_physique = 1 ;
    esquive = 5 ;
    numero_objet_second_slot = 5 ;
} ;

Consommables::Consommables()
{
    type_equipement_objet = "objet" ;
} ;

Poison::Poison()
{
    type_equipement = "poison" ;
} ;

Fioles::Fioles()
{
    icon_poison_et_tp_et_parchemin = "F" ;
    nom_equipement = "fiole de poison" ;
    type_degat = "poison" ;
    degats_brut = 2 ;
    numero_objet_quatrieme_slot = 1 ;
} ;

Enduit::Enduit()
{
    icon_poison_et_tp_et_parchemin = "E" ;
    nom_equipement = "enduit empoisonnee" ;
    type_degat = "buff_poison" ;
    degats_brut = 2 ;
    numero_objet_quatrieme_slot = 2 ;
} ;

Potions::Potions()
{
    type_equipement = "potion" ;
} ;

Petites_potions::Petites_potions()
{
    icon_potion = "p" ;
    pv = 5 ;
    nom_equipement = "petite potion" ;
    type_degat = "soin" ;
    numero_objet_troisieme_slot = 1 ;
} ;

Moyennes_potions::Moyennes_potions()
{
    icon_potion = "m" ;
    pv = 10 ;
    nom_equipement = "moyenne potion" ;
    type_degat = "soin" ;
    numero_objet_troisieme_slot = 2 ;
} ;

Grandes_potions::Grandes_potions()
{
    icon_potion = "g" ;
    pv = 15 ;
    nom_equipement = "grande potion" ;
    type_degat = "soin" ;
    numero_objet_troisieme_slot = 3 ;
} ;

Anti_poison::Anti_poison()
{
    nom_equipement = "anti poison" ;
    type_degat = "soin poison" ;
    //numero_objet = 38 ;
} ;

Anti_mutisme::Anti_mutisme()
{
    nom_equipement = "anti mutisme" ;
    type_degat = "soin mutisme" ;
    //numero_objet = 39 ;
} ;

Anti_paralysie::Anti_paralysie()
{
    nom_equipement = "anti paralysie" ;
    type_degat = "soin paralysie" ;
    //numero_objet = 40 ;
} ;

Cle_teleportation::Cle_teleportation()
{
    icon_poison_et_tp_et_parchemin = "V" ;
    nom_equipement = "cle teleportation" ;
    type_degat = "tp" ;
    numero_objet_quatrieme_slot = 3 ;
} ;

Parchemins::Parchemins()
{
    type_equipement = "parchemin" ;
    icon_poison_et_tp_et_parchemin = "S" ;
} ;

Feu::Feu()
{
    magie = 5 ;
    nom_equipement = "parchemin brulant" ;
    type_degat = "magique" ;
    numero_objet_quatrieme_slot = 4 ;
} ;

Soin::Soin()
{
    magie = 5 ;
    nom_equipement = "parchemin de soin" ;
    type_degat = "soin" ;
    numero_objet_quatrieme_slot = 5 ;
} ;

Buff::Buff()
{
    force = 1 ;
    magie = 1 ;
    defense_physique = 1 ;
    defense_magique = 1 ;
    nom_equipement = "parchemin de puissance" ;
    type_degat = "buff" ;
    numero_objet_quatrieme_slot = 6 ;
} ;

Terre::Terre()
{
    magie = 5 ;
    nom_equipement = "parchemin tellurique" ;
    type_degat = "physique" ;
    numero_objet_quatrieme_slot = 7 ;
} ;

Piege::Piege()
{
    type_equipement = "piege" ;
    icon_piege = "T" ;
} ;

Runes::Runes()
{
    magie = 8 ;
    nom_equipement = "piege runique" ;
    type_degat = "magique" ;
    numero_objet_sixieme_slot = 1 ;
} ;

Tourelles::Tourelles()
{
    force = 8 ;
    nom_equipement = "arbalete piegee" ;
    type_degat = "physique" ;
    numero_objet_sixieme_slot = 2 ;
} ;

Changement_etat::Changement_etat()
{
    nom_equipement = "piege incapacitant" ;
    type_degat = "change etat" ;
    numero_objet_sixieme_slot = 3 ;
} ;

#endif //equipement_cpp
