/**
 \file son.h
 \brief Initialisation et gestion du son
 * tout ce qui n'est pas dans la lib sound
 **/

/**
 \brief Tableau de char pour stocker le nom de notes
 **/
const char* noteName[12] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

/**
 * \brief Structure servant à stocker les paramètres des notes.
 * Certains paramètres seront regroupés dans un soucis d'économmie mémoire
 **/
typedef struct NOTE{
	u8 noteName; // C = 0, C# = 1, etc... ca correspond au tableau const plus haut

	//Paramètres pour la fonction snd_playSoundOnChannel1 et 2
	u8 sweeptime;
	u8 sweepdir;
	u8 sweepshifts;
	u8 volume;
    u8 envdir;
    u8 envsteptime;
    u8 waveduty; 
    u8 soundlength;
    u8 loopmode;
    u8 sfreq;
    u8 transpose;
    u8 output;
    
    //Paramètres en plus pour la fonction snd_playSoundOnChannel3
	u8 voice;
    u8 bank;
    u8 bankMode;
    
    //Paramètres en plus pour la fonction snd_playSoundOnChannel4
    u8 shiftFreq;
    u8 stepping;
    u8 freqRatio;
} note;

/**
 \brief Structure pour créer les 16 notes d'un pattern
 **/
typedef struct PATTERN{
	note notes[16];
} pattern;

/**
 \brief Création des patterns pour tous les canaux
 **/
#define NB_PATTERN 2
typedef struct CHANNEL {
	pattern pattern[NB_PATTERN];
} channel;

/*Création des 4 cannaux*/
channel chan[4];

//Channel
u8 chanCourant = 0;//PU1

//Pattern en cours
u8 patternCourant = 0;

//Note en cours
u8 noteEnCours = 0;//noteEnCours = curseurEnCours

