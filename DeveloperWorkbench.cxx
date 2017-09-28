#include <FL/FL.H>
#include <FL/FL_Box.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Widget.H>
#include "DeveloperWorkbench.hxx"
#include <FL/Fl_File_Chooser.H>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <string.h>

#include "ApplicationEditor.hxx"

#define DEBUG(L) /// fprintf(stderr, "Here %d", L)

DeveloperWorkbench *DeveloperWorkbench::instance = NULL;


void change_text(int pos, int nInserted, int nDeleted,  int nRestyled, const char* deletedText,  void* cbArg)
{
      fprintf(stdout, "Event catched here");

}


void new_cb(Fl_Widget*, void* v)
{

}
void open_cb(Fl_Widget*, void* v)
{
    // Create the file chooser, and show it
    Fl_File_Chooser chooser(".",                        // directory
                            "*",                        // filter
                            Fl_File_Chooser::SINGLE,     // chooser type
                            "Open File");        // title
    chooser.show();

    // Block until user picks something.
    //     (The other way to do this is to use a callback())
    //
    while(chooser.shown())
        { Fl::wait(); }

    // User hit cancel?
    if ( chooser.value() == NULL )
        { fprintf(stderr, "(User hit 'Cancel')\n"); return; }

    // Print what the user picked
    fprintf(stderr, "--------------------\n");
    fprintf(stderr, "DIRECTORY: '%s'\n", chooser.directory());
    fprintf(stderr, "    VALUE: '%s'\n", chooser.value());
    fprintf(stderr, "    COUNT: %d files selected\n", chooser.count());

    if(DeveloperWorkbench::get() != NULL && chooser.count( ) >= 1){

    	std::ifstream is(chooser.value(0) );
        if(is.is_open())
        {
        	std::string lines;
        	std::string line;
        	while(getline(is, line)){
        		lines+=line;
        		lines+= '\n';
        	}
        	is.close();

        	if(lines.size() > 0){
        		DeveloperWorkbench::get()->set_text(lines.c_str());
        	}


        }


    }


}

void insert_cb(Fl_Widget*, void* v)
{

}
void save_cb(Fl_Widget*, void* v)
{

}
void saveas_cb(Fl_Widget*, void* v)
{

}

void view_cb(Fl_Widget*, void* v)
{

}
void close_cb(Fl_Widget*, void* v)
{

}
void quit_cb(Fl_Widget*, void* v)
{
   exit(-1);
}
void undo_cb(Fl_Widget*, void* v)
{

}
void cut_cb(Fl_Widget*, void* v)
{
	DeveloperWorkbench *workbench = DeveloperWorkbench::get();
	Fl_Text_Editor::kf_cut(0, workbench->get_editor());
}

void copy_cb(Fl_Widget*, void* v)
{
	DeveloperWorkbench *workbench = DeveloperWorkbench::get();
	Fl_Text_Editor::kf_copy(0, workbench->get_editor());
}
void paste_cb(Fl_Widget*, void* v)
{
	DeveloperWorkbench *workbench = DeveloperWorkbench::get();
	Fl_Text_Editor::kf_paste(0, workbench->get_editor());
}
void delete_cb(Fl_Widget*, void* v)
{
	DeveloperWorkbench *workbench = DeveloperWorkbench::get();
	workbench->get_text_buffer()->remove_selection();
}
void find_cb(Fl_Widget*, void* v)
{






}
void  find2_cb(Fl_Widget*, void* v)
{

}

void replace_cb(Fl_Widget*, void* v)
{
    Fl_Window *find_window = new Fl_Window(DeveloperWorkbench::get()->w()/2-100,
    									   DeveloperWorkbench::get()->h()/2,
										   400, 105,"Replace in Text"
    		);

   /* Fl_Input *replace_find = new Fl_Input(70, 10, 300, 25, "Find:");
    Fl_Input *replace_with = new Fl_Input(70, 40, 300, 25, "Replace:");
    Fl_Button *replace_all = new Fl_Button(10, 70, 90, 25, "Replace All");
    Fl_Button *replace_next = new Fl_Button(105, 70, 120, 25, "Replace Next");
    Fl_Button *replace_cancel = new Fl_Button(230, 70, 60, 25, "Cancel");*/

    find_window->end();
    find_window->show();
}

void replace2_cb(Fl_Widget*, void* v)
{

}

void style_unfinished_cb(int, void *)
{


}

const char *code_types[]={
		"int",
		"String",
		"float",
		"double"
		"char",
		"class",
		"struct",
		"union",
		"int32_t",
		"long",
		"long long",
		"long double"
		"char",
		"char16_t",
		"char32_t",
        "void",
		"unsigned"
};

const char *code_keywords[]=
{

		"alignas",
		"alignof",
		"and",
		"and_eq",
		"asm",
		"auto",
		"bitand",
		"bitor",

		"break",
		"case",
		"catch",

		"class",
		"compl",
		"const",
		"constexpr",
		"const_cast",
		"continue",
		"decltype",
		"default",
		"delete",
		"do",

		"dynamic_cast",
		"else",
		"enum",
		"explicit",
		"export",
		"extern",
		"false",

		"for",
		"friend",
		"goto",
		"if",
		"inline",

		"mutable",
		"namespace",
		"new",
		"noexcept",
		"not",
		"not_eq",
		"nullptr",
		"operator",
		"or",
		"or_eq",
		"private",
		"protected",
		"public",
		"register",
		"reinterpret_cast",
		"return",

		"sizeof",
		"static",
		"static_assert",
		"static_cast",
		"struct",
		"switch",
		"template",
		"this",
		"thread_local",
		"throw",
		"true",
		"try",
		"typedef",
		"typeid",
		"typename",
		"union",

		"using",
		"virtual",

		"volatile",

		"while",
		"xor",
		"xor_eq",
		"override",
		"final"
};


int compare_keywords(const char *s, const char *d){

	fprintf(stderr,"Key s = [%s] Key d [%s]", s,d);
	return strcmp(s, d);
}



//
// 'style parse()' - Parse text and produce style data.
//
void style_parse(const char *text,char *style,int length)
{
	if(text==NULL)
	{
		fprintf(stderr, "Text is null for some reason");
		return;
	}


	char current;
	int col;
	int last;
	char buf[255],
	*bufptr;
	const char *temp;
	for (current = *style, col = 0, last = 0; length > 0; length --, text ++) {
		if (current == 'A')
		{
			DEBUG(__LINE__);
			// Check for directives, comments, strings, and keywords...
			if (col == 0 && *text == '#')
			{
				// Set style to directive
				current = 'E';
			} else if (strncmp(text, "//", 2) == 0)
			{
				current = 'B';
			} else if (strncmp(text, "/*", 2) == 0) {
				current = 'C';
			} else if (strncmp(text, "\\\"", 2) == 0) {
				// Quoted quote...
				*style++ = current;
				*style++ = current;
				text ++;
				length --;
				col += 2;
				continue;
			} else if (*text == '\"') {
			   current = 'D';
			} else if (!last && islower(*text)) {
			// Might be a keyword...
			for (temp = text, bufptr = buf; islower(*temp) && bufptr < (buf + sizeof(buf) - 1);  *bufptr++ = *temp++);
			  if (!islower(*temp)) {
				  *bufptr = '\0';
				   bufptr = buf;
				   if (bsearch(&bufptr, code_types, sizeof(code_types) / sizeof(code_types[0]), sizeof(code_types[0]),(compare_fn) compare_keywords)) {
					  while (text < temp)
					  {
						  *style++ = 'F';
						  text ++;
						  length --;
						  col ++;
					   }
					  text --;
					  length ++;
					  last = 1;
					  continue;
				 } else if (bsearch(&bufptr, code_keywords, sizeof(code_keywords) / sizeof(code_keywords[0]),  sizeof(code_keywords[0]),(compare_fn) compare_keywords)) {
				   while (text < temp)
				   {
					   *style++ = 'G';
					   text ++;
					   length --;
					   col ++;
				   }
					   text --;
					   length ++;
					   last = 1;
					   continue;
				   }
				 }
			  }
		  }
		else if (current == 'C' && strncmp(text, "*/", 2) == 0)
		{
			  DEBUG(__LINE__);
			  // Close a C comment...
			  *style++ = current;
			  *style++ = current;
			  text ++;
			  length --;
			  current = 'A';
			  col += 2;
			  continue;
		  }
		else if (current == 'D')
		  {
				DEBUG(__LINE__);
				// Continuing in string...
			  if (strncmp(text, "\\\"", 2) == 0)
			  {
				  // Quoted end quote...
				  *style++ = current;
				  *style++ = current;
				  text ++;
				  length --;
				  col += 2;
				  continue;
			  }
			  else if(*text == '\"')
			  {
				  // End quote...
				 * style++ = current;
				  col ++;
				  current = 'A';
				  continue;
			  }
		 }
		else{
			DEBUG(__LINE__);
		}
		// Copy style info...
		if (current == 'A' && (*text == '{' || *text == '}'))
		{
			DEBUG(__LINE__);
			*style++ = 'G';
		}
		else
			*style++ = current;

			col ++;

			last = isalnum(*text) || *text == '.';
		if (*text == '\n')
		{
			DEBUG(__LINE__);
			// Reset column and possibly reset the style
			col = 0;
			if (current == 'B' || current == 'E') current = 'A';
		}

	}
}

void style_update(int pos, int nInserted, int nDeleted, int nRestyled, const char* deletedText, void* cbArg)
{

	int start, end;
    char last, *style=NULL, *text=NULL;
    DeveloperWorkbench *workbench = DeveloperWorkbench::get();
    if(workbench == NULL)
    	return;
    if(nInserted == 0 && nDeleted == 0)///nothing has been done.
    {
      if(workbench->get_style_text_buffer() != NULL)
     	workbench->get_style_text_buffer()->unselect();
    	return;
    }

    if(nInserted > 0){

    	style =  new char[nInserted + 1];
    	memset(style, 'A', nInserted);
    	style[nInserted] = '\0';

       if(workbench->get_style_text_buffer() != NULL)
    	  workbench->get_style_text_buffer()->replace(pos, pos +nDeleted, style);

    	delete[] style;

    }
    else {
    	workbench->get_style_text_buffer()->remove(pos, pos + nDeleted);
    }




    // Select the area that was just updated to avoid unnecessary
    // callbacks...
    workbench->get_style_text_buffer()->select(pos, pos + nInserted - nDeleted);
    // Re-parse the changed region; we do this by parsing from the
    // beginning of the line of the changed region to the end of
    // the line of the changed region... Then we check the last
    // style character and keep updating if we have a multi-line
    // comment character...

    start = workbench->get_text_buffer()->line_start(pos);
    end = workbench->get_text_buffer()->line_end(pos + nInserted - nDeleted);
    text = workbench->get_text_buffer()->text_range(start, end);
    style = workbench->get_text_buffer()->text_range(start, end);
    last = style[end - start - 1];

    fprintf(stderr,"start [%d] end[%d] style text[%s] \n", start, end, style);



    style_parse(text, style, end - start);

    workbench->get_style_text_buffer()->replace(start, end, style);
    ((Fl_Text_Editor *)cbArg)->redisplay_range(start, end);
    if (last != style[end - start - 1]) {
    // The last character on the line changed styles, so reparse the
    // remainder of the buffer...
    free(text);
    free(style);
    end = workbench->get_text_buffer()->length();
    text = workbench->get_text_buffer()->text_range(start, end);
    style = workbench->get_style_text_buffer()->text_range(start, end);
    style_parse(text, style, end - start);
    workbench->get_style_text_buffer()->replace(start, end, style);
    ((Fl_Text_Editor *)cbArg)->redisplay_range(start, end);
    }
    free(text);
    free(style);

}


void about_cb(Fl_Widget *, void *v){

	 Fl_Window *def = new Fl_Window(300,300,400,200,"About DeveloperWorkbench");
	 Fl_Box *box = new Fl_Box(30,30,350,150, "Developer Workbench -- A.perez A real Editor v0.1");
	 box->box(FL_UP_BOX);
	 box->labelcolor(FL_RED);
	 box->labelsize(10);
	 box->labeltype(FL_SHADOW_LABEL);
	 def->end();
	 def->show();
}

Fl_Text_Display::Style_Table_Entry default_style []=
{
	{ FL_BLACK      , FL_COURIER, FL_NORMAL_SIZE},		/// DEFAULT FOR PLAIN
	{ FL_DARK_GREEN , FL_COURIER, FL_NORMAL_SIZE},      /// LINE COMMENT
	{ FL_DARK_GREEN , FL_COURIER, FL_NORMAL_SIZE},      /// BLOCK COMMENT
	{ FL_BLUE       , FL_COURIER, FL_NORMAL_SIZE},      /// string
	{ FL_DARK_RED   , FL_COURIER, FL_NORMAL_SIZE},      /// Directives
	{ FL_DARK_RED   , FL_COURIER, FL_NORMAL_SIZE},      /// TYPES
	{ FL_YELLOW       , FL_COURIER, FL_NORMAL_SIZE},

};




Fl_Menu_Item menuitems[] =
{
  { "&File"             , 0                           ,             0, 0, FL_SUBMENU},
  { "&New File"         , 0                           , (Fl_Callback *)new_cb },
  { "&Open File..."     , FL_COMMAND + 'o'            , (Fl_Callback *)open_cb },
  { "&Insert File..."   , FL_COMMAND + 'i'            , (Fl_Callback *)insert_cb, 0, FL_MENU_DIVIDER },
  { "&Save File"        , FL_COMMAND + 's'            , (Fl_Callback *)save_cb },
  { "Save File &As..."  , FL_COMMAND + FL_SHIFT + 's' , (Fl_Callback *)saveas_cb, 0, FL_MENU_DIVIDER },
  { "New &View"         , FL_ALT + 'v'                , (Fl_Callback *)view_cb, 0 },
  { "&Close View"       , FL_COMMAND + 'w'            , (Fl_Callback *)close_cb, 0,FL_MENU_DIVIDER },
  { "E&xit"             , FL_COMMAND + 'q'            , (Fl_Callback *)quit_cb, 0 },

  { 0 },

  { "&Edit", 0, 0, 0, FL_SUBMENU },
  { "&Undo", FL_COMMAND + 'z', (Fl_Callback *)undo_cb, 0, FL_MENU_DIVIDER },
  { "Cu&t", FL_COMMAND + 'x', (Fl_Callback *)cut_cb },
  { "&Copy", FL_COMMAND + 'c', (Fl_Callback *)copy_cb },
  { "&Paste", FL_COMMAND + 'v', (Fl_Callback *)paste_cb },
  { "&Delete", 0, (Fl_Callback *)delete_cb },
  { 0 },
  { "&Search", 0, 0, 0, FL_SUBMENU },
  { "&Find...", FL_COMMAND + 'f', (Fl_Callback *)find_cb },
  { "F&ind Again", FL_COMMAND + 'g', find2_cb },
  { "&Replace...", FL_COMMAND + 'r', replace_cb },
  { "Re&place Again", FL_COMMAND + 't', replace2_cb },
  { 0 },
  { "&Control Version", 0,0,0, FL_SUBMENU},
  { 0 },
  { "&Share Code", 0,0,0, FL_SUBMENU},
  { 0 },
  { "&Build", 0,0,0, FL_SUBMENU},
  { 0 },
  { "&Configuration", 0,0,0, FL_SUBMENU},
  { 0 },
  { "&About", 0,0,0, FL_SUBMENU},
  { "About DeveloperWorkbench", 0, about_cb },
  { 0 }
};




















DeveloperWorkbench::DeveloperWorkbench(int w, int h): Fl_Double_Window(10,10,w,h,"Developer Workbench v0.1")
{
	editor = new /* Fl_Text_Editor*/ApplicationEditor(59,32, (this->w()-64), (this->h()-64));
	textbuf =new  Fl_Text_Buffer(4096);
	editor->buffer(textbuf);
	menubar =  new Fl_Menu_Bar(0, 0, this->w(), 32);
	menubar->color(0x515151ff);
	menubar->textcolor(0xffffffff);
    menubar->copy(menuitems);
    this->color(0x515151ff);
    stylebuf=new Fl_Text_Buffer(4096);
   //// textbuf->add_modify_callback(change_text, (void *)editor);
   /// textbuf->call_modify_callbacks();


   /*editor->highlight_data(stylebuf, default_style, sizeof(default_style)/sizeof(default_style[0]), 'A', style_unfinished_cb, 0);*/
     textbuf->add_modify_callback(style_update, editor);
    textbuf->call_modify_callbacks();

    Build_dialogs();
}

void DeveloperWorkbench::set_text(const char *buffer)
{
   if(editor != NULL)
   {
	   textbuf->text(buffer);
   }
}

void DeveloperWorkbench::Build_dialogs()
{
   this->replace_dialog = new Fl_Window(300, 105, "Replace");

   file_manager = new Fl_Button(6,38,48,48);
   file_manager->box(FL_PLASTIC_UP_BOX);
   file_manager->label("@fileopen");
   file_manager->callback(open_cb);
   this->add(file_manager);


   save_file = new Fl_Button(6, 100, 48,48);
   save_file->box(FL_PLASTIC_UP_BOX);
   save_file->label("@filesave");
   save_file->callback(open_cb);
   this->add(save_file);


}
