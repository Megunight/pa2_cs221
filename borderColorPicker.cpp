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
        unsigned int x = p.x;
        unsigned int y = p.y;
        unsigned int width = img.width();
        unsigned int height = img.height();
        
        //Check the border of the image
        if (seedcolor.distanceTo(*img.getPixel(x, y)) > tolerance) {
            return *img.getPixel(x, y);
        }
        
        for (unsigned int i = x - borderwidth; i <= x + borderwidth; ++i) {
            for (unsigned int j = y - borderwidth; j <= y + borderwidth; ++j) {
                int distance = (i - x) * (i - x) + (j - y) * (j - y);
                if (distance <= static_cast<int>(borderwidth * borderwidth)) {
                    if (static_cast<int>(i) >= 0 && i < (width) && static_cast<int>(j) >= 0 && j < (height)) {
                        // Check if the neighboring pixel color is different from the seed color
                        if (seedcolor.distanceTo(*img.getPixel(i, j)) > tolerance) {
                            return bordercolor; // Pixel is part of the border
                        }
                    } else {
                        return bordercolor; // Pixel is part of the border (outside image boundaries)
                    }
                }
            }
        }
    
        return *img.getPixel(x, y);
    }

    /**
     * Add your private BorderColorPicker function implementations below
     */
