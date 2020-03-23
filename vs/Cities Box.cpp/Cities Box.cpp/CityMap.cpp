//
//  CityMap.cpp
//  Cities Box
//
//  Created by YotioSoft on 2019/11/27.
//

#include "CityMap.hpp"


bool CityMap::getElement(String str, String searchElementName, String& ret) {
	string strUTF8 = str.toUTF8();
	string searchElementNameUTF8 = searchElementName.toUTF8();
	
	if (strUTF8.find(searchElementNameUTF8) != string::npos && strUTF8.find("=") != string::npos) {
		ret = Unicode::Widen(strUTF8.substr(strUTF8.find("\"") + 1, strUTF8.find(";") - (strUTF8.find("\"") + 2)));
		return true;
	}
	return false;
}

bool CityMap::getElement(String str, String searchElementName, int& ret) {
	string strUTF8 = str.toUTF8();
	string searchElementNameUTF8 = searchElementName.toUTF8();
	
	if (strUTF8.find(searchElementNameUTF8) != string::npos && strUTF8.find("=") != string::npos) {
		ret = stoi(strUTF8.substr(strUTF8.find("= ") + 2, strUTF8.find(";") - (strUTF8.find("= ") + 2)));
		return true;
	}
	return false;
}

bool CityMap::getElement(String str, String searchElementName, bool& ret) {
	string strUTF8 = str.toUTF8();
	string searchElementNameUTF8 = searchElementName.toUTF8();
	
	if (strUTF8.find(searchElementNameUTF8) != string::npos && strUTF8.find("=") != string::npos) {
		int intTemp = stoi(strUTF8.substr(strUTF8.find("= ") + 2, strUTF8.find(";") - (strUTF8.find("= ") + 2)));
		if (intTemp == 1) {
			ret = true;
			return true;
		}
		else if (intTemp == 0) {
			ret = false;
			return true;
		}
	}
	return false;
}

bool CityMap::getTypes(String str, String searchElementName, Array<String>& ret) {
	String aRet;
	if (getElement(str, searchElementName, aRet)) {
		ret = split(aRet, U", ");
		return true;
	}
	return false;
}


void CityMap::load(String loadMapFilePath) {
	if (FileSystem::Extension(loadMapFilePath) == U"cbd") {
		loadCBD(loadMapFilePath);
	}
	else if (FileSystem::Extension(loadMapFilePath) == U"cbj") {
		loadCBJ(loadMapFilePath);
	}
}

static s3d::String extracted(int i, Array<s3d::String> &workplaceStr) {
	String workplaceAndSerial = workplaceStr[i].substr(1, workplaceStr[i].length()-1);
	return workplaceAndSerial;
}

void CityMap::loadCBD(String loadMapFilePath) {
	// �}�b�v�t�@�C���̓ǂݍ���
	mapFilePath = loadMapFilePath;
	
	TextReader mapData(mapFilePath);
	string strTempUTF8;
	String strTemp;
	
	// �e�v�f�̓ǂݏo��
	string currentArrayName = "";
	Array<string> arrayNames =
	{"name", "name2", "category", "category_2", "category_3", "obj_type", "obj_type2", "obj_dire", "obj_dire2",
		"obj_serial_num", "obj_use_tiles_x", "obj_use_tiles_y", "obj_tiles_x", "obj_tiles_y", "residents",
		"workers_Commercial", "workers_Office", "workers_Industrial", "workers_Farm", "workers_Public",
		"students", "land_price", "crime_rate", "education_rate", "happiness", "noise", "crop", "crop_amount",
		"age", "gender", "workplace", "school", "reservation", "original_name"};
	int arrayCount = 0;
	bool mapCleared = false;
	
	mapsize.width = -1;
	mapsize.height = -1;
	
	bool addonLoaded = false;
	
	while (mapData.readLine(strTemp)) {
		strTemp = strTemp.substr(0, strTemp.length()-LINE_FEED_CODE);				// ���s�R�[�h�͏���
		strTempUTF8 = strTemp.toUTF8();
		
		getElement(strTemp, U"Version", savedVersion);
		getElement(strTemp, U"Addons_Set", addonSet);
		
		// �A�h�I���ǂݍ���
		if (!addonLoaded && addonSet.length() > 0) {
			loadAddons(addonSet);
			addonLoaded = true;
		}
		
		getElement(strTemp, U"City_Name", cityName);
		getElement(strTemp, U"Mayor_Name", mayorName);
		getElement(strTemp, U"Total_Population", totalPopulation);
		getElement(strTemp, U"Set_Change_Weather", changeWeather);
		getElement(strTemp, U"Temperature", temperature);
		getElement(strTemp, U"Set_Dark_on_Night", darkOnNight);
		
		getElement(strTemp, U"mapsize_x", mapsize.width);
		getElement(strTemp, U"mapsize_y", mapsize.height);
		
		getElement(strTemp, U"time_Year", time.year);
		getElement(strTemp, U"time_Month", time.month);
		getElement(strTemp, U"time_Date", time.date);
		getElement(strTemp, U"time_Hour", time.hour);
		getElement(strTemp, U"time_Minutes", time.minutes);
		
		getElement(strTemp, U"demand_Residential", demand.residential);
		getElement(strTemp, U"demand_Commercial", demand.commercial);
		getElement(strTemp, U"demand_Office", demand.office);
		getElement(strTemp, U"demand_Industrial", demand.industrial);
		getElement(strTemp, U"demand_Farm", demand.farm);
		
		getElement(strTemp, U"Money", money);
		
		getElement(strTemp, U"budget_of_Police", budget.police);
		getElement(strTemp, U"budget_of_Fire_Depertment", budget.fireDepertment);
		getElement(strTemp, U"budget_of_Post_Office", budget.postOffice);
		getElement(strTemp, U"budget_of_Education", budget.education);
		
		getElement(strTemp, U"tax_of_Residential", tax.residential);
		getElement(strTemp, U"tax_of_Commercial", tax.commercial);
		getElement(strTemp, U"tax_of_Office", tax.office);
		getElement(strTemp, U"tax_of_Industrial", tax.industrial);
		getElement(strTemp, U"tax_of_Farm", tax.farm);
		
		if (!mapCleared && mapsize.width > 0 && mapsize.height > 0) {
			for (int y=0; y<mapsize.height; y++) {
				SquareStruct new_ss;
				squares.push_back(Array<SquareStruct>(mapsize.width, new_ss));
			}
			mapCleared = true;
		}
		
		for (int i=0; i<arrayNames.size(); i++) {
			if (strTempUTF8.find(arrayNames[i]+"(x,y) {") == 0) {
				currentArrayName = arrayNames[i];
				arrayCount = -1;
			}
		}
		if (strTempUTF8.find("}") == 0) {
			currentArrayName = "";
		}
		
		if (currentArrayName == "name" && arrayCount >= 0) {
			Array<String> temp = split(strTemp, U", ");
			
			for (int x=0; x<mapsize.width; x++) {
				// �}�b�v��Addon_Set����`����Ă��Ȃ��ꍇ��Normal�Ƃ݂Ȃ��A�h�I���ǂݍ���
				if (!addonLoaded) {
					addonSet = U"Normal";
					loadAddons(addonSet);
					addonLoaded = true;
				}
				
				// �A�h�I���̃|�C���^��o�^
				if (addons.find(temp[x]) != addons.end()) {
					squares[arrayCount][x].addons << addons[temp[x]];
					
					//squares[array_count][x].category = squares[array_count][x].addons.back()->getCategories();
				}
			}
		}
		
		if (currentArrayName == "name2" && arrayCount >= 0) {
			Array<String> temp = split(strTemp, U", ");
			
			for (int x=0; x<mapsize.width; x++) {
				if (temp[x].length() == 0) {
					continue;
				}
				
				// �A�h�I���̃|�C���^��o�^
				if (addons.find(temp[x]) != addons.end()) {
					Addon* addon_temp = squares[arrayCount][x].addons[0];
					squares[arrayCount][x].addons.back() = addons[temp[x]];
					squares[arrayCount][x].addons << addon_temp;
					
					cout << squares[arrayCount][x].addons[1]->getName() << endl;
					
					/*Array<String> categories = squares[array_count][x].addons.back()->getCategories();
					for (int i=0; i<categories.size(); i++) {
						squares[array_count][x].category.push_back(categories[i]);
					}*/
				}
			}
		}
		/*
		if (current_array_name == "category" && array_count >= 0) {
			Array<String> temp = split(str_temp, U", ");
			
			for (int x=0; x<mapsize.width; x++) {
				squares[array_count][x].category.push_back(temp[x]);
			}
		}
		
		if (current_array_name == "category_2" && array_count >= 0) {
			Array<String> temp = split(str_temp, U", ");
			
			for (int x=0; x<mapsize.width; x++) {
				squares[array_count][x].category.push_back(temp[x]);
			}
		}
		
		if (current_array_name == "category_3" && array_count >= 0) {
			Array<String> temp = split(str_temp, U", ");
			
			for (int x=0; x<mapsize.width; x++) {
				squares[array_count][x].category.push_back(temp[x]);
			}
		}*/
		
		if (currentArrayName == "obj_type" && arrayCount >= 0) {
			Array<String> temp = split(strTemp, U", ");
			
			for (int x=0; x<mapsize.width; x++) {
				if (squares[arrayCount][x].addons.size() == 2) {
					squares[arrayCount][x].types << squares[arrayCount][x].addons[1]->getTypeName(stoi(temp[x].toUTF8()));	// �Ƃ肠�����������̂�[0]�ɂ�����Ă���
					squares[arrayCount][x].types << squares[arrayCount][x].addons[1]->getTypeName(stoi(temp[x].toUTF8()));
				}
				else {
					squares[arrayCount][x].types << squares[arrayCount][x].addons[0]->getTypeName(stoi(temp[x].toUTF8()));
				}
			}
		}
		
		if (currentArrayName == "obj_type2" && arrayCount >= 0) {
			Array<String> temp = split(strTemp, U", ");
			
			for (int x=0; x<mapsize.width; x++) {
				if (squares[arrayCount][x].addons.size() == 2) {
					squares[arrayCount][x].types[0] = squares[arrayCount][x].addons[0]->getTypeName(stoi(temp[x].toUTF8()));
				}
			}
		}
		
		if (currentArrayName == "obj_dire" && arrayCount >= 0) {
			Array<String> temp = split(strTemp, U", ");
			
			for (int x=0; x<mapsize.width; x++) {
				if (squares[arrayCount][x].addons.size() == 2) {
					squares[arrayCount][x].directions << squares[arrayCount][x].addons[1]->getDirectionName(squares[arrayCount][x].types[1], stoi(temp[x].toUTF8()));	// �Ƃ肠�����������̂�[0]�ɂ�����Ă���
					squares[arrayCount][x].directions << squares[arrayCount][x].addons[1]->getDirectionName(squares[arrayCount][x].types[1], stoi(temp[x].toUTF8()));
				}
				else {
					squares[arrayCount][x].directions << squares[arrayCount][x].addons[0]->getDirectionName(squares[arrayCount][x].types[0], stoi(temp[x].toUTF8()));
				}
			}
		}
		
		if (currentArrayName == "obj_dire2" && arrayCount >= 0) {
			Array<String> temp = split(strTemp, U", ");
			
			for (int x=0; x<mapsize.width; x++) {
				if (squares[arrayCount][x].addons.size() == 2) {
					squares[arrayCount][x].directions[0] = squares[arrayCount][x].addons[0]->getDirectionName(squares[arrayCount][x].types[0], stoi(temp[x].toUTF8()));
				}
			}
		}
		
		if (currentArrayName == "obj_serial_num" && arrayCount >= 0) {
			Array<String> temp = split(strTemp, U", ");
			
			for (int x=0; x<mapsize.width; x++) {
				squares[arrayCount][x].serialNumber = stoi(temp[x].toUTF8());
			}
		}
		/*
		if (current_array_name == "obj_use_tiles_x" && array_count >= 0) {
			Array<String> temp = split(str_temp, U", ");
			
			for (int x=0; x<mapsize.width; x++) {
				squares[array_count][x].use_tiles.x = stoi(temp[x].toUTF8());
				
				if (squares[array_count][x].use_tiles.x == 0) {
					squares[array_count][x].use_tiles.x = 1;
				}
			}
		}
		
		if (current_array_name == "obj_use_tiles_y" && array_count >= 0) {
			Array<String> temp = split(str_temp, U", ");
			
			for (int x=0; x<mapsize.width; x++) {
				squares[array_count][x].use_tiles.y = stoi(temp[x].toUTF8());
				
				if (squares[array_count][x].use_tiles.y == 0) {
					squares[array_count][x].use_tiles.y = 1;
				}
			}
		}
		*/
		if (currentArrayName == "obj_tiles_x" && arrayCount >= 0) {
			Array<String> temp = split(strTemp, U", ");
			
			for (int x=0; x<mapsize.width; x++) {
				squares[arrayCount][x].tilesCount.x = stoi(temp[x].toUTF8());
				
				// obj_tiles_x���C��(r140�ȑO�̃o�[�W�����ŕۑ������ꍇ)
				if (savedVersion <= 140) {
					if (squares[arrayCount][x].addons[0]->getUseTiles(squares[arrayCount][x].types[0], squares[arrayCount][x].directions[0]).x > 0) {
						// ������
						if (squares[arrayCount][x].directions[0] == U"left") {
							
						}
						
						// �����
						if (squares[arrayCount][x].directions[0] == U"top") {
							
						}
						
						// ������
						if (squares[arrayCount][x].directions[0] == U"bottom") {
							
						}
						
						// �E����
						if (squares[arrayCount][x].directions[0] == U"right") {
							squares[arrayCount][x].tilesCount.x += squares[arrayCount][x].addons[0]->getUseTiles(squares[arrayCount][x].types[0], squares[arrayCount][x].directions[0]).x - 1;
						}
					}
				}
			}
		}
		
		if (currentArrayName == "obj_tiles_y" && arrayCount >= 0) {
			Array<String> temp = split(strTemp, U", ");
			
			for (int x=0; x<mapsize.width; x++) {
				squares[arrayCount][x].tilesCount.y = stoi(temp[x].toUTF8());
				
				// obj_tiles_y���C��(r140�ȑO�̃o�[�W�����ŕۑ������ꍇ)
				if (savedVersion <= 140) {
					if (squares[arrayCount][x].addons[0]->getUseTiles(squares[arrayCount][x].types[0], squares[arrayCount][x].directions[0]).y > 0) {
						// ������
						if (squares[arrayCount][x].directions[0] == U"left") {
							
						}
						
						// �����
						if (squares[arrayCount][x].directions[0] == U"top") {
							squares[arrayCount][x].tilesCount.y = squares[arrayCount][x].addons[0]->getUseTiles(squares[arrayCount][x].types[0], squares[arrayCount][x].directions[0]).y - 1 - squares[arrayCount][x].tilesCount.y;
						}
						
						// ������
						if (squares[arrayCount][x].directions[0] == U"bottom") {
							squares[arrayCount][x].tilesCount.y = abs(squares[arrayCount][x].tilesCount.y);
						}
						
						// �E����
						if (squares[arrayCount][x].directions[0] == U"right") {
							squares[arrayCount][x].tilesCount.y = squares[arrayCount][x].addons[0]->getUseTiles(squares[arrayCount][x].types[0], squares[arrayCount][x].directions[0]).y - 1 - squares[arrayCount][x].tilesCount.y;
						}
					}
				}
			}
		}
		
		if (currentArrayName == "residents" && arrayCount >= 0) {
			Array<String> temp = split(strTemp, U", ");
			
			for (int x=0; x<mapsize.width; x++) {
				squares[arrayCount][x].residents = stoi(temp[x].toUTF8());
			}
		}
		
		if (currentArrayName == "workers_Commercial" && arrayCount >= 0) {
			Array<String> temp = split(strTemp, U", ");
			
			for (int x=0; x<mapsize.width; x++) {
				squares[arrayCount][x].workers.commercial = stoi(temp[x].toUTF8());
			}
		}
		
		if (currentArrayName == "workers_Office" && arrayCount >= 0) {
			Array<String> temp = split(strTemp, U", ");
			
			for (int x=0; x<mapsize.width; x++) {
				squares[arrayCount][x].workers.office = stoi(temp[x].toUTF8());
			}
		}
		
		if (currentArrayName == "workers_Industrial" && arrayCount >= 0) {
			Array<String> temp = split(strTemp, U", ");
			
			for (int x=0; x<mapsize.width; x++) {
				squares[arrayCount][x].workers.industrial = stoi(temp[x].toUTF8());
			}
		}
		
		if (currentArrayName == "workers_Farm" && arrayCount >= 0) {
			Array<String> temp = split(strTemp, U", ");
			
			for (int x=0; x<mapsize.width; x++) {
				squares[arrayCount][x].workers.farm = stoi(temp[x].toUTF8());
			}
		}
		
		if (currentArrayName == "workers_Public" && arrayCount >= 0) {
			Array<String> temp = split(strTemp, U", ");
			
			for (int x=0; x<mapsize.width; x++) {
				squares[arrayCount][x].workers.publicFacility = stoi(temp[x].toUTF8());
			}
		}
		
		if (currentArrayName == "students" && arrayCount >= 0) {
			Array<String> temp = split(strTemp, U", ");
			
			for (int x=0; x<mapsize.width; x++) {
				squares[arrayCount][x].students = stoi(temp[x].toUTF8());
			}
		}
		
		if (currentArrayName == "land_price" && arrayCount >= 0) {
			Array<String> temp = split(strTemp, U", ");
			
			for (int x=0; x<mapsize.width; x++) {
				squares[arrayCount][x].rate[U"land_price"] = stoi(temp[x].toUTF8());
			}
		}
		
		if (currentArrayName == "happiness" && arrayCount >= 0) {
			Array<String> temp = split(strTemp, U", ");
			
			for (int x=0; x<mapsize.width; x++) {
				squares[arrayCount][x].rate[U"happiness_rate"] = stoi(temp[x].toUTF8());
			}
		}
		
		if (currentArrayName == "crime_rate" && arrayCount >= 0) {
			Array<String> temp = split(strTemp, U", ");
			
			for (int x=0; x<mapsize.width; x++) {
				squares[arrayCount][x].rate[U"crime_rate"] = stoi(temp[x].toUTF8());
			}
		}
		
		if (currentArrayName == "happiness" && arrayCount >= 0) {
			Array<String> temp = split(strTemp, U", ");
			
			for (int x=0; x<mapsize.width; x++) {
				squares[arrayCount][x].rate[U"happiness_rate"] = stoi(temp[x].toUTF8());
			}
		}
		
		if (currentArrayName == "education_rate" && arrayCount >= 0) {
			Array<String> temp = split(strTemp, U", ");
			
			for (int x=0; x<mapsize.width; x++) {
				squares[arrayCount][x].rate[U"education_rate"] = stoi(temp[x].toUTF8());
			}
		}
		/*
		if (current_array_name == "crop" && array_count >= 0) {
			Array<String> temp = split(str_temp, U", ");
			
			for (int x=0; x<mapsize.width; x++) {
				squares[array_count][x].crop.name = temp[x];
			}
		}
		
		if (current_array_name == "crop_amount" && array_count >= 0) {
			Array<String> temp = split(str_temp, U", ");
			
			for (int x=0; x<mapsize.width; x++) {
				squares[array_count][x].crop.amount = stoi(temp[x].toUTF8());
			}
		}
		*/
		if (currentArrayName == "age" && arrayCount >= 0) {
			Array<String> temp = split(strTemp, U", ");
			
			for (int x=0; x<mapsize.width; x++) {
				Array<String> agesStr = split(temp[x], U"]");
				
				for (int i=0; i<agesStr.size(); i++) {
					if (agesStr[i].length() <= 1 || agesStr[i] == U" ") {
						continue;
					}
					squares[arrayCount][x].age.push_back(stoi(agesStr[i].substr(1, agesStr[i].length()-1).toUTF8()));
				}
			}
		}
		
		if (currentArrayName == "gender" && arrayCount >= 0) {
			Array<String> temp = split(strTemp, U", ");
			
			for (int x=0; x<mapsize.width; x++) {
				Array<String> genderStr = split(temp[x], U"]");
				
				for (int i=0; i<genderStr.size(); i++) {
					if (genderStr[i].length() <= 1 || genderStr[i] == U" ") {
						continue;
					}
					squares[arrayCount][x].gender.push_back(genderStr[i].substr(1, genderStr[i].length()-1));
				}
			}
		}
		
		if (currentArrayName == "workplace" && arrayCount >= 0) {
			Array<String> temp = split(strTemp, U", ");
			
			for (int x=0; x<mapsize.width; x++) {
				Array<String> workPlaceStr = split(temp[x], U"]");
				
				for (int i=0; i<workPlaceStr.size(); i++) {
					if (workPlaceStr[i].length() <= 1 || workPlaceStr[i] == U" ") {
						continue;
					}
					s3d::String workPlaceAndSerial = extracted(i, workPlaceStr);
					
					WorkPlaceStruct workPlace;
					if (workPlaceAndSerial.substr(0, 1) == U"c") {
						workPlace.workPlace = RCOIFP::Commercial;
					}
					else if (workPlaceAndSerial.substr(0, 1) == U"o") {
						workPlace.workPlace = RCOIFP::Office;
					}
					else if (workPlaceAndSerial.substr(0, 1) == U"i") {
						workPlace.workPlace = RCOIFP::Industrial;
					}
					else if (workPlaceAndSerial.substr(0, 1) == U"f") {
						workPlace.workPlace = RCOIFP::Farm;
					}
					else if (workPlaceAndSerial.substr(0, 1) == U"p") {
						workPlace.workPlace = RCOIFP::Public;
					}
					
					workPlace.workPlacesSerialNumber = stoi(workPlaceAndSerial.substr(1, workPlaceAndSerial.length()-1).toUTF8());
					
					squares[arrayCount][x].workPlaces.push_back(workPlace);
				}
			}
		}
		
		if (currentArrayName == "school" && arrayCount >= 0) {
			Array<String> temp = split(strTemp, U", ");
			
			for (int x=0; x<mapsize.width; x++) {
				Array<String> schoolStr = split(temp[x], U"]");
				
				for (int i=0; i<schoolStr.size(); i++) {
					if (schoolStr[i].length() <= 1 || schoolStr[i] == U" ") {
						continue;
					}
					String schoolAndSerial = schoolStr[i].substr(1, schoolStr[i].length()-1);
					
					SchoolStruct school;
					if (schoolAndSerial.substr(0, 1) == U"e") {
						school.school = School::ElementarySchool;
					}
					else if (schoolAndSerial.substr(0, 1) == U"j") {
						school.school = School::JuniorHighSchool;
					}
					else if (schoolAndSerial.substr(0, 1) == U"h") {
						school.school = School::HighSchool;
					}
					else if (schoolAndSerial.substr(0, 1) == U"U") {
						school.school = School::University;
					}
					
					school.schoolSerialNumber = stoi(schoolAndSerial.substr(1, schoolAndSerial.length()-1).toUTF8());
					
					squares[arrayCount][x].schools.push_back(school);				}
			}
		}
		
		if (currentArrayName == "reservation" && arrayCount >= 0) {
			Array<String> temp = split(strTemp, U", ");
			
			for (int x=0; x<mapsize.width; x++) {
				if (temp[x] == U"none") {
					squares[arrayCount][x].reservation = RCOIFP::None;
				}
				else if (temp[x] == U"residential") {
					squares[arrayCount][x].reservation = RCOIFP::Residential;
				}
				else if (temp[x] == U"commercial") {
					squares[arrayCount][x].reservation = RCOIFP::Commercial;
				}
				else if (temp[x] == U"office") {
					squares[arrayCount][x].reservation = RCOIFP::Office;
				}
				else if (temp[x] == U"industrial") {
					squares[arrayCount][x].reservation = RCOIFP::Industrial;
				}
				else if (temp[x] == U"farm") {
					squares[arrayCount][x].reservation = RCOIFP::Farm;
				}
				else if (temp[x] == U"public") {
					squares[arrayCount][x].reservation = RCOIFP::Public;
				}
			}
		}
		
		if (currentArrayName == "original_name" && arrayCount >= 0) {
			Array<String> temp = split(strTemp, U", ");
			
			for (int x=0; x<mapsize.width; x++) {
				squares[arrayCount][x].originalName = temp[x];
			}
		}
		
		arrayCount ++;
	}
	
	System::ShowMessageBox(U"���`���̃}�b�v�f�[�^(*.cbd)���ǂݍ��܂�܂����B\n�ۑ����͐V�`��(*.cbj)�ŕۑ�����܂��B", MessageBoxStyle::Warning, MessageBoxButtons::OK);
}

void CityMap::loadCBJ(String loadMapFilePath) {
	mapFilePath = loadMapFilePath;
	
	ifstream ifs(mapFilePath.toUTF8().c_str(), ios::in | ios::binary);
	
	std::string mapXOR((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	string mapDataStr = stringXOR(mapXOR, "citiesboxmapdatafilexor");
	
	saveTextFile("./data/map_temp.cbj_temp", mapDataStr);
	
	JSONReader mapData(U"./data/map_temp.cbj_temp");
	//remove("./data/map_temp.cbj_temp");
	
	savedVersion = mapData[U"Version"].get<int>();
	
	addonSet = mapData[U"Addon_Set"].getString();
	// -> �A�h�I���ǂݍ���
	loadAddons(addonSet);
	
	cityName = mapData[U"City_Name"].getString();
	
	mayorName = mapData[U"Mayor_Name"].getString();
	
	totalPopulation = mapData[U"Total_Population"].get<int>();
	
	changeWeather = mapData[U"Change_Weather"].get<bool>();
	
	temperature = mapData[U"Temperature"].get<int>();
	
	darkOnNight = mapData[U"Dark_on_Night"].get<bool>();
	
	mapsize.width = mapData[U"Map_size.width"].get<int>();
	mapsize.height = mapData[U"Map_size.height"].get<int>();
	
	time.year = mapData[U"Time.year"].get<int>();
	time.month = mapData[U"Time.month"].get<int>();
	time.date = mapData[U"Time.date"].get<int>();
	time.hour = mapData[U"Time.hour"].get<int>();
	time.minutes = mapData[U"Time.minutes"].get<int>();
	
	demand.residential = mapData[U"Demand.residential"].get<int>();
	demand.commercial = mapData[U"Demand.commercial"].get<int>();
	demand.office = mapData[U"Demand.office"].get<int>();
	demand.industrial = mapData[U"Demand.industrial"].get<int>();
	demand.farm = mapData[U"Demand.farm"].get<int>();
	
	money = mapData[U"Money"].get<int>();
	
	budget.police = mapData[U"Budget.police"].get<int>();
	budget.fireDepertment = mapData[U"Budget.fire_depertment"].get<int>();
	budget.postOffice = mapData[U"Budget.post_office"].get<int>();
	budget.education = mapData[U"Budget.education"].get<int>();
	
	tax.residential = mapData[U"Tax.residential"].get<int>();
	tax.commercial = mapData[U"Tax.commercial"].get<int>();
	tax.office = mapData[U"Tax.office"].get<int>();
	tax.industrial = mapData[U"Tax.industrial"].get<int>();
	tax.farm = mapData[U"Tax.farm"].get<int>();
	
	int y = 0;
	for (const auto& mapSquares : mapData[U"Map"].arrayView()) {
		squares.push_back(Array<SquareStruct>());
		int x = 0;
		for (const auto& square : mapSquares.arrayView()) {
			squares[y].push_back(SquareStruct());
			
			for (const auto& jAddons : square[U"addons"].arrayView()) {
				//squares[y][x].category.push_back(j_addons[U"category"].getString());
				squares[y][x].types.push_back(jAddons[U"type_number"].getString());
				squares[y][x].directions.push_back(jAddons[U"direction_number"].getString());
				
				// �A�h�I���̃|�C���^��o�^
				if (addons.find(jAddons[U"name"].getString()) != addons.end()) {
					squares[y][x].addons.push_back(addons[jAddons[U"name"].getString()]);
				}
				else {
					cout << "Cant't find " << jAddons[U"name"].getString() << endl;
				}
			}
			
			//squares[y][x].use_tiles.x = square[U"use_tiles.x"].get<int>();
			//squares[y][x].use_tiles.y = square[U"use_tiles.y"].get<int>();
			
			squares[y][x].tilesCount.x = square[U"tiles_count.x"].get<int>();
			squares[y][x].tilesCount.y = square[U"tiles_count.y"].get<int>();
			
			squares[y][x].serialNumber = square[U"serial_number"].get<int>();
			
			squares[y][x].residents = square[U"residents"].get<int>();
			
			squares[y][x].workers.commercial = square[U"workers.commercial"].get<int>();
			squares[y][x].workers.office = square[U"workers.office"].get<int>();
			squares[y][x].workers.industrial = square[U"workers.industrial"].get<int>();
			squares[y][x].workers.farm = square[U"workers.farm"].get<int>();
			squares[y][x].workers.publicFacility = square[U"workers.public"].get<int>();
			
			squares[y][x].students = square[U"students"].get<int>();
			
			squares[y][x].happinessRate = square[U"happiness_rate"].get<int>();
			
			// �e���̓ǂݍ���
			for (const auto& rate : square[U"rate"].objectView()) {
				squares[y][x].rate[rate.name] = rate.value.get<int>();
			}
			
			/*
			squares[y][x].crop.name = square[U"crop.name"].getString();
			squares[y][x].crop.amount = square[U"crop.amount"].get<int>();
			*/
			
			squares[y][x].age = square[U"age"].getArray<int>();
			
			squares[y][x].gender = square[U"gender"].getArray<String>();
			
			for (const auto& workPlaces : square[U"work_places"].arrayView()) {
				squares[y][x].workPlaces.push_back(WorkPlaceStruct());
				
				squares[y][x].workPlaces.back().workPlace = getRCOIFP(workPlaces[U"work_kind"].get<int>());
				squares[y][x].workPlaces.back().workPlacesSerialNumber = workPlaces[U"serial_number"].get<int>();
			}
			
			for (const auto& schools : square[U"school"].arrayView()) {
				squares[y][x].schools.push_back(SchoolStruct());
				
				squares[y][x].schools.back().school = getSchool(schools[U"school_kind"].get<int>());
				squares[y][x].schools.back().schoolSerialNumber = schools[U"serial_number"].get<int>();
			}
			
			squares[y][x].reservation = getRCOIFP(square[U"reservation"].get<int>());
			
			squares[y][x].originalName = square[U"original_name"].getString();
			
			x++;
		}
		y++;
	}
}

void CityMap::loadAddons(String addonSetName) {
	//Array<FileStruct> addons_path = specific::getAllFilesName("./addons", "adat");
	Array<FileStruct> addonsPath = specific::getAllFilesName("./addons", "adj");
	
	for (int i=0; i<addonsPath.size(); i++) {
		FileStruct fileTemp = addonsPath[i];
		
		cout << fileTemp.file_path << endl;
		
		Addon* loadingAddon = new Addon();
		if (loadingAddon->load(addonsPath[i], addonSetName)) {
			addons[loadingAddon->getName()] = loadingAddon;
		}
		else {
			delete(loadingAddon);
		}
		
		System::Sleep(20);
	}
}

Array<Addon*> CityMap::getFitAddons(Array<String> selectedCategories) {
	Array<Addon*> retAddons;
	
	for (auto addon = addons.begin(); addon != addons.end(); addon++) {
		
		Array<String> anAddonCategories = addon->second->getCategories();
		vector<bool> fit = vector<bool>(selectedCategories.size(), false);
		
		for (auto categoryName = anAddonCategories.begin(); categoryName != anAddonCategories.end(); categoryName++) {
			for (int i=0; i<selectedCategories.size(); i++) {
				if (selectedCategories[i] == *categoryName) {
					fit[i] = true;
					break;
				}
			}
		}
		
		bool fitted = true;
		for (int i=0; i<fit.size(); i++) {
			if (!fit[i]) {
				fitted = false;
			}
		}
		if (fitted) {
			retAddons << addon->second;
		}
	}
	
	return retAddons;
}

map<String, Addon*> CityMap::getAllAddons() {
	return addons;
}

void CityMap::drawSquare(CoordinateStruct coordinate, CameraStruct camera) {
	// �`�悷����W���Z�o
	for (int i=0; i<(int)squares[coordinate.y][coordinate.x].addons.size(); i++) {
		int rate;
		Color rateColor(0, 0, 0, 0);
		if (showRate.length() > 0) {
			rate = getRate(coordinate, showRate);
			if (showRate == U"crime_rate") {
				rateColor = getRateColor(rate, false, 0);
			}
			else {
				rateColor = getRateColor(rate, true, 50);
			}
		}
		
		squares[coordinate.y][coordinate.x].addons[i]->draw(squares[coordinate.y][coordinate.x].types[i], squares[coordinate.y][coordinate.x].directions[i], coordinateToPosition(coordinate, camera), squares[coordinate.y][coordinate.x].addons[i]->getUseTiles(squares[coordinate.y][coordinate.x].types[i], squares[coordinate.y][coordinate.x].directions[i]), squares[coordinate.y][coordinate.x].tilesCount, &rateColor);
	}
}

void CityMap::draw(CameraStruct camera, CursorStruct& cursor) {
	// �}�b�v��`��
	for (short int y=getDrawArea(camera).first.y; y<getDrawArea(camera).second.y; y++) {
		for (short int x=getDrawArea(camera).first.x; x<getDrawArea(camera).second.x; x++) {
			PositionStruct drawPos = coordinateToPosition(CoordinateStruct{x, y}, camera);
			
			// ��}�X���`��
			if (drawPos.x >= -CHIP_SIZE && drawPos.y >= -CHIP_SIZE/2 && drawPos.x <= Scene::Width() && drawPos.y <= Scene::Height() + CHIP_SIZE*2) {
				drawSquare(CoordinateStruct{x, y}, camera);
			}
			
			// �J�[�\���̕`��
			if (x == cursor.coordinate.x && y == cursor.coordinate.y) {
				cursor.texture->draw(cursor.position_per_tiles.x, cursor.position_per_tiles.y, Alpha(128));
			}
		}
	}
}

Array<Addon> CityMap::getAddon(CoordinateStruct coordinate) {
	Array<Addon> retAddons;
	
	for (int i=0; i<squares[coordinate.y][coordinate.x].addons.size(); i++) {
		retAddons << *(squares[coordinate.y][coordinate.x].addons[i]);
	}
	
	return retAddons;
}

RCOIFstruct CityMap::getDemand() {
	return demand;
}

int CityMap::getPopulation() {
	return totalPopulation;
}

int CityMap::getMoney() {
	return money;
}

int CityMap::getTemperature() {
	return temperature;
}

SizeStruct CityMap::getMapSize() {
	return mapsize;
}

PositionStruct CityMap::coordinateToPosition(CoordinateStruct coordinate, CameraStruct camera) {
	// �J�����̍��W���f�t�H���g�l�i64*mapsize.width/2-Scene::Width()/2, 0�j�̂Ƃ��̕`��ʒu���Z�o
	CameraStruct defaultCamera;
	defaultCamera.position = PositionStruct{0, 0};
	defaultCamera.center = {0, 0};
	
	// ��_�ƂȂ�x:0, y:0�̃}�X�̕\���ʒu���Z�o����
	PositionStruct square0x0Position = PositionStruct{defaultCamera.position.x - camera.position.x,
		defaultCamera.position.y - camera.position.y};
	
	PositionStruct squarePosition = PositionStruct{square0x0Position.x+coordinate.x*32-coordinate.y*32, square0x0Position.y+coordinate.y*16+coordinate.x*16};
	
	return squarePosition;
}

CoordinateStruct CityMap::positionToCoordinate(PositionStruct position, CameraStruct camera) {
	int tempMX = position.x+camera.position.x-CHIP_SIZE/2;
	int tempMY = position.y+camera.position.y;
	
	CoordinateStruct ret;
	ret.x = (tempMY + tempMX/2) / (CHIP_SIZE/2);
	ret.y = (-tempMX + tempMY*2) / CHIP_SIZE;
	
	if (ret.x < 0) {
		ret.x = 0;
	}
	if (ret.y < 0) {
		ret.y = 0;
	}
	
	if (ret.x >= mapsize.width) {
		ret.x = mapsize.width-1;
	}
	if (ret.y >= mapsize.height) {
		ret.y = mapsize.height-1;
	}
	
	return ret;
}

pair<CoordinateStruct, CoordinateStruct> CityMap::getDrawArea(CameraStruct camera) {
	// �J�����̍��W���ς���Ă��Ȃ����range��Ԃ�
	if (camera.position.x == cameraBefore.position.x && camera.position.y == cameraBefore.position.y) {
		return range;
	}
	cameraBefore = camera;
	
	// �`��ł���͈�
	int rangeOneDirection = (sqrt(powf(Scene::Width(), 2)+powf(Scene::Height(), 2))/sqrt(powf(CHIP_SIZE/2, 2)+powf(CHIP_SIZE/4, 2)));
	
	// ��ʒ����̍��W
	CoordinateStruct centerCoordinate = positionToCoordinate(PositionStruct{Scene::Width()/2, Scene::Height()/2}, camera);
	
	pair<CoordinateStruct, CoordinateStruct> ret;
	// ����̍��W
	ret.first = CoordinateStruct{centerCoordinate.x-rangeOneDirection, centerCoordinate.y-rangeOneDirection};
	
	if (ret.first.x < 0) {
		ret.first.x = 0;
	}
	if (ret.first.y < 0) {
		ret.first.y = 0;
	}
	if (ret.first.x >= mapsize.width) {
		ret.first.x = mapsize.width-1;
	}
	if (ret.first.y >= mapsize.height) {
		ret.first.y = mapsize.height-1;
	}
	
	// �E���̍��W
	ret.second = CoordinateStruct{centerCoordinate.x+rangeOneDirection, centerCoordinate.y+rangeOneDirection};
	
	if (ret.second.x < 0) {
		ret.second.x = 0;
	}
	if (ret.second.y < 0) {
		ret.second.y = 0;
	}
	if (ret.second.x >= mapsize.width) {
		ret.second.x = mapsize.width-1;
	}
	if (ret.second.y >= mapsize.height) {
		ret.second.y = mapsize.height-1;
	}
	
	range = ret;
	
	return ret;
}

// �����ꂩ�̃A�h�I�����J�e�S���Ɋ܂܂�Ă��邩
bool CityMap::isInCategories(String searchCategory, CoordinateStruct coordinate) {
	SquareStruct* currentSquare = &squares[coordinate.y][coordinate.x];
	
	for (int i=0; i<currentSquare->addons.size(); i++) {
		if (currentSquare->addons[i]->isInCategories(searchCategory)) {
			return true;
		}
	}
	
	return false;
}

// �A�h�I���̐ݒu
bool CityMap::build(CoordinateStruct position, Addon* selectedAddon, bool needToBreak) {
	SquareStruct* currentSquare = &squares[position.y][position.x];
	
	String type, direction;
	Array<CoordinateStruct> needUpdate;
	if (getBuildTypeAndDirection(position, selectedAddon, type, direction, needUpdate)) {
		CoordinateStruct useTiles = selectedAddon->getUseTiles(type, direction);
		
		if (direction == U"left") {
			position.y += useTiles.y-1;
		}
		if (direction == U"right") {
			position.x -= useTiles.x-1;
			position.y += useTiles.y-1;
		}
		else if (direction == U"top") {
			position.y += useTiles.y-1;
		}
		
		// ���ʂ��擾
		map<String, EffectStruct> effects = selectedAddon->getEffects();
		
		// �����ƂȂ���W���擾
		int centerX = useTiles.x/2;
		int centerY = useTiles.y/2;
		
		for (int y=0; abs(y)<useTiles.y; y--) {
			for (int x=0; abs(x)<useTiles.x; x++) {
				if (needToBreak && type != U"train_crossing" && type != U"bridge") {
					breaking(CoordinateStruct{position.x+x, position.y+y});
				}
				
				currentSquare = &squares[position.y+y][position.x+x];
				
				if (type != U"train_crossing" && type != U"bridge") {
					currentSquare->addons.clear();
					currentSquare->types.clear();
					currentSquare->directions.clear();
				}
				
				currentSquare->types << type;
				currentSquare->directions << direction;
				
				currentSquare->serialNumber = 0;
				
				currentSquare->tilesCount = {abs(x), abs(y)};
				
				currentSquare->residents = 0;
				currentSquare->workers = {0, 0, 0, 0, 0};
				currentSquare->students = 0;
				currentSquare->reservation = RCOIFP::None;
				
				currentSquare->addons << selectedAddon;
				
				// ���ʂ�n�}�֔��f
				if (abs(x) == centerX && abs(y) == centerY) {
					for (auto effect = effects.begin(); effect != effects.end(); effect++) {
						double effectPerGrid = effect->second.influence / effect->second.grid;
						for (int ey=-effect->second.grid; ey<=effect->second.grid; ey++) {
							for (int ex=-effect->second.grid; ex<=effect->second.grid; ex++) {
								if (isPositionAvailable(CoordinateStruct{position.x+x+ex, position.y+y+ey})) {
									squares[position.y+y+ey][position.x+x+ex].rate[effect->first] += effectPerGrid*max(abs(effect->second.grid-1-ey), abs(effect->second.grid-1-ex));
								}
							}
						}
					}
				}
			}
		}
		
		// (���H�Ȃǂ�)���͂̃A�h�I���̏C�����K�v�ȏꍇ�͏C������
		if (needUpdate.size() > 0) {
			Array<String> searchCategories = {U"road", U"train", U"waterway"};
			
			for (int i=0; i<needUpdate.size(); i++) {
				
				if (needUpdate[i].x < 0 || needUpdate[i].y < 0) {
					continue;
				}
				
				for (int j=0; j<squares[needUpdate[i].y][needUpdate[i].x].addons.size(); j++) {
					if (squares[needUpdate[i].y][needUpdate[i].x].addons[j]->isInCategories(searchCategories)) {
						if (!(needUpdate[j].x == -1 && needUpdate[j].y == -1)) {
							cout << "update for " << needUpdate[i].x << "," << needUpdate[i].y << endl;
							update(needUpdate[i], squares[needUpdate[i].y][needUpdate[i].x].addons[j], needUpdate);
						}
					}
				}
			}
		}
	}
	
	return true;
}

void CityMap::update(CoordinateStruct position, Addon* selectedAddon, Array<CoordinateStruct>& needUpdate) {
	SquareStruct* currentSquare = &squares[position.y][position.x];
	
	// ���؂Ƌ��̏ꍇ�͍X�V�s�v
	for (int i=0; i<currentSquare->types.size(); i++) {
		if (currentSquare->types[i] == U"train_crossing" || currentSquare->types[i] == U"bridge") {
			return;
		}
	}
	
	String type, direction;
	if (getBuildTypeAndDirection(position, selectedAddon, type, direction, needUpdate)) {
		currentSquare->addons.clear();
		currentSquare->types.clear();
		currentSquare->directions.clear();
		
		currentSquare->types << type;
		currentSquare->directions << direction;
		
		currentSquare->serialNumber = 0;
		currentSquare->tilesCount = {0, 0};
		currentSquare->residents = 0;
		currentSquare->workers = {0, 0, 0, 0, 0};
		currentSquare->students = 0;
		currentSquare->reservation = RCOIFP::None;
		
		currentSquare->addons << selectedAddon;
	}
}

void CityMap::breaking(CoordinateStruct coordinate) {
	SquareStruct* currentSquare = &squares[coordinate.y][coordinate.x];
	Array<Addon*> breakAddons = currentSquare->addons;
	
	for (int i=0; i<breakAddons.size(); i++) {
		currentSquare = &squares[coordinate.y][coordinate.x];
		CoordinateStruct useTiles = breakAddons[i]->getUseTiles(currentSquare->types[i], currentSquare->directions[i]);
		
		CoordinateStruct startPoint = moveToAddonStartSquare(coordinate, i);
		currentSquare = &squares[startPoint.y][startPoint.x];
		
		// ���ʂ��擾
		map<String, EffectStruct> effects = breakAddons[i]->getEffects();
		
		// �����ƂȂ���W���擾
		int centerX = useTiles.x/2;
		int centerY = useTiles.y/2;
		
		for (int y=0; abs(y)<useTiles.y; y--) {
			for (int x=0; x<useTiles.x; x++) {
				SquareStruct beforeBreak = squares[startPoint.y+y][startPoint.x+x];
				build(CoordinateStruct{startPoint.x+x, startPoint.y+y}, addons[U"tile_greenfield"], false);
				
				// ���ʂ�����
				if (abs(x) == centerX && abs(y) == centerY) {
					for (auto effect = effects.begin(); effect != effects.end(); effect++) {
						double effectPerGrid = effect->second.influence / effect->second.grid;
						for (int ey=-effect->second.grid; ey<=effect->second.grid; ey++) {
							for (int ex=-effect->second.grid; ex<=effect->second.grid; ex++) {
								if (isPositionAvailable(CoordinateStruct{startPoint.x+x+ex, startPoint.y+y+ey})) {
									squares[startPoint.y+y+ey][startPoint.x+x+ex].rate[effect->first] -= effectPerGrid*max(abs(effect->second.grid-1-ey), abs(effect->second.grid-1-ex));
								}
							}
						}
					}
				}
				
				if (beforeBreak.addons[i]->isInCategories(U"connectable_type")) {
					Array<CoordinateStruct> needUpdate;
					
					for (int j=0; j<AROUND_TILES; j++) {
						for (int k=0; k<squares[startPoint.y+y+AroundTiles[j].second.y][startPoint.x+x+AroundTiles[j].second.x].addons.size(); k++) {
							if ((beforeBreak.addons[i]->isInCategories(U"road") && squares[startPoint.y+y+AroundTiles[j].second.y][startPoint.x+x+AroundTiles[j].second.x].addons[k]->isInCategories(U"road")) ||
								(beforeBreak.addons[i]->isInCategories(U"train") && squares[startPoint.y+y+AroundTiles[j].second.y][startPoint.x+x+AroundTiles[j].second.x].addons[k]->isInCategories(U"train")) ||
								(beforeBreak.addons[i]->isInCategories(U"waterway") && squares[startPoint.y+y+AroundTiles[j].second.y][startPoint.x+x+AroundTiles[j].second.x].addons[k]->isInCategories(U"waterway")) ||
								(beforeBreak.addons[i]->isInCategories(U"airport") && squares[startPoint.y+y+AroundTiles[j].second.y][startPoint.x+x+AroundTiles[j].second.x].addons[k]->isInCategories(U"airport"))) {
								needUpdate << CoordinateStruct{startPoint.x+x+AroundTiles[j].second.x, startPoint.y+y+AroundTiles[j].second.y};
							}
						}
					}
					
					if (breakAddons[i]->isInCategories(U"road")) {
						for (int j=0; j<needUpdate.size(); j++) {
							if (squares[needUpdate[j].y][needUpdate[j].x].addons[i]->isInCategories(U"railroad")) {
								needUpdate[j] = {-1, -1};
							}
						}
					}
					
					for (int j=0; j<needUpdate.size(); j++) {
						for (int k=0; k<squares[startPoint.y+y+AroundTiles[j].second.y][startPoint.x+x+AroundTiles[j].second.x].addons.size(); k++) {
							if (!(needUpdate[j].x == -1 && needUpdate[j].y == -1)) {
								cout << "breaking update: " << needUpdate[j].x << "," << needUpdate[j].y << endl;
								update(needUpdate[j], squares[needUpdate[j].y][needUpdate[j].x].addons[k], needUpdate);
							}
						}
					}
					
				}
			}
		}
	}
}

CoordinateStruct CityMap::moveToAddonStartSquare(CoordinateStruct searchCoordinate, int addonNumber) {
	SquareStruct* searchSquare = &squares[searchCoordinate.y][searchCoordinate.x];
	
	searchCoordinate.x -= searchSquare->tilesCount.x;
	searchCoordinate.y += searchSquare->tilesCount.y;
	
	return CoordinateStruct{searchCoordinate.x, searchCoordinate.y};
}

// �ݒu����ꏊ�ɍ���Type��Direction���擾
bool CityMap::getBuildTypeAndDirection(CoordinateStruct coordinate, Addon* selectedAddon, String& retType, String& retDirection, Array<CoordinateStruct>& needUpdate) {
	// �ڑ��^�C�v�i���H�Ȃǁj�A�h�I���̏ꍇ
	if (selectedAddon->isInCategories(U"connectable_type")) {
		// ���͂ɓ��H�����邩�i���݉\���j�m�F����
		int totalAroundRoad = 0;
		Array<pair<String, CoordinateStruct>> aroundRoadCoordinate;
		
		bool needUpdateMore = true;
		if (needUpdate.size() > 0) {
			needUpdateMore = false;
		}
		
		for (int i=0; i<AROUND_TILES; i++) {
			CoordinateStruct currentSquare = {coordinate.x+AroundTiles[i].second.x, coordinate.y+AroundTiles[i].second.y};
			
			if (currentSquare.x < 0 || currentSquare.y < 0 || currentSquare.x >= mapsize.width || currentSquare.y >= mapsize.height) {
				continue;
			}
			
			for (int j=0; j<squares[currentSquare.y][currentSquare.x].addons.size(); j++) {
				// ���H�̏ꍇ
				if ((selectedAddon->isInCategories(U"road") && squares[currentSquare.y][currentSquare.x].addons[j]->isInCategories(U"road")) ||
					(selectedAddon->isInCategories(U"train") && squares[currentSquare.y][currentSquare.x].addons[j]->isInCategories(U"train")) ||
					(selectedAddon->isInCategories(U"waterway") && squares[currentSquare.y][currentSquare.x].addons[j]->isInCategories(U"waterway")) ||
					(selectedAddon->isInCategories(U"airport") && squares[currentSquare.y][currentSquare.x].addons[j]->isInCategories(U"airport"))) {
					totalAroundRoad ++;
					aroundRoadCoordinate << AroundTiles[i];
					
					if (needUpdateMore) {
						needUpdate << currentSquare;
					}
					
					break;
				}
			}
		}
		
		// ���؂�ݒu����K�v������ꍇ
		if (selectedAddon->isInCategories(U"road")) {
			for (int i=0; i<squares[coordinate.y][coordinate.x].addons.size(); i++) {
				if (squares[coordinate.y][coordinate.x].addons[i]->isInCategories(U"railroad")) {
					retType = U"train_crossing";
					
					if (squares[coordinate.y][coordinate.x].directions[i] == U"width") {
						retDirection = U"width";
					}
					else {
						retDirection = U"depth";
					}
					
					for (int j=0; j<needUpdate.size(); j++) {
						if (squares[needUpdate[j].y][needUpdate[j].x].addons[i]->isInCategories(U"railroad")) {
							needUpdate[j] = {-1, -1};
						}
					}
					
					return true;
				}
			}
		}
		
		// ����ݒu����K�v������ꍇ
		if (selectedAddon->isInCategories(U"road")) {
			for (int i=0; i<squares[coordinate.y][coordinate.x].addons.size(); i++) {
				if (squares[coordinate.y][coordinate.x].addons[i]->isInCategories(U"waterway")) {
					retType = U"bridge";
					
					if (squares[coordinate.y][coordinate.x].directions[i] == U"width") {
						retDirection = U"depth";
					}
					else {
						retDirection = U"width";
					}
					
					for (int j=0; j<needUpdate.size(); j++) {
						if (squares[needUpdate[j].y][needUpdate[j].x].addons[i]->isInCategories(U"waterway")) {
							needUpdate[j] = {-1, -1};
						}
					}
					
					return true;
				}
			}
		}
		
		// ���̑�
		if (totalAroundRoad == 0) {
			retType = U"intersection_cross";
			retDirection = U"normal";
			return true;
		}
		if (totalAroundRoad == 1) {
			retType = U"dead_end";
			retDirection = aroundRoadCoordinate[0].first;
			return true;
		}
		if (totalAroundRoad == 2) {
			CoordinateStruct roadDelta = {0, 0};
			
			for (int i=0; i<2; i++) {
				roadDelta.x += aroundRoadCoordinate[i].second.x;
				roadDelta.y += aroundRoadCoordinate[i].second.y;
			}
			
			// �c������
			if (roadDelta.x == 0 && roadDelta.y == 0) {
				retType = U"default";
				
				if (aroundRoadCoordinate[0].second.x != 0) {
					retDirection = U"depth";
				}
				else {
					retDirection = U"width";
				}
				
				return true;
			}
			// �Ȃ���p
			else {
				retType = U"turn";
				
				if (findStringArray(aroundRoadCoordinate, Array<String>{U"left", U"top"})){
					retDirection = U"left-top";
					return true;
				}
				if (findStringArray(aroundRoadCoordinate, Array<String>{U"right", U"top"})){
					retDirection = U"right-top";
					return true;
				}
				if (findStringArray(aroundRoadCoordinate, Array<String>{U"left", U"bottom"})){
					retDirection = U"left-bottom";
					return true;
				}
				if (findStringArray(aroundRoadCoordinate, Array<String>{U"right", U"bottom"})){
					retDirection = U"right-bottom";
					return true;
				}
				
				return false;
			}
		}
		if (totalAroundRoad == 3) {
			retType = U"intersection_T";
			
			if (findStringArray(aroundRoadCoordinate, Array<String>{U"left", U"top", U"bottom"})){
				retDirection = U"left-top-bottom";
				return true;
			}
			if (findStringArray(aroundRoadCoordinate, Array<String>{U"right", U"top", U"bottom"})){
				retDirection = U"right-top-bottom";
				return true;
			}
			if (findStringArray(aroundRoadCoordinate, Array<String>{U"left", U"right", U"top"})){
				retDirection = U"left-right-top";
				return true;
			}
			if (findStringArray(aroundRoadCoordinate, Array<String>{U"left", U"right", U"bottom"})){
				retDirection = U"left-right-bottom";
				return true;
			}
			
			return false;
		}
		if (totalAroundRoad == 4) {
			retType = U"intersection_cross";
			retDirection = U"normal";
			return true;
		}
	}
	
	// �I�u�W�F�N�g�^�C�v�̏ꍇ
	if (selectedAddon->isInCategories(U"object_type")) {
		// ���͂ɓ��H�����邩�m�F����
		for (int i=0; i<AROUND_TILES; i++) {
			CoordinateStruct currentSquare = {coordinate.x+AroundTiles[i].second.x, coordinate.y+AroundTiles[i].second.y};
			
			for (int j=0; j<squares[currentSquare.y][currentSquare.x].addons.size(); j++) {
				if (squares[currentSquare.y][currentSquare.x].addons[j]->isInCategories(U"road")) {
					String retTypeTemp = U"normal";
					String retDirectionTemp = AroundTiles[i].first;
					
					// �����̃^�C�����g���ꍇ�A���Ă�����ɏ�Q���Ȃǂ��Ȃ����m�F����
					bool cannotBuild = false;
					
					int addX = 1, addY = 1;
					if (retTypeTemp == U"right") {
						addX = -1;
					}
					else if (retTypeTemp == U"bottom") {
						addY = -1;
					}
					
					for (int y=0; y<selectedAddon->getUseTiles(retType, retDirection).y; y+=addY) {
						for (int x=0; y<selectedAddon->getUseTiles(retType, retDirection).x; x+=addX) {
							for (int k=0; k<squares[y][x].addons.size(); k++) {
								if (squares[y][x].addons[k]->isInCategories(U"connectable_type")) {
									cannotBuild = true;
									break;
								}
							}
							if (cannotBuild) break;
						}
						if (cannotBuild) break;
					}
					
					if (!cannotBuild) {
						retType = retTypeTemp;
						retDirection = retDirectionTemp;
						return true;
					}
				}
			}
		}
	}
	
	// �^�C���̏ꍇ
	if (selectedAddon->isInCategories(U"put_type")) {
		retType = U"normal";
		retDirection = U"normal";
		return true;
	}
	
	return false;					// ���݂��Ȃ� or �ݒu�s�\�ȏꍇ
}

// �A�h�I�����폜
void CityMap::clear(CoordinateStruct position) {
	SquareStruct* currentSquare = &squares[position.y][position.x];
	Addon* selectedAddon = addons[U"tile_greenfield"];
	
	currentSquare->addons.clear();
	currentSquare->types.clear();
	currentSquare->directions.clear();
	
	currentSquare->types << U"normal";
	currentSquare->directions << U"normal";
	currentSquare->serialNumber = 0;
	currentSquare->tilesCount = {0, 0};
	//current_square->use_tiles = {1, 1};
	currentSquare->tilesCount = {0, 0};
	currentSquare->residents = 0;
	currentSquare->workers = {0, 0, 0, 0, 0};
	currentSquare->students = 0;
	currentSquare->reservation = RCOIFP::None;
	
	currentSquare->addons << selectedAddon;
	
	// �K���x��߂�
}

bool CityMap::isPositionAvailable(CoordinateStruct coordinate) {
	if (coordinate.x >= 0 && coordinate.x <= mapsize.width-1 && coordinate.y >= 0 && coordinate.y <= mapsize.height-1) {
		return true;
	}
	else {
		return false;
	}
}

TimeStruct CityMap::cityTime(int minutesDelta) {
	time.minutes += minutesDelta;
	
	if (time.minutes >= 60) {
		time.hour ++;
		time.minutes -= 60;
		
		if (time.hour >= 24) {
			time.date ++;
			time.hour -= 24;
			
			if (time.month == 4 || time.month == 6 || time.month == 9 || time.month == 11) {
				if (time.date >= 31) {
					time.month ++;
					time.date -= 30;
				}
			}
			else if (time.month == 2) {
				if (time.year % 4 == 0 && time.date >= 30) {
					time.month ++;
					time.date -= 29;
				}
				else if (time.date >= 29) {
					time.month ++;
					time.date -= 28;
				}
			}
			else if (time.date >= 32) {
				time.month ++;
				time.date -= 31;
				
				if (time.month >= 13) {
					time.year ++;
					time.month -= 12;
				}
			}
		}
	}
	
	
	return time;
}

map<String, int> CityMap::getRate(CoordinateStruct coordinate) {
	return squares[coordinate.y][coordinate.x].rate;
}

int CityMap::getRate(CoordinateStruct coordinate, String rateName) {
	if (squares[coordinate.y][coordinate.x].rate.find(rateName) != squares[coordinate.y][coordinate.x].rate.end()) {
		return squares[coordinate.y][coordinate.x].rate[rateName];
	}
	else {
		return 0;
	}
}

Color CityMap::getRateColor(int rate, bool upper, int standard) {
	Color ret(50, 50, 50, 200);
	
	if (upper) {
		if (rate > standard) {
			ret.b += (rate-standard) * 1.27;
		}
		else if (rate < standard) {
			ret.r += (standard-rate) * 1.27;
		}
		return ret;
	}
	
	if (rate < standard) {
		ret.b += (standard-rate) * 1.27;
	}
	else if (rate > standard) {
		ret.r += (rate-standard) * 1.27;
	}
	
	return ret;
}

void CityMap::setShowRate(String rateName) {
	showRate = rateName;
}

bool CityMap::save() {
	// JsonWriter��錾
	JSONWriter mapData;
	
	mapData.startObject();
	{
		mapData.key(U"Version").write(RELEASE_NUMBER);
		mapData.key(U"Addon_Set").write(addonSet);
		mapData.key(U"City_Name").write(cityName);
		mapData.key(U"Mayor_Name").write(mayorName);
		mapData.key(U"Total_Population").write(totalPopulation);
		mapData.key(U"Change_Weather").write(changeWeather);
		mapData.key(U"Temperature").write(temperature);
		mapData.key(U"Dark_on_Night").write(darkOnNight);
		
		mapData.key(U"Map_size").startObject();
		{
			mapData.key(U"width").write(mapsize.width);
			mapData.key(U"height").write(mapsize.height);
		}
		mapData.endObject();
		
		mapData.key(U"Time").startObject();
		{
			mapData.key(U"year").write(time.year);
			mapData.key(U"month").write(time.month);
			mapData.key(U"date").write(time.date);
			mapData.key(U"hour").write(time.hour);
			mapData.key(U"minutes").write(time.minutes);
		}
		mapData.endObject();
		
		mapData.key(U"Demand").startObject();
		{
			mapData.key(U"residential").write(demand.residential);
			mapData.key(U"commercial").write(demand.commercial);
			mapData.key(U"office").write(demand.office);
			mapData.key(U"industrial").write(demand.industrial);
			mapData.key(U"farm").write(demand.farm);
		}
		mapData.endObject();
		
		mapData.key(U"Money").write(money);
		
		mapData.key(U"Budget").startObject();
		{
			mapData.key(U"police").write(budget.police);
			mapData.key(U"fire_depertment").write(budget.fireDepertment);
			mapData.key(U"post_office").write(budget.postOffice);
			mapData.key(U"education").write(budget.education);
		}
		mapData.endObject();
		
		mapData.key(U"Tax").startObject();
		{
			mapData.key(U"residential").write(tax.residential);
			mapData.key(U"commercial").write(tax.commercial);
			mapData.key(U"office").write(tax.office);
			mapData.key(U"industrial").write(tax.industrial);
			mapData.key(U"farm").write(tax.farm);
		}
		mapData.endObject();
		
		mapData.key(U"Map").startArray();
		{
			for (int y=0; y<mapsize.height; y++) {
				mapData.startArray();
				{
					for (int x=0; x<mapsize.width; x++) {
						mapData.startObject();
						{
							mapData.key(U"addons").startArray();
							{
								for (int i=0; i<squares[y][x].addons.size(); i++) {
									mapData.startObject();
									{
										mapData.key(U"name").write(squares[y][x].addons[i]->getName());
										//map_file.key(U"category").write(squares[y][x].category[i]);
										mapData.key(U"type_number").write(squares[y][x].types[i]);
										mapData.key(U"direction_number").write(squares[y][x].directions[i]);
									}
									mapData.endObject();
								}
							}
							mapData.endArray();
							/*
							map_file.key(U"use_tiles").startObject();
							{
								map_file.key(U"x").write(squares[y][x].use_tiles.x);
								map_file.key(U"y").write(squares[y][x].use_tiles.y);
							}
							map_file.endObject();
							*/
							mapData.key(U"tiles_count").startObject();
							{
								mapData.key(U"x").write(squares[y][x].tilesCount.x);
								mapData.key(U"y").write(squares[y][x].tilesCount.y);
							}
							mapData.endObject();
							
							mapData.key(U"serial_number").write(squares[y][x].serialNumber);
							
							mapData.key(U"residents").write(squares[y][x].residents);
							
							mapData.key(U"workers").startObject();
							{
								mapData.key(U"commercial").write(squares[y][x].workers.commercial);
								mapData.key(U"office").write(squares[y][x].workers.office);
								mapData.key(U"industrial").write(squares[y][x].workers.industrial);
								mapData.key(U"farm").write(squares[y][x].workers.farm);
								mapData.key(U"public").write(squares[y][x].workers.publicFacility);
							}
							mapData.endObject();
							
							mapData.key(U"students").write(squares[y][x].students);
							
							mapData.key(U"rate").startObject();
							{
								for (auto rate = squares[y][x].rate.begin(); rate != squares[y][x].rate.end() ; rate++) {
									if (rate->second != 0) {
										mapData.key(rate->first).write(rate->second);
									}
								}
							}
							mapData.endObject();
							
							/*
							map_file.key(U"crop").startObject();
							{
								map_file.key(U"name").write(squares[y][x].crop.name);
								map_file.key(U"amount").write(squares[y][x].crop.amount);
							}
							map_file.endObject();
							 */
							
							mapData.key(U"age").startArray();
							{
								for (int i=0; i<squares[y][x].age.size(); i++) {
									mapData.write(squares[y][x].age[i]);
								}
							}
							mapData.endArray();
							
							mapData.key(U"gender").startArray();
							{
								for (int i=0; i<squares[y][x].gender.size(); i++) {
									mapData.write(squares[y][x].gender[i]);
								}
							}
							mapData.endArray();
							
							mapData.key(U"work_places").startArray();
							{
								for (int i=0; i<squares[y][x].workPlaces.size(); i++) {
									mapData.startObject();
									{
										mapData.key(U"work_kind").write(squares[y][x].workPlaces[i].workPlace);
										mapData.key(U"serial_number").write(squares[y][x].workPlaces[i].workPlacesSerialNumber);
									}
									mapData.endObject();
								}
							}
							mapData.endArray();
							
							mapData.key(U"school").startArray();
							{
								for (int i=0; i<squares[y][x].schools.size(); i++) {
									mapData.startObject();
									{
										mapData.key(U"school_kind").write(squares[y][x].schools[i].school);
										mapData.key(U"serial_number").write(squares[y][x].schools[i].schoolSerialNumber);
									}
									mapData.endObject();
								}
							}
							mapData.endArray();
							
							mapData.key(U"reservation").write(squares[y][x].reservation);
							
							mapData.key(U"original_name").write(squares[y][x].originalName);
						}
						mapData.endObject();
					}
				}
				mapData.endArray();
			}
		}
		mapData.endArray();
	}
	mapData.endObject();
	
	saveTextFile(mapFilePath.toUTF8()+".cbj", stringXOR(mapData.get().toUTF8(), "citiesboxmapdatafilexor"));
	//saveTextFile(map_file_path.toUTF8()+".cbj", map_file.get().toUTF8());
	//map_file.save(map_file_path+U".cbj");
	
	return true;
}

void CityMap::freeMapAndAddons() {
	for (auto i = addons.begin(); i != addons.end() ; i++) {
		delete(i->second);
	}
	
	Array<Array<SquareStruct>>().swap(squares);
}