#include "utility.h"

#define MAXRGB 255
#define MINRGB 0


int utility::checkValue(int value)
{
	if (value > MAXRGB)
		return MAXRGB;
	if (value < MINRGB)
		return MINRGB;
	return value;
}


bool check_roi(int i, int j, int roi_i, int roi_j, int roi_i_size, int roi_j_size)
{
	if(i >= roi_i && i <= roi_i+roi_i_size)
		if(j >= roi_j && j <= roi_j+roi_j_size) 
			return 1;
	return 0;
}


void utility::roi_binarize(image &src, image &tgt, int threshold, int roi_i, 
		int roi_j, int roi_i_size, int roi_j_size)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());

	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			if(check_roi(i, j, roi_i, roi_j, roi_i_size, roi_j_size))
			{
				if (src.getPixel(i,j) < threshold)
					tgt.setPixel(i,j,MINRGB);
				else
					tgt.setPixel(i,j,MAXRGB);
			}
			else
			{
				tgt.setPixel( i, j, src.getPixel(i,j) );
			}
				
		}
	}
}


void utility::roi_addGrey(image &src, image &tgt, int value, int roi_i, 
		int roi_j, int roi_i_size, int roi_j_size)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());

	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			if(check_roi(i, j, roi_i, roi_j, roi_i_size, roi_j_size))
			{
				tgt.setPixel(i,j,checkValue(src.getPixel(i,j) + value)); 
			}
			else
			{
				tgt.setPixel( i, j, src.getPixel(i,j) );
			}
				
		}
	}
}




// void utility::addGrey(image &src, image &tgt, int value)
// {
// 	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
// 	for (int i=0; i<src.getNumberOfRows(); i++)
// 		for (int j=0; j<src.getNumberOfColumns(); j++)
// 		{
// 			tgt.setPixel(i,j,checkValue(src.getPixel(i,j)+value)); 
// 		}
// }


// void utility::binarize(image &src, image &tgt, int threshold)
// {
// 	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
// 	for (int i=0; i<src.getNumberOfRows(); i++)
// 	{
// 		for (int j=0; j<src.getNumberOfColumns(); j++)
// 		{
// 			if (src.getPixel(i,j) < threshold)
// 				tgt.setPixel(i,j,MINRGB);
// 			else
// 				tgt.setPixel(i,j,MAXRGB);
// 		}
// 	}
// }


// void utility::scale(image &src, image &tgt, float ratio)
// {
// 	int rows = (int)((float)src.getNumberOfRows() * ratio);
// 	int cols  = (int)((float)src.getNumberOfColumns() * ratio);
// 	tgt.resize(rows, cols);
// 	for (int i=0; i<rows; i++)
// 	{
// 		for (int j=0; j<cols; j++)
// 		{	
// 			/* Map the pixel of new image back to original image */
// 			int i2 = (int)floor((float)i/ratio);
// 			int j2 = (int)floor((float)j/ratio);
// 			if (ratio == 2) {
// 				/* Directly copy the value */
// 				tgt.setPixel(i,j,checkValue(src.getPixel(i2,j2)));
// 			}

// 			if (ratio == 0.5) {
// 				/* Average the values of four pixels */
// 				int value = src.getPixel(i2,j2) + src.getPixel(i2,j2+1) + src.getPixel(i2+1,j2) + src.getPixel(i2+1,j2+1);
// 				tgt.setPixel(i,j,checkValue(value/4));
// 			}
// 		}
// 	}
// }



// std::string utility::intToString(int number)
// {
//    std::stringstream ss;//create a stringstream
//    ss << number;//add number to the stream
//    return ss.str();//return a string with the contents of the stream
// }