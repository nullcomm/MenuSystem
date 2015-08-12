/*
 * MenuSystem.h
 *
 *  Created on: Aug 10, 2015
 *      Author: cnull
 */

#ifndef MENUSYSTEM_H_
#define MENUSYSTEM_H_

#include <serLCD.h>

class MenuSystem: public serLCD {
public:
	MenuSystem(char**,char**,char**,int**,int,int width=16);
	virtual ~MenuSystem();
	void setMenuTitles(char**);
	void setActionTitles(char**);
	void setActionValues(char**);
	void setMenus(int**);

	int getRightPadding(char*, int);
	int getLeftPadding(char*, int);

	char * getMenuTitle(int);
	char * getActionTitle(int);
	char * getActionValue(int);
	int getMenuOption(int, int);

	void printTopMenu(char*, int);
	void printSubMenu(char*, int);

	void displayMenu();
	void displayNextMenu();

	void displayNextSubMenu();
	void displayPrevSubMenu();

	void displayNextAction();
	void displayPrevAction();

	void selectSubMenu();
	void deSelectSubMenu();

	int getCurMenu();
	int getCurSubMenu();
	int getCurOption();


private:
	char ** _mTitles;
	char ** _aTitles;
	char ** _aValues;
	int  ** _menus;

	int _curMenu;
	int _curSubMenu;
	int _curOption;

	int _screenWidth;

	int _numMenuTitles;
	int _numActionTitles;
	int _numActionValues;

	int _numSubMenus;
};

#endif /* MENUSYSTEM_H_ */
