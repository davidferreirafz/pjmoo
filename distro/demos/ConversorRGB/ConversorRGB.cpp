/*****************************************************************/
/* Declaração - Includes                                         */
/*****************************************************************/
#include <math.h>
#include <stdlib.h>
#include <iostream>

#include "SystemColor.h"


//////////////////////////////////////////////
// Entry point
int main(int argc, char *argv[])
{

	HSV hsv;
	RGB rgb;
	
	hsv.h=0;
	hsv.s=0.50;
	hsv.v=0.50;


	rgb = SystemColor::forRGB(hsv);
	
	printf("\n\r HSV -> H:%f S:%f V:%f",hsv.h,hsv.s,hsv.v);
	printf("\n\r RGB -> R:%d G:%d B:%d",rgb.r,rgb.g,rgb.b);

	hsv = SystemColor::forHSV(rgb);

	printf("\n\r HSV -> H:%f S:%f V:%f",hsv.h,hsv.s,hsv.v);
	printf("\n\r RGB -> R:%d G:%d B:%d",rgb.r,rgb.g,rgb.b);
		    	
	return 0;  
}
