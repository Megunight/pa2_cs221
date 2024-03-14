/**
 * @file quarterColorPicker.cpp
 * @description Implements the QuarterColorPicker constructor and () function
 *              for CPSC 221 PA2
 *
 *              THIS FILE WILL BE SUBMITTED
 */

#include "quarterColorPicker.h"

QuarterColorPicker::QuarterColorPicker(PNG& inputimg, unsigned char b_amount)
{
    referenceimg = inputimg;
    brightamount = b_amount;
    referenceimg.resize(referenceimg.width() / 2, referenceimg.height() / 2);
}

/**
 * Picks the color for pixel (x, y).
 *
 * Using the private reference image, scale each dimension by half
 * and tile the smaller image in a 2 x 2 grid over the original dimensions
 * of the image, and return the pixel at the appropriate coordinate from
 * the tiled image, brightened on each R/G/B channel by the required amount.
 * 
 * The value of each pixel in the scaled image will be a bilinear interpolation
 * of a 2x2 pixel region from the original image, with each of the R/G/B/A channels
 * processed individually. Interpolate over the x-axis before the y-axis.
 * Truncate any fractional values on the R/G/B channels. Brighten each color channel
 * as the final step.
 * 
 * @pre referenceimg width and height are both even
 */
RGBAPixel QuarterColorPicker::operator()(PixelPoint p)
{
    unsigned int x = p.x;
    unsigned int y = p.y;
    // ensures that x and y are within bounds and matches the reduced dimensions of reference img
    if (x >= referenceimg.width())
        x = x / 2;
    if (y >= referenceimg.height())
        y = y / 2;
    
    RGBAPixel* rPixel = referenceimg.getPixel(x, y);
    
}

/**
 * Add your private QuarterColorPicker function implementations below
 */
 