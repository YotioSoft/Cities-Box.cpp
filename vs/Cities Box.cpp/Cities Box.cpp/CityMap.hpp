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
	int public_facility;
} WorkersStruct;

typedef struct BudgetStruct {
	int police;
	int fire_depertment;
	int post_office;
	int education;
} BudgetStruct;

typedef struct WorkPlaceStruct {
	RCOIFP::Type work_place;
	int work_places_serial_number;
} WorkPlaceStruct;

typedef struct SchoolStruct {
	School::Type school;
	int school_serial_number;
} SchoolStruct;

typedef struct SquareStruct {
	String original_name;
	//Array<String> category;
	
	Array<String> types;
	Array<String> directions;
	
	int serial_number;
	
	CoordinateStruct tiles_count;
	
	int residents;
	WorkersStruct workers;
	int students;
	
	int happiness_rate;
	
	//CropStruct crop;
	
	Array<int> age;
	Array<String> gender;
	
	Array<WorkPlaceStruct> work_places;
	Array<SchoolStruct> schools;
	
	RCOIFP::Type reservation;
	
	Array<Addon*> addons;
	
} SquareStruct;



class CityMap {
public:
	// �}�b�v�̓ǂݍ���
	void load(String new_map_file_path);
	void loadCBD(String new_map_file_path);
	void loadCBJ(String new_map_file_path);
	
	// �A�h�I���̓ǂݍ���
	void loadAddons(String addon_set_name);
	
	// �J�e�S���ɓ��Ă͂܂�A�h�I���̈ꗗ��Ԃ�
	Array<Addon*> getFitAddons(Array<String> selected_categories);
	
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
	
	// �}�b�v�T�C�Y�̎擾
	SizeStruct getMapSize();
	
	// ���W����`��ʒu���擾
	CoordinateStruct positionToCoordinate(PositionStruct position, CameraStruct camera);
	
	PositionStruct coordinateToPosition(CoordinateStruct coordinate, CameraStruct camera);
	
	// �`��͈͂��擾
	pair<CoordinateStruct, CoordinateStruct> getDrawArea(CameraStruct camera);
	
	// �����ꂩ�̃A�h�I�����J�e�S���Ɋ܂܂�Ă��邩
	bool isInCategories(String search_category, CoordinateStruct coordinate);
	
	// �A�h�I����ݒu
	bool build(CoordinateStruct position, Addon* selected_addon, bool need_to_break);
	
	// �A�h�I�����X�V
	void update(CoordinateStruct position, Addon* selected_addon, Array<CoordinateStruct>& need_update);
	
	// �A�h�I��������
	void breaking(CoordinateStruct position);
	
	// �A�h�I���̎n�_�ƂȂ�}�X�Ɉړ�����
	CoordinateStruct moveToAddonStartSquare(CoordinateStruct search_coordinate, int addon_number);
	
	// �w�肵���ꏊ�ɍ����A�h�I����Type��Direction���擾
	bool getBuildTypeAndDirection(CoordinateStruct coordinate, Addon* selected_addon, String& ret_type, String& ret_direction, Array<CoordinateStruct>& need_update);
	
	// �A�h�I�����폜
	void clear(CoordinateStruct position);
	
	// �}�b�v�ۑ�
	bool save();
	
	// ���������
	void freeMapAndAddons();
	
private:
	int saved_version;
	String addon_set;
	
	String city_name;
	String mayor_name;
	int total_population;
	bool change_weather;
	int temperature;
	bool dark_on_night;
	
	SizeStruct mapsize;
	
	TimeStruct time;
	
	RCOIFstruct demand;
	
	int money;
	
	BudgetStruct budget;
	RCOIFstruct tax;
	
	Array<Array<SquareStruct>> squares;
	
	bool loading_complete;
	
	map<String, Addon*> addons;
	
	CameraStruct camera_before;
	pair<CoordinateStruct, CoordinateStruct> range;
	
	String map_file_path;
	
	// �v���C�x�[�g�֐�
	bool getElement(String str, String search_element_name, String& ret);
	bool getElement(String str, String search_element_name, int& ret);
	bool getElement(String str, String search_element_name, bool& ret);
	bool getTypes(String str, String search_element_name, Array<String>& ret);
};

#endif /* CityMap_hpp */
