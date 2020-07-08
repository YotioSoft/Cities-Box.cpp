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
	Button(ImageStruct& image, int newSize);																						// �摜����
	Button(ImageStruct& image, int newSize, String newLabel, Font& newFont);														// �摜����
	Button(IconFont::ID iconID);																									// ���S�t�H���g����
	Button(IconFont::ID iconID, int newSize, int newIconSize, PositionStruct newShift);												// ���S�t�H���g����
	Button(IconFont::ID iconID, int newSize, int newIconSize, PositionStruct newShift, String newLabel, Font& newFont);				// ���S�t�H���g����
	
	// �ݒ�
	void set(ImageStruct& image);																									// �摜����
	void set(ImageStruct& image, int newSize);																						// �摜����
	void set(ImageStruct& image, int newSize, String newLabel, Font& newFont);														// �摜����
	void set(IconFont::ID iconID);																									// ���S�t�H���g����
	void set(IconFont::ID iconID, int newSize, int newIconSize, PositionStruct newShift);											// ���S�t�H���g����
	void set(IconFont::ID iconID, int newSize, int newIconSize, PositionStruct newShift, String newLabel, Font& newFont);			// ���S�t�H���g����
	
	// �z�u
	void put(PositionStruct newPosition);
	void putRelative(PositionStruct newPosition, PositionStruct leftTop);
	
	// �����ꂽ���ǂ���
	bool push();
	bool pushRelative(PositionStruct leftTop);
	
	// �A�N�e�B�u���ǂ���
	bool isActive();
	
	// �I������
	void release();
	
private:
	Texture buttonTexture;
	
	bool isIcon;
	
	PositionStruct position;
	SizeStruct size;
	SizeStruct iconSize;
	
	PositionStruct shift;
	
	Font font;
	String label;
	PositionStruct labelPosition;
	
	bool active;
};

#endif /* Button_hpp */
