//
//  TitleMenu.cpp
//  Cities Box
//
//  Created by YotioSoft on 2019/12/01.
//

#include "TitleMenu.hpp"

bool titleMenu(Images& images, Font& font16, String& filePath) {
	Scene::SetBackground(Color(50, 50, 50));
	
	ImageStruct* logo = &images.images["title_menu"]["logo"];
	
	// �{�^���̐錾
	Button loadMapButton(IconFont::Floppy, 50, 50, PositionStruct{3, 3}, U"�ǂݍ���", font16);			// �ǂݍ���
	Button newMapButton(IconFont::Plus, 50, 50, PositionStruct{3, 3}, U"�V�����}�b�v", font16);			// �V�����}�b�v
	Button newAddonButton(IconFont::Compass, 50, 50, PositionStruct{3, 3}, U"�A�h�I�����쐬����", font16);	// �V�����A�h�I��
	
	bool b;
	Color colorWhite = Color(Palette::White);
	
	while (System::Update()) {
		logo->texture.draw(Scene::Width()/2-logo->texture.width()/2, Scene::Height()/2-logo->texture.height()*1.75);
		
		//font16(U"ver.2.0 alpha").draw(Scene::Width()/2-)
		cMes(font16, U"ver.2.0 alpha", PositionStruct{0, Scene::Height()/2-(int)(logo->texture.height()*1.75)+150}, SizeStruct{Scene::Width(), 20}, colorWhite);
		
		loadMapButton.put(PositionStruct{Scene::Width()/2-75-50, Scene::Height()*3/5});
		newMapButton.put(PositionStruct{Scene::Width()/2-25, Scene::Height()*3/5});
		newAddonButton.put(PositionStruct{Scene::Width()/2+75, Scene::Height()*3/5});
		
		if (loadMapButton.push()) {
			// �t�@�C���I���_�C�A���O
			Array<FileFilter> ff = {{U"�Z�[�u�f�[�^", {U"cbd", U"cbj"}}};
			String filePathTemp;
			if (const auto open = Dialog::OpenFile(ff)) {
				filePath = open.value();
				
				b = System::Update();
				loadingScreen(font16);
				return true;
			}
		}
		if (newMapButton.push()) {
			return false;
		}
		if (newAddonButton.push()) {
			newAddonButton.release();
			AddonMaker addonMaker;
			addonMaker.menu(font16);
		}
		
		System::Sleep(50);
	}
	
	return false;
}

bool loadingScreen(Font& font16) {
	font16(U"Loading...").draw(Scene::Width()/2-35, Scene::Height()/2-8, Color(Palette::White));
	return System::Update();
}
