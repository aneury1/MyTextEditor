#include "ApplicationEditor.hxx"



ApplicationEditor::ApplicationEditor(int X, int Y, int W, int H, const char* l) :Fl_Text_Editor(X, Y,W,H,l)
{

}

ApplicationEditor::~ApplicationEditor()
{
	remove_all_key_bindings();
}
int ApplicationEditor::handle(int e)
{
  return Fl_Text_Editor::handle(e);
}
void ApplicationEditor::insert_mode(int b)
{
	Fl_Text_Editor::insert_mode(b);
}
int ApplicationEditor::insert_mode()
{
	return Fl_Text_Editor::insert_mode();
}
void  ApplicationEditor::add_key_binding(int key, int state, Key_Func f, Key_Binding** list)
{
	Fl_Text_Editor::add_key_binding(key,  state, f,  list);
}
void  ApplicationEditor::add_key_binding(int key, int state, Key_Func f)
{
	Fl_Text_Editor::add_key_binding( key,  state, f);
}
void  ApplicationEditor::remove_key_binding(int key, int state, Key_Binding** list)
{
	Fl_Text_Editor::remove_key_binding(key, state, list);
}
void  ApplicationEditor::remove_key_binding(int key, int state)
{
	Fl_Text_Editor::remove_key_binding( key, state);
}
void  ApplicationEditor::remove_all_key_bindings(Key_Binding** list)
{
	Fl_Text_Editor::remove_all_key_bindings(list);
}
void  ApplicationEditor::remove_all_key_bindings()
{
	Fl_Text_Editor::remove_all_key_bindings();
}
void  ApplicationEditor::add_default_key_bindings(Key_Binding** list)
{
	Fl_Text_Editor::add_default_key_bindings(list);
}
