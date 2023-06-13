#include "Logging.h"

using namespace hl;

template <typename Tq> 
inline void io::printScalar(Tq& inp)
{
    std::cout<<inp<<"\n";
}

void io::print(std::string text)
{
    printScalar(text);
}

bool io::dirExists(const std::string& path)
{
#if defined(_WIN32)
    struct _stat info;
    if (_stat(path.c_str(), &info) != 0)
    {
        return false;
    }
    return (info.st_mode & _S_IFDIR) != 0;
#else 
    struct stat info;
    if (stat(path.c_str(), &info) != 0)
    {
        return false;
    }
    return (info.st_mode & S_IFDIR) != 0;
#endif
}

bool io::makePath(const std::string& path)
{
#if defined(_WIN32)
    int ret = _mkdir(path.c_str());
#else
    mode_t mode = 0755;
    int ret = mkdir(path.c_str(), mode);
#endif
    if (ret == 0)
        return true;

    switch (errno)
    {
    case ENOENT:
        // parent didn't exist, try to create it
        {
            int pos = path.find_last_of('/');
            if (pos == std::string::npos)
#if defined(_WIN32)
                pos = path.find_last_of('\\');
            if (pos == std::string::npos)
#endif
                return false;
            if (!makePath( path.substr(0, pos) ))
                return false;
        }
        // now, try to create again
#if defined(_WIN32)
        return 0 == _mkdir(path.c_str());
#else 
        return 0 == mkdir(path.c_str(), mode);
#endif

    case EEXIST:
        // done!
        return dirExists(path);

    default:
        return false;
    }
}

std::string io::makeLogDirName(std::vector<std::string> params)
{
    std::string str = "";
    for (auto &el : params)
        str += el + "_";
    return str.substr(0, str.size()-1);
}

int io::test(int a, int b)
{return 0;}

void io::close() {}

void io::append2csv(std::string dir, std::string name, float n)
{
    appendScalar2csv(dir, name, n);
}

void io::append2csv(std::string dir, std::string name, int n)
{
    appendScalar2csv(dir, name, n);
}

void io::append2csv(std::string dir, std::string name, double n)
{
    appendScalar2csv(dir, name, n);
}

template <typename num>
void io::appendScalar2csv(std::string dir, std::string name, num n)
{
    std::ofstream file;
    file.open(dir + "/" + name + ".csv", std::ios::app);
    file << std::to_string(n) << '\n';
    file.close();
}

void io::write2csv(std::string dir, std::string name, float n)
{
    writeScalar2csv(dir, name, n);
}

void io::write2csv(std::string dir, std::string name, int n)
{
    writeScalar2csv(dir, name, n);
}

template <typename num>
void io::writeScalar2csv(std::string dir, std::string name, num n)
{
    std::ofstream file;
    file.open(dir + "/" + name + ".csv");
    file << std::to_string(n) << '\n';
    file.close();
}

void io::makeDynamicDir(std::string &dir)
{
    dir += "_1";
    int k = 1;
    bool found = false;

    while (!found)
    {
        if (!dirExists(dir))
        {
            makePath(dir);
            found = true;                                                    
        }
        else
        {
            k++;
            if (k<=10)
            {
                dir.erase(dir.end()-1);
                dir += std::to_string(k);
            }
            else if (k<=100)
            {
                dir.erase(dir.end()-2, dir.end());
                dir += std::to_string(k);
            }
            else
            {
                dir.erase(dir.end()-3, dir.end());
                dir += std::to_string(k);
            }
        }
    }
}

void io::write2d2csv(std::string dir, std::string name, std::vector<std::vector<float>> &array)
{
    write2dArr2csv(dir, name, array);
}

void io::write2d2csv(std::string dir, std::string name, std::vector<std::vector<int>> &array)
{
    write2dArr2csv(dir, name, array);
}

void io::write2d2csv(std::string dir, std::string name, std::vector<std::vector<double>> &array)
{
    write2dArr2csv(dir, name, array);
}

template <typename t1>
void io::write2dArr2csv(std::string dir, std::string name, t1& array)
{
    std::ofstream out(dir + "/" + name + ".csv");

    for (auto& row : array) 
    {
        for (auto col : row)
            out << col <<',';
        out << '\n';
    }
}

std::vector<std::vector<int>> io::readIntArrFromCsv(std::string address)
{
    /*This function gets an 'address' to a '.csv' file from a base which is the 
    <repo-root>/data/address, reads the file, and returns it as a 2D vector*/
    std::vector<std::vector<int>> data;
    std::ifstream input(address);
    int i = 0;
    for( std::string line; getline( input, line ); )
    {
        data.push_back(std::vector<int>());
        std::istringstream iss(line);
        std::string num;
        while(std::getline(iss, num, ','))
        {
            data[i].push_back(stof(num));
        }
        i++;
    }
    return data;
}

std::vector<std::vector<float>> io::readFloatArrFromCsv(std::string address)
{
    /*This function gets an 'address' to a '.csv' file from a base which is the 
    <repo-root>/data/address, reads the file, and returns it as a 2D vector*/
    std::vector<std::vector<float>> data;
    std::ifstream input(address);
    int i = 0;
    for( std::string line; getline( input, line ); )
    {
        data.push_back(std::vector<float>());
        std::istringstream iss(line);
        std::string num;
        while(std::getline(iss, num, ','))
        {
            data[i].push_back(stof(num));
        }
        i++;
    }
    return data;
}

std::vector<std::vector<double>> io::readDoubleArrFromCsv(std::string address)
{
    /*This function gets an 'address' to a '.csv' file from a base which is the 
    <repo-root>/data/address, reads the file, and returns it as a 2D vector*/
    std::vector<std::vector<double>> data;
    std::ifstream input(address);
    int i = 0;
    for( std::string line; getline( input, line ); )
    {
        data.push_back(std::vector<double>());
        std::istringstream iss(line);
        std::string num;
        while(std::getline(iss, num, ','))
        {
            data[i].push_back(stof(num));
        }
        i++;
    }
    return data;
}

bool io::fileExists (const std::string &name)
{
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0); 
}

void io::appendVec2csv(std::string dir, std::string name, std::vector<float> inp)
{
    std::ofstream file;
    file.open(dir + "/" + name + ".csv", std::ios::app);
    for (auto & el: inp)
        file << el << ',';
    file << '\n';
    file.close();
}