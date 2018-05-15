#include "dictionary.h"
#include <iostream>

Dictionary::Dictionary()
{
    wordLength = 0;

    readDictionary();
}

void Dictionary::readDictionary()
{
    //TODO: handle "no such file case"

    //QFile file("../test.txt");
    QFile file("../dictionary.txt"); //external file versus resourse file
    file.open(QIODevice::ReadWrite);
    QTextStream in(&file);

    while(!in.atEnd())
    {
        QString word = in.readLine();
        if(wordLength != 0)
        {
            if(word.size() == wordLength)
            {
                 words.push_back(new QString(word));
            }
        }
        else
        {
           words.push_back(new QString(word));
        }
    }
}

QString* Dictionary::getWord()
{
    //TODO: this function should not be called if words.size() == 0
    if(words.size() > 0)
    {
        int maxIndex = words.size() -1;
        int random = rand() % maxIndex;
        QString* word = words[random];

        //remove the word after it has been chosen
        words.erase(words.begin()+random);

        return word;
    }
    else
    {
        return new QString("");
    }
}

void Dictionary::setWordLength(int length)
{
    wordLength = length;
}
