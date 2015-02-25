#ifndef LANG_PL
#define LANG_PL
class lang_pl{
	static std::map<std::string, std::string> x;
	static bool inited;
public:
	lang_pl(){
		if(!inited){
			x["za_male_okno_"] = "Za małe okno!";
			x["czy_zakonczyc_"] = "Czy aby na pewno chcesz zakończyć?";
			x["utworz"] = "Utwórz";
			x["zapisz"] = "Zapisz";
			x["otworz"] = "Otwórz";
			x["wyjscie"] = "Wyjście";
			x["pomoc"] = "Pomoc";
			x["czy_zapisac_poprzedni"] = "Czy zapisać poprzedni?";
			x["sciezka_do_pliku"] = "Ścieżka do pliku";
			x["uwaga_przekroczono_bufor_"] = "UWAGA! Przekroczono bufor, kontynuować?";
			x["jednak_nie_chcesz_zapisywac"] = "Jednak nie chcesz zapisywać?";
			x["juz_istnieje_nadpisac"] = "Już istnieje, nadpisać?";
			x["nie_mozna_utworzyc"] = "Nie można utworzyć!";
			x["tak"] = "t";
			x["nie"] = "n";
			x["nie_mozna_pisac_do_pliku"] = "Nie można pisać do pliku";
		}
	}
	std::string get(std::string const &key) { return x[key]; }
};
bool lang_pl::inited = false;
std::map<std::string, std::string> lang_pl::x;
#endif // LANG_PL
