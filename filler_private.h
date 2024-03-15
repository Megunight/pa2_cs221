/**
 * @file filler_private.h
 * @description student declarations of private functions
 *              for Filler, CPSC 221 PA2
 *
 *              THIS FILE WILL BE SUBMITTED.
 *
 *              Simply declare your function prototypes here.
 *              No other scaffolding is necessary.
 */

 // begin your declarations below

/*
returns PixelPoint of x, y coord on img and with colour RGBAPixel
*/
PixelPoint getPixelPoint(unsigned int x, unsigned int y);

bool find(const std::vector<PixelPoint> v, PixelPoint p);