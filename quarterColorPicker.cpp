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
    ogImage = inputimg;
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
        x = x - ogImage.width() / 2;
    if (y >= referenceimg.height())
        y = y - ogImage.height() / 2;
    RGBAPixel color = bilinearBrightness(x, y);
    return color;
}

/**
 * Add your private QuarterColorPicker function implementations below
 */
 
/**
 * @param x is the x-coord of the scaled referenceimg
 * @param y is the y-coord of the scaled referenceimg
 */
RGBAPixel QuarterColorPicker::bilinearBrightness(unsigned int x, unsigned int y) {
    unsigned int ogX = 2 * x;
    unsigned int ogY = 2 * y;

    RGBAPixel* p1 = ogImage.getPixel(ogX, ogY);
    RGBAPixel* p2 = ogImage.getPixel(ogX + 1, ogY);
    RGBAPixel* p3 = ogImage.getPixel(ogX, ogY + 1);
    RGBAPixel* p4 = ogImage.getPixel(ogX + 1, ogY + 1);

    RGBAPixel p;

    unsigned int red = ((p1->r + p2->r) / 2 + (p3->r + p4->r) / 2) / 2 + brightamount;
    unsigned int green = ((p1->g + p2->g) / 2 + (p3->g + p4->g) / 2) / 2 + brightamount;
    unsigned int blue = ((p1->b + p2->b) / 2 + (p3->b + p4->b) / 2) / 2 + brightamount;
    double alpha = ((p1->a + p2->a) / 2 + (p3->a + p4->a) / 2) / 2;
    
    if (red > 255)
        p.r = 255;
    else
        p.r = red;
    if (green > 255)
        p.g = 255;
    else
        p.g = green;
    if (blue > 255)
        p.b = 255;
    else
        p.b = blue;
    
    p.a = alpha;
    
    return p;
}