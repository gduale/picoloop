#include <string.h> //Pour strlen()

/*Attente de la synchronisation verticale : 60 par seconde en hardware*/
void waitForVSync() {
    volatile u16* vreg = (volatile u16*) 0x04000004;
    while (*vreg & (1 << 0));
    while (!(*vreg & (1 << 0)));
}

/*Faire une pause basé sur la synchronisation verticale*/
void pause(unite) {
    u16 i;
    for (i = 0; i < unite; i++)
        waitForVSync();
}

/*Rempli l'écran de blanc*/
void remplirEcran(int Couleur) {
    u16 x, y;
    for (y = 0; y < 160; y++) {
        for (x = 0; x < 240; x++) {
            videoBuffer[y * 240 + x] = Couleur;
        }
    }
}

/*Dessine un carré à la dimension et aux positions donnée en paramètre*/
void carre(u16 posX, u16 posY, u16 taille, int Couleur) {
    u16 x, y;
    for (y = posY; y < posY + taille; y++) {
        for (x = posX; x < posX + taille; x++)
            videoBuffer[y * 240 + x] = Couleur;
    }
}

/*Affiche une pou16 à une position donnée pour une couleurs précise*/
void afficherPoint(u16 x, u16 y, int Couleur) {
    //	u16 gris=rand() % 31;
    videoBuffer[y * 240 + x] = Couleur;
}

/*Affiche une lettre à une position donnée*/
void afficherLettre(const int *Lettre, u16 posX, u16 posY, int Couleur) {
    u16 i, x, y;
    i = 0;
    for (y = posY; y < posY + 8; y++) {
        for (x = posX; x < posX + 8; x++) {
            if (Lettre[i] == 1)
                afficherPoint(x, y, Couleur);
            i++;
        }
    }
}

/*Afficher une chaine de caractère*/
//afficherChaine("FLIP FLOP",5,5,BLANC);

void afficherChaine(char *maChaine, int indiceX, int indiceY, int Couleur) {
    u16 cpt = 0;
    while (cpt < strlen(maChaine)) {
        if (maChaine[cpt] == 'A')
            afficherLettre(A, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == 'B')
            afficherLettre(B, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == 'C')
            afficherLettre(C, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == 'D')
            afficherLettre(D, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == 'E')
            afficherLettre(E, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == 'F')
            afficherLettre(F, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == 'G')
            afficherLettre(G, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == 'H')
            afficherLettre(H, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == 'I')
            afficherLettre(I, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == 'J')
            afficherLettre(J, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == 'K')
            afficherLettre(K, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == 'L')
            afficherLettre(L, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == 'M')
            afficherLettre(M, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == 'N')
            afficherLettre(N, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == 'O')
            afficherLettre(O, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == 'P')
            afficherLettre(P, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == 'Q')
            afficherLettre(Q, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == 'R')
            afficherLettre(R, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == 'S')
            afficherLettre(S, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == 'T')
            afficherLettre(T, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == 'U')
            afficherLettre(U, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == 'V')
            afficherLettre(V, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == 'W')
            afficherLettre(W, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == 'X')
            afficherLettre(X, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == 'Y')
            afficherLettre(Y, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == 'Z')
            afficherLettre(Z, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == ' ')
            afficherLettre(ESPACE, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == '!')
            afficherLettre(ESCLAMATION, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == '@')
            afficherLettre(AROBASE, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == '#')
            afficherLettre(DIEZE, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == '.')
            afficherLettre(POINT, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == '-')
            afficherLettre(TIRET, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == ':')
            afficherLettre(DEUXPOINT, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == '/')
            afficherLettre(SLASH, indiceX, indiceY, Couleur);

        //Les minuscules
        if (maChaine[cpt] == 'a')
            afficherLettre(a, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == 'b')
            afficherLettre(b, indiceX, indiceY, Couleur);

        //Utilisé pour effacer
        if (maChaine[cpt] == 'w')
            afficherLettre(w, indiceX, indiceY, Couleur);

        //Les chiffres
        if (maChaine[cpt] == '0')
            afficherLettre(c0, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == '1')
            afficherLettre(c1, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == '2')
            afficherLettre(c2, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == '3')
            afficherLettre(c3, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == '4')
            afficherLettre(c4, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == '5')
            afficherLettre(c5, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == '6')
            afficherLettre(c6, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == '7')
            afficherLettre(c7, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == '8')
            afficherLettre(c8, indiceX, indiceY, Couleur);
        if (maChaine[cpt] == '9')
            afficherLettre(c9, indiceX, indiceY, Couleur);

        cpt++;
        indiceX += 8;
        if (cpt == 24) {
            indiceY += 8;
            indiceX -= 192;
        }
    }

}

/*Afficher une ligne horizontale*/
void ligneH(u16 x, u16 y, u16 taille, int Couleur) {
    u16 i;
    for (i = 0; i <= taille; i++) {
        afficherPoint(x, y, Couleur);
        x++;
    }
}

/*Afficher une ligne verticale*/
void ligneV(u16 x, u16 y, u16 taille, int Couleur) {
    u16 i;
    for (i = 0; i <= taille; i++) {
        afficherPoint(x, y, Couleur);
        y++;
    }
}

/*Dessine un rentangle à la dimension et aux positions donnée en paramètre*/
void curseur(u16 x, u16 y, u16 taille, int Couleur) {
    ligneH(x, y, taille, Couleur);
    ligneV(x, y, taille, Couleur);
    ligneV(x + taille, y, taille, Couleur);
    ligneH(x, y + taille, taille, Couleur);
}

/*Dessine un rentangle à la dimension et aux positions donnée en paramètre*/
void rectangle(u16 x, u16 y, u16 largeur, u16 hauteur, int Couleur) {
    ligneH(x, y, largeur, Couleur);
    ligneV(x, y, hauteur, Couleur);
    ligneV(x + largeur, y, hauteur, Couleur);
    ligneH(x, y + hauteur, largeur, Couleur);
}

//void dessinerPattern(u8 posXCurseurPattern, u8 noteEnCours) {

void dessinerPattern(u8 posXCurseurPattern, u8 posYCurseurPattern) {
    u8 x, y, xx, yy;
    xx = 0;
    yy = posYCurseurPattern;

    //Tailles des carrés
    u8 tailleCarre;
    tailleCarre = 20;

    //Couleur des carrés
    u8 Couleur = NOIR;

    //On dessine les 16 carrés
    for (y = 0; y < 4; y++) {
        for (x = 0; x < 4; x++) {
            rectangle(xx + posXCurseurPattern, yy, tailleCarre, tailleCarre, Couleur);
            ligneV(xx + posXCurseurPattern + 3, yy, tailleCarre, Couleur);
            ligneV(xx + posXCurseurPattern + 8, yy, tailleCarre, Couleur);
            ligneV(xx + posXCurseurPattern + 12, yy, tailleCarre, Couleur);
            ligneV(xx + posXCurseurPattern + 17, yy, tailleCarre, Couleur);
            xx += 30;
        }
        yy += 30;
        xx = 0;
    }
}

/*Fonction prise sur AFDAC, elle affiche un pixel de couleur en mode 4 (et en mode 3 aussi visiblement)*/
void Mode4_PutPixel(u16 x, u16 y, u8 Couleur) {
    u16 temp;
    //récupère la valeur qui est déjà à cette place.
    temp = videoBuffer[(y * 240 + x) >> 1];
    if (x & 1) {
        //Si coordonée x paire
        // Efface la partie haute de la variable
        temp = temp & 0x00FF;
        temp = temp + (Couleur << 8);
    } else {
        //Si coordonée x impaire
        // Efface la partie basse de la variable
        temp = temp & 0xFF00;
        temp = temp + Couleur;
    }
    videoBuffer[(y * 240 + x) >> 1] = temp;
}

