//
//  Menu.cpp
//  Cities-Box
//
//  Created by YotioSoft on 2019/12/07.
//

#include "Menu.hpp"

void Menu::set(PositionStruct new_position, SizeStruct new_size, CityMap* new_map, Font* new_font8, Font* new_font12, Font* new_font16) {
	position = new_position;
	size = new_size;
	
	font8 = new_font8;
	font12 = new_font12;
	font16 = new_font16;
	
	map = new_map;
	
	selected_addon = nullptr;
	
	button[U"cursor"].set(IconFont::Cursor, 30, 26, PositionStruct{8, 2});
	
	button[U"road"].set(IconFont::Road, 30, 26, PositionStruct{ 0, 6 });
	button[U"train"].set(IconFont::Railroad, 30, 28, PositionStruct{ 2, 2 });
	button[U"residential"].set(IconFont::Residential, 30, 30, PositionStruct{-3, 2});
	button[U"commercial"].set(IconFont::Commercial, 30, 26, PositionStruct{-3, 2});
	button[U"office"].set(IconFont::Office, 30, 30, PositionStruct{0, 1});
	button[U"industrial"].set(IconFont::Industrial, 30, 30, PositionStruct{0, 2});
	button[U"farm"].set(IconFont::Farm, 30, 26, PositionStruct{-3, 2});
	button[U"public"].set(IconFont::Public, 30, 30, PositionStruct{0, 2});
	
	button[U"park"].set(IconFont::Park, 30, 30, PositionStruct{2, 2});
	button[U"ship"].set(IconFont::WaterWay, 30, 26, PositionStruct{0, 2});
	button[U"air_port"].set(IconFont::AirPort, 30, 24, PositionStruct{-1, 4});
	button[U"tile"].set(IconFont::Field, 30, 30, PositionStruct{2, 2});
	
	button[U"information"].set(IconFont::Information, 30, 26, PositionStruct{2, 2});
	button[U"rate"].set(IconFont::Rate, 30, 30, PositionStruct{0, 2});
	button[U"delete"].set(IconFont::Delete, 30, 30, PositionStruct{0, 2});
	button[U"budget"].set(IconFont::Budget, 30, 26, PositionStruct{-1, 4});
	button[U"setting"].set(IconFont::Setting, 30, 28, PositionStruct{1, 1});
	button[U"save"].set(IconFont::Save, 30, 30, PositionStruct{2, 2});
	
	menu_mode = MenuMode::None;
	
	selected_addon_name = U"";
	
	population = Texture(Icon(IconFont::Population, 20));
	
	render = RenderTexture(size.width, size.height, Color(45, 52, 54));
	
	show_rate_menu = false;
	
	// 効果テクスチャを用意
	effect_icons[U"crime_rate"] = Texture(Icon(IconFont::Crime, 16));
	effect_icons[U"durability"] = Texture(Icon(IconFont::Durability, 16));
	effect_icons[U"education_rate"] = Texture(Icon(IconFont::Education, 16));
	effect_icons[U"firing_rate"] = Texture(Icon(IconFont::Firing, 16));
	effect_icons[U"garbage_disposal"] = Texture(Icon(IconFont::Garbage, 16));
	effect_icons[U"land_price"] = Texture(Icon(IconFont::LandPrice, 16));
	effect_icons[U"mobile_communication"] = Texture(Icon(IconFont::MobileCommunication, 16));
	effect_icons[U"noise"] = Texture(Icon(IconFont::Noise, 16));
	effect_icons[U"post"] = Texture(Icon(IconFont::Post, 16));
	effect_icons[U"television"] = Texture(Icon(IconFont::Television, 16));
	effect_icons[U"tourist_attraction"] = Texture(Icon(IconFont::Tourist, 16));
	effect_icons[U"radio"] = Texture(Icon(IconFont::Radio, 16));
	
	// レート表示用ボタン
	button[U"rate_land_price"].set(IconFont::LandPrice, 16, 16, PositionStruct{0, 0});
}

void Menu::releaseBeforeButton(MenuMode::Type before_selected_button) {
	switch (before_selected_button) {
		case MenuMode::Cursor:
			button[U"cursor"].release();
			return;
		case MenuMode::Road:
			button[U"road"].release();
			return;
		case MenuMode::Train:
			button[U"train"].release();
			return;
		case MenuMode::Residential:
			button[U"residential"].release();
			return;
		case MenuMode::Commercial:
			button[U"commercial"].release();
			return;
		case MenuMode::Office:
			button[U"office"].release();
			return;
		case MenuMode::Industrial:
			button[U"industrial"].release();
			return;
		case MenuMode::Farm:
			button[U"farm"].release();
			return;
		case MenuMode::Public:
			button[U"public"].release();
			return;
		case MenuMode::Park:
			button[U"park"].release();
			return;
		case MenuMode::Ship:
			button[U"ship"].release();
			return;
		case MenuMode::AirPort:
			button[U"air_port"].release();
			return;
		case MenuMode::Tile:
			button[U"tile"].release();
			return;
		case MenuMode::Delete:
			button[U"delete"].release();
			return;
		case MenuMode::Save:
			button[U"save"].release();
			return;
		case MenuMode::None:
			return;
	}
}

void Menu::getSelectedAddon() {
	
}

void Menu::update() {
	render.clear(Color(45, 52, 54));
	ScopedRenderTarget2D rt(render);
	
	button[U"cursor"].putRelative(PositionStruct{10, 0}, position);
	 
	button[U"road"].putRelative(PositionStruct{55, 0}, position);
	button[U"train"].putRelative(PositionStruct{55+35, 0}, position);
	button[U"residential"].putRelative(PositionStruct{55+70, 0}, position);
	button[U"commercial"].putRelative(PositionStruct{55+105, 0}, position);
	button[U"office"].putRelative(PositionStruct{55+140, 0}, position);
	button[U"industrial"].putRelative(PositionStruct{55+175, 0}, position);
	button[U"farm"].putRelative(PositionStruct{55+210, 0}, position);
	button[U"public"].putRelative(PositionStruct{55+245, 0}, position);
	
	button[U"park"].putRelative(PositionStruct{345, 0}, position);
	button[U"ship"].putRelative(PositionStruct{345+35, 0}, position);
	button[U"air_port"].putRelative(PositionStruct{345+70, 0}, position);
	button[U"tile"].putRelative(PositionStruct{345+105, 0}, position);
	
	button[U"information"].putRelative(PositionStruct{495, 0}, position);
	button[U"rate"].putRelative(PositionStruct{495+35, 0}, position);
	button[U"delete"].putRelative(PositionStruct{495+70, 0}, position);
	button[U"budget"].putRelative(PositionStruct{495+105, 0}, position);
	button[U"setting"].putRelative(PositionStruct{495+140, 0}, position);
	button[U"save"].putRelative(PositionStruct{495+175, 0}, position);
	
	// RCOIFメータを表示
	(*font8)(U"R").draw(size.width-80+3, size.height-15+2, Color(Palette::White));
	(*font8)(U"C").draw(size.width-80+3+8, size.height-15+2, Color(Palette::White));
	(*font8)(U"O").draw(size.width-80+3+16, size.height-15+2, Color(Palette::White));
	(*font8)(U"I").draw(size.width-80+3+24, size.height-15+2, Color(Palette::White));
	(*font8)(U"F").draw(size.width-80+3+32, size.height-15+2, Color(Palette::White));
	
	Rect(size.width-80, size.height-15, 8, -max(map->getDemand().residential*0.4, 1.0)).draw(Color(39, 174, 96));
	Rect(size.width-80+8, size.height-15, 8, -max(map->getDemand().commercial*0.4, 1.0)).draw(Color(9, 132, 227));
	Rect(size.width-80+16, size.height-15, 8, -max(map->getDemand().office*0.4, 1.0)).draw(Color(0, 206, 201));
	Rect(size.width-80+24, size.height-15, 8, -max(map->getDemand().industrial*0.4, 1.0)).draw(Color(253, 203, 110));
	Rect(size.width-80+32, size.height-15, 8, -max(map->getDemand().farm*0.4, 1.0)).draw(Color(211, 84, 0));
	
	population.draw(10, size.height-25);
	(*font16)(Format(map->getPopulation())).draw(10+30, size.height-25-3, Color(Palette::White));
	 
	(*font16)(U"§ "+Format(map->getMoney())).draw(10+100, size.height-25-3, Color(Palette::White));
}

Addon* Menu::draw(bool& need_update) {
	render.draw(position.x, position.y);
	
	// ボタンが押されたときの動作
	if (button[U"cursor"].pushRelative(position)) {
		if (menu_mode != MenuMode::Cursor) {
			releaseBeforeButton(menu_mode);
		}
		
		menu_mode = MenuMode::Cursor;
		selected_addon = nullptr;
		show_addons.clear();
		button[U"cursor"].release();
		need_update = true;
	}
	if (button[U"road"].pushRelative(position)) {
		if (menu_mode != MenuMode::Road) {
			releaseBeforeButton(menu_mode);
			menu_mode = MenuMode::Road;
			selected_addon = nullptr;
			mode_str = U"road";
			show_addons = map->getFitAddons(Array<String>{mode_str});
			
			category_buttons.clear();
			category_buttons << pair<String, Button>(U"promenade", Button(IconFont::WALK, 16, 16, PositionStruct{2, 0}));
			category_buttons << pair<String, Button>(U"car", Button(IconFont::CAR, 16, 16, PositionStruct{0, 0}));
		}
		else {
			menu_mode = MenuMode::Cursor;
		}
		need_update = true;
	}
	if (button[U"train"].pushRelative(position)) {
		if (menu_mode != MenuMode::Train) {
			releaseBeforeButton(menu_mode);
			menu_mode = MenuMode::Train;
			selected_addon = nullptr;
			mode_str = U"train";
			show_addons = map->getFitAddons(Array<String>{mode_str});
			
			category_buttons.clear();
		}
		else {
			menu_mode = MenuMode::Cursor;
		}
		need_update = true;
	}
	if (button[U"residential"].pushRelative(position)) {
		if (menu_mode != MenuMode::Residential){
			releaseBeforeButton(menu_mode);
			menu_mode = MenuMode::Residential;
			selected_addon = nullptr;
			mode_str = U"residential";
			show_addons = map->getFitAddons(Array<String>{mode_str});
			
			category_buttons.clear();
			category_buttons << pair<String, Button>(U"low_density", Button(IconFont::Residential, 16, 16, PositionStruct{0, 0}));
			category_buttons << pair<String, Button>(U"high_density", Button(IconFont::Office, 16, 16, PositionStruct{2, 0}));
		}
		else {
			menu_mode = MenuMode::Cursor;
		}
		need_update = true;
	}
	if (button[U"commercial"].pushRelative(position)) {
		if (menu_mode != MenuMode::Commercial) {
			releaseBeforeButton(menu_mode);
			menu_mode = MenuMode::Commercial;
			selected_addon = nullptr;
			mode_str = U"commercial";
			show_addons = map->getFitAddons(Array<String>{mode_str});
			
			category_buttons.clear();
			category_buttons << pair<String, Button>(U"low_density", Button(IconFont::Commercial, 16, 14, PositionStruct{0, 0}));
			category_buttons << pair<String, Button>(U"high_density", Button(IconFont::Office, 16, 16, PositionStruct{2, 0}));
		}
		else {
			menu_mode = MenuMode::Cursor;
		}
		need_update = true;
	}
	if (button[U"office"].pushRelative(position)) {
		if (menu_mode != MenuMode::Office) {
			releaseBeforeButton(menu_mode);
			menu_mode = MenuMode::Office;
			selected_addon = nullptr;
			mode_str = U"office";
			show_addons = map->getFitAddons(Array<String>{mode_str});
			
			category_buttons.clear();
		}
		else {
			menu_mode = MenuMode::Cursor;
		}
		need_update = true;
	}
	if (button[U"industrial"].pushRelative(position)) {
		if (menu_mode != MenuMode::Industrial) {
			releaseBeforeButton(menu_mode);
			menu_mode = MenuMode::Industrial;
			selected_addon = nullptr;
			mode_str = U"industrial";
			show_addons = map->getFitAddons(Array<String>{mode_str});
			
			category_buttons.clear();
		}
		else {
			menu_mode = MenuMode::Cursor;
		}
		need_update = true;
	}
	if (button[U"farm"].pushRelative(position)) {
		if (menu_mode != MenuMode::Farm) {
			releaseBeforeButton(menu_mode);
			menu_mode = MenuMode::Farm;
			selected_addon = nullptr;
			mode_str = U"farm";
			show_addons = map->getFitAddons(Array<String>{mode_str});
			
			category_buttons.clear();
		}
		else {
			menu_mode = MenuMode::Cursor;
		}
		need_update = true;
	}
	if (button[U"public"].pushRelative(position)) {
		if (menu_mode != MenuMode::Public) {
			releaseBeforeButton(menu_mode);
			menu_mode = MenuMode::Public;
			selected_addon = nullptr;
			mode_str = U"public";
			show_addons = map->getFitAddons(Array<String>{mode_str});
			
			category_buttons.clear();
		}
		else {
			menu_mode = MenuMode::Cursor;
		}
		need_update = true;
	}
	if (button[U"park"].pushRelative(position)) {
		if (menu_mode != MenuMode::Park) {
			releaseBeforeButton(menu_mode);
			menu_mode = MenuMode::Park;
			selected_addon = nullptr;
			mode_str = U"park";
			show_addons = map->getFitAddons(Array<String>{mode_str});
			
			category_buttons.clear();
		}
		else {
			menu_mode = MenuMode::Cursor;
		}
		need_update = true;
	}
	if (button[U"ship"].pushRelative(position)) {
		if (menu_mode != MenuMode::Ship) {
			releaseBeforeButton(menu_mode);
			menu_mode = MenuMode::Ship;
			selected_addon = nullptr;
			mode_str = U"ship";
			show_addons = map->getFitAddons(Array<String>{mode_str});
			
			category_buttons.clear();
		}
		else {
			menu_mode = MenuMode::Cursor;
		}
		need_update = true;
	}
	if (button[U"air_port"].pushRelative(position)) {
		if (menu_mode != MenuMode::AirPort) {
			releaseBeforeButton(menu_mode);
			menu_mode = MenuMode::AirPort;
			selected_addon = nullptr;
			mode_str = U"air_port";
			show_addons = map->getFitAddons(Array<String>{mode_str});
			
			category_buttons.clear();
		}
		else {
			menu_mode = MenuMode::Cursor;
		}
		need_update = true;
	}
	if (button[U"tile"].pushRelative(position)) {
		if (menu_mode != MenuMode::Tile) {
			releaseBeforeButton(menu_mode);
			menu_mode = MenuMode::Tile;
			selected_addon = nullptr;
			mode_str = U"tile";
			show_addons = map->getFitAddons(Array<String>{mode_str});
			
			category_buttons.clear();
		}
		else {
			menu_mode = MenuMode::Cursor;
		}
		need_update = true;
	}
	
	if (button[U"delete"].pushRelative(position)) {
		if (menu_mode != MenuMode::Delete) {
			releaseBeforeButton(menu_mode);
			menu_mode = MenuMode::Delete;
			selected_addon = map->getAllAddons()[U"tile_greenfield"];
			selected_addon_name = selected_addon->getName();
			mode_str = U"delete";
			show_addons.clear();
		}
		else {
			menu_mode = MenuMode::Cursor;
		}
		need_update = true;
	}
	
	if (button[U"rate"].pushRelative(position)) {
		show_rate_menu = !show_rate_menu;
		need_update = true;
	}
	
	if (button[U"save"].pushRelative(position)) {
		map->save();
		button[U"save"].release();
	}
	
	if (show_rate_menu) {
		if (rateMenu()) {
			need_update = true;
		}
	}
	
	return selected_addon;
}

void Menu::addonMenu() {
	if (show_addons.size() == 0) {
		return;
	}
	
	Rect(position.x+16, position.y-42, size.width, 42).draw(Color(9, 132, 227, 200));
	Rect(position.x+16, position.y-80, size.width, 38).draw(Color(45, 52, 54, 200));
	Rect(position.x, position.y-80, 16, 80).draw(Color(45, 52, 54, 200));
	
	if (show_addons.size() > 0) {
		int selected_i = -1, cursor_i = -1;
		for (int i=0; i<show_addons.size(); i++) {
			String addon_name = show_addons[i]->getName();
			
			bool cursor_on = (Cursor::Pos().x >= 30+32*i && Cursor::Pos().y >= position.y-40 && Cursor::Pos().x < 30+32*(i+1) && Cursor::Pos().y <= position.y-40+32);
			if (cursor_on || selected_addon_name == addon_name) {
				show_addons[i]->drawIcon(PositionStruct{position.x+30+32*i, position.y-37}, PositionStruct{0, 32}, SizeStruct{32, 32});
				
				if (MouseL.down() &&
					Cursor::Pos().x >= position.x+30 && Cursor::Pos().x <= position.x-30+size.width &&
					Cursor::Pos().y >= position.y-37 && Cursor::Pos().y <= position.y-37+32) {
					if (selected_addon_name == addon_name) {
						selected_addon_name = U"";
						selected_addon = nullptr;
					}
					else {
						selected_addon_name = addon_name;
						selected_addon = show_addons[i];
					}
				}
				
				selected_i = i;
				
				if (cursor_on || cursor_i == -1) {
					cursor_i = i;
				}
			}
			else {
				show_addons[i]->drawIcon(PositionStruct{position.x+30+32*i, position.y-37}, PositionStruct{0, 0}, SizeStruct{32, 32});
			}
		}
		
		if (cursor_i == selected_i && selected_i >= 0) {
			// 名前と説明
			String name_jp = show_addons[selected_i]->getNameJP();
			(*font16)(name_jp).draw(position.x+30, position.y-80+2);
			(*font12)(show_addons[selected_i]->getSummary()).draw(position.x+30, position.y-60+2);
			
			// 効果アイコン
			::map<String, EffectStruct> effects = show_addons[selected_i]->getEffects();
			int i = 0;
			int leftmost = (*font16)(name_jp).region(Scene::Width() / 2, Scene::Height() / 2).w+50;
			for (auto effect = effects.begin(); effect != effects.end(); effect++) {
				if (!effect_icons[effect->first].isEmpty()) {
					effect_icons[effect->first].draw(leftmost+i*48, position.y-75);
					(*font12)(U"{:+}"_fmt(effect->second.influence)).draw(leftmost+i*48+22, position.y-75);
					i++;
				}
			}
		}
		else if (cursor_i >= 0) {
			String name_jp = show_addons[cursor_i]->getNameJP();
			(*font16)(name_jp).draw(position.x+30, position.y-80+2);
			(*font12)(show_addons[cursor_i]->getSummary()).draw(position.x+30, position.y-60+2);
			
			// 効果アイコン
			::map<String, EffectStruct> effects = show_addons[cursor_i]->getEffects();
			int i = 0;
			int leftmost = (*font16)(name_jp).region(Scene::Width() / 2, Scene::Height() / 2).w+50;
			for (auto effect = effects.begin(); effect != effects.end(); effect++) {
				if (!effect_icons[effect->first].isEmpty()) {
					effect_icons[effect->first].draw(leftmost+i*48, position.y-75);
					(*font12)(U"{:+}"_fmt(effect->second.influence)).draw(leftmost+i*48+22, position.y-75);
					i++;
				}
			}
		}
		
		for (int i=0; i<category_buttons.size(); i++) {
			category_buttons[i].second.put(PositionStruct{0, position.y-37+16*i});
			
			if (category_buttons[i].second.push()) {
				if (category_buttons[i].second.isActive()) {
					show_addons = map->getFitAddons(Array<String>{mode_str, category_buttons[i].first});
					
					for (int j=0; j<category_buttons.size(); j++) {
						if (j != i) {
							category_buttons[j].second.release();
						}
					}
				}
				else {
					show_addons = map->getFitAddons(Array<String>{mode_str});
				}
			}
		}
	}
}

bool Menu::rateMenu() {
	Rect(position.x+495+35+16-32*4/2, position.y-32*3, 32*4, 32*3).draw(Color(100, 100, 100));
	
	button[U"rate_land_price"].put(PositionStruct{position.x+495+35+16-32*4/2+5, position.y-32*3+5});
	
	if (button[U"rate_land_price"].push()) {
		if (show_rate_name != U"land_price") {
			show_rate_name = U"land_price";
			map->setShowRate(show_rate_name);
			return true;
		}
		else {
			show_rate_name = U"";
			map->setShowRate(show_rate_name);
			return true;
		}
	}
	
	return false;
}
