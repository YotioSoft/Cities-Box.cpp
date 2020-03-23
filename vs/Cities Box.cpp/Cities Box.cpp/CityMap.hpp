//
//  CityMap.hpp
//  Cities Box
//
//  Created by YotioSoft on 2019/11/27.
//

#ifndef CityMap_hpp
#define CityMap_hpp

#include "Specific.hpp"
#include "Addon.hpp"
#include "OtherFunctions.hpp"

typedef struct TimeStruct {
	int year;
	int month;
	int date;
	int hour;
	int minutes;
} TimeStruct;

typedef struct RCOIFstruct {
	int residential;
	int commercial;
	int office;
	int industrial;
	int farm;
} RCOIFstruct;

typedef struct WorkersStruct {
	int commercial;
	int office;
	int industrial;
	int farm;
	int publicFacility;
} WorkersStruct;

typedef struct BudgetStruct {
	int police;
	int fireDepertment;
	int postOffice;
	int education;
} BudgetStruct;

typedef struct WorkPlaceStruct {
	RCOIFP::Type workPlace;
	int workPlacesSerialNumber;
} WorkPlaceStruct;

typedef struct SchoolStruct {
	School::Type school;
	int schoolSerialNumber;
} SchoolStruct;

typedef struct SquareStruct {
	String originalName;
	//Array<String> category;
	
	Array<String> types;
	Array<String> directions;
	
	int serialNumber;
	
	CoordinateStruct tilesCount;
	
	int residents;
	WorkersStruct workers;
	int students;
	
	int happinessRate;
	map<String, int> rate;
	
	//CropStruct crop;
	
	Array<int> age;
	Array<String> gender;
	
	Array<WorkPlaceStruct> workPlaces;
	Array<SchoolStruct> schools;
	
	RCOIFP::Type reservation;
	
	Array<Addon*> addons;
	
} SquareStruct;



class CityMap {
public:
	// �}�b�v�̓ǂݍ���
	void load(String loadMapFilePath);
	void loadCBD(String loadMapFilePath);
	void loadCBJ(String loadMapFilePath);
	
	// �A�h�I���̓ǂݍ���
	void loadAddons(String addonSetName);
	
	// �J�e�S���ɓ��Ă͂܂�A�h�I���̈ꗗ��Ԃ�
	Array<Addon*> getFitAddons(Array<String> selectedCategories);
	
	// �A�h�I�����X�g��Ԃ�
	map<String, Addon*> getAllAddons();
	
	// �Ǎ������
	void loadingScreen();
	
	// �}�b�v�̕`��
	void drawSquare(CoordinateStruct coordinate, CameraStruct camera);
	void draw(CameraStruct camera, CursorStruct& cursor);
	
	// Addon�\���̂̎擾
	Array<Addon> getAddon(CoordinateStruct coordinate);
	
	// ���v�x�̎擾
	RCOIFstruct getDemand();
	
	// �l���̎擾
	int getPopulation();
	
	// �����̎擾
	int getMoney();
	
	// �C���̎擾
	int getTemperature();
	
	// �}�b�v�T�C�Y�̎擾
	SizeStruct getMapSize();
	
	// ���W����`��ʒu���擾
	CoordinateStruct positionToCoordinate(PositionStruct position, CameraStruct camera);
	
	PositionStruct coordinateToPosition(CoordinateStruct coordinate, CameraStruct camera);
	
	// �`��͈͂��擾
	pair<CoordinateStruct, CoordinateStruct> getDrawArea(CameraStruct camera);
	
	// �����ꂩ�̃A�h�I�����J�e�S���Ɋ܂܂�Ă��邩
	bool isInCategories(String searchCategory, CoordinateStruct coordinate);
	
	// �A�h�I����ݒu
	bool build(CoordinateStruct position, Addon* selectedAddon, bool needToBreak);
	
	// �A�h�I�����X�V
	void update(CoordinateStruct position, Addon* selectedAddon, Array<CoordinateStruct>& needUpdate);
	
	// �A�h�I��������
	void breaking(CoordinateStruct position);
	
	// �A�h�I���̎n�_�ƂȂ�}�X�Ɉړ�����
	CoordinateStruct moveToAddonStartSquare(CoordinateStruct searchCoordinate, int addonNumber);
	
	// �w�肵���ꏊ�ɍ����A�h�I����Type��Direction���擾
	bool getBuildTypeAndDirection(CoordinateStruct coordinate, Addon* selectedAddon, String& retType, String& retDirection, Array<CoordinateStruct>& needUpdate);
	
	// �A�h�I�����폜
	void clear(CoordinateStruct position);
	
	// ���W���}�b�v�͈͓��ɓ����Ă��邩
	bool isPositionAvailable(CoordinateStruct coordinate);
	
	// ���Ԃ�i�܂��Ď擾
	TimeStruct cityTime(int minutesDelta);
	
	// �e�����擾
	map<String, int> getRate(CoordinateStruct coordinate);
	int getRate(CoordinateStruct coordinate, String rateName);
	
	// �e����\������Ƃ��̐F���擾
	Color getRateColor(int rate, bool upper, int standard);
	
	// ���[�g�\�����[�h
	void setShowRate(String rateName);
	
	// �}�b�v�ۑ�
	bool save();
	
	// ���������
	void freeMapAndAddons();
	
private:
	int savedVersion;
	String addonSet;
	
	String cityName;
	String mayorName;
	int totalPopulation;
	bool changeWeather;
	int temperature;
	bool darkOnNight;
	
	SizeStruct mapsize;
	
	TimeStruct time;
	
	RCOIFstruct demand;
	
	int money;
	
	BudgetStruct budget;
	RCOIFstruct tax;
	
	Array<Array<SquareStruct>> squares;
	
	bool loadingComplete;
	
	map<String, Addon*> addons;
	
	CameraStruct cameraBefore;
	pair<CoordinateStruct, CoordinateStruct> range;
	
	String mapFilePath;
	
	String showRate = U"";
	
	// �v���C�x�[�g�֐�
	bool getElement(String str, String searchElementName, String& ret);
	bool getElement(String str, String searchElementName, int& ret);
	bool getElement(String str, String searchElementName, bool& ret);
	bool getTypes(String str, String searchElementName, Array<String>& ret);
};

#endif /* CityMap_hpp */
