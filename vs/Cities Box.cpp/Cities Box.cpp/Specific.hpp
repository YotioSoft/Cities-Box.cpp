//
//  SpecificHeader.hpp ( for Windows )
//  Cities Box
//
//  Created by YotioSoft on 2019/11/30.
//
//  �� : ���̃t�@�C����Windows�����̃w�b�_�t�@�C���ł��B
//

#pragma once

#include <filesystem>

#include "Header.hpp"
#include "OtherFunctions.hpp"

/* OS�ˑ��̒萔�Ȃ� */
#define LINE_FEED_CODE			0	// ���s�R�[�h�ɗp���镶����

namespace specific {
	Array<FileStruct> getAllFilesName(string folderPath, string extension);
}