/**
 * \file main.h
 * \brief Définition des types de variables et registres utilisés
 **/

/**
 * \brief Types usuels sur GBA
 **/
//typedef unsigned char    u8;
//typedef unsigned short   u16;
//typedef unsigned long    u32;

/**
 * Variables globales
 **/
int numBank;
int position=2;
u8	playing = 1;//Par défaut lorsque l'on demarre picoloop ça joue la musique.
u8 menuActif = 1;/*Quel est le paramètre du menu qui est actif : volume/envelope OU note/Octave etc. Par défaut on met en menuActif l'icone Volume/Enveloppe*/
#define pauseParDefaut 10


/**
 *\brief Registres pour la gestion de l'écran et mode graphique
 **/
#define REG_DISPCNT *(volatile u32*)0x4000000
#define MODE_3          0x3
#define MODE_4          0x4
#define BG2             0x400 // background 2
#define OBJ_ENABLED		0x0100

/** 
 \brief Dimensions de l'écran en mode 4
 **/
#define LARGEUR_ECRAN	240
#define HAUTEUR_ECRAN	160

/** 
 \biref Écran et palette de couleurs
 **/
u16* videoBuffer 	= (u16*) 0x6000000;
u16* palette       	= (u16*) 0x5000000;
u16* spritePalette 	= (u16*) 0x5000200;

/**
 *\brief Couleur RGB
 **/
#define RGBPICO(r, g, b)     ((r) | (g << 5) | (b << 10)) // Pour mode 3
//#define RGB(r,g,b)        ((r)+((g)<<5)+((b)<<10)) //pour le mode 4 ?

/** 
 \brief La gestion des touches
 **/
#define REG_KEYS *(volatile unsigned long*) 0x4000130
#define REG_TOUCHES (~(REG_KEYS) & 0x03FF)

#define TOUCHE_A 		0x0001
#define TOUCHE_B 		0x0002
#define TOUCHE_SELECT 	0x0004
#define TOUCHE_START 	0x0008
#define TOUCHE_DROITE 	0x0010
#define TOUCHE_GAUCHE 	0x0020
#define TOUCHE_HAUT 	0x0040
#define TOUCHE_BAS 		0x0080
#define TOUCHE_R 		0x0100
#define TOUCHE_L		0x0200

/**
 \brief Définition des Couleurs
 * http://www.jokconcept.net/codes-couleurs-hexdecimal.php)
 */
#define BLANC	RGBPICO(255, 255, 255)
#define ROUGE	RGBPICO(255, 0, 0)
#define JAUNE	RGBPICO(255, 255, 0)
#define BLEU	RGBPICO(0, 10, 153)
#define BLEUCLAIR	RGBPICO(0, 25, 153)
#define NOIR	RGBPICO(0, 0, 0)
#define GRIS	RGBPICO(90,90,90)
#define VERT	RGBPICO(100,200,100)
#define VIOLET	RGBPICO(50,100,50)
#define ROSE	RGBPICO(255,204,255)

/**
 \brief Registres pour les Timers
 *A voir plus tard avec HAM
 */
#define TIME_FREQUENCY_SYSTEM 0x0
#define TIME_FREQUENCY_64 0x1
#define TIME_FREQUENCY_256 0x2
#define TIME_FREQUENCY_1024 0x3
#define TIME_OVERFLOW 0x4
#define TIME_ENABLE 0x80
#define TIME_IRQ_ENABLE 0x40

#define REG_TM2DPICO         *(volatile u16*) 0x4000108
#define REG_TM2CNTPICO       *(volatile u16*) 0x400010A
#define REG_TM3DPICO         *(volatile u16*) 0x400010C
#define REG_TM3CNTPICO       *(volatile u16*) 0x400010E

