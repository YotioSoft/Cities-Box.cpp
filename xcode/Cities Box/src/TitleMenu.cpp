//
//  TitleMenu.cpp
//  Cities Box
//
//  Created by YotioSoft on 2019/12/01.
//

#include "TitleMenu.hpp"

bool titleMenu(Images& images, Font& font16) {
	Scene::SetBackground(Color(50, 50, 50));
	
	ImageStruct* logo = &images.images["title_menu"]["logo"];
	
	// ボタンの宣言
	Button load_button(IconFont::Floppy, 50, U"読み込み", font16);			// 読み込み
	Button new_map_button(IconFont::Plus, 50, U"新しいマップ", font16);		// 新しいマップ
	
	bool b;
	
	while (System::Update()) {
		logo->texture.draw(Scene::Width()/2-logo->texture.width()/2, Scene::Height()/2-logo->texture.height()*1.75);
		
		//font16(U"ver.2.0 alpha").draw(Scene::Width()/2-)
		
		load_button.put(PositionStruct{Scene::Width()/2-75, Scene::Height()*3/5});
		new_map_button.put(PositionStruct{Scene::Width()/2+25, Scene::Height()*3/5});
		
		if (load_button.push()) {
			b = System::Update();
			loadingScreen(font16);
			return true;
		}
		if (new_map_button.push()) {
			b = System::Update();
			loadingScreen(font16);
			return true;
		}
		
		specific::sleep(50);
	}
	
	return false;
}

bool loadingScreen(Font& font16) {
	font16(U"Loading...").draw(Scene::Width()/2-35, Scene::Height()/2-8, Color(Palette::White));
	return System::Update();
}
