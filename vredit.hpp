#ifndef VREDIT
#define VREDIT

class vredit{
		private:
	bool debug;
	bool doclear;
	bool editor;
	bool menu;
	bool zmodyfikowano;
	bool colormode;
	bool drawtitle;

	char buf[CHARBUF];
	short z;
	short pozycja;
	unsigned short wx,ex;
	unsigned short wy,ey;
	unsigned short tabindent;
	short margintop,marginbot,marginlr;
	int z1,z2,z3,z4;
	wchar_t znak;
	wchar_t wcbuff;
	size_t px,py,y,charsinline,charsabove,charsunder,tabsinline,vscroll,lscroll,pos,lines;

	std::fstream plik1;

	std::wstring bufor;
	std::string nazwa;
	std::string buforek;
	const std::string NAME="VRedit";
	const std::string EMAIL="jimikuba@o2.pl";

		public:
	bool exit;

	vredit(){				//Konstructor
		srand(time(NULL)); //ustawienie ziarna generatora pseudolosowego
		setlocale(LC_ALL, "");
		initscr(); //inicjalizacja ncurses
		if(has_colors()==TRUE){
			colormode=true;
			start_color();
			//init_pair(0,COLOR_GREEN,COLOR_BLACK);
			init_pair(1, COLOR_YELLOW,COLOR_BLACK);

		}else colormode=false;

		//ustawienie parametrów działania konsoli
		keypad(stdscr,true);
		this->flowm();

		menu=false;
		editor=true;
		doclear=false;
		drawtitle=false;
		zmodyfikowano=false;
		exit=false;
		pozycja=px=py=y=charsinline=vscroll=lscroll=lines=0;
		margintop=2;
		marginbot=1;
		marginlr=2;
		tabindent=3;

		wx=getmaxx(stdscr);
		wy=getmaxy(stdscr);
		ey=wy-margintop-marginbot;
		ex=wx/2-marginlr*2;

		l("pl",1);
	}
	~vredit(){				//Destructor
		endwin(); //koniec trybu ncurses
	}

	void znakClear(){
		znak=-1;
		z1=z2=z3=z4=-1;
	}
	void flowm(){
		nodelay(stdscr,true);
		curs_set(0);
		noecho();
	}
	void textm(){
		nodelay(stdscr,false);
		curs_set(1);
		echo();
	}
	void clicktocontinue(bool flowmafter=true){
		textm();
		getch();
		if(flowmafter) flowm();
	}
	void menubold(std::string tekst, short &it,short &yshift){
		if(pozycja==it) attron(A_BOLD|A_UNDERLINE);
		mvprintw(wy/2+yshift,marginlr+ex/2-tekst.size()/2,tekst.c_str());
		mvprintw(wy/2+yshift,marginlr*3+ex+ex/2-tekst.size()/2,tekst.c_str());
		if(pozycja==it) attroff(A_BOLD|A_UNDERLINE);
		it++;
		yshift++;
	}
	void menutog(){
		if(menu){
			menu=false;
			editor=true;
		}else{
			menu=true;
			editor=false;
		}
	}
	void lscrollNow(){
		lscroll=0;
		if(px>(wx/2-2*marginlr-2)) lscroll=px-(wx/2-2*marginlr-2);
	}
	void vscrollNow(){

	}
	void pxToLast(short where=0){
		if(where==-1){
			px=charsabove;
		}else if(where==1){
			px=charsunder;
		}else{
			px=posOfLast();
		}
		lscrollNow();
	}
	bool taknie(bool autoyes=false){
		printw("[");
		attron(A_BOLD);
		if(autoyes) buforek=l("tak"); else buforek=l("nie");
		boost::algorithm::to_upper(buforek);
		addstr(buforek.c_str());
		attroff(A_BOLD);
		printw("/");
		if(autoyes) addstr(l("nie").c_str()); else addstr(l("tak").c_str());
		printw("]: ");

		nodelay(stdscr,false);
		short znak=getch();
		nodelay(stdscr,true);
		switch(znak){
			case 's':
			case 'S':
			case 'y':
			case 'Y':
			case 't':
			case 'T':{
				return true;
			}break;

			case 'n':
			case 'N':{
				return false;
			}break;
		}
		return autoyes;
	}
	bool nowy(std::fstream &plik){
		std::string randname;
		do{
			randname.clear();
			randname.append("/tmp/");
			for(int i=0; i<10; i++) randname.push_back(rand()%43+48);
			plik.open(randname,std::ios::in);
			if(plik.good()) plik.close();
		}while(plik.good());

		plik.open(randname,std::ios::out);
		if(plik.good()) return true; else{
			mvprintw(0,0,randname.c_str());
			return false;
		}
	}
	bool isreadable(std::string path){
		std::fstream plik;
		plik.open(path,std::ios_base::in);
		if(plik.good()){
			plik.close();
			return true;
		}
		plik.close();
		return false;
	}
	bool iswritable(std::string path){
		std::fstream plik;
		plik.open(path,std::ios_base::app);
		if(plik.good()){
			plik.close();
			return true;
		}
		plik.close();
		return false;

	}
	bool isrwable(std::string path){
		if(isreadable(path) && iswritable(path)) return true;
		return false;
	}
	bool wpisz(){
		if(iswritable(nazwa)){
			std::wfstream plik;
			plik.open(nazwa,std::ios::out);
			plik.imbue(std::locale(""));
			plik<<bufor;
			plik.close();
			return true;
		}else{
			mvaddstr(0,0,l("nie_mozna_pisac_do_pliku").c_str());
			printw(" %s",nazwa.c_str());
			clicktocontinue();
			return false;
		}
		return false;
	}
	bool zapisywanie(bool forceoverwrite=false){
		bool err;
		bool czypisac;
		do{
			err=true;
			czypisac=false;
			clear();
			if(nazwa.empty()){
				forceoverwrite=false;
				mvaddstr(wy/2,1,l("sciezka_do_pliku").c_str());
				addstr(": ");
				char bb[CHARBUF];
				getch();
				textm();

				while(getnstr(bb,CHARBUF)==ERR){
					mvaddstr(wy/2,wx/2-10,l("uwaga_przekroczono_bufor_").c_str());
					if(taknie())break;
				}
				nazwa.clear();
				nazwa=bb;
			}
			flowm();
			if(nazwa.empty()){
				mvaddstr(wy/2,wx/2-10,l("jednak_nie_chcesz_zapisywac").c_str());
				if(taknie()){
					return false;
				}else{
					continue;
				}
			}

			mvprintw(0,0,nazwa.c_str());

			if(!forceoverwrite && isreadable(nazwa)){
				clear();
				mvaddstr(wy/2,wx/2-10,l("juz_istnieje_nadpisac").c_str());
				if(taknie()){
					czypisac=true;
					err=false;
				}else nazwa.clear();
			}else czypisac=true;

			if(czypisac && wpisz()) {err=false;} else {err=true;nazwa.clear();}
		}while(err);

		return true;
	}
	bool xyCheck(size_t xx=std::string::npos, size_t yy=std::string::npos){
		if(xx==std::string::npos && yy==std::string::npos){
			xx=px;
			yy=py;
		}
		size_t n=0;
		size_t i=0;
		size_t x=0;
		bool ongoodline=false;

		if(yy==0) {x=1; ongoodline=true;}
		for(i=0; i<bufor.size();i++){
			if(bufor[i]=='\n'){
				if(ongoodline) return false; else n++;
				if(yy==n && !ongoodline) ongoodline=true;
			}
			if(ongoodline){
				if(xx==x) return true;
				x++;
			}
		}
		return false;
	}
	size_t xy2p(){
		size_t n=0;
		size_t i=0;

		if(py==0) return px;

		for(i=0; i<bufor.size();i++){
			if(py==n) break;
			if(bufor[i]=='\n') n++;
		}
		return i+px;
	}
	size_t posOfLast(size_t yy=std::string::npos){
		if(yy==std::string::npos) yy=py;

		size_t n=0;
		size_t i=0;
		size_t x=0;
		if(yy==0) x=1;
		for(i=0; i<bufor.size();i++){
			if(bufor[i]=='\n'){
				if(yy==n) break; else n++;
				x=0;
			}
			x++;
		}
		return x-1;
	}

	void catchZnak(){
		//pobieranie ewentualnych 4 bajtów dla UTF-8
		z1=getch();
		z2=getch();
		z3=getch();
		z4=getch();
		getch(); //zabezpieczenie przed buforem stdin
		znak=utf8_code(z1,z2,z3,z4);
	}
	void debugZnak(){
		if(znak!=-1) {mvprintw(0,0,"%3u",znak); mvaddnwstr(0,10,&znak,1);} else mvprintw(0,0,"            ");
	}

	void handleEditor(){
		if(editor && !menu){ //interfejs edytora

			pos=xy2p();
			if(px>(wx/2-2*marginlr-2+lscroll)) lscroll++;
			if(px<lscroll) lscroll--;

			if(py>(wy-marginbot-margintop-1+vscroll)) vscroll++;
			if(py<vscroll) vscroll--;
			if(!zmodyfikowano && bufor.size()>0) zmodyfikowano=true;

			mvprintw(0,wx-50,"%3u %3u %3u %3u %3u %3u %3u %3u %3d %3d",wx,wy,ex,ey,lines,vscroll,lscroll,pos,px,py);
			mvprintw(1,wx-50,"%3s %3s %3s %3s %3c %3c %3c %3c %3c %3c","wx","wy","ex","ey",'L','v','l','p','x','y');
			mvaddch(py-vscroll+margintop,px-lscroll+marginlr+tabindent,mvinch(py-vscroll+margintop,px-lscroll+marginlr) | A_REVERSE);
			mvaddch(py-vscroll+margintop,px-lscroll+marginlr+wx/2+tabindent,mvinch(py-vscroll+margintop,px-lscroll+marginlr+wx/2) | A_REVERSE);

			tabsinline=y=0;
			charsinline=charsabove=charsunder=-1;
			for(size_t i=0; i<bufor.size(); i++){
				if(bufor[i]=='\n'){
					if(y+1==py) charsabove=charsinline+1;
					if(y-1==py) charsunder=charsinline+1;
					y++;
					charsinline=-1;
					tabsinline=0;
				}else charsinline++;
				if(y>=wy-marginbot-margintop+vscroll) break;

				if(y>=vscroll){
					if(charsinline<ex && i+lscroll<bufor.size()){
						if(y==py){
							if(px==charsinline+lscroll){attron(A_REVERSE);}
							if(bufor[i+lscroll]>=32) mvaddnwstr(y+margintop-vscroll,charsinline+marginlr+tabsinline,&bufor[i+lscroll],1);
							if(bufor[i+lscroll]>=32) mvaddnwstr(y+margintop-vscroll,charsinline+marginlr+tabsinline+ex+marginlr*2,&bufor[i+lscroll],1);
							if(px==charsinline+lscroll) attroff(A_REVERSE);

							if(lscroll>0){
								mvaddch(y+margintop-vscroll,marginlr-1,'<' | A_BOLD | COLOR_PAIR(1));
								mvaddch(y+margintop-vscroll,marginlr*3-1+ex,'<' | A_BOLD | COLOR_PAIR(1));
							}
						}else{
							mvaddnwstr(y+margintop-vscroll,charsinline+marginlr,&bufor[i],1);
							mvaddnwstr(y+margintop-vscroll,charsinline+marginlr+ex+marginlr*2,&bufor[i],1);
						}
					}

					if(charsinline>ex-3 && charsinline!=-1){
						mvaddch(y+margintop-vscroll,ex+1,'>' | A_BOLD | COLOR_PAIR(1));
						mvaddch(y+margintop-vscroll,ex*2+5,'>' | A_BOLD | COLOR_PAIR(1));
					}

					if(ex+lscroll-marginlr>=charsinline+1){
						mvaddch(y+margintop-vscroll,ex+1,' ' | A_BOLD | COLOR_PAIR(1));
						mvaddch(y+margintop-vscroll,ex*2+5,' ' | A_BOLD | COLOR_PAIR(1));
					}


				}
			}
			if(charsunder==-1) charsunder=charsinline+1;

							//reakcja na użycie klawiszy

/*			for(int i=1; i<wy; i++){
				for(int j=0; j<wx/2-marginlr-1;j++){
					wcbuff=mvinch(i,j);
					mvaddnwstr(i,j+wx/2,&wcbuff,1);
				}
			}*/

			if(znak>=32 && znak<56000){
				bufor.insert(pos,1,znak);
				px++;
			}

			switch(znak){
				case 0:{	//np ctrl+space
					menutog();
					pozycja=0;
				}break;
				case 9:{	//tab
					bufor.insert(pos,1,'\t');
					px++;
				}break;
				case 10:{	//enter
					bufor.insert(pos,1,'\n');
					px=0;
					py++;
					lines++;
				}break;

				case KEY_BACKSPACE:
				case MYKEY_BACKSPACE:{
					if(pos>0){
						pos--;
						if(bufor[pos]=='\n'){
							py--;
							pxToLast(-1);
							lines--;
						}else if(px-1!=std::string::npos) px--;
						bufor.erase(pos,1);
					}
				}break;

				case KEY_DC:
				case MYKEY_DELETE:{
					//pos--;
					if(bufor[pos]=='\n') lines--;
					bufor.erase(pos,1);
				}break;

				case KEY_END:
				case MYKEY_END:{
					pxToLast();
				}break;

				case KEY_HOME:
				case MYKEY_HOME:{
					px=0;
				}break;

				case KEY_UP:
				case MYKEY_UP:{
					if(py-1!=std::string::npos)py--;
					if(!xyCheck()){
						pxToLast(-1);
					}
				}break;

				case KEY_DOWN:
				case MYKEY_DOWN:{
					if(py+1<=y ) py++;
					if(!xyCheck()){
						pxToLast(1);
					}
				}break;

				case KEY_LEFT:
				case MYKEY_LEFT:{
					//if(px-1!=std::string::npos) px--;
					if(pos>0){
						pos--;
						if(bufor[pos]=='\n'){
							py--;
							pxToLast(-1);
						}else if(px-1!=std::string::npos) px--;
					}
				}break;

				case KEY_RIGHT:
				case MYKEY_RIGHT:{
					z=bufor[xy2p()];
					if(z!='\n' && z!=0) px++; else if(z=='\n'){px=0; py++;}
				}break;

				case MYKEY_PAGEDN:{ //PageDown
					if(xyCheck(0,py+(ey-1)*2)){
						py+=(ey-1)*2;
					}else{
						py=lines;
					}

					if(xyCheck(px,py)){
						px=px;
					}else{
						pxToLast();
					}
				}break;

				case MYKEY_PAGEUP:{ //PageUp
					if(xyCheck(0,py-(ey-1)*2)){
						py-=(ey-1)*2;
					}else{
						py=0;
					}
					if(xyCheck(px,py)){
						px=px;
					}else{
						pxToLast();
					}
				}break;

			}

			if(znak!=-1){
				doclear=true;
				if(px==0 && lscroll!=0) lscroll=0;
			}
			znakClear();
		}
	}
	void handleMenu(){
		if(menu){ //interfejs menu
				//reakcja na użycie klawiszy
			switch(znak){
				case KEY_UP:
				case MYKEY_UP:
				case 'W':
				case 'w':
				{
					if(pozycja-1>=0) pozycja--; else pozycja=4;
				}break;
				case KEY_DOWN:
				case MYKEY_DOWN:
				case 'S':
				case 's':
				{
					if(pozycja+1<=4) pozycja++; else pozycja=0;
				}break;

				case 0:{ //np ctrl+spacja
					menutog();
					doclear=true;
				}
			}


			if(znak=='\n'){
				doclear=true;
				switch(pozycja){
					case 0:{		//Utwórz nowy
						if(zmodyfikowano){
							clear();
							mvaddstr(wy/2,wx/2-10,l("czy_zapisac_poprzedni").c_str());
							if(taknie(true)){
								zapisywanie();
							}
						}
						menutog();
						zmodyfikowano=false;
						bufor.clear();
						nazwa.clear();
						px=0;
						py=0;
						lines=0;
					}break;
					case 1:{		//Zapisz
						if(zapisywanie(true)) zmodyfikowano=false;
						menutog();
					}break;
					case 2:{		//Otwórz

					}break;
					case 3:{		//Pomoc

					}break;
					case 4:{		//Wyjście
						if(zmodyfikowano){
							clear();
							mvaddstr(wy/2,wx/2-10,l("czy_chcesz_zapisac").c_str());
							if(taknie(true)){
								zapisywanie();
							}
						}
						exit=true;
					}break;
				}
			}
		//koniec obsługi klawiszy
			znakClear();

			mvprintw(0,0,"v%s%s",AutoVersion::FULLVERSION_STRING,AutoVersion::STATUS_SHORT);
			mvprintw(wy-1,0,l("ctrl_plus_spacja_").c_str());
			short it=0,ss=-3;
			menubold(l("utworz"),it,ss);
			menubold(l("zapisz"),it,ss);
			menubold(l("otworz"),it,ss);
			menubold(l("pomoc"),it,ss);
			menubold(l("wyjscie"),it,ss);
		}
	}
	void printTitle(){
		if(drawtitle){
			mvaddstr(0,(wx/2)-(NAME.size()+EMAIL.size()+6)/2,NAME.c_str());
			addstr(" [by ");
			addstr(EMAIL.c_str());
			addstr("]");
		}
	}
	void printSizeWarning(){
		if(wx<marginlr*4+2||wy<margintop+marginbot+2){
			mvaddstr(wy-1,0,l("za_male_okno_").c_str());
		}
	}
	void screenStep(){
		refresh(); //odświerzenie zawartości
		std::this_thread::sleep_for(std::chrono::milliseconds(25)); //takt pętli głównej co 75ms
		if(getmaxx(stdscr)!=wx || getmaxy(stdscr)!=wy){
			doclear=true; //wymuszenie czyszczenia ekranu przy zmianie rozmiarów konsoli
			wx=getmaxx(stdscr);
			wy=getmaxy(stdscr);
			ey=wy-margintop-marginbot;
			ex=wx/2-marginlr*2;
		}
		if(doclear){ clear(); doclear=false;} //czyści obraz gdy jest to niezbędne

	}
};
#endif // VREDIT
