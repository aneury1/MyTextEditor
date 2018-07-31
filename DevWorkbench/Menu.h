/*
 * Menu.h
 *
 *  Created on: Jul 31, 2018
 *      Author: aperez
 */

#ifndef MENU_H_
#define MENU_H_
#include <FL/Fl_Menu_Item.h>
#include <map>
#include <string>
class Menu
{
    struct menu_children
    {
    	Fl_Menu_Item* item;
    	std::string parent;
    };
    std::map<std::string, Fl_Menu_Item *>parent_menu;
    std::map<std::string, menu_children *>children;

    int CountAllMenuItem();
    int CountItemByMainMenuItem(std::string tag);
    int CountParentMainMenuItem();

public:

    void createParentMenuElement(std::string text);

    Fl_Menu_Item *getMenuCompilation();


};





#endif /* MENU_H_ */
