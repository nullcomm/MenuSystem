/*
 * MenuSystem.cpp
 *
 *  Created on: Aug 10, 2015
 *      Author: cnull
 */

#include "MenuSystem.h"

MenuSystem::MenuSystem(char ** mTitles, char ** aTitles, char ** aValues, int ** menus, int lcdPin, int width)
: serLCD(lcdPin)
{
	setMenuTitles(mTitles);
	setActionTitles(aTitles);
	setActionValues(aValues);
	setMenus(menus);
	_screenWidth = width;
	_curMenu = 0;
	_curSubMenu = 1;
	_curOption = 0;
}

void MenuSystem::displayMenu(){
    if (_curMenu == 0){
        if(_curSubMenu < _numMenuTitles){
            printTopMenu(getMenuTitle(_curMenu), _screenWidth);
            printSubMenu(getMenuTitle(_curSubMenu), _screenWidth - 4);
        }
    }else{
        printTopMenu(getMenuTitle(_curMenu), _screenWidth);
        if(getMenuOption(_curSubMenu, _curOption)){
            printSubMenu(getActionTitle(getMenuOption(_curSubMenu,_curOption) - 1), _screenWidth - 4);
        }
    }
}


void MenuSystem::printSubMenu(char* val, int width){
	clearLine(2);
	print("< ");
	for(int i = 0; i < getLeftPadding(val, width); i++){
		print(" ");
	}
	print(val);
	for(int i = 0; i < getRightPadding(val, width); i++){
		print(" ");
	}
	print(" >");
}

void MenuSystem::printTopMenu(char* val, int width){
	clearLine(1);
	for(int i = 0; i < getLeftPadding(val, width); i++){
		print(" ");
	}
	print(val);
	for(int i = 0; i < getRightPadding(val, width); i++){
		print(" ");
	}

}

int MenuSystem::getLeftPadding(char* val, int width){
	int len = strlen(val);
	if (len < width){
//		Serial.print("Left padding = ");
//		Serial.println((width - len) / 2);
		return (width - len) / 2;
	}
	return 0;
};

int MenuSystem::getRightPadding(char* val, int width){
	int len = strlen(val);
	if(len < width){
		if((width - len) % 2 == 0){
//			Serial.print("Right padding = ");
//			Serial.println((width -len) / 2);
			return (width - len) / 2;
		}else{
//			Serial.print("Right padding = ");
//			Serial.println(((width - len) / 2) + 1);
			return ((width -len) / 2) + 1;
		}
	}
	return 0;
};

void MenuSystem::setMenus(int ** array){
	_menus = array;
}

void MenuSystem::setMenuTitles(char ** array){
	int x = 0;
	while(strlen(array[x])){
		x++;
	}
//	Serial.print("Num Titles : ");
//	Serial.print(x);
//	Serial.print(" Num SubMenus : ");
//	Serial.println(x - 1);
	_numMenuTitles = x;
	_numSubMenus = x -1;
	_mTitles = array;
}

void MenuSystem::setActionTitles(char ** array){
	int x = 0;
	while(strlen(array[x])){
		x++;
	}
	_numActionTitles = x;
	_aTitles = array;
}

void MenuSystem::setActionValues(char ** array){
	int x = 0;
	while(strlen(array[x])){
		x++;
	}
	_numActionValues = x;
	_aValues = array;
}

char * MenuSystem::getMenuTitle(int num){
	return _mTitles[num];
}

char * MenuSystem::getActionTitle(int num){
	return _aTitles[num];
}

char * MenuSystem::getActionValue(int num){
	return _aValues[num];
}

int MenuSystem::getMenuOption(int menu, int option){
	if(menu > 0 && menu <= _numMenuTitles){
		int x = 0;
		while(_menus[menu][x] > 0){
			x++;
		}
		option -= 1;
		if(option  >= 0 && option < x){
			return _menus[menu][option];
		}
	}
	return false;
}

void MenuSystem::displayNextSubMenu(){
    if(_curSubMenu + 1 <= _numMenuTitles){
        _curSubMenu++;
        displayMenu();
    }
}

void MenuSystem::displayPrevSubMenu(){
    if(_curSubMenu - 1 > 0){
        _curSubMenu--;
        displayMenu();
    }
}

void MenuSystem::selectSubMenu(){
    _curMenu = _curSubMenu;
    _curOption = getMenuOption(_curMenu,1);
    Serial.print("Current Menu : ");
    Serial.println(_curMenu);
    Serial.print("Current option : ");
    Serial.println(_curOption);
    displayMenu();
}

void MenuSystem::deSelectSubMenu(){
    _curMenu = 0;
    displayMenu();
}

void MenuSystem::displayNextAction(){
    if(getMenuOption(_curSubMenu, (_curOption + 1))){
        _curOption++;
        displayMenu();
    }
}

void MenuSystem::displayPrevAction(){
    if(getMenuOption(_curSubMenu, (_curOption - 1))){
        _curOption--;
        displayMenu();
    }
}

void MenuSystem::displayNextMenu(){
    if((_curSubMenu + 1) <= _numSubMenus ){
        _curSubMenu++;
    }else{
        _curSubMenu = 1;
    }
    displayMenu();
}

int MenuSystem::getCurMenu(){
	return _curMenu;
}

int MenuSystem::getCurSubMenu(){
	return _curSubMenu;
}

int MenuSystem::getCurOption(){
	return _curOption;
}

MenuSystem::~MenuSystem() {
	// TODO Auto-generated destructor stub
}

