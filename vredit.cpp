//Autor: jimikuba@o2.pl  Licencja: Public Domain
	//ładowanie bibliotek

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

#include "envParams.hpp"
#include "simpleWin.hpp"
#include "winHandler.hpp"
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
