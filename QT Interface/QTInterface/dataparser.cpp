#include "dataparser.h"
#include <QCoreApplication>
#include <QTextStream>
#include <iostream>
#include <vector>

std::vector<float> DataParser::parseData(QByteArray *readData)
{
    std::vector<float> parsedData;
    bool isReadingValue = false;
    QString currentValue = "";
    for (int i = 0; i < readData->size(); i++)
    {
        if (readData->at(i) == '{')
        {
            isReadingValue = true;
            continue;
        }

        if(isReadingValue)
        {
            if(readData->at(i) == ',')
            {
                parsedData.push_back(currentValue.toFloat());
                currentValue.clear();
            }
            else if(readData->at(i) == '}')
            {
                parsedData.push_back(currentValue.toFloat());
                readData->clear();
                return parsedData;
            }
            else
            {
                currentValue.append(readData->at(i));
            }
        }
    }

    return std::vector<float>();
}

