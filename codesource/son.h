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
typedef struct NOTE {
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
typedef struct PATTERN {
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
u8 chanCourant = 0; //PU1

//Pattern en cours
u8 patternCourant = 0;

//Note en cours
u8 noteEnCours = 0; //noteEnCours = curseurEnCours


//Timer !
#define WAIT_LOOP 1
int cpt = 0;
int compteurCycle = 0;

void timerFunction() {
    compteurCycle++;
    if (compteurCycle > WAIT_LOOP) {
        cpt++;
         snd_playSoundOnChannel1(
                chan[chanCourant].pattern[patternCourant].notes[note].sweeptime,
                chan[chanCourant].pattern[patternCourant].notes[note].sweepdir,
                chan[chanCourant].pattern[patternCourant].notes[note].sweepshifts,
                chan[chanCourant].pattern[patternCourant].notes[note].volume,
                chan[chanCourant].pattern[patternCourant].notes[note].envdir,
                chan[chanCourant].pattern[patternCourant].notes[note].envsteptime,
                chan[chanCourant].pattern[patternCourant].notes[note].waveduty,
                chan[chanCourant].pattern[patternCourant].notes[note].soundlength,
                chan[chanCourant].pattern[patternCourant].notes[note].loopmode,
                chan[chanCourant].pattern[patternCourant].notes[note].output,
                chan[chanCourant].pattern[patternCourant].notes[note].sfreq, 0);
        compteurCycle = 0;
    }
}

void startPlayer() {
    ham_StartIntHandler (INT_TYPE_TIM3, (void*) &timerFunction);
    R_TIM3CNT = 0;
    M_TIM3CNT_IRQ_ENABLE
    M_TIM3CNT_TIMER_START
}

//
//int main() {
//
//    ham_Init();
//    ham_InitText(1);
//    ham_SetBgMode(0);
//    
//    ham_DrawText(0,1,"WTF ?");
//    
//    ham_StartIntHandler (INT_TYPE_TIM3, (void*) &timerFunction);
//    R_TIM3CNT = 0;
//    M_TIM3CNT_IRQ_ENABLE
//    M_TIM3CNT_TIMER_START
//    
//    while (1){
//    }
//    
//    return 0;
//}
//
