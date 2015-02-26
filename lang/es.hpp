#ifndef LANG_ES
#define LANG_ES
class lang_es{
	static std::map<std::string, std::string> x;
	static bool inited;
public:
	lang_es(){
		if(!inited){
			x["za_male_okno_"] = "Demasiado pequeña ventana!";
			x["czy_zakonczyc_"] = "¿Seguro que quieres salir?";
			x["utworz"] = "Crear";
			x["zapisz"] = "Guarde el archivo";
			x["otworz"] = "Abra el archivo";
			x["wyjscie"] = "Salida";
			x["pomoc"] = "Ayuda";
			x["czy_zapisac_poprzedni"] = "¿Quieres guardar el archivo anterior?";
			x["sciezka_do_pliku"] = "Ruta al archivo";
			x["uwaga_przekroczono_bufor_"] = "ADVERTENCIA! Desbordamiento de búfer ¿Continuar?";
			x["jednak_nie_chcesz_zapisywac"] = "¿Así que usted no desea guardarlo?";
			x["juz_istnieje_nadpisac"] = "¿Todavia existe, sobrescribir?";
			x["nie_mozna_utworzyc"] = "No se puede crear eso!";
			x["tak"] = "s";
			x["nie"] = "n";
			x["nie_mozna_pisac_do_pliku"] = "No se puede escribir en el archivo";
			x["ctrl_plus_spacja_"] = "Ctrl+Space - cerrar menú";
			x["czy_chcesz_zapisac"] = "¿Quieres guardar los cambios?";
		}
	}
	std::string get(std::string const &key) { return x[key]; }
};
bool lang_es::inited = false;
std::map<std::string, std::string> lang_es::x;
#endif // LANG_ES
