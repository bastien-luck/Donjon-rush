#ifndef equipement_h
#define equipement_h

#include <iostream>

using namespace std ;

class Equipement
{
public :
    int pv ;
    int esquive ;
    int chance ;
    int force ;
    int magie ;
    int defense_physique ;
    int defense_magique ;
    string nom_equipement ;
    string type_degat ;
    int degats_brut ;
    int place_arme ;
    string type_equipement ;
    string type_equipement_objet ;
    string sous_type_equipement ;
    string icon_arme_et_armure ;
    string icon_accessoire ;
    string icon_potion ;
    string icon_poison_et_tp_et_parchemin ;
    string icon_perso_et_piege_actif ;
    string icon_piege ;
    int numero_objet_premier_slot ;
    int numero_objet_second_slot ;
    int numero_objet_troisieme_slot ;
    int numero_objet_quatrieme_slot ;
    int numero_objet_sixieme_slot ;
public :
    Equipement() ;
    ~Equipement(){} ;
};

class Vide : public Equipement
{
public :
    Vide() ;
    ~Vide(){} ;
};

class Armes : public Equipement
{
public :
    Armes() ;
    ~Armes(){} ;

};

class Epee_une_main : public Armes
{
public :
    Epee_une_main() ;
    ~Epee_une_main(){} ;
};

class Epee_une_main_classique : public Epee_une_main
{
public :
    Epee_une_main_classique() ;
    ~Epee_une_main_classique(){} ;
};

class Epee_une_main_elementaire : public Epee_une_main
{
public :
    Epee_une_main_elementaire() ;
    ~Epee_une_main_elementaire(){} ;
};

class Bouclier : public Armes
{
public :
    Bouclier() ;
    ~Bouclier(){} ;
};

class Petit_bouclier : public Bouclier
{
public :
    Petit_bouclier() ;
    ~Petit_bouclier(){} ;
};

class Grand_bouclier : public Bouclier
{
public :
    Grand_bouclier() ;
    ~Grand_bouclier(){} ;
};

class Epee_deux_mains : public Armes
{
public :
    Epee_deux_mains() ;
    ~Epee_deux_mains(){} ;
};

class Epee_deux_mains_classique : public Epee_deux_mains
{
public :
    Epee_deux_mains_classique() ;
    ~Epee_deux_mains_classique(){} ;
};

class Epee_deux_mains_elementaire : public Epee_deux_mains
{
public :
    Epee_deux_mains_elementaire() ;
    ~Epee_deux_mains_elementaire(){} ;
};

class Sceptre : public Armes
{
public :
    Sceptre() ;
    ~Sceptre(){} ;
};

class Sceptre_d_incantation : public Sceptre
{
public :
    Sceptre_d_incantation() ;
    ~Sceptre_d_incantation(){} ;
};

class Sceptre_de_combat : public Sceptre
{
public :
    Sceptre_de_combat() ;
    ~Sceptre_de_combat(){} ;
};

class Objet_magique : public Armes
{
public :
    Objet_magique() ;
    ~Objet_magique(){} ;
};

class Livre : public Objet_magique
{
public :
    Livre() ;
    ~Livre(){} ;
};

class Boule_magique : public Objet_magique
{
public :
    Boule_magique() ;
    ~Boule_magique(){} ;
};

class Baguette : public Armes
{
public :
    Baguette() ;
    ~Baguette(){} ;
};

class Baguette_de_mobilite : public Baguette
{
public :
    Baguette_de_mobilite() ;
    ~Baguette_de_mobilite(){} ;
};

class Baguette_de_soin : public Baguette
{
public :
    Baguette_de_soin() ;
    ~Baguette_de_soin(){} ;
};

class Lance : public Armes
{
public :
    Lance() ;
    ~Lance(){} ;
};

class Lance_fine : public Lance
{
public :
    Lance_fine() ;
    ~Lance_fine(){} ;
};

class Lance_d_accro : public Lance
{
public :
    Lance_d_accro() ;
    ~Lance_d_accro(){} ;
};

class Arme_de_jet : public Armes
{
public :
    Arme_de_jet() ;
    ~Arme_de_jet(){} ;
};

class Sarbacane : public Arme_de_jet
{
public :
    Sarbacane() ;
    ~Sarbacane(){} ;
};

class Bolas : public Arme_de_jet
{
public :
    Bolas() ;
    ~Bolas(){} ;
};

class Armures : public Equipement
{
public :
    Armures() ;
    ~Armures(){} ;

};

class Casque : public Armures
{
public :
    Casque() ;
    ~Casque(){} ;
};

class Heaume : public Casque
{
public :
    Heaume() ;
    ~Heaume(){} ;
};

class Chapeau : public Casque
{
public :
    Chapeau() ;
    ~Chapeau(){} ;
};

class Serre_tete : public Casque
{
public :
    Serre_tete() ;
    ~Serre_tete(){} ;
};

class Plastron : public Armures
{
public :
    Plastron() ;
    ~Plastron(){} ;
};

class Armure_lourde : public Plastron
{
public :
    Armure_lourde() ;
    ~Armure_lourde(){} ;
};

class Armure_legere : public Plastron
{
public :
    Armure_legere() ;
    ~Armure_legere(){} ;
};

class Robe : public Plastron
{
public :
    Robe() ;
    ~Robe(){} ;
};

class Bottes : public Armures
{
public :
    Bottes() ;
    ~Bottes(){} ;
};

class Bottes_lourdes : public Bottes
{
public :
    Bottes_lourdes() ;
    ~Bottes_lourdes(){} ;
};

class Chaussures : public Bottes
{
public :
    Chaussures() ;
    ~Chaussures(){} ;
};

class Chaussons : public Bottes
{
public :
    Chaussons() ;
    ~Chaussons(){} ;
};

class Jambieres : public Armures
{
public :
    Jambieres() ;
    ~Jambieres(){} ;
};

class Jambieres_lourdes : public Jambieres
{
public :
    Jambieres_lourdes() ;
    ~Jambieres_lourdes(){} ;
};

class Jambieres_moyennes : public Jambieres
{
public :
    Jambieres_moyennes() ;
    ~Jambieres_moyennes(){} ;
};

class Jambieres_legeres : public Jambieres
{
public :
    Jambieres_legeres() ;
    ~Jambieres_legeres(){} ;
};

class Gantelets : public Armures
{
public :
    Gantelets() ;
    ~Gantelets(){} ;
};

class Gantelets_offensifs : public Gantelets
{
public :
    Gantelets_offensifs() ;
    ~Gantelets_offensifs(){} ;
};

class Gantelets_lourds : public Gantelets
{
public :
    Gantelets_lourds() ;
    ~Gantelets_lourds(){} ;
};

class Gantelets_legers : public Gantelets
{
public :
    Gantelets_legers() ;
    ~Gantelets_legers(){} ;
};

class Accessoires : public Equipement
{
public :
    Accessoires() ;
    ~Accessoires(){} ;
};

class Masque_a_gaz : public Accessoires
{
public :
    Masque_a_gaz() ;
    ~Masque_a_gaz(){} ;
};

class Crucifix : public Accessoires
{
public :
    Crucifix() ;
    ~Crucifix(){} ;
};

class Ceinture : public Accessoires
{
public :
    Ceinture() ;
    ~Ceinture(){} ;
};

class Bracelets : public Accessoires
{
public :
    Bracelets() ;
    ~Bracelets(){} ;
};

class Brassard : public Accessoires
{
public :
    Brassard() ;
    ~Brassard(){} ;
};

class Consommables : public Equipement
{
public :
    Consommables() ;
    ~Consommables(){} ;
};

class Poison : public Consommables
{
public :
    Poison() ;
    ~Poison(){} ;
};

class Fioles : public Poison
{
public :
    Fioles() ;
    ~Fioles(){} ;
};

class Enduit : public Poison
{
public :
    Enduit() ;
    ~Enduit(){} ;
};

class Potions : public Consommables
{
public :
    Potions() ;
    ~Potions(){} ;
};

class Petites_potions : public Potions
{
public :
    Petites_potions() ;
    ~Petites_potions(){} ;
};

class Moyennes_potions : public Potions
{
public :
    Moyennes_potions() ;
    ~Moyennes_potions(){} ;
};

class Grandes_potions : public Potions
{
public :
    Grandes_potions() ;
    ~Grandes_potions(){} ;
};

class Anti_poison : public Potions
{
public :
    Anti_poison() ;
    ~Anti_poison(){} ;
};

class Anti_mutisme : public Potions
{
public :
    Anti_mutisme() ;
    ~Anti_mutisme(){} ;
};

class Anti_paralysie : public Potions
{
public :
    Anti_paralysie() ;
    ~Anti_paralysie(){} ;
};

class Cle_teleportation : public Consommables
{
public :
    Cle_teleportation() ;
    ~Cle_teleportation(){} ;
};

class Parchemins : public Consommables
{
public :
    Parchemins() ;
    ~Parchemins(){} ;
};

class Feu : public Parchemins
{
public :
    Feu() ;
    ~Feu(){} ;
};

class Soin : public Parchemins
{
public :
    Soin() ;
    ~Soin(){} ;
};

class Buff : public Parchemins
{
public :
    Buff() ;
    ~Buff(){} ;
};

class Terre : public Parchemins
{
public :
    Terre() ;
    ~Terre(){} ;
};

class Piege : public Consommables
{
public :
    Piege() ;
    ~Piege(){} ;
};

class Runes : public Piege
{
public :
    Runes() ;
    ~Runes(){} ;
};

class Tourelles : public Piege
{
public :
    Tourelles() ;
    ~Tourelles(){} ;
};

class Changement_etat : public Piege
{
public :
    Changement_etat() ;
    ~Changement_etat(){} ;
};

#endif //equipement_h
