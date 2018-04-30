#ifndef DATAPARSER_H
#define DATAPARSER_H
#include <QByteArray>
#include <QTextStream>
#include <vector>

class DataParser
{
public:
    std::vector<float> parseData(QByteArray *readData);
};

#endif // DATAPARSER_H
