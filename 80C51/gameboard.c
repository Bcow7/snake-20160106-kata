#include <string.h>
#include "main.h"
#include "t6963c.h"
#include "bdd.h"
#include "gameboard.h"

#define ROM_CG_ADDRESS 0x0000

/**
 * Copie la d�finition d'un caract�re depuis la ROM vers la zone de d�finition
 * des caract�res du T6963C.
 * @param positionInRom Position du caract�re dans la ROM.
 * @param cgCode Code du caract�re dans le t6963c.
 */
void GMB_copyFromRomToCg(unsigned char positionInRom, unsigned char cgCode) {
	unsigned char *rom_cg_address = (unsigned char __xdata *) (ROM_CG_ADDRESS + positionInRom * 8);
	unsigned int video_cg_address = cgCode * 8 + T6963C_ZONE_CG;
	T6963C_autoWrite(video_cg_address, rom_cg_address, 8);
}

/**
 * Initialise les caract�res utilis�s pendant le jeu.
 */
void GMB_initialize() {
	GMB_copyFromRomToCg( 0, OBSTACLE_A);
	GMB_copyFromRomToCg( 1, OBSTACLE_B);
	GMB_copyFromRomToCg( 2, OBSTACLE_C);
	GMB_copyFromRomToCg( 3, OBSTACLE_D);
	GMB_copyFromRomToCg( 4, OBSTACLE_E);
	GMB_copyFromRomToCg( 5, OBSTACLE_F);
	GMB_copyFromRomToCg( 6, OBSTACLE_G);
	GMB_copyFromRomToCg( 7, OBSTACLE_H);

	GMB_copyFromRomToCg( 8, SNAKE_BODY);
	GMB_copyFromRomToCg( 9, SNAKE_SWALLOW);
	GMB_copyFromRomToCg(10, SNAKE_HEAD);
	GMB_copyFromRomToCg(11, SNAKE_DEAD);

	GMB_copyFromRomToCg(12, FRUIT);
}

/**
 * Dessine un rectangle entre les coordonn�es sp�cifi�es.
 * Le carr� est dessin� avec des caract�res OBSTACLE_*, pour
 * que le serpent ne puisse pas le traverser.
 * @param x0, y0: Coordonn�es de l'angle sup�rieur droit.
 * @param x1, y1: Coordonn�es de l'angle inf�rieur gauche.
 */
void GMB_draw(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1) {
	// � faire
}

/**
 * Remplit avec des espaces le rectangle d�fini par les coordonn�es.
 * Permet de nettoyer l'int�rieur du rectangle dessin� avec GMB_draw.
 * @param x0, y0: Coordonn�es de l'angle sup�rieur droit.
 * @param x1, y1: Coordonn�es de l'angle inf�rieur gauche.
 */
void GMB_clear(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1) {
	// � faire
}

/**
 * Affiche un texte entour� d'un rectangle.
 * La largeur du rectangle est d�finie par la longueur du texte.
 * La fonction ne v�rifie pas si le texte d�passe les bords de l'�cran.
 * @param x0, y0 L'angle sup�rieur droit du rectangle.
 * @param text Le texte � afficher.
 */
void GMB_display(unsigned char x0, unsigned char y0, char *text) {
	// � faire
}

#ifdef TEST
int bddGameboardDraw() {
	BddExpectedContent c = {
		"ABBBBBBBBC",
		"D........E",
		"D........E",
		"D........E",
		"FGGGGGGGGH"
	};

	BDD_clear();
	GMB_draw(BDD_SCREEN_X, BDD_SCREEN_Y, BDD_SCREEN_X + BDD_SCREEN_WIDTH - 1, BDD_SCREEN_Y + BDD_SCREEN_HEIGHT - 1);
	return BDD_assert(c, "GMBD");
}

int bddGameboardClear() {
	BddExpectedContent c = {
		"..........",
		".        .",
		".        .",
		".        .",
		".........."
	};

	BDD_clear();
	GMB_clear(BDD_SCREEN_X + 1, BDD_SCREEN_Y + 1, BDD_SCREEN_X + BDD_SCREEN_WIDTH - 2, BDD_SCREEN_Y + BDD_SCREEN_HEIGHT - 2);
	return BDD_assert(c, "GMBC");
}

int bddGameboardDisplay() {
	BddExpectedContent c = {
		"..........",
		".ABBBBBC..",
		".D TXT E..",
		".FGGGGGH..",
		".........."
	};

	BDD_clear();
	GMB_display(BDD_SCREEN_X + 1, BDD_SCREEN_Y + 1, " TXT ");
	return BDD_assert(c, "GMBT");
}

int testGameboard() {
	int testsInError = 0;

	testsInError += bddGameboardDraw();
	testsInError += bddGameboardClear();
	testsInError += bddGameboardDisplay();

	return testsInError;
}
#endif
