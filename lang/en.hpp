#ifndef LANG_EN
#define LANG_EN
class lang_en{
	static std::map<std::string, std::string> x;
	static bool inited;
public:
	lang_en(){
		if(!inited){
			x["za_male_okno_"] = "Too small window!";
			x["czy_zakonczyc_"] = "Do you realy want quit?";
			x["utworz"] = "Create";
			x["zapisz"] = "Save";
			x["otworz"] = "Open";
			x["wyjscie"] = "Exit";
			x["pomoc"] = "Help";
			x["czy_zapisac_poprzedni"] = "Would you like to save previous file?";
			x["sciezka_do_pliku"] = "Path to file";
			x["uwaga_przekroczono_bufor_"] = "WARNING! Buffer overflow, continue?";
			x["jednak_nie_chcesz_zapisywac"] = "So you don't want to save it?";
			x["juz_istnieje_nadpisac"] = "Alredy exists, overwrite?";
			x["nie_mozna_utworzyc"] = "Can't create that!";
			x["tak"] = "y";
			x["nie"] = "n";
			x["nie_mozna_pisac_do_pliku"] = "Can't write to file";
		}
	}
	std::string get(std::string const &key) { return x[key]; }
};
bool lang_en::inited = false;
std::map<std::string, std::string> lang_en::x;
#endif // LANG_EN
