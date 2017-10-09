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
#include "Variables.hh"
#include "string_utils.h"
#include "callback.h"
#include <vector>
using std::vector;
DeveloperWorkbench *DeveloperWorkbench::instance = NULL;

int find(const char *str, const char *sb, int beg)
{
    int  whole= strlen(str), len2=strlen(sb);
    bool found=false;
    int i = beg;
    for( i=beg; i < whole; i++)
     {
        if( str[i] == sb[0])
        {
            found = true;
            for( int o=0; o < len2; o++)
            {
                if(str[i+o] != sb[o])
                {
                   found = false;
                   break;
                }
                else
                {
                    found =true;
                }
            }
        }
        if(found == true)
        {
		   break;
		}
     }
if(found==true)
   return i;
   else
   return -1;
}

int find_only_word(const char *str, const char *sb, int beg)
{
    int  whole= strlen(str), len2=strlen(sb);
    bool found=false;
    int i = beg;
    int o;
    for( i=beg; i < whole; i++)
     {
        if( str[i] == sb[0])
        {
            found = true;
            for( o=0; o < len2; o++)
            {
                if(str[i+o] != sb[o])
                {
                   found = false;
                   break;
                }
                else
                {
                    found =true;
                }
            }
        }
        if(found == true)
        {
		   if(str[i+o+1] == ' ' || str[i+o+1]  == '\n'|| str[i+o+1] == '\0')
		   break;
		   else
		     found =false;
		}

     }
if(found==true)
   return i;
   else
   return -1;
}

int count_all(const char *str, const char *tok)
{
   int counts=0;
   int found=0;
   while((found=find(str, tok, found))!= -1)
     {
		 counts++;
         if(found == -1)
           break;
           else
         found += strlen(tok);
     }
     return counts;
}


int find_word(const char *str, const char *sb, int beg)
{
   int len = strlen(sb);
   int ret= -1;
   ret =find(str, sb, beg);
   if(ret != -1)
   {
	   if(str[len+1] != ' ')
	      ;
	   else
		   ret= -1;
   }
    return ret;
}




vector<int> get_string_pos(const char *str, const char *tok)
{
   vector<int>pos;
   int found=-1;
	/// while((found=find(str, tok, found))!= -1)
   while((found=find_word(str, tok, found))!= -1)
   {
         if(found != -1)
           {
			   pos.push_back(found);
			   found += strlen(tok);
           }
     }
     return pos;
}

void change_buffer_with_char(char *buffer,int len,vector<int>inpos, char ch)
{
	if(buffer == NULL || inpos.size()<=0)
	   return;
	for(int i=0; i < inpos.size();i++){
	    int ib = inpos[i];
	    for(int f=0;f<len;f++)
	    {
            buffer[f+ib]=ch;
        }
	}
}


void style_unfinished_cb(int f, void *d){}

static const char *default_code_keywords[]=
{
		"alignas",//1
		"alignof",//2
		"and",//3
		"and_eq",//5
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

static const char *cpp_code_types[]=
{
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







void style_parse(const char *text ,char *style,int length)
{
    int key_size = sizeof(default_code_keywords)/sizeof(default_code_keywords[0]);
    for(int i=0; i < key_size; i++)
    {
    	vector<int>current_keyword_offset = get_string_pos(text, default_code_keywords[i]);
    	if(current_keyword_offset.size()> 0)
    	{

    		change_buffer_with_char(style,strlen(default_code_keywords[i]), current_keyword_offset, 'B');
    	}
    }

    int cpp_types_size = sizeof(cpp_code_types)/sizeof(cpp_code_types[0]);

    for(int i=0; i < cpp_types_size; i++)
    {
    	vector<int>current_types_offset = get_string_pos(text, cpp_code_types[i]);
    	if(current_types_offset.size()> 0)
    	{
    		change_buffer_with_char(style,strlen(cpp_code_types[i]), current_types_offset, 'D');
    	}
    }

}



void style_update(int pos, int nInserted, int nDeleted, int nRestyled, const char* deletedText, void* cbArg)
{

    char *style=NULL;
    DeveloperWorkbench *workbench = DeveloperWorkbench::get();
    if(workbench == NULL)
    	return;
    if(nInserted == 0 && nDeleted == 0)
    {
      if(workbench->get_style_text_buffer() != NULL)
      	workbench->get_style_text_buffer()->unselect();
    	return;
    }

    style = new char[4096+1];
    memset(style, 'A', 4096);
    style_parse(workbench->get_text_buffer()->text() , style, 4096);
    workbench->set_text_style(style);

    delete[] style;
    style= NULL;


#if 0
    if(nInserted > 0)
    {
        style =  new char[4096+1];
    	memset(style, 'A', 4096);
    	style[4096] = '\0';
       if(workbench->get_style_text_buffer() != NULL)
    	  workbench->get_style_text_buffer()->replace(pos, pos + nDeleted, style);
    	delete[] style;
    }
    else
    {
    	workbench->get_style_text_buffer()->remove(pos, pos + nDeleted);
    }

    workbench->get_style_text_buffer()->select(pos, pos + nInserted - nDeleted);
    start = workbench->get_text_buffer()->line_start(pos);
    end = workbench->get_text_buffer()->line_end(pos + nInserted - nDeleted);
    text = workbench->get_text_buffer()->text_range(start, end);
    style = workbench->get_text_buffer()->text_range(start, end);
    last = style[end - start - 1];
  //  style_parse(text, style, end - start);
    style_parse(text, style, 4096);
    workbench->get_style_text_buffer()->replace(start, end, style);
    ((Fl_Text_Editor *)cbArg)->redisplay_range(start, end);
    if (last != style[end - start - 1])
    {
		/*free(text);
		free(style);*/

    	delete text;
    	delete style;

		end = workbench->get_text_buffer()->length();
		text = workbench->get_text_buffer()->text_range(start, end);
		style = workbench->get_style_text_buffer()->text_range(start, end);
		///style_parse(text, style, end - start);
		style_parse(text, style, 4096);
		workbench->get_style_text_buffer()->replace(start, end, style);
		((Fl_Text_Editor *)cbArg)->redisplay_range(start, end);
    }
    /*free(text);
    free(style);*/
 	delete text;
    delete style;
#endif
}



DeveloperWorkbench::DeveloperWorkbench(int w, int h): Fl_Double_Window(10,10,w,h,"Developer Workbench v0.1")
{
	editor = new ApplicationEditor(59,32, (this->w()-64), (this->h()-64));
	textbuf =new  Fl_Text_Buffer(4096);
	editor->buffer(textbuf);
	menubar =  new Fl_Menu_Bar(0, 0, this->w(), 32);
	menubar->color(0x515151ff);
	menubar->textcolor(0xffffffff);
    menubar->copy(menuitems);
    this->color(0x515151ff);
    stylebuf=new Fl_Text_Buffer(4096);
    editor->highlight_data(stylebuf, default_style, sizeof(default_style)/sizeof(default_style[0]), 'B', style_unfinished_cb, 0);
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
   ///file_manager->callback(NULL);
   this->add(file_manager);

   save_file = new Fl_Button(6, 100, 48,48);
   save_file->box(FL_PLASTIC_UP_BOX);
   save_file->label("@filesave");
   ///save_file->callback(NULL);
   this->add(save_file);
}
