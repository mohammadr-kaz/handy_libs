#ifndef MIIO2V_LOGGING_H
#define MIIO2V_LOGGING_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <sys/stat.h> // stat
#include <errno.h>    // errno, ENOENT, EEXIST
#if defined(_WIN32)
#include <direct.h>   // _mkdir
#endif


namespace hl::io
{
    template <typename Tq> 
    inline void printScalar(Tq&);

    void print(std::string);

    bool dirExists(const std::string&);

    bool makePath(const std::string&);

    std::string makeLogDirName(std::vector<std::string>);

    int test(int, int);

    void close();

    template <typename num>
    void writeScalar2csv(std::string, std::string, num);

    void write2csv(std::string, std::string, int);
    void write2csv(std::string, std::string, float);

    template <typename num>
    void appendScalar2csv(std::string, std::string, num);

    void append2csv(std::string, std::string, int);
    void append2csv(std::string, std::string, float);
    void append2csv(std::string, std::string, double);

    void makeDynamicDir(std::string&);

    template <typename t1>
    void write2dArr2csv(std::string, std::string, t1&);

    void write2d2csv(std::string, std::string, std::vector<std::vector<int>>&);
    void write2d2csv(std::string, std::string, std::vector<std::vector<float>>&);
    void write2d2csv(std::string, std::string, std::vector<std::vector<double>>&);

    std::vector<std::vector<double>> readDoubleArrFromCsv(std::string);
    std::vector<std::vector<float>> readFloatArrFromCsv(std::string);
    std::vector<std::vector<int>> readIntArrFromCsv(std::string);

    bool fileExists (const std::string&);

    void appendVecStr2csv(std::string, std::string, std::vector<std::string>);
    void appendVec2csv(std::string, std::string, std::vector<float>);
}

#endif
