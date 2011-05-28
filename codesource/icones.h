/*Dessin des icônes*/

/*Dessine l'icone pour l'enveloppe et le volume*/
void iconeEnvVol(u16 x, u16 y, u32 Couleur) {
	u16 taille = 10;
	ligneV(x,y+3,taille-8,Couleur);
	ligneV(x+1,y+2,taille-6,Couleur);
	ligneV(x+2,y+1,taille-4,Couleur);
	ligneV(x+3,y,taille-2,Couleur);
	ligneV(x+4,y-1,taille,Couleur);
	ligneV(x+5,y-1,taille,Couleur);
	
	ligneV(x+7,y+2,1,Couleur);
	ligneV(x+7,y+5,1,Couleur);
	ligneV(x+8,y,1,Couleur);
	ligneV(x+8,y+3,2,Couleur);
	ligneV(x+8,y+7,1,Couleur);

	ligneV(x+9,y+1,1,Couleur);
	ligneV(x+9,y+6,1,Couleur);
	ligneV(x+10,y+2,4,Couleur);
}

/*Dessine l'icone pour la note et l'octave*/
void iconeNoteOctave(u16 x, u16 y, u32 Couleur) {
	ligneH(x+2,y,6,Couleur);
	ligneH(x+2,y+1,6,Couleur);
	ligneV(x+2,y,5,Couleur);
	ligneV(x+1,y+3,2,Couleur);
	ligneV(x,y+3,2,Couleur);
	ligneV(x+8,y,8,Couleur);
	ligneV(x+7,y+6,2,Couleur);
	ligneV(x+6,y+6,2,Couleur);
}

/*Dessine l'icone Pulse (onde carré)*/
void pulse(u16 x, u16 y, u16 taille, u32 Couleur) {
	ligneV(x,y,taille,Couleur);
	ligneV(x+1,y,taille,Couleur);
	ligneH(x,y+1,taille,Couleur);
	ligneH(x,y,taille,Couleur);
	ligneV(x+taille-1,y,taille,Couleur);
	ligneV(x+taille,y,taille,Couleur);
	ligneH(x+taille,y-1+taille,taille,Couleur);
	ligneH(x+taille,y+taille,taille,Couleur);
	ligneV(x+(taille*2)-1,y,taille,Couleur);
	ligneV(x+(taille*2),y,taille,Couleur);
}

/*Dessine l'icone WAVE (onde modifiable)*/
void iconeOnde(u16 x, u16 y, u16 taille, u32 Couleur) {
	ligneV(x,y+5,taille-5,Couleur);
	ligneV(x+1,y+5,taille-5,Couleur);
	ligneV(x+2,y,taille,Couleur);
	ligneV(x+3,y,taille,Couleur);
	ligneV(x+4,y+4,taille-4,Couleur);
	ligneV(x+5,y+4,taille-4,Couleur);
	ligneV(x+6,y+1,taille-1,Couleur);
	ligneV(x+7,y+1,taille-1,Couleur);
	ligneV(x+8,y+3,taille-3,Couleur);
	ligneV(x+9,y+3,taille-3,Couleur);
	ligneV(x+10,y+1,taille-1,Couleur);
	ligneV(x+11,y+1,taille-1,Couleur);
}

/*Dessine l'icone Gauche Droite*/
void iconeGaucheDroite(u16 x, u16 y, u32 Couleur) {
	rectangle(x,y,16,8,Couleur);
	ligneV(x+8,y,8,Couleur);
	//L
	ligneV(x+2,y+2,4,Couleur);
	ligneH(x+3,y+6,3,Couleur);
	//R
	ligneV(x+10,y+3,3,Couleur);
	ligneH(x+11,y+2,3,Couleur);
}

void iconeEffet1(u16 x, u16 y, u32 Couleur) {
	carre(x,y,2,Couleur);
	carre(x+5,y,2,Couleur);
	carre(x,y+5,2,Couleur);
	carre(x+5,y+5,2,Couleur);
}

void iconeEffet2(u16 x, u16 y, u32 Couleur) {
	carre(x,y+6,2,Couleur);
	carre(x+5,y+3,2,Couleur);
	carre(x+10,y,2,Couleur);
}

void iconeEffet3(u16 x, u16 y, u32 Couleur) {
	carre(x,y,2,Couleur);
	carre(x+5,y,2,Couleur);
	carre(x+10,y,2,Couleur);
}

void iconeEffet4(u16 x, u16 y, u32 Couleur) {
	carre(x,y,2,Couleur);
	carre(x+5,y+3,2,Couleur);
	carre(x+10,y+6,2,Couleur);
}

void iconeEffet5(u16 x, u16 y, u32 Couleur) {
	carre(x,y,2,Couleur);
	carre(x+5,y+3,2,Couleur);
	carre(x+10,y+6,2,Couleur);
}

void horloge(u16 x, u16 y ,u32 Couleur) {
	ligneH(x,y,8,Couleur);
	ligneH(x,y+10,8,Couleur);
	ligneV(x,y,8,Couleur);
	ligneV(x+8,y,8,Couleur);
	
}

/*Afficher les icônes du menu de l'écran Pattern*/
void menu(u8 menuActif, u8 menuEnCours) {
	int Couleur = GRIS;
	int Couleur1 = NOIR;
	u8 xMenu = 190;
	u8 yMenu = 20;
	
	/*Première ligne du menu*/
	if(menuActif==1) {
		iconeEnvVol(xMenu,yMenu,Couleur1);
		if(menuEnCours==1) {
			rectangle(xMenu-3,yMenu-3,20,16,NOIR);
		} else {
			rectangle(xMenu-3,yMenu-3,20,16,BLANC);//Efface
		}
	}
	else {
		rectangle(xMenu-3,yMenu-3,20,16,BLANC);//Efface
		iconeEnvVol(xMenu,yMenu,Couleur);
	}
		
	yMenu += 20;
	if(menuActif==2) {
		iconeNoteOctave(xMenu+2,yMenu,Couleur1);
		if(menuEnCours==2) {
			rectangle(xMenu-3,yMenu-3,20,16,NOIR);
		} else {
			rectangle(xMenu-3,yMenu-3,20,16,BLANC);//Efface
		}
	}
	else {
		rectangle(xMenu-3,yMenu-3,20,16,BLANC);//Efface
		iconeNoteOctave(xMenu+2,yMenu,Couleur);
	}
	
	
	
	
	yMenu += 20;
	if(menuActif==3) {
		horloge(xMenu,yMenu,Couleur1);
		if(menuEnCours==3) {
			rectangle(xMenu-3,yMenu-3,20,16,NOIR);
		} else {
			rectangle(xMenu-3,yMenu-3,20,16,BLANC);//Efface
		}
	}
	else {
		rectangle(xMenu-3,yMenu-3,20,16,BLANC);//Efface
		horloge(xMenu,yMenu,Couleur);
	}
	
	
		
	yMenu += 20;
	if(menuActif==4) {
		pulse(xMenu,yMenu,7,Couleur1);
		if(menuEnCours==3) {
			rectangle(xMenu-3,yMenu-3,20,16,NOIR);
		} else {
			rectangle(xMenu-3,yMenu-3,20,16,BLANC);//Efface
		}
	}
	else {
		rectangle(xMenu-3,yMenu-3,20,16,BLANC);//Efface
		pulse(xMenu,yMenu,7,Couleur);
	}
		
	yMenu += 20;
	if(menuActif==5) {
		iconeOnde(xMenu,yMenu,7,Couleur1);
		if(menuEnCours==4) {
			rectangle(xMenu-3,yMenu-3,20,16,NOIR);
		} else {
			rectangle(xMenu-3,yMenu-3,20,16,BLANC);//Efface
		}
	}
	else {
		rectangle(xMenu-3,yMenu-3,20,16,BLANC);//Efface
		iconeOnde(xMenu,yMenu,7,Couleur);
	}
	
	yMenu += 20;
	if(menuActif==6) {
		iconeGaucheDroite(xMenu-1,yMenu,Couleur1);
		if(menuEnCours==5) {
			rectangle(xMenu-3,yMenu-3,20,16,NOIR);
		} else {
			rectangle(xMenu-3,yMenu-3,20,16,BLANC);//Efface
		}
	}
	else {
		rectangle(xMenu-3,yMenu-3,20,16,BLANC);//Efface
		iconeGaucheDroite(xMenu-1,yMenu,Couleur);
	}
	
	/*Deuxième ligne du menu*/
	xMenu = 220;
	yMenu = 20;
	if(menuActif==7) {
		iconeEffet1(xMenu,yMenu,Couleur1);
		if(menuEnCours==6) {
			rectangle(xMenu-3,yMenu-3,20,16,NOIR);
		} else {
			rectangle(xMenu-3,yMenu-3,20,16,BLANC);//Efface
		}
	} else {
		rectangle(xMenu-3,yMenu-3,20,16,BLANC);//Efface
		iconeEffet1(xMenu,yMenu,Couleur);
	}
		
	yMenu += 20;
	if(menuActif==8) {
		iconeEffet2(xMenu,yMenu,Couleur1);
		if(menuEnCours==7) {
			rectangle(xMenu-3,yMenu-3,20,16,NOIR);
		} else {
			rectangle(xMenu-3,yMenu-3,20,16,BLANC);//Efface
		}
	} else {
		rectangle(xMenu-3,yMenu-3,20,16,BLANC);//Efface
		iconeEffet2(xMenu,yMenu,Couleur);
	}
		
	yMenu += 20;
	if(menuActif==9) {
		iconeEffet3(xMenu,yMenu,Couleur1);
		if(menuEnCours==8) {
			rectangle(xMenu-3,yMenu-3,20,16,NOIR);
		} else {
			rectangle(xMenu-3,yMenu-3,20,16,BLANC);//Efface
		}
	} else {
		rectangle(xMenu-3,yMenu-3,20,16,BLANC);//Efface
		iconeEffet3(xMenu,yMenu,Couleur);
	}
		
	yMenu += 20;
	if(menuActif==10) {
		iconeEffet4(xMenu,yMenu,Couleur1);
		if(menuEnCours==9) {
			rectangle(xMenu-3,yMenu-3,20,16,NOIR);
		} else {
			rectangle(xMenu-3,yMenu-3,20,16,BLANC);//Efface
		}
	} else {
		rectangle(xMenu-3,yMenu-3,20,16,BLANC);//Efface
		iconeEffet4(xMenu,yMenu,Couleur);
	}
		
	yMenu += 20;
	if(menuActif==11) {
		iconeEffet5(xMenu,yMenu,Couleur1);
		if(menuEnCours==10) {
			rectangle(xMenu-3,yMenu-3,20,16,NOIR);
		} else {
			rectangle(xMenu-3,yMenu-3,20,16,BLANC);//Efface
		}
	} else {
		rectangle(xMenu-3,yMenu-3,20,16,BLANC);//Efface
		iconeEffet5(xMenu,yMenu,Couleur);
	}
}
