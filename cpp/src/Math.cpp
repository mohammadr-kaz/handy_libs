#include "Math.h"

using namespace hl;

size_t math::random(size_t min, size_t max)
{
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max - 1);
    return dist(rng);
}

float math::random(float min, float max, int range)
{
    int rndI = random(0, range);
    return min + (((max - min) * rndI) / range);
}

float math::calcEuclideanDist(int x1, int y1, int x2, int y2)
{
    return sqrt(float(pow((x1 - x2), 2) + pow((y1 - y2), 2)));
}

void math::amplifyMat(float gain, std::vector<std::vector<float>> &mat)
{
    for (int i = 0; i < mat.size(); i++)
        for (int j = 0; j < mat[0].size(); j++)
            mat[i][j] = gain * mat[i][j];
}

int math::test(int a, int b)
{
    return a + b;
}

double math::average1d(const std::vector<double> &inp)
{
    return averageVec(inp, inp[0]);
}

float math::average1d(const std::vector<float> &inp)
{
    return averageVec(inp, inp[0]);
}

float math::average1d(const std::vector<int> &inp)
{
    return averageVec(inp, inp[0]);
}

template <typename vecType, typename elType>
float math::averageVec(vecType &vec, elType e)
{
    elType sum;
    int k = 0;
    for (auto &el : vec)
    {
        sum += el;
        k++;
    }
    return sum / float(k);
}

float math::nonZeroMean(const std::vector<float> &vec)
{
    float sum;
    int k = 0;
    for (auto &el : vec)
    {
        if (el != 0)
        {
            sum += el;
            k++;
        }
    }
    return sum / float(k);
}

float math::average2d(std::vector<std::vector<float>> &inp)
{
    return averageArr(inp, inp[0][0]);
}

float math::average2d(std::vector<std::vector<double>> &inp)
{
    return averageArr(inp, inp[0][0]);
}

template <typename arrType, typename elType>
float math::averageArr(arrType &arr, elType e)
{
    elType sum;
    int k = 0;
    for (auto &vec : arr)
    {
        for (auto &el : vec)
        {
            sum += el;
            k++;
        }
    }
    return sum / float(k);
}

double math::movingAverage1d(std::vector<double> &vec, int buffer_size)
{
    return movingAverage(vec, vec[0], buffer_size);
}

float math::movingAverage1d(std::vector<float> &vec, int buffer_size)
{
    return movingAverage(vec, vec[0], buffer_size);
}

template <typename tp>
tp math::movingAverage(std::vector<tp> &vec, tp num, int buffer_size)
{
    int vec_size = vec.size();
    if (!vec_size)
        return 0;

    if (vec_size < buffer_size)
        return averageVec(vec, vec[0]);
    else
        return average1d(std::vector<tp>(vec.end() - buffer_size, vec.end()));
}

float math::movingOccuranceAverage(std::vector<bool> &vec, int buffer_size, bool val)
{
    return movingOccurAverage(vec, buffer_size, val);
}

template <typename tp>
float math::movingOccurAverage(std::vector<tp> &vec, int buffer_size, tp val)
{
    int vec_size = vec.size();
    if (!vec_size)
        return 0;

    if (vec_size < buffer_size)
        return float(std::count(vec.begin(), vec.end(), true)) / float(vec_size);
    else
        return float(std::count(vec.end() - buffer_size, vec.end(), true)) / buffer_size;
}

template <typename tp>
void math::bufferVec(std::vector<tp> &vec, tp new_element, int buffer_size)
{
    if (vec.size() > buffer_size)
        vec.erase(vec.begin());
    vec.push_back(new_element);
}

void math::bufferVector(std::vector<double> &vec, double new_element, int buffer_size)
{
    bufferVec(vec, new_element, buffer_size);
}

void math::bufferVector(std::vector<bool> &vec, bool new_element, int buffer_size)
{
    bufferVec(vec, new_element, buffer_size);
}

void math::cartToPolar(float x, float y, float x_center, float y_center, float &rho, float &angle)
{
    float dx, dy;

    dx = x - x_center;
    dy = y - y_center;

    rho = std::sqrt(dx * dx + dy * dy);
    angle = atan2(y, x) * 180 / M_PI;
}

float math::convertAngle(float &ang_deg)
{
    float angle_deg = ang_deg + 90;

    if (angle_deg >= 0)
        return angle_deg;
    else
        return angle_deg + 360;
}

float math::calcAngleWrtNorth(float xa, float ya, float xt, float yt)
{
    // float PI = 3.1415926;
    float ang, angle;
    if (xa < xt && ya <= yt)
    {
        ang = atan(abs(yt - ya) / abs(xt - xa));
        angle = ang * 180 / PI;
        angle += 90;
    }

    else if (xa <= xt && ya > yt)
    {
        ang = atan(abs(xt - xa) / abs(yt - ya));
        angle = ang * 180 / PI;
    }

    else if (xa >= xt && ya < yt)
    {
        ang = atan(abs(xt - xa) / abs(yt - ya));
        angle = ang * 180 / PI;
        angle += 180;
    }

    else if (xa > xt && ya >= yt)
    {
        ang = atan(abs(yt - ya) / abs(xt - xa));
        angle = ang * 180 / PI;
        angle += 270;
    }

    return angle;
}

void math::calcPolarPoint(float range, float angle, float &dx, float &dy)
{
    dx = range * cos(angle - PI / 2.0);
    dy = range * sin(angle - PI / 2.0);
}

void math::normalizeVector(const std::vector<float> &vec, std::vector<float> &normVec)
{
    float maxVec = *std::max_element(vec.begin(), vec.end());
    float minVec = *std::min_element(vec.begin(), vec.end());

    for (int i = 0; i < vec.size(); i++)
        normVec.push_back(vec[i] / (maxVec - std::min(minVec, float(0))));
}

void math::normalizeVector(const std::vector<float> &vec, std::vector<float> &normVec, float min, float max)
{
    float maxVec = max;
    float minVec = min;

    for (int i = 0; i < vec.size(); i++)
        normVec.push_back((vec[i] - minVec) / (maxVec - minVec));
    // normVec.push_back((vec[i] - minVec)/(maxVec - std::min(minVec, float(0))));
}

bool math::onSegment(Point &p, Point &q, Point &r)
{
    if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
        q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
        return true;
    return false;
}

int math::orientation(Point &p, Point &q, Point &r)
{
    float val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (val == 0)
        return 0; // Collinear

    return (val > 0) ? 1 : 2; // Clockwise or Counterclockwise
}

bool math::checkIntersection(std::vector<float> &line1, std::vector<float> &line2)
{
    Point p1, q1, p2, q2;

    p1.x = line1[0];
    p1.y = line1[1];
    
    q1.x = line1[2];
    q1.y = line1[3];
    
    p2.x = line2[0];
    p2.y = line2[1];
    
    q2.x = line2[2];
    q2.y = line2[3];
    

    int o1 = math::orientation(p1, q1, p2);
    int o2 = math::orientation(p1, q1, q2);
    int o3 = math::orientation(p2, q2, p1);
    int o4 = math::orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4)
        return true;

    if (o1 == 0 && math::onSegment(p1, p2, q1))
        return true;

    if (o2 == 0 && math::onSegment(p1, q2, q1))
        return true;

    if (o3 == 0 && math::onSegment(p2, p1, q2))
        return true;

    if (o4 == 0 && math::onSegment(p2, q1, q2))
        return true;

    return false;
}

int math::argmax(const std::vector<float> &v)
{
    int index = 0;
    float max_value = v[0];
    for (int i = 1; i < v.size(); i++) 
    {
        if (v[i] > max_value) 
        {
            max_value = v[i];
            index = i;
        }
    }
    return index;
}