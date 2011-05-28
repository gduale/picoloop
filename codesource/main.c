#include <mygba.h>
#include "main.h"
#include "son.h"
#include "mesfonts.h"
#include "fonctions.h"
#include "icones.h"
#include "soundApi/soundApi.h"
#include "ecrans.h"
//#include "menu/01.pal.h"
//#include "menu/01.raw.h"

int main(void) {
    ham_Init();
    ham_InitText(1);
    /*Passer en mode X*/
    REG_DISPCNT = (MODE_3 | BG2 | OBJ_ENABLED);

    snd_init_soundApi();

    //Initialisation du son
    //On met 99 dans sfreq afin de pouvoir faire des tests sur les notes
    for (chanCourant = 0; chanCourant < 4; chanCourant++) {
        for (patternCourant = 0; patternCourant < 2; patternCourant++) {
            for (noteEnCours = 0; noteEnCours < 16; noteEnCours++) {
                chan[chanCourant].pattern[patternCourant].notes[noteEnCours].sfreq = 99;
            }
        }
    }

    chanCourant = 0; //PU1
    //Pattern en cours
    patternCourant = 0;
    //Note en cours
    noteEnCours = 0;

    /*Affiche l'écran d'accueil*/
    ecranAccueil();

    remplirEcran(BLANC);

    carte();
    while (1) {
        afficherChaine("BUG : ON EST SORTI!", 30, 50, ROUGE);
    }
    return 0;
}/*Fin de main()*/
