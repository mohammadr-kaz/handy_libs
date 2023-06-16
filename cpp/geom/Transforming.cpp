#include "Transforming.h"
#include "UTM.h"
#include "Defs.h"

void hl::geom::cropUTMRect()
{
    // // TODO: (MK) The followings are hard codes. Automize calculation of them. Because the
    // // inputs to the current part of the algorithm (lat-lon of center + w-h) are enough
    // // for everything!
    // double lat_i = 35 * df::deg2rad;
    // double lon_i = 50 * df::deg2rad;
    // double lat_f = 37 * df::deg2rad;
    // double lon_f = 53 * df::deg2rad;

    // int zoneUTM_i = hl::geom::getUTMZone(lat_i, lon_i);
    // int zoneUTM_f = hl::geom::getUTMZone(lat_f, lon_f);

    // // TODO: (MK) Refer to the header file: "Transforming.h". See what function
    // // 'hl::geom::cropUTMRect()' does. Replace related part of the followings
    // // with a single call to hl::geom::cropUTMRect().
    // double xUTM_i;
    // double yUTM_i;
    // double xUTM_f;
    // double yUTM_f;

    // double xUTM_c;
    // double yUTM_c;

    // hl::geom::LatLonToUTMXY(lat_i, lon_i, zoneUTM_i, xUTM_i, yUTM_i);
    // hl::geom::LatLonToUTMXY(lat_f, lon_f, zoneUTM_f, xUTM_f, yUTM_f);

    // df::Point2D mapCenterLoc = config.ui.getMapCenterLoc();
    // double lat_center = mapCenterLoc.x * df::deg2rad;
    // double lon_center = mapCenterLoc.y * df::deg2rad;
    // int zoneUTM_center = hl::geom::getUTMZone(lat_center, lon_center);
    // hl::geom::LatLonToUTMXY(lat_center, lon_center, zoneUTM_center, xUTM_c, yUTM_c);

    // int x_center = std::round((xUTM_c - xUTM_i) * renderVision.cols / (xUTM_f - xUTM_i));
    // int y_center = std::round((yUTM_c - yUTM_i) * renderVision.rows / (yUTM_f - yUTM_i));

    // df::Point2D mapDim = config.ui.getMapDim();
    // int width = std::round(mapDim.x * renderVision.cols / (xUTM_f - xUTM_i));
    // int height = std::round(mapDim.y * renderVision.rows / (yUTM_f - yUTM_i));

    // cv::Rect ROI = cv::Rect(x_center - width / 2, y_center - height / 2, width, height);
}