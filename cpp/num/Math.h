#ifndef HL_MATH_H
#define HL_MATH_H

#include <istream>
#include <random>
#include <math.h>
#include <iostream>
#include <algorithm>

#define PI 3.14159265358979323846

namespace hl::math
{
    struct Point
    {
        float x, y;
    };

    size_t random(size_t, size_t);
    float random(float, float, int);
    float calcEuclideanDist(int, int, int, int);
    void amplifyMat(float, std::vector<std::vector<float>> &);
    int test(int, int);

    template <typename vecType, typename elType>
    float averageVec(vecType&, elType);
    float average1d(const std::vector<float>&);
    float average1d(const std::vector<int>&);
    double average1d(const std::vector<double>&);

    float nonZeroMean(const std::vector<float>&);

    template <typename arrType, typename elType>
    float averageArr(arrType&, elType);
    float average2d(std::vector<std::vector<float>>&);
    float average2d(std::vector<std::vector<double>>&);

    template <typename tp>
    tp movingAverage(std::vector<tp>&, tp, int);
    float movingAverage1d(std::vector<float>&, int);
    double movingAverage1d(std::vector<double>&, int);

    template <typename tp>
    float movingOccurAverage(std::vector<tp>&, int, tp);
    float movingOccuranceAverage(std::vector<bool>&, int, bool);

    template <typename tp>
    void bufferVec(std::vector<tp> &, tp, int);
    void bufferVector(std::vector<double>&, double, int);
    void bufferVector(std::vector<bool>&, bool, int);

    void cartToPolar(float, float, float, float, float&, float&);

    float convertAngle(float&);
    float calcAngleWrtNorth(float, float, float, float);

    void calcPolarPoint(float, float, float&, float&);

    void normalizeVector(const std::vector<float>&, std::vector<float>&, float, float);
    void normalizeVector(const std::vector<float>&, std::vector<float>&);

    bool onSegment(Point&, Point&, Point&);
    int orientation(Point&, Point&, Point&);
    bool checkIntersection(std::vector<float>&, std::vector<float>&);

    int argmax(const std::vector<float>&);

    class Smoother1D
    {
        int numCoeffs; //MUST be > 0
        std::vector<float> b; //Filter coefficients
        std::vector<float> m; //Filter memories

    public:
        Smoother1D(int _numCoeffs) :
        numCoeffs(_numCoeffs)
        {
            if (numCoeffs<1)
                numCoeffs = 1; //Must be > 0 or bad stuff happens

            float val = 1./numCoeffs;
            for (int ii=0; ii<numCoeffs; ++ii) {
                b.push_back(val);
                m.push_back(0.);
            }
        }    

        void filter(std::vector<float> &a)
        {
            float output;

            for (int nn=0; nn<a.size(); ++nn)
            {
                //Apply smoothing filter to signal
                output = 0;
                m[0] = a[nn];
                for (int ii=0; ii<numCoeffs; ++ii) {
                    output+=b[ii]*m[ii];
                }

                //Reshuffle memories
                for (int ii = numCoeffs-1; ii!=0; --ii) {
                    m[ii] = m[ii-1];
                }                        
                a[nn] = output;
            }
        }
    };

    int specialArgmax(const std::vector<float>&, int);
}

#endif
