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
	
	int sizeWidth;					// �摜�̉������̃T�C�Y
	int sizeHeight;					// �摜�̏c�����̃T�C�Y
	int chipX;						// �A�h�I������߂鉡�����̃}�X�̐�
	int chipY;						// �A�h�I������߂�c�����̃}�X�̐�
	
	int topLeftX;					// �����x���W
	int topLeftY;					// �����y���W
	int bottomRightX;				// �E����x���W
	int bottomRightY;				// �E����y���W
} AddonDirectionStruct;

typedef struct AddonTypeStruct {
	string type;
	
	String image;					// �A�h�I���摜�̃p�X
	String nightMask;				// �i�C�g�}�X�N�摜�̃p�X
	Array<String> directionNames;	// type�Ɋ܂܂�����
	RGBstruct transparentColor;		// ���ߐF��RGB�l
	
	map<String, AddonDirectionStruct> directions;	// type�Ɋ܂܂��e�����̏��
	
	Texture texture;				// �A�h�I���摜�̃e�N�X�`��
} AddonTypeStruct;

typedef struct EffectStruct {
	int influence;
	int grid;
} EffectStruct;

typedef struct EffectsStruct {
	EffectStruct landPrice 				= {0, 0};	// �n��
	EffectStruct crimeRate 				= {0, 0};	// �ƍߗ�
	EffectStruct educationRate 			= {0, 0};	// ����x
	EffectStruct noise 					= {0, 0};	// ����
	EffectStruct garbageDisposal 		= {0, 0};	// ���ݏ�������
	EffectStruct firingRate 			= {0, 0};	// ���Η�
	EffectStruct post					= {0, 0};	// �X�֏[���x
	EffectStruct mobileCommunication	= {0, 0};	// ���o�C���ʐM
	EffectStruct freeWiFi				= {0, 0};	// ����Wi-Fi�X�|�b�g
	EffectStruct television				= {0, 0};	// �e���r����
	EffectStruct radio					= {0, 0};	// ���W�I����
	EffectStruct touristAttraction		= {0, 0};	// �ό����͓x
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
	bool load(FileStruct newFilePath, String loadingAddonsSetName);
	bool loadADAT(FileStruct newFilePath, String loadingAddonsSetName);
	bool loadADJ(FileStruct newFilePath, String loadingAddonsSetName);
	
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
	String getDirectionName(int typeNum, int directionNum);
	String getDirectionName(String typeName, int directionNum);
	
	// �J�e�S�����擾
	Array<String> getCategories();
	
	// �w�肵���J�e�S���ɊY�����邩
	bool isInCategories(String searchCategory);
	bool isInCategories(Array<String> searchCategories);
	
	// ���ʂ��擾
	map<String, EffectStruct> getEffects();
	
	// �A�C�R���̃e�N�X�`���̎擾
	void drawIcon(PositionStruct position, PositionStruct leftTop, SizeStruct size);
	
	// �g�p����^�C�����擾
	CoordinateStruct getUseTiles(String typeName, String directionName);
	
	// �ŏI�I�ɕ\��������W���擾
	PositionStruct getPosition(String typeName, String directionName, PositionStruct position, CoordinateStruct useTiles, CoordinateStruct tilesCount);
	
	// �A�h�I����`�悷��
	void draw(String typeName, String directionName, PositionStruct position, CoordinateStruct useTiles, CoordinateStruct tilesCount, Color* addColor);
	
	// JSON�`���ɕϊ�����
	void converter();
	
protected:
	// �A�h�I���t�@�C���̃p�X
	FileStruct addonFilePath;
	
	// �A�h�I����
	String addonName;				// �p�ꖼ
	String addonJPName;				// ���{�ꖼ
	
	// ����Җ�
	String addonAuthor;
	
	// ������
	String addonSummary;
	
	// ��������A�h�I���Z�b�g�̖��O�i�󔒂�Normal�Ƃ݂Ȃ��j
	Array<String> belongAddonsSetName;
	
	// �A�h�I���̃^�C�v
	Array<String> addonCategories;
	
	// �A�C�R���摜�̃p�X
	String addonIcon;
	
	// �A�C�R���̃e�N�X�`��
	Texture iconTexture;
	
	// �g�p����type
	Array<String> useTypes;
	
	// ���e�l�� or �ő�]�ƈ���
	int maximumCapacity;
	
	// �����̌���
	map<String, EffectStruct> effects;
	
	// �n��
	int landPriceInfluence;			// �㏸�z
	int landPriceInfluenceGrid;		// �n���̏㉺���e������}�X
	
	// �etype�̏��
	map<String, AddonTypeStruct> types;
	
	
	// �v���C�x�[�g�֐�
	bool getElement(String str, String searchElementName, String& ret);
	bool getElement(String str, String searchElementName, int& ret);
	bool getTypes(String str, String searchElementName, Array<String>& ret);
	void setAlphaColor(Image& imageTemp, Color transparentRGB);
};

#endif /* Addon_hpp */
