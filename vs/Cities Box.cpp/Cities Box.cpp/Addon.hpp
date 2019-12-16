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
	
	String image;					// �A�h�I���摜�̃p�X
	String night_mask;				// �i�C�g�}�X�N�摜�̃p�X
	Array<String> direction_names;	// type�Ɋ܂܂�����
	RGBstruct transparent_color;	// ���ߐF��RGB�l
	
	map<String, AddonDirectionStruct> directions;	// type�Ɋ܂܂��e�����̏��
	
	Texture texture;				// �A�h�I���摜�̃e�N�X�`��
} AddonTypeStruct;

typedef struct EffectStruct {
	int influence;
	int grid;
} EffectStruct;

typedef struct EffectsStruct {
	EffectStruct land_price 			= {0, 0};	// �n��
	EffectStruct crime_rate 			= {0, 0};	// �ƍߗ�
	EffectStruct education_rate 		= {0, 0};	// ����x
	EffectStruct noise 					= {0, 0};	// ����
	EffectStruct garbage_disposal 		= {0, 0};	// ���ݏ�������
	EffectStruct firing_rate 			= {0, 0};	// ���Η�
	EffectStruct post					= {0, 0};	// �X�֏[���x
	EffectStruct mobile_communication	= {0, 0};	// ���o�C���ʐM
	EffectStruct free_wifi				= {0, 0};	// ����Wi-Fi�X�|�b�g
	EffectStruct television				= {0, 0};	// �e���r����
	EffectStruct radio					= {0, 0};	// ���W�I����
	EffectStruct tourist_attraction		= {0, 0};	// �ό����͓x
	EffectStruct durability				= {0, 0};	// �ϋv���S��
} EffectsStruct;

typedef struct CropStruct {
	String name;
	int amount;
} CropStruct;

class Addon {
public:
	Addon();
	
	// ���e�̕ύX
	bool load(FileStruct new_file_path, String loading_addons_set_name);
	bool loadADAT(FileStruct new_file_path, String loading_addons_set_name);
	bool loadADJ(FileStruct new_file_path, String loading_addons_set_name);
	
	// ���O�̎擾
	String getName();		// ����
	String getNameJP();		// ���{�ꖼ
	
	// ����Җ��̎擾
	String getAuthorName();
	
	// �������̎擾
	String getSummary();
	
	// Type�̖��O�̎擾
	String getTypeName(int type_num);
	
	// Direction�̖��O�̎擾
	String getDirectionName(int type_num, int direction_num);
	String getDirectionName(String type_name, int direction_num);
	
	// �J�e�S�����擾
	Array<String> getCategories();
	
	// �w�肵���J�e�S���ɊY�����邩
	bool isInCategories(String search_category);
	bool isInCategories(Array<String> search_categories);
	
	// ���ʂ��擾
	map<String, EffectStruct> getEffects();
	
	// �A�C�R���̃e�N�X�`���̎擾
	void drawIcon(PositionStruct position, PositionStruct left_top, SizeStruct size);
	
	// �g�p����^�C�����擾
	CoordinateStruct getUseTiles(String type_name, String direction_name);
	
	// �ŏI�I�ɕ\��������W���擾
	PositionStruct getPosition(String type_name, String direction_name, PositionStruct position, CoordinateStruct use_tiles, CoordinateStruct tiles_count);
	
	// �A�h�I����`�悷��
	void draw(String type_name, String direction_name, PositionStruct position, CoordinateStruct use_tiles, CoordinateStruct tiles_count);
	
	// JSON�`���ɕϊ�����
	void converter();
	
private:
	// �A�h�I���t�@�C���̃p�X
	FileStruct addon_file_path;
	
	// �A�h�I����
	String addon_name;				// �p�ꖼ
	String addon_jp_name;			// ���{�ꖼ
	
	// ����Җ�
	String addon_author;
	
	// ������
	String addon_summary;
	
	// ��������A�h�I���Z�b�g�̖��O�i�󔒂�Normal�Ƃ݂Ȃ��j
	Array<String> belong_addons_set_name;
	
	// �A�h�I���̃^�C�v
	Array<String> addon_categories;
	
	// �A�C�R���摜�̃p�X
	String addon_icon;
	
	// �A�C�R���̃e�N�X�`��
	Texture icon_texture;
	
	// �g�p����type
	Array<String> use_types;
	
	// ���e�l�� or �ő�]�ƈ���
	int maximum_capacity;
	
	// �����̌���
	map<String, EffectStruct> effects;
	
	// �n��
	int land_price_influence;		// �㏸�z
	int land_price_influence_grid;	// �n���̏㉺���e������}�X
	
	// �etype�̏��
	map<String, AddonTypeStruct> types;
	
	
	// �v���C�x�[�g�֐�
	bool getElement(String str, String search_element_name, String& ret);
	bool getElement(String str, String search_element_name, int& ret);
	bool getTypes(String str, String search_element_name, Array<String>& ret);
	void set_alpha_color(Image& image_temp, Color transparent_rgb);
};

#endif /* Addon_hpp */
