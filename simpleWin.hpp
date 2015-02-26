#ifndef SIMPLEWIN_HPP
#define SIMPLEWIN_HPP
class UID{
	private:
		static size_t UIDiterator;

	public:
		size_t get(){
			return UIDiterator++;
		}
};
size_t UID::UIDiterator=0;


class simpleWin{
		private:
	bool movable;
	bool resizeable;
	bool decoration;

	bool active;

	short x;
	short y;
	unsigned short width;
	unsigned short height;
	size_t id;
	std::string title;



		public:
	simpleWin(std::string Title,short X=0, short Y=0, unsigned short Width=8, unsigned short Height=4, bool Movable=true, bool Resizeable=true, bool Decoration=true, bool Active=true){
		title=Title;
		x=X;
		y=Y;
		width=Width;
		height=Height;
		movable=Movable;
		resizeable=Resizeable;
		decoration=Decoration;
		active=Active;
	}

	bool isActive(){return active;}
	bool setSize(const unsigned short w, const unsigned short h, const bool force=false){
		if(!force){
			if(w==0 || h==0) return false;
			width=w;
			height=h;
		}else{

		}

		return true;
	}

};
#endif // SIMPLEWIN_HPP
