#include "Specific.hpp"

#include "StartUp.hpp"
#include "TitleMenu.hpp"
#include "Images.hpp"
#include "Addon.hpp"
#include "CityMap.hpp"
#include "SubWindow.hpp"
#include "DetailsBar.hpp"
#include "Menu.hpp"

void Main() {
	Window::SetTitle(U"Cities Box.cpp");
	
	Window::SetStyle(WindowStyle::Sizable);
	Scene::SetScaleMode(ScaleMode::ResizeFill);
	
	Scene::SetBackground(Color(50, 50, 50));
	
	/*---------------------------------------------
	 				�t�@�C���ǂݍ���
	 --------------------------------------------*/	
	// �摜�̓ǂݍ���
	Images images;
	loadImages(images);
	
	// �t�H���g�̐錾
	Font font16(16, U"example/font/NotoSansCJKjp/NotoSansCJKjp-Bold.otf");
	Font font12(12, U"example/font/NotoSansCJKjp/NotoSansCJKjp-Regular.otf");
	Font font8(8, U"example/font/NotoSansCJKjp/NotoSansCJKjp-Regular.otf");
	
	// �^�C�g�����j���[���
	String mapFilePath;
	if (!titleMenu(images, font16, mapFilePath)) {
		return;				// �^�C�g����ʂŃE�B���h�E�������v���O�����I��
	}
	
	// �}�b�v�ƃA�h�I���̓ǂݍ���
	CityMap map;
	map.load(mapFilePath);
	
	//map.save();
	
	// �J�����̏����ʒu
	CameraStruct camera;
	camera.position = PositionStruct{-Scene::Width()/2+64/2, -150};
	
	// �J�[�\���̈ʒu
	CursorStruct cursor;
	cursor.texture = &(images.images["pointer"]["blue"].texture);
	
	// �`�揈��
	RenderTexture bufferTexture(Scene::Width(), Scene::Height(), Color(30, 30, 30));
	bool updateMap = true, firstLoop = true;
	
	// �T�u�E�B���h�E
	SubWindow subWindow(U"Test Window", &font16, SizeStruct{400, 200}, Color(Palette::White));
	SubWindow subWindow2(U"Test Window2", &font16, SizeStruct{300, 150}, Color(Palette::White));
	
	// ���j���[
	Menu menu;
	menu.set(PositionStruct{0, Scene::Height()-60}, SizeStruct{Scene::Width(), 60}, &map, &font8, &font12, &font16);
	
	// �I�����ꂽ�A�h�I��
	Addon* selectedAddon;
	
	// �O�񍶃N���b�N�����Ƃ��̃}�b�v��̍��W
	CoordinateStruct beforeMousePressedCoordinate = {0, 0};
	bool pressing = false;
	
	// ����
	TimeStruct time;
	
	// Details Bar�̐ݒ�
	DetailsBar detailsBar(PositionStruct{Scene::Size().x-450, 10}, &font16);
	
	while (System::Update()) {
		// �J�����̑���
		if (KeyLeft.pressed()) {
			camera.position.x -= 20;
			updateMap = true;
		}
		if (KeyRight.pressed()) {
			camera.position.x += 20;
			updateMap = true;
		}
		if (KeyUp.pressed()) {
			camera.position.y -= 10;
			updateMap = true;
		}
		if (KeyDown.pressed()) {
			camera.position.y += 10;
			updateMap = true;
		}
		
		// �J�[�\���̈ʒu���擾
		if (updateMap || Cursor::Delta().x != 0 || Cursor::Delta().y != 0) {
			cursor.position = PositionStruct{Cursor::Pos().x, Cursor::Pos().y};
			cursor.coordinate = map.positionToCoordinate(cursor.position, camera);
			cursor.position_per_tiles = map.coordinateToPosition(cursor.coordinate, camera);
			
			updateMap = true;
		}
		
		//cout << "cursor: " << cursor.coordinate.x << "," << cursor.coordinate.y << " : " << map.getAddon(cursor.coordinate)[0].getName() << endl;
		
		// �}�b�v�Ȃǂ��X�V����K�v������ꍇ�̓o�b�t�@�ɕ`��i�X�V�j����
		if (updateMap) {
			bufferTexture.clear(Color(30, 30, 30));
			
			// �}�b�v�̕`��
			ScopedRenderTarget2D target(bufferTexture);
			map.draw(camera, cursor);
			
			menu.update();
			
			if (firstLoop) {
				firstLoop = false;
				
				// �T�u�E�B���h�E�̕`��
				/*
				sub_window.getRenderTexture()->clear(Color(Palette::White));
				ScopedRenderTarget2D target(*sub_window.getRenderTexture());
				font16(U"�e�X�g�ł���").draw(0, 0, Color(Palette::Black));
				sub_window.update();
				
				sub_window2.getRenderTexture()->clear(Color(Palette::White));
				target = ScopedRenderTarget2D(*sub_window2.getRenderTexture());
				font16(U"�e�X�g�ł���").draw(0, 0, Color(Palette::Black));
				sub_window2.update();*/
			}
			else {
				updateMap = false;
			}
		}
		
		// �o�b�t�@��`��
		bufferTexture.draw(0, 0);
		//sub_window.draw();
		//sub_window2.draw();
		
		// ���Ԃ�i�܂��ĕ\������
		time = map.cityTime(1);
		
		// Details Bar�̕\��
		detailsBar.printWeather(WeatherStruct::Sunny);
		detailsBar.printTemperature(map.getTemperature());
		detailsBar.printTime(time);
		detailsBar.printPopulation(map.getPopulation());
		detailsBar.printMoney(map.getMoney());
		
		// ���j���[�y�уA�h�I���I�����j���[�̕\��
		// �A�h�I�����I�����ꂽ��A�I�����ꂽ�A�h�I���̃|�C���^��Ԃ�
		selectedAddon = menu.draw(updateMap);
		menu.addonMenu();
		
		font16(U"{:04d}"_fmt(time.year)+U"/"+U"{:02d}"_fmt(time.month)+U"/"+U"{:02d}"_fmt(time.date)+U" "+U"{:02d}"_fmt(time.hour)+U":"+U"{:02d}"_fmt(time.minutes)).draw(230, Scene::Height()-25-3);
		
		// �}�b�v��ŃN���b�N���ꂽ��A�h�I����ݒu
		if (selectedAddon != nullptr && MouseL.pressed() && cursor.position.y <= Scene::Height()-60-80) {
			if (cursor.coordinate.x != beforeMousePressedCoordinate.x || cursor.coordinate.y != beforeMousePressedCoordinate.y) {
				cout << selectedAddon->getName() << endl;
				map.build(cursor.coordinate, selectedAddon, true);
				beforeMousePressedCoordinate = cursor.coordinate;
				updateMap = true;
				pressing = true;
			}
		}
		if (pressing) {
			if (!MouseL.pressed()) {
				beforeMousePressedCoordinate = {-1, -1};
				pressing = false;
			}
		}
		
		System::Sleep(20);
	}
	
	map.freeMapAndAddons();
	
	return;
}
