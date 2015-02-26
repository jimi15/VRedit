#ifndef LANG
#define LANG

static std::string l(const std::string &input,const int option=0){
//	static bool init;
	static std::string lang;
	std::string output;

	if(lang.empty()){
			#if defined LANG_PL
				lang="pl";
			#elif defined LANG_EN
				lang="en";
			#elif defined LANG_ES
				lang="es";
			#endif
	}

	switch(option){
		case 0:{	//Wypisywanie z bazy
			if(lang=="pl"){
				#if defined LANG_PL
				output=lang_pl().get(input);
				#endif
			}else if(lang=="en"){
				#if defined LANG_EN
				output=lang_en().get(input);
				#endif
			}else if(lang=="es"){
				#if defined LANG_ES
				output=lang_es().get(input);
				#endif
			}else{
				output=input;
			}
		}break;
		case 1:{	//Ustawianie języka
			#ifdef LANG_PL
				if(input=="pl") lang=input;
			#endif
			#ifdef LANG_EN
				if(input=="en") lang=input;
			#endif
			#ifdef LANG_ES
				if(input=="es") lang=input;
			#endif
		}break;
		case 2:{	//Wypisywanie dostępnych języków
			#ifdef LANG_PL
				output.append("pl ");
			#endif
			#ifdef LANG_EN
				output.append("en ");
			#endif
			#ifdef LANG_ES
				output.append("es ");
			#endif
		}break;
	}
	if(output.empty()) output=input;
	return output;
}

#endif
