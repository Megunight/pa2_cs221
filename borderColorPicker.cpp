    /**
     * @file borderColorPicker.cpp
     * @description Implements the BorderColorPicker constructor and () function
     *              for CPSC 221 PA2
     *
     *              THIS FILE WILL BE SUBMITTED
     */

    #include "borderColorPicker.h"
    #include <cmath>

    /**
     * Constructs a new BorderColorPicker.
     *
     * @param width        Number of pixels to color around border.
     * @param inputimage   Image for referencing original image colors.
     * @param bcolor       Color to be used for painting the fill border.
     * @param tol          Tolerance used to determine the border of the fill.
     */
    BorderColorPicker::BorderColorPicker(unsigned int width, PNG& inputimage, RGBAPixel scolor, RGBAPixel bcolor, double tol)
    {
        // Complete your implementation below
        borderwidth = width;
        img = inputimage;
        seedcolor = scolor;
        bordercolor = bcolor;
        tolerance = tol;
    }

    /**
     * Picks the color for pixel at point. If the x or y coordinate is
     * at or within an Euclidean radius of borderwidth pixels from the border of
     * the fill region, it will be colored with the required border color.
     * Otherwise, its color will not be changed.
     *
     * @param p   The point for which you're picking a color.
     * @return    The color chosen for (p).
     */
    RGBAPixel BorderColorPicker::operator()(PixelPoint p)
    {
        // Replace the line below with your implementation
        unsigned int x = p.x;
        unsigned int y = p.y;
        unsigned int width = img.width();
        unsigned int height = img.height();
        
        //Check the border of the image
        if (x < borderwidth || y < borderwidth || x >= width - borderwidth || y >= height - borderwidth) {
            return bordercolor;
        }
        
        for (int i = x - borderwidth; i <= x + borderwidth; i++) {
            for (int j = y - borderwidth; j <= y + borderwidth; j++) {
                if (i >= 0 && i < width && j >= 0 && j < height) {
                    RGBAPixel* pixel = img.getPixel(i, j);
                    double distance = sqrt(pow(pixel->r - seedcolor.r, 2) +
                                        pow(pixel->g - seedcolor.g, 2) +
                                        pow(pixel->b - seedcolor.b, 2));
                    if (distance <= tolerance) {
                        return bordercolor;
                    }
                }
            }
        }
    
        return seedcolor;
    }

    /**
     * Add your private BorderColorPicker function implementations below
     */
