//
//  Addon.hpp
//  Cities Box
//
//  Created by YotioSoft on 2019/11/27.
//
#ifndef Addon_hpp
#define Addon_hpp

#include "Specific.hpp"
#include "Images.hpp"

typedef struct AddonDirectionStruct {
	string direction;
	
	int size_width;					// �摜�̉������̃T�C�Y
	int size_height;				// �摜�̏c�����̃T�C�Y
	int chip_x;						// �A�h�I������߂鉡�����̃}�X�̐�
	int chip_y;						// �A�h�I������߂�c�����̃}�X�̐�
	
	int top_left_x;					// �����x���W
	int top_left_y;					// �����y���W
	int bottom_right_x;				// �E����x���W
	int bottom_right_y;				// �E����y���W
} AddonDirectionStruct;

typedef struct AddonTypeStruct {
	string type;
	
	string image;					// �A�h�I���摜�̃p�X
	string night_mask;				// �i�C�g�}�X�N�摜�̃p�X
	Array<string> direction;		// type�Ɋ܂܂�����
	RGBstruct transparent_color;	// ���ߐF��RGB�l
	
	map<string, AddonDirectionStruct> directions;	// type�Ɋ܂܂��e�����̏��
	
	Texture texture;				// �A�h�I���摜�̃e�N�X�`��
} AddonTypeStruct;

class Addon {
public:
	Addon();
	
	// ���e�̕ύX
	bool load(FileStruct file_path, string loading_addons_set_name);
	
	// ���O�̎擾
	string getName();		// ����
	string getNameJP();		// ���{�ꖼ
	
	// ����Җ��̎擾
	string getAuthorName();
	
	// �������̎擾
	string getSummary();
	
	// Type�̖��O�̎擾
	string getTypeName(int type_num);
	
	// Direction�̖��O�̎擾
	string getDirectionName(int type_num, int direction_num);
	
	// �A�C�R����ImageStruct�̎擾
	ImageStruct getIconImageStruct();
	
	// �A�h�I����`�悷��
	void draw(string type_name, string direction_name, PositionStruct position, CoordinateStruct use_tiles, CoordinateStruct tiles_count);
	
private:
	// �A�h�I����
	string addon_name;				// �p�ꖼ
	string addon_jp_name;			// ���{�ꖼ
	
	// ����Җ�
	string addon_author;
	
	// ������
	string addon_summary;
	
	// ��������A�h�I���Z�b�g�̖��O�i�󔒂�Normal�Ƃ݂Ȃ��j
	string belong_addons_set_name;
	
	// �A�h�I���̃^�C�v
	string addon_type;
	
	// �A�C�R���摜�̃p�X
	string addon_icon;
	
	// �g�p����type
	Array<string> use_types;
	
	// �g�p����direction
	Array<Array<string>> directions_name;
	
	// ���e�l��
	int maxium_capacity;
	
	// �n��
	int land_price_influence;		// �㏸�z
	int land_price_influence_grid;	// �n���̏㉺���e������}�X
	
	// �etype�̏��
	map<string, AddonTypeStruct> types;
	
	
	// �v���C�x�[�g�֐�
	bool getElement(string str, string search_element_name, string& ret);
	bool getElement(string str, string search_element_name, int& ret);
	bool getTypes(string str, string search_element_name, Array<string>& ret);
	void set_alpha_color(Image& image_temp, Color transparent_rgb);
};

#endif /* Addon_hpp */
