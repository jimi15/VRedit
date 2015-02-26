#ifndef VERSION_HPP
#define VERSION_HPP

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "26";
	static const char MONTH[] = "02";
	static const char YEAR[] = "2015";
	static const char UBUNTU_VERSION_STYLE[] =  "15.02";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 0;
	static const long MINOR  = 0;
	static const long BUILD  = 10;
	static const long REVISION  = 48;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 294;
	#define RC_FILEVERSION 0,0,10,48
	#define RC_FILEVERSION_STRING "0, 0, 10, 48\0"
	static const char FULLVERSION_STRING [] = "0.0.10.48";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 11;
	

}
#endif //VERSION_HPP
