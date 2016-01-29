 
//**************************************************************************
//* WARNING: This file was automatically generated.  Any changes you make  *
//*          to this file will be lost if you generate the file again.     *
//**************************************************************************
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <nivision.h>
#include <iostream>

#include "ImageProcessing.h"

// If you call Machine Vision functions in your script, add NIMachineVision.c to the project.

#define IVA_MAX_BUFFERS 20
#define IVA_STORE_RESULT_NAMES

#define VisionErrChk(Function) {if (!(Function)) {success = 0; goto Error;}}

typedef enum IVA_ResultType_Enum {IVA_NUMERIC, IVA_BOOLEAN, IVA_STRING} IVA_ResultType;

typedef union IVA_ResultValue_Struct    // A result in Vision Assistant can be of type double, BOOL or string.
{
    double numVal;
    bool   boolVal;
    char*  strVal;
} IVA_ResultValue;

typedef struct IVA_Result_Struct
{
#if defined (IVA_STORE_RESULT_NAMES)
    char resultName[256];           // Result name
#endif
    IVA_ResultType  type;           // Result type
    IVA_ResultValue resultVal;      // Result value
} IVA_Result;

typedef struct IVA_StepResultsStruct
{
#if defined (IVA_STORE_RESULT_NAMES)
    char stepName[256];             // Step name
#endif
    int         numResults;         // number of results created by the step
    IVA_Result* results;            // array of results
} IVA_StepResults;

typedef struct IVA_Data_Struct
{
    Image* buffers[IVA_MAX_BUFFERS];            // Vision Assistant Image Buffers
    IVA_StepResults* stepResults;              // Array of step results
    int numSteps;                               // Number of steps allocated in the stepResults array
    CoordinateSystem *baseCoordinateSystems;    // Base Coordinate Systems
    CoordinateSystem *MeasurementSystems;       // Measurement Coordinate Systems
    int numCoordSys;                            // Number of coordinate systems
} IVA_Data;



static IVA_Data* IVA_InitData(int numSteps, int numCoordSys);
static int IVA_DisposeData(IVA_Data* ivaData);
static int IVA_DisposeStepResults(IVA_Data* ivaData, int stepIndex);
static int IVA_CLRThreshold(Image* image, int min1, int max1, int min2, int max2, int min3, int max3, int colorMode);
static int IVA_ParticleFilter(Image* image,
                                       int pParameter[],
                                       float plower[],
                                       float pUpper[],
                                       int pCalibrated[],
                                       int pExclude[],
                                       int criteriaCount,
                                       int rejectMatches,
                                       int connectivity);

bool ImageProcessing::processingOn = false;

int ImageProcessing::IVA_ProcessImage(Image *image)
{
	int success = 1;
	if(!processingOn) return success;
    IVA_Data *ivaData;
    ImageType imageType;
    int pParameter[1] = {35};
    float plower[1] = {0};
    float pUpper[1] = {50};
    int pCalibrated[1] = {0};
    int pExclude[1] = {0};
    ImageType imageType1;

    // Initializes internal data (buffers and array of points for caliper measurements)
    VisionErrChk(ivaData = IVA_InitData(5, 0));

	VisionErrChk(IVA_CLRThreshold(image, 0, 99, 144, 255, 102, 255, IMAQ_RGB));

    //-------------------------------------------------------------------//
    //                       Lookup Table: Equalize                      //
    //-------------------------------------------------------------------//
    // Calculates the histogram of the image and redistributes pixel values across
    // the desired range to maintain the same pixel value distribution.
    VisionErrChk(imaqGetImageType(image, &imageType));
    VisionErrChk(imaqEqualize(image, image, 0, (imageType == IMAQ_IMAGE_U8 ? 255 : 0), NULL));

	VisionErrChk(IVA_ParticleFilter(image, pParameter, plower, pUpper, 
		pCalibrated, pExclude, 1, TRUE, TRUE));

    //-------------------------------------------------------------------//
    //                       Lookup Table: Equalize                      //
    //-------------------------------------------------------------------//
    // Calculates the histogram of the image and redistributes pixel values across
    // the desired range to maintain the same pixel value distribution.
    VisionErrChk(imaqGetImageType(image, &imageType1));
    VisionErrChk(imaqEqualize(image, image, 0, (imageType1 == IMAQ_IMAGE_U8 ? 255 : 0), NULL));

    // Releases the memory allocated in the IVA_Data structure.
    IVA_DisposeData(ivaData);

Error:
	return success;
}

////////////////////////////////////////////////////////////////////////////////
//
// Function Name: IVA_CLRThreshold
//
// Description  : Thresholds a color image.
//
// Parameters   : image      -  Input image
//                min1       -  Minimum range for the first plane
//                max1       -  Maximum range for the first plane
//                min2       -  Minimum range for the second plane
//                max2       -  Maximum range for the second plane
//                min3       -  Minimum range for the third plane
//                max3       -  Maximum range for the third plane
//                colorMode  -  Color space in which to perform the threshold
//
// Return Value : success
//
////////////////////////////////////////////////////////////////////////////////
static int IVA_CLRThreshold(Image* image, int min1, int max1, int min2, int max2, int min3, int max3, int colorMode)
{
    int success = 1;
    Image* thresholdImage;
    Range plane1Range;
    Range plane2Range;
    Range plane3Range;


    //-------------------------------------------------------------------//
    //                          Color Threshold                          //
    //-------------------------------------------------------------------//

    // Creates an 8 bit image for the thresholded image.
    VisionErrChk(thresholdImage = imaqCreateImage(IMAQ_IMAGE_U8, 7));

    // Set the threshold range for the 3 planes.
    plane1Range.minValue = min1;
    plane1Range.maxValue = max1;
    plane2Range.minValue = min2;
    plane2Range.maxValue = max2;
    plane3Range.minValue = min3;
    plane3Range.maxValue = max3;

    // Thresholds the color image.

    ColorMode colorMode2;
    memcpy(&colorMode2, &colorMode, sizeof(colorMode2));
    VisionErrChk(imaqColorThreshold(thresholdImage, image, 1, colorMode2, &plane1Range, &plane2Range, &plane3Range));

    // Copies the threshold image in the souce image.
    VisionErrChk(imaqDuplicate(image, thresholdImage));

Error:
    imaqDispose(thresholdImage);

    return success;
}


////////////////////////////////////////////////////////////////////////////////
//
// Function Name: IVA_ParticleFilter
//
// Description  : Filters particles based on their morphological measurements.
//
// Parameters   : image          -  Input image
//                pParameter     -  Morphological measurement that the function
//                                  uses for filtering.
//                plower         -  Lower bound of the criteria range.
//                pUpper         -  Upper bound of the criteria range.
//                pCalibrated    -  Whether to take a calibrated measurement or not.
//                pExclude       -  TRUE indicates that a match occurs when the
//                                  value is outside the criteria range.
//                criteriaCount  -  number of particle filter criteria.
//                rejectMatches  -  Set this parameter to TRUE to transfer only
//                                  those particles that do not meet all the criteria.
//                                  Set this parameter to FALSE to transfer only those
//                                  particles that meet all the criteria to the destination.
//                connectivity   -  Set this parameter to 1 to use connectivity-8
//                                  to determine whether particles are touching.
//                                  Set this parameter to 0 to use connectivity-4
//                                  to determine whether particles are touching.
//
// Return Value : success
//
////////////////////////////////////////////////////////////////////////////////
static int IVA_ParticleFilter(Image* image,
                                       int pParameter[],
                                       float plower[],
                                       float pUpper[],
                                       int pCalibrated[],
                                       int pExclude[],
                                       int criteriaCount,
                                       int rejectMatches,
                                       int connectivity)
{
    int success = 1;
    ParticleFilterCriteria2* particleCriteria = NULL;
    int i;
    ParticleFilterOptions particleFilterOptions;
    int numParticles;


    //-------------------------------------------------------------------//
    //                          Particle Filter                          //
    //-------------------------------------------------------------------//

    if (criteriaCount > 0)
    {
        // Fill in the ParticleFilterCriteria2 structure.
        particleCriteria = (ParticleFilterCriteria2*)malloc(criteriaCount * sizeof(ParticleFilterCriteria2));

        for (i = 0 ; i < criteriaCount ; i++)
        {
        	MeasurementType measurementType;
        	int iMeasurementType = pParameter[i];
        	memcpy(&measurementType, &iMeasurementType, sizeof(iMeasurementType));
            particleCriteria[i].parameter = measurementType;
            particleCriteria[i].lower = plower[i];
            particleCriteria[i].upper = pUpper[i];
            particleCriteria[i].calibrated = pCalibrated[i];
            particleCriteria[i].exclude = pExclude[i];
        }
        
        particleFilterOptions.rejectMatches = rejectMatches;
        particleFilterOptions.rejectBorder = 0;
        particleFilterOptions.connectivity8 = connectivity;
        
        // Filters particles based on their morphological measurements.
        VisionErrChk(imaqParticleFilter3(image, image, particleCriteria, criteriaCount, &particleFilterOptions, NULL, &numParticles));
    }

Error:
    free(particleCriteria);

    return success;
}


// modify autogenerated code to make compiler ignore warning.
// since this is autogenerated we can assume it's ok
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#pragma GCC diagnostic ignored "-Wformat-zero-length"
////////////////////////////////////////////////////////////////////////////////
//
// Function Name: IVA_InitData
//
// Description  : Initializes data for buffer management and results.
//
// Parameters   : # of steps
//                # of coordinate systems
//
// Return Value : success
//
////////////////////////////////////////////////////////////////////////////////
static IVA_Data* IVA_InitData(int numSteps, int numCoordSys)
{
    int success = 1;
    IVA_Data* ivaData = NULL;
    int i;


    // Allocate the data structure.
    VisionErrChk(ivaData = (IVA_Data*)malloc(sizeof (IVA_Data)));

    // Initializes the image pointers to NULL.
    for (i = 0 ; i < IVA_MAX_BUFFERS ; i++)
        ivaData->buffers[i] = NULL;

    // Initializes the steo results array to numSteps elements.
    ivaData->numSteps = numSteps;

    ivaData->stepResults = (IVA_StepResults*)malloc(ivaData->numSteps * sizeof(IVA_StepResults));
    for (i = 0 ; i < numSteps ; i++)
    {
        #if defined (IVA_STORE_RESULT_NAMES)
            std::sprintf(ivaData->stepResults[i].stepName, "");
        #endif
        ivaData->stepResults[i].numResults = 0;
        ivaData->stepResults[i].results = NULL;
    }

    // Create the coordinate systems
    ivaData->baseCoordinateSystems = NULL;
    ivaData->MeasurementSystems = NULL;
    if (numCoordSys)
    {
        ivaData->baseCoordinateSystems = (CoordinateSystem*)malloc(sizeof(CoordinateSystem) * numCoordSys);
        ivaData->MeasurementSystems = (CoordinateSystem*)malloc(sizeof(CoordinateSystem) * numCoordSys);
    }

    ivaData->numCoordSys = numCoordSys;

Error:
    return ivaData;
}
#pragma GCC diagnostic warning "-Wunused-but-set-variable"
#pragma GCC diagnostic warning "-Wformat-zero-length"


////////////////////////////////////////////////////////////////////////////////
//
// Function Name: IVA_DisposeData
//
// Description  : Releases the memory allocated in the IVA_Data structure
//
// Parameters   : ivaData  -  Internal data structure
//
// Return Value : success
//
////////////////////////////////////////////////////////////////////////////////
static int IVA_DisposeData(IVA_Data* ivaData)
{
    int i;


    // Releases the memory allocated for the image buffers.
    for (i = 0 ; i < IVA_MAX_BUFFERS ; i++)
        imaqDispose(ivaData->buffers[i]);

    // Releases the memory allocated for the array of measurements.
    for (i = 0 ; i < ivaData->numSteps ; i++)
        IVA_DisposeStepResults(ivaData, i);

    free(ivaData->stepResults);

    // Dispose of coordinate systems
    if (ivaData->numCoordSys)
    {
        free(ivaData->baseCoordinateSystems);
        free(ivaData->MeasurementSystems);
    }

    free(ivaData);

    return true;
}


////////////////////////////////////////////////////////////////////////////////
//
// Function Name: IVA_DisposeStepResults
//
// Description  : Dispose of the results of a specific step.
//
// Parameters   : ivaData    -  Internal data structure
//                stepIndex  -  step index
//
// Return Value : success
//
////////////////////////////////////////////////////////////////////////////////
static int IVA_DisposeStepResults(IVA_Data* ivaData, int stepIndex)
{
    int i;

    
    for (i = 0 ; i < ivaData->stepResults[stepIndex].numResults ; i++)
    {
        if (ivaData->stepResults[stepIndex].results[i].type == IVA_STRING)
            free(ivaData->stepResults[stepIndex].results[i].resultVal.strVal);
    }

    free(ivaData->stepResults[stepIndex].results);

    return true;
}


