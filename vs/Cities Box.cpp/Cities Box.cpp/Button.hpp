//
//  Button.hpp
//  Cities Box
//
//  Created by YotioSoft on 2019/12/01.
//

#ifndef Button_hpp
#define Button_hpp

#include "Specific.hpp"

class Button {
public:
	// �R���X�g���N�^
	Button();
	Button(ImageStruct& image);																										// �摜����
	Button(ImageStruct& image, int new_size);																						// �摜����
	Button(ImageStruct& image, int new_size, String new_label, Font& new_font);														// �摜����
	Button(IconFont::ID icon_id);																									// ���S�t�H���g����
	Button(IconFont::ID icon_id, int new_size, int new_icon_size, PositionStruct new_shift);										// ���S�t�H���g����
	Button(IconFont::ID icon_id, int new_size, int new_icon_size, PositionStruct new_shift, String new_label, Font& new_font);		// ���S�t�H���g����
	
	// �ݒ�
	void set(ImageStruct& image);																									// �摜����
	void set(ImageStruct& image, int new_size);																						// �摜����
	void set(ImageStruct& image, int new_size, String new_label, Font& new_font);													// �摜����
	void set(IconFont::ID icon_id);																									// ���S�t�H���g����
	void set(IconFont::ID icon_id, int new_size, int new_icon_size, PositionStruct new_shift);										// ���S�t�H���g����
	void set(IconFont::ID icon_id, int new_size, int new_icon_size, PositionStruct new_shift, String new_label, Font& new_font);	// ���S�t�H���g����
	
	// �z�u
	void put(PositionStruct new_position);
	
	// �����ꂽ���ǂ���
	bool push();
	
private:
	Texture button_texture;
	
	bool isIcon;
	
	PositionStruct position;
	SizeStruct size;
	SizeStruct icon_size;
	
	PositionStruct shift;
	
	Font font;
	String label;
	PositionStruct label_position;
};

#endif /* Button_hpp */
