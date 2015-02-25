//Autor: jimikuba@o2.pl  Licencja: Public Domain
/* TODO LIST:
	-save file
	-open file
	-user defined tab indent
	-security backup if writable
	-safe-mode [read only]
	-safe-binary [read only]
	-autosave
	-cut/copy/paste and text selecting
	-BOM file handling
	-history managment
	-write assistant
	-multitab support
	-simple C++ syntax highligting
*/
	//ładowanie bibliotek

#define _GLIBCXX_USE_WCHAR_T 1

#include <ncursesw/ncurses.h>
#include <boost/algorithm/string.hpp>
#include <boost/locale.hpp>
#include <cmath>
#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>
#include <map>


#include "version.hpp"
#include "lang/pl.hpp"
#include "lang/en.hpp"
#include "lang/es.hpp"
#include "lang.hpp"

#include "utf8.hpp"

#define CHARBUF 1024
#include "vredit.hpp"

int main(){
	vredit *vre=new vredit;
	while(!vre->exit){
		vre->catchZnak();
		vre->debugZnak();
		vre->handleEditor();
		vre->handleMenu();
		vre->printTitle();
		vre->printSizeWarning();
		vre->screenStep();
	}
	delete vre;
	return 0; //koniec programu
}
