#include "GlobalStructure.hxx"
#include "Menu.h"
#include <FL/Fl_Menu_Bar.h>
#include <FL/Fl.h>


int main(int argc, char *argv[])
{
   _data.main_window = new Fl_Double_Window(0,0,Fl::w()-10, Fl::h(),"UNTITLED");
   Menu menua;
   menua.createParentMenuElement("File");
   menua.createParentMenuElement("File");
   menua.createParentMenuElement("File");
   menua.createParentMenuElement("File");
   Fl_Menu_Bar* menu= new Fl_Menu_Bar(1,1,300,58);
   menu->copy(menua.getMenuCompilation());
   _data.main_window->end();
   _data.main_window->show(argc,argv);
   return Fl::run();
}
