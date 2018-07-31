/*
 * Menu.cpp
 *
 *  Created on: Jul 31, 2018
 *      Author: aperez
 */
#include <string.h>
#include "Menu.h"

int Menu::CountAllMenuItem()
{
	int ret;
    for()
}


int Menu::CountItemByMainMenuItem(std::string tag)
{


}



void Menu::createParentMenuElement(std::string text)
{
    Fl_Menu_Item *item = new Fl_Menu_Item();
    memset(item, 0x00, sizeof(Fl_Menu_Item));
    item->label(text.c_str());
    item->flags = FL_SUBMENU;
    this->parent_menu[text]=item;
}

Fl_Menu_Item *Menu::getMenuCompilation()
{
	int i =0;
    Fl_Menu_Item *ret = new Fl_Menu_Item[];

    return ret;
}
