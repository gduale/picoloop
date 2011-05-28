/*Ecran affiché lors du ON de la GBA*/
void ecranAccueil() {
    /*Couleur de fond de l'écran*/
    remplirEcran(BLANC);

    /*Titre de l'écran*/
    //afficherChaine("ABCDEFGHIJKLMNOPQRSTUVWXYZ!@#",5,15,BLEU);
    //afficherChaine("CONTACT@FLIPFLOP.FR",5,35,ROSE);
    afficherChaine("- PICOLOOP -", 65, 20, BLEU);
    afficherChaine("V0.1", 95, 30, NOIR);
    pulse(80, 50, 30, NOIR);
    afficherChaine("PRESS START", 70, 100, NOIR);
    afficherLettre(COEUR, 60, 100, ROUGE);
    afficherLettre(COEUR, 160, 100, ROUGE);
    afficherChaine("BY FLIP-FLOP", 1, 145, NOIR);
    afficherChaine("FEAT SPINTRONIC", 115, 145, NOIR);

    u16 sortir;
    sortir = 0;
    while (sortir != 1) {
        switch (REG_TOUCHES) {
            case TOUCHE_START:
                sortir = 1;
                break;
        }
    }
}

/*Selectionner une banque (utilisé par ecranProjet())*/
int selectionerBanque(int cpt, int operation) {
    if (operation == 1)
        if (cpt < 9)
            cpt++;
    if (operation == 0)
        if (cpt > 0)
            cpt--;
    pause(20);
    carre(41, 15, 9, BLANC); //Effacer l'ancien chiffre
    afficherLettre(chiffres[cpt], 42, 15, BLEU);
    return cpt;
}

/*Changer la lettre en cours afin de nommer une chanson*/
u16 changerLettre(u16 position, u8 haut, u16 cpt) {
    if (haut == 1)
        if (cpt < 25)
            cpt++;
    if (haut == 0)
        if (cpt > 0)
            cpt--;

    pause(20);
    carre(position, 15, 9, BLANC); //Effacer l'ancienne lettre

    afficherLettre(lettres[cpt], position, 15, BLEU);

    return cpt;
}

/*Dessine les patterns de 0 à F pour l'écran PROJET*/
void dessinerLignePattern() {
    u16 i, inc;

    /*Canal P1*/
    inc = 0;
    afficherChaine("PU", 5, 60, GRIS);
    afficherLettre(chiffres[1], 22, 60, GRIS);
    for (i = 0; i < 16; i++) {//!!!!!!A CORRIGER ! OVERFLOW ! (pour tous les cannaux)
        afficherLettre(chiffres[i], 40 + inc, 60, VERT);
        inc += 10;
    }

    /*Canal P2*/
    inc = 0;
    afficherChaine("PU", 5, 70, GRIS);
    afficherLettre(chiffres[2], 22, 70, GRIS);
    for (i = 0; i < 16; i++) {
        afficherLettre(chiffres[i], 40 + inc, 70, VERT);
        inc += 10;
    }

    /*Canal WAV*/
    inc = 0;
    afficherChaine("WAV", 5, 80, GRIS);
    for (i = 0; i < 16; i++) {
        afficherLettre(chiffres[i], 40 + inc, 80, VERT);
        inc += 10;
    }

    /*Canal NOISE*/
    inc = 0;
    afficherChaine("NOI", 5, 90, GRIS);
    for (i = 0; i < 16; i++) {
        afficherLettre(chiffres[i], 40 + inc, 90, VERT);
        inc += 10;
    }

    /*Sample 1*/
    inc = 0;
    afficherChaine("S", 5, 100, GRIS);
    afficherLettre(chiffres[0], 13, 100, GRIS);
    afficherLettre(chiffres[1], 21, 100, GRIS);
    for (i = 0; i < 16; i++) {
        afficherLettre(chiffres[i], 40 + inc, 100, VERT);
        inc += 10;
    }

    /*Sample 2*/
    inc = 0;
    afficherChaine("S", 5, 110, GRIS);
    afficherLettre(chiffres[0], 13, 110, GRIS);
    afficherLettre(chiffres[2], 21, 110, GRIS);
    for (i = 0; i < 16; i++) {
        afficherLettre(chiffres[i], 40 + inc, 110, VERT);
        inc += 10;
    }
}

/*Affiche le texte statique pour l'écran PROJET*/
void afficherTexteEcranProjet() {
    /*Titre de l'écran*/
    afficherChaine("PROJECT", 88, 2, ROSE);

    /*Affiche le curseur et le numéro de la banque en cours*/
    afficherChaine("BANK:", 2, 15, GRIS);
    curseur(40, 14, 10, BLEU);
    afficherLettre(chiffres[numBank], 42, 15, BLEU);

    /*Afficher NAME pour la chanson*/
    afficherChaine("NAME:", 80, 15, GRIS);

    /*Afficher le tempo*/
    afficherChaine("TEMPO:", 2, 30, GRIS);

    /*Afficher les lignes de patterns pour les 4 chan*/
    dessinerLignePattern();
}

/*Dessiner l'écran projet*/
int ecranProjet() {
    remplirEcran(BLANC);

    /*Variables*/
    u16 sortir, i, action, cptLettre, indiceLettre, posXCurseurName, posXCurseurPattern, posYCurseurPattern, chanCourant, numLettre, x, posLettreNomchanson;
    int cptBank, lettreNomChanson;
    sortir = 0;
    i = 0;
    cptLettre = -1; //voir mesfonts.h
    numLettre = 0; //C'est pour placer la position du curseur bleu dans NAME. Comme ça on bloque le nom des tracks à 8 caractères.
    indiceLettre = 0;
    posXCurseurName = 119; //Position du curseur qui souligne le texte dans NAME
    posXCurseurPattern = 39; //Position du curseur qui entoure le pattern en cours
    posYCurseurPattern = 59; //Position du curseur qui entoure le pattern en cours

    /*Le chanel en cours: 1=PU1 2=PU2 3=WAV 4=NOISE 5=Sample1 6=Sample2*/
    chanCourant = 1;

    /*La variable action sert à savoir si on affecte (la position du curseur) la banque, le nom ou les cannaux*/
    /* 1=bank / 2=name / 3=tempo / 4=cannaux*/
    action = 1;

    /*Affiche le texte statique pour l'écran PROJET*/
    afficherTexteEcranProjet();

    //On tente l'affichage du nom de la chanson -> Ca fonctionne le nom de la track est bien dans "int *nomChanson"
    posLettreNomchanson = posXCurseurName;
    for (x = 0; x < 8; x++) {
        //carre(posXCurseurName,15,10,BLANC);
        lettreNomChanson = nomChanson[x];
        if (nomChanson[x] != 0) {
            //afficherLettre(lettres[lettreNomChanson],posLettreNomchanson,15,BLEU);
            afficherLettre(lettres[nomChanson[x]], posLettreNomchanson, 15, BLEU);
        }
        posLettreNomchanson += 10;
    }


    while (sortir == 0) {
        cptBank = numBank;
        cptLettre = indiceLettre;
        pause(2);

        switch (REG_TOUCHES) {
                /*Navigation dans la MAP*/
            case TOUCHE_SELECT | TOUCHE_GAUCHE:
                sortir = 1;
                break;

                /*Navigation dans la MAP*/
            case TOUCHE_SELECT | TOUCHE_DROITE:
                sortir = 3;
                break;

                /*Navigation dans la MAP*/
            case TOUCHE_SELECT | TOUCHE_HAUT:
                sortir = 99;
                break;

            case TOUCHE_A | TOUCHE_HAUT:
                if (action == 1) {//On est dans BANK
                    numBank = selectionerBanque(cptBank, 1);
                }
                if (action == 2) {//On est dans NAME
                    indiceLettre = changerLettre(posXCurseurName, 1, cptLettre);
                    nomChanson[numLettre] = indiceLettre;
                }
                if (action == 3) {//On est dans TEMPO
                    //A FAIRE
                }
                break;

            case TOUCHE_A | TOUCHE_BAS:
                if (action == 1)
                    numBank = selectionerBanque(cptBank, 0);
                if (action == 2) {
                    indiceLettre = changerLettre(posXCurseurName, 0, cptLettre);
                    nomChanson[numLettre] = indiceLettre;
                }
                break;

                /*Bascule le curseur entre les différents objets*/
            case TOUCHE_L:
                if (action == 1) { //Bascule sur NAME
                    curseur(40, 14, 10, BLANC); //Efface le curseur BANK
                    ligneH(posXCurseurName, 24, 8, BLEU);
                }
                if (action == 2) { //Bascule sur Tempo
                    ligneH(posXCurseurName, 24, 8, BLANC); //Efface le curseur NAME
                    rectangle(50, 29, 20, 10, BLEU);
                }
                if (action == 3) { //Bascule sur Patterns
                    rectangle(50, 29, 20, 10, BLANC); //Efface le curseur du Tempo
                    curseur(posXCurseurPattern, posYCurseurPattern, 9, BLEU);
                }
                if (action == 4) { //Reviens sur BANK
                    curseur(posXCurseurPattern, posYCurseurPattern, 9, BLANC); //Efface le curseur des patterns
                    curseur(40, 14, 10, BLEU);
                }
                action++;
                if (action == 5)
                    action = 1;

                pause(20);

                break;

                /*On déplace le curseur*/
            case TOUCHE_DROITE:
                /*
                        if(position<119+80)
                                position += 10;
                        action = 2;
                        pause(20);*/
                if (action == 2) {//On est sur NAME
                    if (numLettre < 7) {
                        ligneH(posXCurseurName, 24, 8, BLANC); //Efface l'ancienne position
                        posXCurseurName += 10;
                        ligneH(posXCurseurName, 24, 8, BLEU);
                        numLettre++;
                    }
                }

                if (action == 4) {//On est sur Pattern
                    if (posXCurseurPattern < 180) {
                        curseur(posXCurseurPattern, posYCurseurPattern, 9, BLANC);
                        posXCurseurPattern += 10;
                        curseur(posXCurseurPattern, posYCurseurPattern, 9, BLEU);
                    }
                }
                pause(10);
                break;

                /*On déplace le curseur*/
            case TOUCHE_GAUCHE:
                if (action == 2) {//On est sur NAME
                    if (numLettre > 0) {
                        ligneH(posXCurseurName, 24, 8, BLANC); //Efface l'ancienne position
                        posXCurseurName -= 10;
                        ligneH(posXCurseurName, 24, 8, BLEU);
                        numLettre--;
                    }
                }

                if (action == 4) {//On est sur Pattern
                    if (posXCurseurPattern > 39) {
                        curseur(posXCurseurPattern, posYCurseurPattern, 9, BLANC);
                        posXCurseurPattern -= 10;
                        curseur(posXCurseurPattern, posYCurseurPattern, 9, BLEU);
                    }
                }
                pause(10);
                break;

            case TOUCHE_HAUT:
                if (action == 4) {
                    if (chanCourant > 1) {
                        curseur(posXCurseurPattern, posYCurseurPattern, 9, BLANC);
                        posYCurseurPattern -= 10;
                        curseur(posXCurseurPattern, posYCurseurPattern, 9, BLEU);
                        chanCourant--;
                    }
                }
                pause(10);
                break;

            case TOUCHE_BAS:
                if (action == 4) {
                    if (chanCourant < 6) {
                        curseur(posXCurseurPattern, posYCurseurPattern, 9, BLANC);
                        posYCurseurPattern += 10;
                        curseur(posXCurseurPattern, posYCurseurPattern, 9, BLEU);
                        chanCourant++;
                    }
                }
                pause(10);
                break;
        }
    }
    return sortir;
}

/*Griser le fond de la note en cours*/
void griserNoteEnCours(u8 posXCurseurPattern, u8 posYCurseurPattern, u8 direction) {
    int Couleur = ROSE;
    int Couleur2 = BLANC;
    u8 xx, yy;
    xx = 0;
    yy = 0;

    //Dessine
    ligneV(posXCurseurPattern + 1, posYCurseurPattern + 1, 18, Couleur);
    ligneV(posXCurseurPattern + 2, posYCurseurPattern + 1, 18, Couleur);

    ligneV(posXCurseurPattern + 9, posYCurseurPattern + 1, 18, Couleur);
    ligneV(posXCurseurPattern + 10, posYCurseurPattern + 1, 18, Couleur);
    ligneV(posXCurseurPattern + 11, posYCurseurPattern + 1, 18, Couleur);

    ligneV(posXCurseurPattern + 18, posYCurseurPattern + 1, 18, Couleur);
    ligneV(posXCurseurPattern + 19, posYCurseurPattern + 1, 18, Couleur);

    //Efface
    switch (direction) {
        case 'd':
            xx = posXCurseurPattern - 30;
            yy = posYCurseurPattern;
            break;

        case 'g':
            xx = posXCurseurPattern + 30;
            yy = posYCurseurPattern;
            break;

        case 'h':
            yy = posYCurseurPattern + 30;
            xx = posXCurseurPattern;
            break;

        case 'b':
            yy = posYCurseurPattern - 30;
            xx = posXCurseurPattern;
            break;
    }

    if (direction != 'a') {
        ligneV(xx + 1, yy + 1, 18, Couleur2);
        ligneV(xx + 2, yy + 1, 18, Couleur2);

        ligneV(xx + 9, yy + 1, 18, Couleur2);
        ligneV(xx + 10, yy + 1, 18, Couleur2);
        ligneV(xx + 11, yy + 1, 18, Couleur2);

        ligneV(xx + 18, yy + 1, 18, Couleur2);
        ligneV(xx + 19, yy + 1, 18, Couleur2);
    }
}

/*Paramètres par defauts des notes*/

/*Cette fonction est appelé lorsque l'on appuie sur la touche A*/
void initNote() {
    /* * \param sweeptime Temps de sweep de 0 à 7
     * \param sweepdir Direction du sweep 1 increase, 0 decrease
     * \param sweepshifts L'effet sweep de 0 à 7
     * \param volume De 0 à F
     * \param envdir Direction de l'enveloppe 1 increase, 0 decrease
     * \param envsteptime Pas de l'enveloppe de 0 à 7
     * \param waveduty Forme de l'onde 0, 1, 2 ou 3
     * \param soundlength Durée du son 0 à 3f (attention valeur inversée: 3f = court) ACTIF seulement si loopmode = 1
     * \param loopmode Timed 1, continuous 0
     * \param sfreq Le numéro de fréquence de la note jouée. de 0 à 72 cf: const u16 freqs[NB_FREQUENCES]
     * \param transpose La valeur de transposition de 0 à FF
     */
    chan[chanCourant].pattern[patternCourant].notes[noteEnCours].volume = 8; //Volume à moitié
    chan[chanCourant].pattern[patternCourant].notes[noteEnCours].soundlength = 22; //maxi=63=très court
    chan[chanCourant].pattern[patternCourant].notes[noteEnCours].loopmode = 1; //Pas de loop

    chan[chanCourant].pattern[patternCourant].notes[noteEnCours].sfreq = 24; //C-4

    chan[chanCourant].pattern[patternCourant].notes[noteEnCours].envsteptime = 5; //maxi=7
    chan[chanCourant].pattern[patternCourant].notes[noteEnCours].sweeptime = 3; //maxi=7

    chan[chanCourant].pattern[patternCourant].notes[noteEnCours].sweepdir = 1; //0 ou 1
    chan[chanCourant].pattern[patternCourant].notes[noteEnCours].envdir = 1; //0 ou 1

    chan[chanCourant].pattern[patternCourant].notes[noteEnCours].sweepshifts = 5; //maxi=7
    chan[chanCourant].pattern[patternCourant].notes[noteEnCours].waveduty = 2; //maxi=3

    chan[chanCourant].pattern[patternCourant].notes[noteEnCours].output = 3;
}

/*Les carrés des paramètres*/
void dessinePotentiometre(u8 posXCurseurPattern, u8 posYCurseurPattern, u8 noteEnCours) {
    waitForVSync();
    //Variables pour les curseurs des paramètres des notes
    u8 xParam1, xParam2, yParam1, yParam2, Couleur, i;
    Couleur = ROUGE;

    xParam1 = posXCurseurPattern + 4;
    xParam2 = posXCurseurPattern + 13;

    /*Switch sur les différents menu possible*/
    switch (menuActif) {
        case 1://Volume / Enveloppe
            //Mise à l'échelle des valeurs si besoin
            yParam1 = chan[chanCourant].pattern[patternCourant].notes[noteEnCours].volume;
            yParam2 = chan[chanCourant].pattern[patternCourant].notes[noteEnCours].soundlength / 4;
            break;

        case 2://Octave / Note
            yParam1 = chan[chanCourant].pattern[patternCourant].notes[noteEnCours].sfreq / 12;
            yParam2 = chan[chanCourant].pattern[patternCourant].notes[noteEnCours].sfreq / 4;
            break;

        case 3://Pitch
            yParam1 = chan[chanCourant].pattern[patternCourant].notes[noteEnCours].sweepshifts * 2;
            yParam2 = chan[chanCourant].pattern[patternCourant].notes[noteEnCours].sweeptime * 2;
            break;

        case 4://Wave
            yParam1 = chan[chanCourant].pattern[patternCourant].notes[noteEnCours].waveduty * 6;
            //yParam2 = 0;//Il faudra dessiner un seul paramètre pour ce menu
            yParam2 = chan[chanCourant].pattern[patternCourant].notes[noteEnCours].sweepdir * 18; //0 ou 1
            break;

        case 5://WLeft Right
            //todo
            yParam1 = 8; //FAKE VALEURS POUR LE MOMENT
            yParam2 = 8; //Idem
            break;

        case 6://Effect 1
            //todo
            yParam1 = 2; //FAKE VALEURS POUR LE MOMENT
            yParam2 = 2; //Idem
            break;

        case 7://Effect 2
            //todo
            yParam1 = 4; //FAKE VALEURS POUR LE MOMENT
            yParam2 = 4; //Idem
            break;

        case 8://Effect 3
            //todo
            yParam1 = 6; //FAKE VALEURS POUR LE MOMENT
            yParam2 = 6; //Idem
            break;

        case 9://Effect 4
            //todo
            yParam1 = 8; //FAKE VALEURS POUR LE MOMENT
            yParam2 = 8; //Idem
            break;

        case 10://Effect 5
            //todo
            yParam1 = 10; //FAKE VALEURS POUR LE MOMENT
            yParam2 = 10; //Idem
            break;

    }

    //Efface potentiomètre 1
    for (i = 0; i <= 18; i++) {
        ligneH(xParam1, posYCurseurPattern + 1 + i, 3, BLANC);
    }
    //Efface potentiomètre 2
    for (i = 0; i <= 18; i++) {
        ligneH(xParam2, posYCurseurPattern + 1 + i, 3, BLANC);
    }

    //Dessine potentiomètre 1
    for (i = 0; i <= yParam1; i++) {
        ligneH(xParam1, posYCurseurPattern + 19 - i, 3, BLEU);
    }

    //Dessine potentiomètre 2
    for (i = 0; i <= yParam2; i++) {
        ligneH(xParam2, posYCurseurPattern + 19 - i, 3, BLEU);
    }
}

/** Modifie la valeur du paramètre sélectioné
 * Et apelle la fonction pour dessiner les potentiomètre avec la nouvelle valeur
 **/
void parametreAModifier(u8 numParam, u8 monte, u8 posXCurseurPattern, u8 posYCurseurPattern) {
    switch (menuActif) {
        case 1://Volume / Enveloppe
            if (numParam == 1) {
                if (monte == 1) {
                    if (chan[chanCourant].pattern[patternCourant].notes[noteEnCours].volume < 15) {
                        chan[chanCourant].pattern[patternCourant].notes[noteEnCours].volume++;
                        dessinePotentiometre(posXCurseurPattern, posYCurseurPattern, noteEnCours);
                    }
                } else {
                    if (chan[chanCourant].pattern[patternCourant].notes[noteEnCours].volume > 0) {
                        chan[chanCourant].pattern[patternCourant].notes[noteEnCours].volume--;
                        dessinePotentiometre(posXCurseurPattern, posYCurseurPattern, noteEnCours);
                    }
                }
            }
            if (numParam == 2) {
                if (monte == 1) {
                    if (chan[chanCourant].pattern[patternCourant].notes[noteEnCours].soundlength < 63) {
                        chan[chanCourant].pattern[patternCourant].notes[noteEnCours].soundlength++;
                        dessinePotentiometre(posXCurseurPattern, posYCurseurPattern, noteEnCours);
                        chan[chanCourant].pattern[patternCourant].notes[noteEnCours].loopmode = 1;
                    }
                } else {
                    if (chan[chanCourant].pattern[patternCourant].notes[noteEnCours].soundlength > 0) {
                        chan[chanCourant].pattern[patternCourant].notes[noteEnCours].soundlength--;
                        dessinePotentiometre(posXCurseurPattern, posYCurseurPattern, noteEnCours);
                    }
                    if (chan[chanCourant].pattern[patternCourant].notes[noteEnCours].soundlength == 0) {
                        chan[chanCourant].pattern[patternCourant].notes[noteEnCours].loopmode = 0; //Note infinie
                    }
                }
            }
            break;

        case 2://Octave / Note
            if (numParam == 1) {
                if (monte == 1) {
                    if (chan[chanCourant].pattern[patternCourant].notes[noteEnCours].sfreq < 71) {
                        chan[chanCourant].pattern[patternCourant].notes[noteEnCours].sfreq += 12;
                    }
                } else {
                    if (chan[chanCourant].pattern[patternCourant].notes[noteEnCours].sfreq > 0) {
                        chan[chanCourant].pattern[patternCourant].notes[noteEnCours].sfreq -= 12;
                    }
                }
            }
            if (numParam == 2) {
                if (monte == 1) {
                    if (chan[chanCourant].pattern[patternCourant].notes[noteEnCours].sfreq < 71) {
                        chan[chanCourant].pattern[patternCourant].notes[noteEnCours].sfreq++;
                    }
                } else {
                    if (chan[chanCourant].pattern[patternCourant].notes[noteEnCours].sfreq > 0) {
                        chan[chanCourant].pattern[patternCourant].notes[noteEnCours].sfreq--;
                    }
                }
            }
            break;

        case 3://Time
            if (numParam == 1) {
                if (monte == 1) {
                    if (chan[chanCourant].pattern[patternCourant].notes[noteEnCours].envsteptime < 7) {
                        chan[chanCourant].pattern[patternCourant].notes[noteEnCours].envsteptime++;
                    }
                } else {
                    if (chan[chanCourant].pattern[patternCourant].notes[noteEnCours].envsteptime > 0) {
                        chan[chanCourant].pattern[patternCourant].notes[noteEnCours].envsteptime--;
                    }
                }
            }
            if (numParam == 2) {
                if (monte == 1) {
                    if (chan[chanCourant].pattern[patternCourant].notes[noteEnCours].sweeptime < 7) {
                        chan[chanCourant].pattern[patternCourant].notes[noteEnCours].sweeptime++;
                    }
                } else {
                    if (chan[chanCourant].pattern[patternCourant].notes[noteEnCours].sweeptime > 0) {
                        chan[chanCourant].pattern[patternCourant].notes[noteEnCours].sweeptime--;
                    }
                }
            }
            break;

        case 4://Direction
            if (numParam == 1) {
                if (monte == 1) {
                    if (chan[chanCourant].pattern[patternCourant].notes[noteEnCours].sweepdir < 1) {
                        chan[chanCourant].pattern[patternCourant].notes[noteEnCours].sweepdir++;
                    }
                } else {
                    if (chan[chanCourant].pattern[patternCourant].notes[noteEnCours].sweepdir > 0) {
                        chan[chanCourant].pattern[patternCourant].notes[noteEnCours].sweepdir--;
                    }
                }
            }
            if (numParam == 2) {
                if (monte == 1) {
                    if (chan[chanCourant].pattern[patternCourant].notes[noteEnCours].envdir < 1) {
                        chan[chanCourant].pattern[patternCourant].notes[noteEnCours].envdir++;
                    }
                } else {
                    if (chan[chanCourant].pattern[patternCourant].notes[noteEnCours].envdir > 0) {
                        chan[chanCourant].pattern[patternCourant].notes[noteEnCours].envdir--;
                    }
                }
            }
            break;

        case 5://Left Right
            //todo
            break;
    }
}

/*Afficher les notes sur la grille 4x4*/
void afficherNote() {
    u8 x, y, xx, yy, cpt;
    xx = 5;
    yy = 20;
    cpt = 0;

    for (y = 0; y < 4; y++) {
        for (x = 0; x < 4; x++) {
            if (chan[chanCourant].pattern[patternCourant].notes[cpt].sfreq != 99) {
                dessinePotentiometre(xx, yy, cpt);
            }
            cpt++;
            xx += 30;
        }
        yy += 30;
        xx = 5;
    }
}

/*L'écran PATTERN*/
int ecranPattern() {
    remplirEcran(BLANC);
    afficherChaine("PATTERN", 85, 1, ROSE);

    //Affiche le chan
    afficherChaine("PU1", 5, 1, NOIR);

    /*Position en X Y des carrés*/
    //u16 posXCurseurPattern,posYCurseurPattern;
    u16 posXCurseurPattern = 5;
    u16 posYCurseurPattern = 20;

    /*Indices pour se balader dans le carré de 16 notes*/
    //u16 XnoteMax,YnoteMax;
    u16 XnoteMax = 0; //Indice pour ne pas faire dépasser le curseur du menu.
    u16 YnoteMax = 0;

    /*La variable action sert à savoir si on affecte (la position du curseur) aux notes ou au menu*/
    /* 1=notes / 2=menu */
    u16 action;
    action = 1;

    /*Indices pour se balader dans le menu*/
    u16 XmenuMax, YmenuMax;
    XmenuMax = 0;
    YmenuMax = 0;

    /*Affiche les 16 carrés*/
    dessinerPattern(posXCurseurPattern, posYCurseurPattern);

    /*Grise la première note*/
    griserNoteEnCours(posXCurseurPattern, posYCurseurPattern, 'a');

    /*Affiche le menu des paramètres*/
    menu(menuActif, 99);

    /*Utilisé pour sortir de la boucle de cet écran*/
    u16 sortir;
    sortir = 0;

    //test
    u8 note; //test pour la lecture sans tempo.

    //Indice de boucle
    u8 i;

    /*Affiche les potentiomètres sur les carrés d'après le menuActif*/
    afficherNote();

    /*La boucle principale de l'écran*/
    while (sortir == 0) {
        pause(2);
        switch (REG_TOUCHES) {
            case TOUCHE_SELECT | TOUCHE_GAUCHE:
                sortir = 2;
                break;

            case TOUCHE_DROITE:
                //On est dans les notes
                if (action == 1) {
                    if (XnoteMax < 3) {
                        posXCurseurPattern += 30;
                        griserNoteEnCours(posXCurseurPattern, posYCurseurPattern, 'd');
                        noteEnCours++;
                        pause(pauseParDefaut);
                        XnoteMax++;
                    }
                }

                //On est dans le menu
                if (action == 2) {
                    if (XmenuMax < 2) {
                        if (menuActif < 6)
                            menuActif += 5;
                        menu(menuActif, menuActif);
                        afficherNote();
                        XmenuMax++;
                        pause(pauseParDefaut);
                    }
                }
                break;

            case TOUCHE_GAUCHE:
                if (action == 1) {
                    if (XnoteMax > 0) {
                        posXCurseurPattern -= 30;
                        griserNoteEnCours(posXCurseurPattern, posYCurseurPattern, 'g');
                        noteEnCours--;
                        XnoteMax--;
                        pause(pauseParDefaut);
                    }
                }

                if (action == 2) {
                    if (XmenuMax > 0) {
                        if (menuActif > 5)
                            menuActif -= 5;
                        menu(menuActif, menuActif);
                        afficherNote();
                        XmenuMax--;
                        pause(pauseParDefaut);
                    }
                }
                break;

            case TOUCHE_BAS:
                if (action == 1) {
                    if (YnoteMax < 3) {
                        posYCurseurPattern += 30;
                        griserNoteEnCours(posXCurseurPattern, posYCurseurPattern, 'b');
                        noteEnCours += 4;
                        YnoteMax++;
                        pause(pauseParDefaut);
                    }
                }

                if (action == 2) {
                    if (YmenuMax < 4) {
                        if (menuActif < 10) {
                            menuActif++;
                            menu(menuActif, menuActif);
                            afficherNote();
                        }
                        YmenuMax++;
                        pause(pauseParDefaut);
                    }
                }
                break;

            case TOUCHE_HAUT:
                if (action == 1) {
                    if (YnoteMax > 0) {
                        posYCurseurPattern -= 30;
                        griserNoteEnCours(posXCurseurPattern, posYCurseurPattern, 'h');
                        noteEnCours -= 4;
                        YnoteMax--;
                        pause(pauseParDefaut);
                    }
                }

                if (action == 2) {
                    if (YmenuMax > 0) {
                        if (menuActif > 0) {
                            menuActif--;
                            menu(menuActif, menuActif);
                            afficherNote();
                        }
                        YmenuMax--;
                        pause(pauseParDefaut);
                    }
                }
                break;

            case TOUCHE_L:
                if (action == 1) {//On est sur les notes
                    menu(menuActif, menuActif);
                    pause(pauseParDefaut);
                }
                if (action == 2) {//On est sur le menu
                    menu(menuActif, 99);
                    pause(pauseParDefaut);
                }
                action++;
                if (action == 3) {
                    action = 1;
                }

                break;

            case TOUCHE_HAUT | TOUCHE_A:
                if (action == 1) {//On est sur les 16 notes
                    parametreAModifier(1, 1, posXCurseurPattern, posYCurseurPattern);
                    dessinePotentiometre(posXCurseurPattern, posYCurseurPattern, noteEnCours);
                }
                pause(pauseParDefaut);
                break;

            case TOUCHE_BAS | TOUCHE_A:
                if (action == 1) {//On est sur les 16 notes
                    parametreAModifier(1, 0, posXCurseurPattern, posYCurseurPattern);
                    dessinePotentiometre(posXCurseurPattern, posYCurseurPattern, noteEnCours);
                }
                pause(pauseParDefaut);
                break;

            case TOUCHE_DROITE | TOUCHE_A:
                if (action == 1) {//On est sur les 16 notes
                    parametreAModifier(2, 1, posXCurseurPattern, posYCurseurPattern);
                    dessinePotentiometre(posXCurseurPattern, posYCurseurPattern, noteEnCours);
                }
                break;

            case TOUCHE_GAUCHE | TOUCHE_A:
                if (action == 1) {//On est sur les 16 notes
                    parametreAModifier(2, 0, posXCurseurPattern, posYCurseurPattern);
                    dessinePotentiometre(posXCurseurPattern, posYCurseurPattern, noteEnCours);
                }
                break;

                //On pose une note standard
            case TOUCHE_A:
                if (action == 1) {//On est sur les notes
                    /*Si il n'y a pas de note on pose une note par defaut*/
                    if (chan[chanCourant].pattern[patternCourant].notes[noteEnCours].sfreq == 99) {
                        initNote();
                        griserNoteEnCours(posXCurseurPattern, posYCurseurPattern, 'a');
                        dessinePotentiometre(posXCurseurPattern, posYCurseurPattern, noteEnCours);
                    }
                }
                break;

            case TOUCHE_B:
                //On coupe la note en cours
                chan[chanCourant].pattern[patternCourant].notes[99] = chan[chanCourant].pattern[patternCourant].notes[noteEnCours];
                //Efface potentiomètre 1
                for (i = 0; i <= 18; i++) {
                    ligneH(posXCurseurPattern + 4, posYCurseurPattern + 1 + i, 3, BLANC);
                }
                //Efface potentiomètre 2
                for (i = 0; i <= 18; i++) {
                    ligneH(posXCurseurPattern + 13, posYCurseurPattern + 1 + i, 3, BLANC);
                }

                //On Kill la note que l'on vient de couper
                chan[chanCourant].pattern[patternCourant].notes[note].sweeptime = 0;
                chan[chanCourant].pattern[patternCourant].notes[note].sweepdir = 0;
                chan[chanCourant].pattern[patternCourant].notes[note].sweepshifts = 0;
                chan[chanCourant].pattern[patternCourant].notes[note].volume = 0;
                chan[chanCourant].pattern[patternCourant].notes[note].envdir = 0;
                chan[chanCourant].pattern[patternCourant].notes[note].envsteptime = 0;
                chan[chanCourant].pattern[patternCourant].notes[note].waveduty = 0;
                chan[chanCourant].pattern[patternCourant].notes[note].soundlength = 0;
                chan[chanCourant].pattern[patternCourant].notes[note].loopmode = 0;
                chan[chanCourant].pattern[patternCourant].notes[note].sfreq = 99;
                break;

                //Stope ou lance la lecture du son : TEST
            case TOUCHE_START:
                //Test : joue un son VIA boucle CPU !
                //for(note=0;note<16;note++) {
                /*void snd_playSoundOnChannel1(
                                u16 sweeptime, u16 sweepdir, u16 sweepshifts, u16 volume,
                                        u16 envdir, u16 envsteptime, u16 waveduty, u16 soundlength,
                                        u16 loopmode, u8 output, u16 sfreq, u8 transpose);*/
               // startPlayer();
                //	}
                /*if(playing==1) {
                        snd_stopAllSounds();
                        playing = 0;
                }
                else {
                        snd_init_soundApi();
                        playing = 1;
                }
                pause(pauseParDefaut);*/
                break;
        }
    }
    return sortir;
}

int ecranSequenceur() {
    remplirEcran(BLANC);
    afficherChaine("SEQUENCER", 80, 1, ROSE);
    afficherChaine("SOON !", 30, 50, VERT);

    u16 sortir;
    sortir = 0;
    while (sortir == 0) {
        pause(2);
        switch (REG_TOUCHES) {
            case TOUCHE_SELECT | TOUCHE_DROITE:
                sortir = 2;
                pause(15);
                break;
        }
    }
    return sortir;
}

int ecranAbout() {
    remplirEcran(BLANC);
    afficherChaine("ABOUT", 85, 1, ROSE);
    afficherChaine("PICOLOOP IS A FREE SOFT", 5, 20, GRIS);
    afficherChaine("YOU CAN COPY IT", 5, 40, GRIS);
    afficherChaine("ETC ETC ETC ETC", 5, 60, GRIS);
    afficherChaine("MORE INFORMATION ON", 50, 100, BLEUCLAIR);
    afficherChaine("WWW.FLIPFLOP.FR", 70, 120, BLEUCLAIR);
    u16 sortir;
    sortir = 0;
    while (sortir == 0) {
        pause(2);
        switch (REG_TOUCHES) {
            case TOUCHE_SELECT | TOUCHE_BAS:
                sortir = 2;
                break;
        }
    }
    return sortir;
}

/*Boucle infinie qui permet de switcher entre les différents écrans avec select+direction*/
void carte() {
    while (1) {
        pause(10);
        if (position == 99)
            position = ecranAbout();

        if (position == 1)
            position = ecranSequenceur();

        if (position == 2)
            position = ecranProjet();

        if (position == 3)
            position = ecranPattern();
    }
}
