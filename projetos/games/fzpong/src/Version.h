#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Software Status
	static const char STATUS[] = "FZ";
	static const char STATUS_SHORT[] = "fz";
	
	//Standard Version Type
	static const long MAJOR = 2;
	static const long MINOR = 4;
	static const long BUILD = 74;
	static const long REVISION = 426;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 141;
	#define RC_FILEVERSION 2,4,74,426
	#define RC_FILEVERSION_STRING "2, 4, 74, 426\0"
	static const char FULLVERSION_STRING[] = "2.4.74.426";
	
	//SVN Version
	static const char SVN_REVISION[] = "251";
	static const char SVN_DATE[] = "2010-04-12T01:49:10.186363Z";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 74;
	

}
#endif //VERSION_H
