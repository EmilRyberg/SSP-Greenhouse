#ifndef DATAPARSER_H
#define DATAPARSER_H
#include <QByteArray>
#include <QTextStream>
#include <vector>

class DataParser
{
public:
    std::vector<double> parseData(QByteArray *readData);
};

#endif // DATAPARSER_H
