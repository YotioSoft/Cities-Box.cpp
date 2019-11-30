//
//  Addon.cpp
//  Cities Box
//
//  Created by YotioSoft on 2019/11/27.
//

#include "Addon.hpp"

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

bool Addon::getTypes(string str, string search_element_name, vector<string>& ret) {
	string a_ret;
	if (getElement(str, search_element_name, a_ret)) {
		ret = split(a_ret, ", ");
		return true;
	}
	return false;
}

Image Addon::set_alpha_color(string image_file_path, int clear_r, int clear_g, int clear_b) {
	Image image_temp(Unicode::Widen(image_file_path));
	
	for (int h=0; h<image_temp.height(); h++) {
		for (int w=0; w<image_temp.width(); w++) {
			if (image_temp[w][h].r == 0 && image_temp[w][h].g == 0 && image_temp[w][h].b == 0) {
				image_temp[w][h].setA(0);
			}
		}
	}
	
	return image_temp;
}

void Addon::load(FileStruct file_path) {
	// �A�h�I���t�@�C���̓ǂݍ���
	ifstream ifs(file_path.file_path.c_str());
	string str_temp;
	
	if (ifs.fail()) {
		cerr << "Failed to open file." << endl;
	}
	
	// �e�v�f�̓ǂݏo��
	string current_loading_type = "";
	string current_direction = "";
	
	vector<string> directions_name;
	
	while (getline(ifs, str_temp)) {
		//str_temp = str_temp.substr(0, str_temp.size() - LINE_FEED_CODE);

		// ���O
		getElement(str_temp, "addon_name", addon_name);
		getElement(str_temp, "addon_jp_name", addon_jp_name);
		
		// ����Җ�
		getElement(str_temp, "addon_author", addon_author);
		
		// ������
		getElement(str_temp, "addon_summary", addon_summary);
		
		// �A�C�R���摜�̃p�X
		getElement(str_temp, "addon_icon", addon_icon);
		
		// �A�h�I����type
		getElement(str_temp, "addon_type", addon_type);
		
		// �ő���e�l��
		getElement(str_temp, "maxium_capacity", maxium_capacity);
		
		// �n��
		getElement(str_temp, "land_price_influence", land_price_influence);
		getElement(str_temp, "land_price_influence_grid", land_price_influence_grid);
		
		// �g�p����type
		getTypes(str_temp, "use_types", use_types);
		
		// �etype�̓��e���擾
		// ���ݓǍ�����type���擾
		for (int i=0; i<use_types.size(); i++) {
			if (str_temp.find(use_types[i]) != string::npos && str_temp.find("{") != string::npos) {
				current_loading_type = use_types[i];
			}
		}
		if (current_loading_type != "") {
			// �摜�̃p�X
			getElement(str_temp, "image", types[current_loading_type].image);
			
			// Texture�̐ݒ�
			if (types[current_loading_type].image.size() > 0) {
				types[current_loading_type].texture = Texture(set_alpha_color(file_path.folder_path+"/"+types[current_loading_type].image, 0, 0, 0));
			}
			
			// �i�C�g�}�X�N�摜�̃p�X
			getElement(str_temp, "night_mask", types[current_loading_type].night_mask);
			
			// type�Ɋ܂܂������Ɗe�����̏����擾
			getTypes(str_temp, "direction", directions_name);
			
			for (int i=0; i<directions_name.size(); i++) {
				if (str_temp.find(directions_name[i]) != string::npos && str_temp.find("{") != string::npos) {
					current_direction = directions_name[i];
				}
			}
			if (current_direction != "") {
				// �A�h�I���̑傫��
				getElement(str_temp, "size_x", types[current_loading_type].directions[current_direction].size_width);		// ��
				getElement(str_temp, "size_y", types[current_loading_type].directions[current_direction].size_height);		// �c
				
				// �A�h�I������߂�}�X�̐�
				getElement(str_temp, "chip_x", types[current_loading_type].directions[current_direction].chip_x);			// ��
				getElement(str_temp, "chip_y", types[current_loading_type].directions[current_direction].chip_y);			// �c
				
				// �摜��̍���̍��W
				getElement(str_temp, "top_left_x", types[current_loading_type].directions[current_direction].top_left_x);
				getElement(str_temp, "top_left_y", types[current_loading_type].directions[current_direction].top_left_y);
				
				// ��ʏ�̉E���̍��W
				getElement(str_temp, "bottom_right_x", types[current_loading_type].directions[current_direction].bottom_right_x);
				getElement(str_temp, "bottom_right_y", types[current_loading_type].directions[current_direction].bottom_right_y);
			}
		}
	}
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

void Addon::draw(string type_name, string direction_name, PositionStruct position) {
	AddonDirectionStruct direction_temp = types[type_name].directions[direction_name];
	
	types[type_name].texture(direction_temp.top_left_x, direction_temp.top_left_y, direction_temp.bottom_right_x-direction_temp.top_left_x, direction_temp.bottom_right_y-direction_temp.top_left_y)
	.draw(position.x, position.y);
}
