/*
 * ApplicationEditor.hxx
 *
 *  Created on: Sep 28, 2017
 *      Author: aperez
 */

#ifndef APPLICATIONEDITOR_HXX_
#define APPLICATIONEDITOR_HXX_

#include <FL/FL_Double_Window.H>
#include <FL/FL_Text_Editor.H>
#include <FL/FL_Text_Buffer.H>
#include <FL/FL_Menu_Bar.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Button.H>


class ApplicationEditor : public Fl_Text_Editor
{

public:
	ApplicationEditor(int X, int Y, int W, int H, const char* l = 0);
    ~ApplicationEditor();
    virtual int handle(int e);
    void insert_mode(int b);
    int insert_mode();

    void add_key_binding(int key, int state, Key_Func f, Key_Binding** list);
    void add_key_binding(int key, int state, Key_Func f);
    void remove_key_binding(int key, int state, Key_Binding** list);
    void remove_key_binding(int key, int state);
    void remove_all_key_bindings(Key_Binding** list);
    void remove_all_key_bindings();
    void add_default_key_bindings(Key_Binding** list);
};



#endif /* APPLICATIONEDITOR_HXX_ */
