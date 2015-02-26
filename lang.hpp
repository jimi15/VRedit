#ifndef LANG
#define LANG

static std::string l(const std::string &input,const int option=0){
//	static bool init;
	static std::string lang;
	std::string output;

	if(lang.empty()){
			#if defined LANG_PL
				lang="polski";
			#elif defined LANG_EN
				lang="angielski";
			#elif defined LANG_ES
				lang="hiszpanski";
			#endif
	}

	switch(option){
		case 0:{	//Wypisywanie z bazy
			if(lang=="polski"){
				#if defined LANG_PL
				output=lang_pl().get(input);
				#endif
			}else if(lang=="angielski"){
				#if defined LANG_EN
				output=lang_en().get(input);
				#endif
			}else if(lang=="hiszpanski"){
				#if defined LANG_ES
				output=lang_es().get(input);
				#endif
			}else{
				output=input;
			}
		}break;
		case 1:{	//Ustawianie języka
			#ifdef LANG_PL
				if(input=="polski") lang=input;
			#endif
			#ifdef LANG_EN
				if(input=="angielski") lang=input;
			#endif
			#ifdef LANG_ES
				if(input=="hiszpanski") lang=input;
			#endif
		}break;
		case 2:{	//Wypisywanie dostępnych języków
			#ifdef LANG_PL
				output.append("polski ");
			#endif
			#ifdef LANG_EN
				output.append("angielski ");
			#endif
			#ifdef LANG_ES
				output.append("hiszpanski ");
			#endif
		}break;
	}
	if(output.empty()) output=input;
	return output;
}

#endif
