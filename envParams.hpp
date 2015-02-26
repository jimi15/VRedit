#ifndef ENVPARAMS_HPP
#define ENVPARAMS_HPP
class envParams{
		private:
	static unsigned short wx,ex;
	static unsigned short wy,ey;
	static short margintop,marginbot,marginlr;
	static bool colormode;
	envParams(){}

		public:
	static unsigned short gwx(){return wx;}
	static unsigned short gwy(){return wy;}
	static unsigned short gex(){return ex;}
	static unsigned short gey(){return ey;}
	static short gmt(){return margintop;}
	static short gmb(){return marginbot;}
	static short gmlr(){return marginlr;}

	static void swx(const unsigned short value){wx=value;}
	static void swy(const unsigned short value){wy=value;}
	static void sex(const unsigned short value){ex=value;}
	static void sey(const unsigned short value){ey=value;}
	static void scm(const bool value){colormode=value;}
	static void smt(const short value){margintop=value;}
	static void smb(const short value){marginbot=value;}
	static void smlr(const short value){marginlr=value;}
};

#endif // ENVPARAMS_HPP
