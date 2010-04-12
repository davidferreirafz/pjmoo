#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Software Status
	static const char STATUS[] = "FZ";
	static const char STATUS_SHORT[] = "fz";
	
	//Standard Version Type
	static const long MAJOR = 2;
	static const long MINOR = 4;
	static const long BUILD = 58;
	static const long REVISION = 336;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 121;
	#define RC_FILEVERSION 2,4,58,336
	#define RC_FILEVERSION_STRING "2, 4, 58, 336\0"
	static const char FULLVERSION_STRING[] = "2.4.58.336";
	
	//SVN Version
	static const char SVN_REVISION[] = "250";
	static const char SVN_DATE[] = "2010-04-01T17:36:35.919677Z";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 58;
	

}
#endif //VERSION_h
