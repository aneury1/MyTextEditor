/*
 * DeveloperWorkbench.hxx
 *
 *  Created on: Sep 27, 2017
 *      Author: aperez
 */

#ifndef DEVELOPERWORKBENCH_HXX_
#define DEVELOPERWORKBENCH_HXX_

#include <FL/FL_Double_Window.H>
#include <FL/FL_Text_Editor.H>
#include <FL/FL_Text_Buffer.H>
#include <FL/FL_Menu_Bar.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Button.H>


typedef int (*compare_fn)(const void *, const void *);




class DeveloperWorkbench : public Fl_Double_Window
{

   Fl_Text_Buffer *textbuf;
   Fl_Text_Buffer *stylebuf;

   Fl_Menu_Bar    *menubar;

   ////Dialogs
   Fl_Window *replace_dialog;


   void Build_dialogs();

   DeveloperWorkbench(int w, int h);

   static DeveloperWorkbench *instance;
   Fl_Text_Editor *editor;


   Fl_Button *file_manager;
   Fl_Button *save_file;



public:


   Fl_Text_Editor *get_editor(){
	   return editor;
   }

   Fl_Text_Buffer *get_text_buffer(){
	   return textbuf;
   }
   Fl_Text_Buffer *get_style_text_buffer(){
  	   return stylebuf;
     }


    static DeveloperWorkbench *get(int w, int h){
       if(instance == NULL)
    	 instance = new DeveloperWorkbench(w,h);
       return instance;
    }


    static DeveloperWorkbench * get(){
    	return instance;
    }


   void set_text(const char *buffer);




};


#endif /* DEVELOPERWORKBENCH_HXX_ */
