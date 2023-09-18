/************************************************************
 *															*
 * This sample project include three functions:				*
 * 1. Add intensity for gray-level image.					*
 *    Input: source image, output image name, value			*
 *															*
 * 2. Image thresholding: pixels will become black if the	*
 *    intensity is below the threshold, and white if above	*
 *    or equal the threhold.								*
 *    Input: source image, output image name, threshold		*
 *															*
 * 3. Image scaling: reduction/expansion of 2 for 			*
 *    the width and length. This project uses averaging 	*
 *    technique for reduction and pixel replication			*
 *    technique for expansion.								*
 *    Input: source image, output image name, scale factor	*
 *															*
 ************************************************************/

#include "../iptools/core.h"
#include <string.h>

using namespace std;

#define MAXLEN 256

int main (int argc, char** argv)
{
	image src, tgt;
	FILE *fp;
	char str[MAXLEN];
	char outfile[MAXLEN];
	char *pch;
	if ((fp = fopen(argv[1],"r")) == NULL) {
		fprintf(stderr, "Can't open file: %s\n", argv[1]);
		exit(1);
	}

	while(fgets(str,MAXLEN,fp) != NULL) {
		pch = strtok(str, " ");
		src.read(pch);

		pch = strtok(NULL, " ");
		strcpy(outfile, pch);

		// reading function name, each function will specify 
		// specify how many parameters will be read
		pch = strtok(NULL, " ");

        if (strcmp(pch,"rBin")==0) 
		{
			pch = strtok(NULL, " ");
			int threshold = atoi(pch);

			pch = strtok(NULL, " ");
			int roi_i = atoi(pch);

			pch = strtok(NULL, " ");
			int roi_j = atoi(pch);

			pch = strtok(NULL, " ");
			int roi_i_size = atoi(pch);

			pch = strtok(NULL, " ");
			int roi_j_size = atoi(pch);

        	utility::roi_binarize(src, tgt, threshold, roi_i, roi_j, roi_i_size, roi_j_size);
        }

        else if (strcmp(pch,"rAdd")==0) 
		{
			pch = strtok(NULL, " ");
			int value = atoi(pch);

			pch = strtok(NULL, " ");
			int roi_i = atoi(pch);

			pch = strtok(NULL, " ");
			int roi_j = atoi(pch);

			pch = strtok(NULL, " ");
			int roi_i_size = atoi(pch);

			pch = strtok(NULL, " ");
			int roi_j_size = atoi(pch);

        	utility::roi_addGrey(src, tgt, value, roi_i, roi_j, roi_i_size, roi_j_size);
        }

		pch = strtok(NULL, " ");

		tgt.save(outfile);
	}
	fclose(fp);
	return 0;
}
