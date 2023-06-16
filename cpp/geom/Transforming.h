#ifndef HL_TRANSFORMING_H
#define HL_TRANSFORMING_H

namespace hl::geom 
{
    // input: 
    //      - A 'lat-long' (in degree or rad) related to center of an area on earth
    //      - A 'width-height' (double - in meter) for the area center of which is declared 
    //        with the 'lat-long'
    // ouput:
    //      - 2 'x-y' (double) couples as UTM coordinates for up-left and down-right points of 
    //        the rectangular area
    void cropUTMRect();
}

#endif