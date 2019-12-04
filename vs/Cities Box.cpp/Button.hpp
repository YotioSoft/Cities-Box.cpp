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
	Button(ImageStruct& image);														// �摜����
	Button(ImageStruct& image, int new_size);										// �摜����
	Button(ImageStruct& image, int new_size, String new_label, Font& new_font);		// �摜����
	Button(IconFont::ID icon_id);													// ���S�t�H���g����
	Button(IconFont::ID icon_id, int new_size);										// ���S�t�H���g����
	Button(IconFont::ID icon_id, int new_size, String new_label, Font& new_font);	// ���S�t�H���g����
	
	// �z�u
	void put(PositionStruct new_position);
	
	// �����ꂽ���ǂ���
	bool push();
	
private:
	Texture button_texture;
	
	bool isIcon;
	
	PositionStruct position;
	SizeStruct size;
	
	Font font;
	String label;
	PositionStruct label_position;
};

#endif /* Button_hpp */
