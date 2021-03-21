//
//  OtherFunctions.hpp
//  Cities Box
//
//  Created by YotioSoft on 2019/11/27.
//

#ifndef OtherFunctions_hpp
#define OtherFunctions_hpp

#include "Specific.hpp"

Array<string> splitUTF8(string str, string separator);
Array<String> split(String str, String separator);

void cMes(Font& font, String str, PositionStruct topLeft, PositionStruct bottomRight, Color& color);
void cMes(Font& font, String str, PositionStruct topLeft, Size size, Color& color);

PositionStruct getStringTopLeft(Font& font, String str, PositionStruct topLeft, PositionStruct bottomRight);
PositionStruct getStringTopLeft(Font& font, String str, PositionStruct topLeft, Size size);

void saveTextFile(string filePath, string str);
void saveTextFile(string filePath, Array<string> strV);
void saveTextFile(string filePath, Array<FileStruct> fs);
void saveTextFile(string filePath, FileStruct fs);

string replaceString(string beforeStr, string searchStr, string afterStr);

RCOIFP::Type getRCOIFP(int number);
School::Type getSchool(int number);

string stringXOR(const std::string &data, const std::string &key);

TypeID::Type typeNameToTypeID(String type_name);
DirectionID::Type directionNameToDirectionID(String direction_name);
Array<DirectionID::Type> directionNameToDirectionID(Array<String> direction_name);

#endif /* OtherFunctions_hpp */
