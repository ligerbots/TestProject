//**************************************************************************
//* WARNING: This file was automatically generated.  Any changes you make  *
//*          to this file will be lost if you generate the file again.     *
//**************************************************************************
#ifndef IMAGEPROCESSING_TASK_INCLUDE
#define IMAGEPROCESSING_TASK_INCLUDE

#include <nivision.h>

class ImageProcessing {
protected:
	static bool processingOn;
public:
	static int IVA_ProcessImage(Image *image);
	static void setProcessingOn(bool processing){
		processingOn = processing;
	}
	static bool isProcessingOn(){
		return processingOn;
	}
	static void toggleProcessingOn(){
		processingOn = !processingOn;
	}
};

#endif // ifndef IMAGEPROCESSING_TASK_INCLUDE
