//
//  Images.hpp
//  Cities Box
//
//  Created by YotioSoft on 2019/11/27.
//
#pragma once

#ifndef Images_hpp
#define Images_hpp

#include "Specific.hpp"
#include "OtherFunctions.hpp"

#endif /* Images_hpp */

typedef struct Images {
	// �w�肵���p�X����摜�t�@�C�������ׂēǂݍ���
	void load(string filePath, string tag);
	void load(string filePath, string tag, Color transparent);
	
	// �摜�̊i�[����\���̘̂A�z�z��
	map<string, map<string, ImageStruct>> images;
} Images;
