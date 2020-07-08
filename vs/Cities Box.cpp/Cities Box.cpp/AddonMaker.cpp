//
//  AddonMaker.cpp
//  Addon Maker on Command Line
//
//  Created by YotioSoft on 2020/02/13.
//  Copyright c 2020 YotioSoft. All rights reserved.
//

#include "AddonMaker.hpp"

void AddonMaker::menu(Font& font16) {
	Array<String> categoriesList = {U"�Z��", U"����", U"�I�t�B�X", U"�H��", U"�_��", U"�����{��", U"����", U"���H", U"���H�Ɖw", U"���H", U"��`"};
	PulldownMenu categoriesPulldownMenu(categoriesList, font16, SizeStruct{400, 40}, PositionStruct{30, 130});
	
	Array<String> densityList = {U"�ᖧ�x", U"�����x"};
	PulldownMenu densityPulldownMenu(densityList, font16, SizeStruct{400, 40}, PositionStruct{30, 230});
	
	Array<String> lowDensityResidentialList = {U"�ꌬ��", U"�V�F�A�n�E�X", U"�񐢑яZ��", U"�ʑ�", U"���̑�"};
	PulldownMenu lowDensityResidentialPulldownMenu(lowDensityResidentialList, font16, SizeStruct{400, 40}, PositionStruct{30, 330});
	Array<String> highDensityResidentialList = {U"�A�p�[�g", U"�}���V����", U"�c�n", U"���̑�"};
	PulldownMenu highDensityResidentialPulldownMenu(highDensityResidentialList, font16, SizeStruct{400, 40}, PositionStruct{30, 330});
	
	Array<String> lowDensityCommercialList = {U"�����X", U"���H�X", U"�X�[�p�[�}�[�P�b�g", U"�R���r�j", U"���ԏ�", U"���̑�"};
	PulldownMenu lowDensityCommercialPulldownMenu(lowDensityCommercialList, font16, SizeStruct{400, 40}, PositionStruct{30, 330});
	Array<String> highDensityCommercialList = {U"�S�ݓX", U"�����^���Ǝ{��", U"���̑�"};
	PulldownMenu highDensityCommercialPulldownMenu(highDensityCommercialList, font16, SizeStruct{400, 40}, PositionStruct{30, 330});
	
	Array<String> officeList = {U"�I�t�B�X�r��", U"�݂���c��", U"�m", U"��c��", U"���C��", U"���̑�"};
	PulldownMenu officePulldownMenu(officeList, font16, SizeStruct{400, 40}, PositionStruct{30, 230});
	
	Array<String> lowDensityIndustrialList = {U"���K�͂ȍH��", U"�q��", U"���H��", U"���̑�"};
	PulldownMenu lowDensityIndustrialPulldownMenu(lowDensityIndustrialList, font16, SizeStruct{400, 40}, PositionStruct{30, 330});
	Array<String> highDensityIndustrialList = {U"��K�͂ȍH��", U"���̑�"};
	PulldownMenu highDensityIndustrialPulldownMenu(highDensityIndustrialList, font16, SizeStruct{400, 40}, PositionStruct{30, 330});
	
	Array<String> farmList = {U"�c", U"��", U"�q��", U"���̑�"};
	PulldownMenu farmPulldownMenu(farmList, font16, SizeStruct{400, 40}, PositionStruct{30, 230});
	
	Array<String> publicList = {U"�s����", U"�s���֘A�{��", U"�Ȓ���", U"�x�@��", U"���h��", U"������", U"�w�Z", U"�}����", U"������", U"���̑�"};
	PulldownMenu publicPulldownMenu(publicList, font16, SizeStruct{400, 40}, PositionStruct{30, 230});
	
	Button returnButton(IconFont::LeftWithCircle, 30, 30, PositionStruct{0, 0});
	
	PulldownMenu* secondMenu = nullptr;
	PulldownMenu* thirdMenu = nullptr;
	
	while (System::Update()) {
		returnButton.put(PositionStruct{20, 20});
		
		if (returnButton.push()) {
			return;
		}
		
		font16(U"�A�h�I�����쐬����").draw(60, 25, Palette::White);
		font16(U"�쐬����A�h�I���̃J�e�S����I��ł�������").draw(20, 100, Palette::White);
		
		switch (categoriesPulldownMenu.selectedNumber()) {
			case 0:			// �Z��
				secondMenu = &densityPulldownMenu;
				if (secondMenu->selectedNumber() == 0) {
					thirdMenu = &lowDensityResidentialPulldownMenu;
				}
				else {
					thirdMenu = &highDensityResidentialPulldownMenu;
				}
				break;
			case 1:			// ����
				secondMenu = &densityPulldownMenu;
				if (secondMenu->selectedNumber() == 0) {
					thirdMenu = &lowDensityCommercialPulldownMenu;
				}
				else {
					thirdMenu = &highDensityCommercialPulldownMenu;
				}
				break;
			case 2:			// �I�t�B�X
				secondMenu = &officePulldownMenu;
				thirdMenu = nullptr;
				break;
			case 3:			// �H��
				secondMenu = &densityPulldownMenu;
				if (secondMenu->selectedNumber() == 0) {
					thirdMenu = &lowDensityIndustrialPulldownMenu;
				}
				else {
					thirdMenu = &highDensityIndustrialPulldownMenu;
				}
				break;
			case 4:			// �_��
				secondMenu = &farmPulldownMenu;
				thirdMenu = nullptr;
				break;
			case 5:			// �����{��
				secondMenu = &publicPulldownMenu;
				thirdMenu = nullptr;
				break;
			default:
				secondMenu = nullptr;
				thirdMenu = nullptr;
		}
		
		if (thirdMenu != nullptr) {
			font16(U"�����̎�ނ�I��ł�������").draw(20, 300, Palette::White);
			thirdMenu->draw();
		}
		if (secondMenu != nullptr) {
			font16(U"�A�h�I���̖��x��I�����Ă�������").draw(20, 200, Palette::White);
			secondMenu->draw();
		}
		
		categoriesPulldownMenu.draw();
	}
}
