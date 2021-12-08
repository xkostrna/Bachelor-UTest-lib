#include "Serialize.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include "Paths.h"
#include "IOErrors.h"

static constexpr char serializeFileName[] = "output.txt";

std::string getDeserializeFilePath() {
    const std::string & outputFileDirectory{Paths::getSharedFolder() + Paths::getPlatformSlash() + serializeFileName};
    return outputFileDirectory;
}

template <typename T>
void Serialize::serialize(const T &valueToSerialize) {
    serialize(valueToSerialize);
}

template<>
void Serialize::serialize(const int & valueToSerialize) {
    std::ofstream outputStream(serializeFileName, std::ios::binary);
    if (outputStream.good()) {
        outputStream.write((char*)&valueToSerialize, sizeof(int));
    }
    else {
        IOErrors::printErrorMessage(__func__, __LINE__);
    }
    outputStream.close();
}

template<>
void Serialize::serialize(const double & valueToSerialize) {
    std::ofstream outputStream(serializeFileName, std::ios::binary);
    if (outputStream.good()) {
        outputStream.write((char*)&valueToSerialize, sizeof(double));
    }
    else {
        IOErrors::printErrorMessage(__func__, __LINE__);
    }
    outputStream.close();
}

template<>
void Serialize::serialize(const std::string & valueToSerialize) {
    size_t size{valueToSerialize.length()};
    std::ofstream outputStream(serializeFileName, std::ios::binary);
    if (outputStream.good()) {
        outputStream.write((char*)&size, sizeof(size));
        outputStream.write((char*)valueToSerialize.c_str(), std::streamsize(size));
    }
    else {
        IOErrors::printErrorMessage(__func__, __LINE__);
    }
    outputStream.close();
}

template<>
void Serialize::serialize(const std::list<int> & valueToSerialize) {
    size_t listSize{valueToSerialize.size()};
    std::ofstream outputStream(serializeFileName, std::ios::binary);
    if (outputStream.good()) {
        outputStream.write((char*)&listSize, sizeof(listSize));
        for (int i : valueToSerialize) {
            outputStream.write((char*)&i, sizeof(int));
        }
    }
    else {
        IOErrors::printErrorMessage(__func__, __LINE__);
    }
    outputStream.close();
}

template <typename TYPE>
TYPE Serialize::deserialize() {
    return TYPE();
}

template<>
int Serialize::deserialize<int>() {
    int deserializedInt{0};
    std::ifstream inputStream{getDeserializeFilePath(), std::ios::binary};
    if (inputStream.good()) {
        inputStream.read((char*)&deserializedInt, sizeof(int));
    }
    else {
        IOErrors::printErrorMessage(__func__, __LINE__);
    }
    inputStream.close();
    return deserializedInt;
}

template<>
double Serialize::deserialize<double>() {
    double deserializedDouble{0.0};
    std::ifstream inputStream{getDeserializeFilePath(), std::ios::binary};
    if (inputStream.good()) {
        inputStream.read((char*)&deserializedDouble, sizeof(double));
    }
    else {
        IOErrors::printErrorMessage(__func__, __LINE__);
    }
    inputStream.close();
    return deserializedDouble;
}

template<>
std::string Serialize::deserialize<std::string>() {
    std::streamsize sizeOfString{};
    std::vector<char> charVector{};
    std::ifstream inputStream{getDeserializeFilePath(), std::ios::binary};
    if (inputStream.good()) {
        inputStream.read((char*)&sizeOfString, sizeof(size_t));
        charVector.resize(sizeOfString+1);
        inputStream.read((char*)&charVector[0], sizeOfString);
    }
    else {
        IOErrors::printErrorMessage(__func__, __LINE__);
    }
    inputStream.close();
    charVector[charVector.size()-1] = '\0';
    std::string deserializedString{&charVector[0]};
    return deserializedString;
}

template<>
std::list<int> Serialize::deserialize<std::list<int>>() {
    std::list<int> deserializedList{};
    std::streamsize sizeOfList{};
    int value{0};
    std::ifstream inputStream{getDeserializeFilePath(), std::ios::binary};
    if (inputStream.good()) {
        inputStream.read((char*)&sizeOfList, sizeof(size_t));
        for (size_t i = 0; i < sizeOfList; i++) {
            inputStream.read((char*)&value, sizeof(int));
            deserializedList.push_back(value);
        }
    }
    else {
        IOErrors::printErrorMessage(__func__, __LINE__);
    }
    inputStream.close();
    return deserializedList;
}
