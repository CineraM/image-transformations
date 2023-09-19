#ifndef UTILITY_H
#define UTILITY_H

#include "../image/image.h"
#include <sstream>
#include <math.h>

class utility
{
	public:
		utility();
		virtual ~utility();
		static std::string intToString(int number);
		static int checkValue(int value);

		static void roi(image &src, image &tgt, 
		int roi_i, int roi_j, int roi_i_size, int roi_j_size);

		static void mergeRoi(image &src, image &roi,image &tgt, int roi_i, int roi_j, 
		int roi_i_size, int roi_j_size);

		static void binarize(image &src, image &tgt, int threshold);

		static void addGrey(image &src, image &tgt, int value);

		static void rotate(image &src, image &tgt, int angle);

};

#endif

