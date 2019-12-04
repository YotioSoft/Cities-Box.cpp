//
//  Addon.cpp
//  Cities Box
//
//  Created by YotioSoft on 2019/11/27.
//

#include "Addon.hpp"

Addon::Addon() {
}

bool Addon::getElement(string str, string search_element_name, string& ret) {
	if (str.find(search_element_name) != string::npos && str.find("=") != string::npos) {
		ret = str.substr(str.find("\"")+1, str.length()-str.find("\"")-2);
		return true;
	}
	return false;
}

bool Addon::getElement(string str, string search_element_name, int& ret) {
	if (str.find(search_element_name) != string::npos && str.find("=") != string::npos) {
		ret = stoi(str.substr(str.find("\"")+1, str.length()-str.find("\"")-2));
		return true;
	}
	return false;
}

bool Addon::getTypes(string str, string search_element_name, Array<string>& ret) {
	string a_ret;
	if (getElement(str, search_element_name, a_ret)) {
		ret = split(a_ret, ", ");
		return true;
	}
	return false;
}

void Addon::set_alpha_color(Image& image_temp, Color transparent_rgb) {
	for (int h=0; h<image_temp.height(); h++) {
		for (int w=0; w<image_temp.width(); w++) {
			if (image_temp[h][w].r == transparent_rgb.r && image_temp[h][w].g == transparent_rgb.g && image_temp[h][w].b == transparent_rgb.b) {
				image_temp[h][w].a = 0;
			}
		}
	}
}

bool Addon::load(FileStruct file_path, string loading_addons_set_name) {
	// アドオンファイルの読み込み
	ifstream ifs(file_path.file_path.c_str());
	string str_temp;
	
	if (ifs.fail()) {
		cerr << "Failed to open file." << endl;
	}
	
	// 各要素の読み出し
	string current_loading_type = "";
	string current_direction = "";
	
	bool loading_type = false;
	bool loading_direction = false;
	
	Color transparent_color;
	transparent_color.r = 0;
	transparent_color.g = 0;
	transparent_color.b = 0;
	
	while (getline(ifs, str_temp)) {
		str_temp = str_temp.substr(0, str_temp.length()-1);
		
		// 名前
		getElement(str_temp, "addon_name", addon_name);
		getElement(str_temp, "addon_jp_name", addon_jp_name);
		
		// 製作者名
		getElement(str_temp, "addon_author", addon_author);
		
		// 説明文
		getElement(str_temp, "addon_summary", addon_summary);
		
		// 所属するアドオンセットの名前
		getElement(str_temp, "belong_addons_set_name", belong_addons_set_name);
		
		if (belong_addons_set_name.length() > 0) {
			if (belong_addons_set_name != loading_addons_set_name && !(loading_addons_set_name.length() > 0)) {
				return false;
			}
		}
		
		// アイコン画像のパス
		getElement(str_temp, "addon_icon", addon_icon);
		
		// アドオンのtype
		getElement(str_temp, "addon_type", addon_type);
		
		// 最大収容人数
		getElement(str_temp, "maxium_capacity", maxium_capacity);
		
		// 地価
		getElement(str_temp, "land_price_influence", land_price_influence);
		getElement(str_temp, "land_price_influence_grid", land_price_influence_grid);
		
		// 使用するtype
		getTypes(str_temp, "use_types", use_types);
		
		// 各typeの内容を取得
		// 現在読込中のtypeを取得
		for (int i=0; i<use_types.size(); i++) {
			if (str_temp.find(use_types[i]+" {") != string::npos && !loading_type) {
				current_loading_type = use_types[i];
				loading_type = true;
				
				directions_name.push_back(Array<string>());
			}
		}
		if (str_temp.find("}") == 0 && !loading_direction) {
			// typeが切り替わるときにTextureの設定
			if (types[current_loading_type].image.length() > 0) {
				Image itemp(Unicode::Widen(file_path.folder_path+"/"+types[current_loading_type].image));
				set_alpha_color(itemp, transparent_color);
				types[current_loading_type].texture = Texture(itemp);
			}
			
			current_direction = "";
			loading_type = false;
		}
		
		if (current_loading_type != "") {
			// 画像のパス
			getElement(str_temp, "image", types[current_loading_type].image);
			
			// 透過色
			string rgb_str;
			getElement(str_temp, "transparent_color", rgb_str);
			
			if (rgb_str.length() > 0) {
				Array<string> rgb_strv = split(rgb_str, ", ");
				
				if (rgb_strv.size() == 3) {
					transparent_color.r = stoi(rgb_strv[0]);
					transparent_color.g = stoi(rgb_strv[1]);
					transparent_color.b = stoi(rgb_strv[2]);
				}
			}
			
			// ナイトマスク画像のパス
			getElement(str_temp, "night_mask", types[current_loading_type].night_mask);
			
			// typeに含まれる方向と各方向の情報を取得
			getTypes(str_temp, "direction", directions_name.back());
			
			for (int i=0; i<directions_name.back().size(); i++) {
				if (str_temp.find(directions_name.back()[i]+" {") != string::npos && !loading_direction) {
					current_direction = directions_name.back()[i];
				}
			}
			if (str_temp.find("}") == 0 && loading_direction) {
				current_direction = "";
				loading_direction = false;
			}
			
			if (current_direction != "") {
				AddonDirectionStruct direction_temp;
				
				// アドオンの大きさ
				getElement(str_temp, "size_x", direction_temp.size_width);		// 横
				getElement(str_temp, "size_y", direction_temp.size_height);		// 縦
				
				// アドオンが占めるマスの数
				getElement(str_temp, "chip_x", direction_temp.chip_x);			// 横
				getElement(str_temp, "chip_y", direction_temp.chip_y);			// 縦
				
				// 画像上の左上の座標
				getElement(str_temp, "top_left_x", direction_temp.top_left_x);
				getElement(str_temp, "top_left_y", direction_temp.top_left_y);
				
				// 画面上の右下の座標
				getElement(str_temp, "bottom_right_x", direction_temp.bottom_right_x);
				getElement(str_temp, "bottom_right_y", direction_temp.bottom_right_y);
				
				types[current_loading_type].directions[current_direction] = direction_temp;
			}
		}
	}
	
	return true;
}

string Addon::getName() {
	return addon_name;
}

string Addon::getNameJP() {
	return addon_jp_name;
}

string Addon::getAuthorName() {
	return addon_author;
}

string Addon::getSummary() {
	return addon_summary;
}

string Addon::getTypeName(int type_num) {
	return use_types[type_num];
}

string Addon::getDirectionName(int type_num, int direction_num) {
	return directions_name[type_num][direction_num];
}

void Addon::draw(string type_name, string direction_name, PositionStruct position, CoordinateStruct use_tiles, CoordinateStruct tiles_count,CoordinateStruct coordinate) {
	AddonDirectionStruct* direction_temp = &(types[type_name].directions[direction_name]);
	
	if ((coordinate.x == 28 || coordinate.x == 29) && coordinate.y == 49) {
		cout << coordinate.x << "," << coordinate.y << " :  " << tiles_count.x << "," << tiles_count.y << endl;
	}
	
	//position.x = position.x + tiles_count.x * CHIP_SIZE/8;
	position.y = position.y + CHIP_SIZE/2 - direction_temp->size_height + CHIP_SIZE/4 * (max(1, use_tiles.x) - 1 - tiles_count.x);
	
	unsigned short int top_left_x = direction_temp->top_left_x;
	top_left_x += CHIP_SIZE/2 * tiles_count.x;
	
	unsigned short int top_left_y = direction_temp->top_left_y;
	top_left_y += CHIP_SIZE/2 * tiles_count.y;
	
	unsigned short int size_width = direction_temp->size_width;
	size_width = CHIP_SIZE;
	
	unsigned short int size_height = direction_temp->size_height;
	
	types[type_name].texture(top_left_x, top_left_y, size_width, size_height).draw(position.x, position.y);
}