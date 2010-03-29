#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "28";
	static const char MONTH[] = "03";
	static const char YEAR[] = "2010";
	static const double UBUNTU_VERSION_STYLE = 10.03;
	
	//Software Status
	static const char STATUS[] = "FZ";
	static const char STATUS_SHORT[] = "fz";
	
	//Standard Version Type
	static const long MAJOR = 2;
	static const long MINOR = 4;
	static const long BUILD = 37;
	static const long REVISION = 210;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 82;
	#define RC_FILEVERSION 2,4,37,210
	#define RC_FILEVERSION_STRING "2, 4, 37, 210\0"
	static const char FULLVERSION_STRING[] = "2.4.37.210";
	
	//SVN Version
	static const char SVN_REVISION[] = "231";
	static const char SVN_DATE[] = "2009-05-14T00:03:11.370763Z";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 37;
	

}
#endif //VERSION_h
