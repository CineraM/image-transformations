#include "utility.h"

#define MAXRGB 255
#define MINRGB 0

image temp1, temp2;


int utility::checkValue(int value)
{
	if (value > MAXRGB)
		return MAXRGB;
	if (value < MINRGB)
		return MINRGB;
	return value;
}

// test fnc
void utility::copyimg(image &src, image &tgt)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			for(int channel = 0; channel<3; channel++)
				tgt.setPixel(i, j, channel, src.getPixel(i, j, channel));
		}
	}
}


bool check_roi(int i, int j, int roi_i, int roi_j, int roi_i_size, int roi_j_size)
{
	if(i >= roi_i && i <= roi_i+roi_i_size-1)
		if(j >= roi_j && j <= roi_j+roi_j_size-1) 
			return 1;
	return 0;
}


void utility::roi(image &src, image &tgt, int roi_i, int roi_j, int roi_i_size, int roi_j_size)
{
	tgt.resize(roi_i_size, roi_j_size);
	int rows = src.getNumberOfRows();
	int cols = src.getNumberOfColumns();

	for (int i=0; i<roi_i_size; i++)
	{
		for (int j=0; j<roi_j_size; j++)
		{
			if((i+roi_i) >= rows || (j+roi_j) >= cols)
			{
				for(int channel = 0; channel<3; channel++)
					tgt.setPixel(i, j, channel, MINRGB);
			}
			else
			{
				for(int channel = 0; channel<3; channel++)
					tgt.setPixel(i, j, channel, src.getPixel(i+roi_i, j+roi_j, channel));
			}
		}
	}

}


void utility::binarize(image &src, image &tgt, int threshold)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			if (src.getPixel(i,j) < threshold)
			{
				for(int channel = 0; channel<3; channel++)
					tgt.setPixel(i, j, channel, MINRGB);
			}
			else
			{
				for(int channel = 0; channel<3; channel++)
					tgt.setPixel(i, j, channel, MAXRGB);
			}
		}
	}
}


void utility::addGrey(image &src, image &tgt, int value)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			for(int channel = 0; channel<3; channel++)
				tgt.setPixel(i, j, channel, checkValue(src.getPixel(i, j, channel)+value));
		}
}


void utility::mergeRoi(image &src, image &roi,image &tgt, int roi_i, int roi_j, 
int roi_i_size, int roi_j_size)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			
			if(check_roi(i, j, roi_i, roi_j, roi_i_size, roi_j_size))
			{
				for(int channel = 0; channel<3; channel++)
					tgt.setPixel(i, j, channel, src.getPixel(i-roi_i, j-roi_j, channel));
			}
			else
			{
				for(int channel = 0; channel<3; channel++)
					tgt.setPixel(i, j, channel, src.getPixel(i, j, channel));
			}
				
		}
	}
}


void utility::scale(image &src, image &tgt, float ratio)
{
	ratio/=10;
	int rows = (int)((float)src.getNumberOfRows() * ratio);
	int cols  = (int)((float)src.getNumberOfColumns() * ratio);
	tgt.resize(rows, cols);
	for (int i=0; i<rows; i++)
	{
		for (int j=0; j<cols; j++)
		{	
			/* Map the pixel of new image back to original image */
			int i2 = (int)floor((float)i/ratio);
			int j2 = (int)floor((float)j/ratio);
			// Directly copy the value 
			for(int channel = 0; channel<3; channel++)
				tgt.setPixel(i, j, channel, checkValue(src.getPixel(i2, j2, channel)));
			}
	}
}


void utility::rotate(image &src, image &tgt, int angle)
{
	int rows = src.getNumberOfRows();
	int cols = src.getNumberOfColumns();

	if(angle == 90 || angle == 270)
		tgt.resize(cols, rows);
	tgt.resize(rows, cols);

	for (int i=0; i<rows; i++)
	{
		for (int j=0; j<cols; j++)
		{
			int new_i, new_j;
			if(angle == 90)
			{
				new_i = j;
				new_j = rows - 1 - i;
			}
			else if(angle == 180)
			{
				new_i = rows - 1 - i;
				new_j = cols - 1 - j;	
			}
			else if(angle == 270)
			{
				new_i = cols - 1 - j;
				new_j = i;	
			}

			for(int channel = 0; channel<3; channel++)
				tgt.setPixel(new_i, new_j, channel, src.getPixel(i, j, channel));
		}
	}
}


void utility::binarizeWrapper(image &src, image &tgt, int fnc_input, 
int roi_i, int roi_j, int roi_i_size, int roi_j_size)
{
	roi(src, temp1, roi_i, roi_j, roi_i_size, roi_j_size);
	binarize(temp1, temp2, fnc_input);
	mergeRoi(src, temp2, tgt, roi_i, roi_j, roi_i_size, roi_j_size);
}


void utility::addGreyWrapper(image &src, image &tgt, int fnc_input, 
int roi_i, int roi_j, int roi_i_size, int roi_j_size)
{
	roi(src, temp1, roi_i, roi_j, roi_i_size, roi_j_size);
	addGrey(temp1, temp2, fnc_input);
	mergeRoi(src, temp2, tgt, roi_i, roi_j, roi_i_size, roi_j_size);
}


void utility::scaleWrapper(image &src, image &tgt, int fnc_input, 
int roi_i, int roi_j, int roi_i_size, int roi_j_size)
{
	roi(src, temp1, roi_i, roi_j, roi_i_size, roi_j_size);
	scale(temp1, tgt, fnc_input);
}


void utility::rotateWrapper(image &src, image &tgt, int fnc_input, 
int roi_i, int roi_j, int roi_i_size, int roi_j_size)
{
	roi(src, temp1, roi_i, roi_j, roi_i_size, roi_j_size);
	rotate(temp1, temp2, fnc_input);
	mergeRoi(src, temp2, tgt, roi_i, roi_j, roi_i_size, roi_j_size);
}