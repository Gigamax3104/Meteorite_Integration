#include	<cstdlib>
#include	<DxLib.h>

#include	"../h/ErrorMessage.h"
#include	"../h/GraphicData.h"

template<typename T>void Font<T>::Draw(Vector2 pos, const char* font, Color c) {
	DrawString(pos.x, pos.y, font, c.color);
}
template<typename T>void Font<T>::Draw(Vector2 pos, std::string font, Color c) {
	DrawString(pos.x, pos.y, (const TCHAR*)&font, c.color);
}

template<typename T>void Font<T>::FDraw(Vector2 pos, const char* font, Color c, const T data) {
	while (data != nullptr) { DrawFormatString(pos.x, pos.y, c.color, font, data); }
}

template<typename T>void Font<T>::FDraw(Vector2 pos, std::string font, Color c, const T data) {
	while (data != nullptr) { DrawFormatString(pos.x, pos.y, c.color, font, data); }
}

template<typename T>void Font<T>::ExDraw(Vector2 pos, Vector2 size, const char* font, Color c, const T data) {
	while (data != nullptr) { DrawExtendFormatString(pos.x, pos.y, size.x, size.y, c.color, font, data); }
}

template<typename T>void Font<T>::ExDraw(Vector2 pos, Vector2 size, std::string font, Color c, const T data){
	while (data != nullptr) { DrawExtendFormatString(pos.x, pos.y, size.x, size.y, c.color, font, data); }
}

void Sound::operator=(const Sound& other) { this->m_sound = other.m_sound; }

const Sound& Sound::operator=(const Sound&& other) noexcept {
	this->m_sound = other.m_sound;

	return *this;
}

void Sound::SetVolume(double raito){
	ChangeVolumeSoundMem(int(255 * raito / 100), m_sound.GetSoundFile()); //0～255をまでをraito÷100で求めた倍率にする。
}

void Sound::Stop_And_Play() {
	SetFontSize(50);

	if (CheckSoundMem(m_sound.GetSoundFile()) == 0) {
		PlaySoundMem(m_sound.GetSoundFile(), m_type);
		DrawString(0, 0, "再生", 0x00ff00);
	}
	else if (CheckSoundMem(m_sound.GetSoundFile()) == 1 && m_type != NULL) {
		StopSoundMem(m_sound.GetSoundFile());
		DrawString(0, 0, "停止", 0xffffff);
	}

	SetFontSize(20);
}
void Image::operator=(const Image& other){
	this->m_image = other.m_image;

	GetGraphSize(m_image.GetImageFile(), (int*)&m_image_graphSize.x, (int*)&m_image_graphSize.y);
}

const Image& Image::operator=(const Image&& other) noexcept {
	this->m_image = other.m_image;

	GetGraphSize(m_image.GetImageFile(), (int*)&m_image_graphSize.x, (int*)&m_image_graphSize.y);

	return *this;
}

void Image::Draw(const Vector2& pos) {
	if(!m_image.CheckSetImageFile()) throw ErrorMassage("画像が設定されてないため、描画することができませんでした。");

	Vector2 half = m_image_graphSize / 2;
	DrawGraph(int(pos.x) - half.x, int(pos.y) - half.y, m_image.GetImageFile(), TRUE);
}

void Image::ExDraw(const Vector2& pos, const Vector2 scale) {
	if (!m_image.CheckSetImageFile()) throw ErrorMassage("画像が設定されてないため、描画することができませんでした。");

	Vector2 r = { m_image_graphSize.x * scale.x / 2, m_image_graphSize.y * scale.y / 2 }; //倍率に合わせてサイズを変える

	DrawExtendGraph(int(pos.x), int(pos.y), int(pos.x) + int(r.x), int(pos.y) + int(r.y), m_image.GetImageFile(), TRUE);
}

void Image::SetImage(const std::string& file_name) {
	m_image.Destroy();

	m_image.LoadFile(file_name);

	int x = m_image_graphSize.x, y = m_image_graphSize.y;
	GetGraphSize(m_image.GetImageFile(), &x, &y);

	m_image_graphSize = Vector2(x, y);
}

void Movie::operator=(const Movie& other) {
	this->m_movie.operator=(other.m_movie);

	GetGraphSize(m_movie.GetMovieFile(), (int*)&m_movie_graphSize.x, (int*)&m_movie_graphSize.y);
}

const Movie& Movie::operator=(const Movie&& other) noexcept {
	if (this != &other) this->m_movie.operator=(other.m_movie);

	GetGraphSize(m_movie.GetMovieFile(), (int*)&m_movie_graphSize.x, (int*)&m_movie_graphSize.y);

	return *this;
}

void Movie::SetVolume(double raito) {
	SetMovieVolumeToGraph(int(10000 * raito / 100), m_movie.GetMovieFile()); //0～10000までをraito÷100で求めた倍率にする。
}

void Movie::Play(const Vector2& pos) {
	if (!m_movie.CheckSetMovieFile()) throw ErrorMassage("Error::映像データが見つからないため、再生することができませんでした。");

	int nowFrame = TellMovieToGraphToFrame(m_movie.GetMovieFile());
	if (nowFrame >= m_movie.GetFrame()) { SeekMovieToGraph(m_movie.GetMovieFile(), 0); PlayMovieToGraph(m_movie.GetMovieFile()); } //再生位置を初期位置に戻して再生
	else if (nowFrame == 0) PlayMovieToGraph(m_movie.GetMovieFile()); //再生

	Vector2 p = { pos.x - m_movie_graphSize.x / 2, pos.y - m_movie_graphSize.y / 2 };

	DrawGraph(p.x, p.y, m_movie.GetMovieFile(), TRUE);
}

void Movie::ExPlay_Scale(const Vector2& pos, const Vector2& scale) {
	if (!m_movie.CheckSetMovieFile()) throw ErrorMassage("Error::映像データが見つからないため、再生することができませんでした。");

	int nowFrame = TellMovieToGraphToFrame(m_movie.GetMovieFile());
	if (nowFrame >= m_movie.GetFrame()) { SeekMovieToGraph(m_movie.GetMovieFile(), 0); PlayMovieToGraph(m_movie.GetMovieFile()); } //再生位置を初期位置に戻して再生
	else if (nowFrame == 0) PlayMovieToGraph(m_movie.GetMovieFile()); //再生

	Vector2 r = { m_movie_graphSize.x * scale.x / 2, m_movie_graphSize.y * scale.y / 2 };

	DrawExtendGraph(int(pos.x) - r.x, int(pos.y) - r.y, int(pos.x) + r.x, int(pos.y) + r.y, m_movie.GetMovieFile(), TRUE);
}
void Movie::ExPlay_Limit(const Vector2& pos, const Vector2& limit_pos) {
	if (!m_movie.CheckSetMovieFile()) throw ErrorMassage("Error::映像データが見つからないため、再生することができませんでした。");

	int nowFrame = TellMovieToGraphToFrame(m_movie.GetMovieFile());
	if (nowFrame >= m_movie.GetFrame()) { SeekMovieToGraph(m_movie.GetMovieFile(), 0); PlayMovieToGraph(m_movie.GetMovieFile()); } //再生位置を初期位置に戻して再生
	else if (nowFrame == 0) PlayMovieToGraph(m_movie.GetMovieFile()); //再生

	Vector2 halfPos = m_movie_graphSize / 2;

	DrawExtendGraph(int(pos.x) - halfPos.x, int(pos.y) - halfPos.y,
		int(limit_pos.x) + halfPos.x, int(limit_pos.y) + halfPos.y, m_movie.GetMovieFile(), TRUE);
}

void Movie::ExPlay(const Vector2& pos, const Vector2& limit_pos, const Vector2& scale) {
	if (!m_movie.CheckSetMovieFile()) throw ErrorMassage("Error::映像データが見つからないため、再生することができませんでした。");

	int nowFrame = TellMovieToGraphToFrame(m_movie.GetMovieFile());
	if (nowFrame >= m_movie.GetFrame()) { SeekMovieToGraph(m_movie.GetMovieFile(), 0); PlayMovieToGraph(m_movie.GetMovieFile()); } //再生位置を初期位置に戻して再生
	else if (nowFrame == 0) PlayMovieToGraph(m_movie.GetMovieFile()); //再生

	Vector2 r = { m_movie_graphSize.x * scale.x / 2, m_movie_graphSize.y * scale.y / 2 };

	DrawExtendGraph(int(pos.x) - r.x, int(pos.y) - r.y, int(limit_pos.x) + r.x, int(limit_pos.y) + r.y, m_movie.GetMovieFile(), TRUE);
}

void Movie::Stop_And_Play() {
	SetFontSize(50);

	if (GetMovieStateToGraph(m_movie.GetMovieFile()) == 0) {
		PlayMovieToGraph(m_movie.GetMovieFile());
		DrawString(0, 0, "再生", 0x00ff00);
	}

	else if (GetMovieStateToGraph(m_movie.GetMovieFile()) == 1) {
		PauseMovieToGraph(m_movie.GetMovieFile());
		DrawString(0, 0, "停止", 0xffffff);
	}

	SetFontSize(20);
}
//GraphicData::GraphicData()
//	: m_size(Vector2(0.0, 0.0)), m_scale(Vector2(1.0, 1.0)),m_graphic(new int[1]) {}
//
//GraphicData::GraphicData(const Vector2& scale, const char* file)
//	: m_scale(scale) {
//	m_file->open(file);
//	Set(file);
//}
//
//GraphicData::GraphicData(const Vector2& scale, const Color& color, const char* file)
//	:m_size(Vector2(0.0, 0.0)), m_scale(scale) {
//	Set(file);
//}
//
//GraphicData::GraphicData(const GraphicData& graphic)
//	: m_scale(graphic.m_scale) {
//	SetFont(graphic.m_font);
//	Set(graphic.m_file);
//}
//
//void GraphicData::operator=(const GraphicData& graphic) {
//	m_scale = graphic.m_scale;
//
//	SetFont(graphic.m_font);
//	Set(graphic.m_file);
//}
//
//void GraphicData::Set(const char* file) {
//	if (m_graphic != E && m_graphic != NULL) DeleteGraph(m_graphic);
//
//	if (m_file != nullptr) m_file + 1 == nullptr ? delete m_file : delete[] m_file;
//
//	m_graphic = LoadGraph(file);
//	if (m_graphic != E) {
//		int x = 0, y = 0;
//
//		GetGraphSize(m_graphic, &x, &y);
//
//		m_size = Vector2(x, y);
//	}
//
//	m_file = new const char[strlen(file)];
//	m_file = file;
//}
//
//void GraphicData::SetFont(int size, int thick) {
//	if (m_font != E && m_font != NULL) DeleteFontToHandle(m_font);
//	m_font = CreateFontToHandle(NULL, size, thick);
//}
//
//void GraphicData::SetFont(int font) {
//	if (m_font != E && m_font != NULL) DeleteFontToHandle(m_font);
//	m_font = font;
//
//}
//void GraphicData::SetScale(const Vector2& scale) { m_scale = scale; }
//
//void GraphicData::Error(int size,int thick) {
//	SetFont(size, thick);
//
//	DrawFormatStringToHandle(0, 0, COLOR_RED, m_font, "NOT FOUND : %s.", m_file);
//}
//
//void GraphicData::Draw(const Vector2& pos, bool transFlag) {
//	if (ErrorCheck() == E) Error(40, 5);
//	else DrawGraph(pos.x, pos.y, m_graphic, transFlag);
//}
//
//void GraphicData::ExtendDraw(const Vector2& pos, bool transFlag) {
//	if (ErrorCheck() == E || !ErrorCheck()) Error(40, 5);
//	else DrawExtendGraph(pos.x - m_size.x / 2, pos.y - m_size.y / 2, (int)(pos.x + m_size.x / 2 * m_size.x),
//		(int)(pos.y + m_size.y / 2 * m_size.y), m_graphic, transFlag);
//}
//
//int GraphicData::ErrorCheck() {
//	if (m_graphic == E) return E;
//	else return m_graphic != NULL ? true : false;
//}
//
//GraphicData::~GraphicData() {
//	if (m_graphic != NULL && m_graphic != E) DeleteGraph(m_graphic);
//	if (m_font != NULL && m_font != E) DeleteFontToHandle(m_font);
//
//	if (m_file != nullptr) m_file + 1 == nullptr ? delete m_file : delete[] m_file;
//}

//GraphicData::GraphicData(const char** imageFile, const char** soundFile, const char** videoFile,int dynamicAllocation) { //画像・音楽・映像を保管するデータとその大きさ・倍率、位置の配列を動的確保し、
//	imagePos = new IntVector2 [dynamicAllocation + 1];													//Setメソッドへ移行する。
//
//	imageScale = new DoubleVector2 [dynamicAllocation + 1];
//
//	imageSize = new IntVector2 [dynamicAllocation + 1];
//
//	soundPos = new IntVector2[SOUNDSIZE];
//
//	videoPos = new IntVector2[VIDEOSIZE];
//
//
//	videoSize = new IntVector2 [VIDEOSIZE];
//
//	data = new int*[DATASIZE];
//
//	data[IMAGE] = new int[IMAGESIZE];
//	data[SOUND] = new int[SOUNDSIZE];
//	data[VIDEO] = new int[VIDEOSIZE];
//
//	SetGraph(imageFile,soundFile,videoFile, dynamicAllocation);
//}
//
//void GraphicData::Reassignment(int dynamicAllocation) {
//	IntVector2* intSave[] = {
//		imagePos[Switch1],imagePos[Switch2],imageSize[Switch1],imageSize[Switch2]
//	};
//
//	DoubleVector2* doubleSave[] = {
//		scale[Switch1],scale[Switch2]
//	};
//
//	imagePos[Switch1] = new IntVector2[dynamicAllocation + 1];
//	for (int i = 0; i < dynamicAllocation; i++) imagePos[Switch1][i] = intSave[0][i];
//
//	imagePos[Switch2] = new IntVector2[dynamicAllocation + 1];
//	for (int i = 0; i < dynamicAllocation; i++) imagePos[Switch2][i] = intSave[1][i];
//
//	scale[Switch1] = new DoubleVector2[dynamicAllocation + 1];
//	for (int i = 0; i < dynamicAllocation; i++) scale[Switch1][i] = doubleSave[0][i];
//
//	scale[Switch2] = new DoubleVector2[dynamicAllocation + 1];
//	for (int i = 0; i < dynamicAllocation; i++) scale[Switch2][i] = doubleSave[1][i];
//
//	imageSize[Switch1] = new IntVector2[dynamicAllocation + 1];
//	imageSize[Switch2] = new IntVector2[dynamicAllocation + 1];
//	for (int i = 0; i < IMAGESIZE * (dynamicAllocation + 1); i++)
//		GetGraphSize(data[IMAGE][i], &imageSize[i / dynamicAllocation][i].x, &imageSize[i / dynamicAllocation][i].y);
//
//	Reset(dynamicAllocation);
//}
//
//void GraphicData::Reset(int dynamicAllocation) {
//	switch (dynamicAllocation) {
//	case STAGE_2:
//		imagePos[Switch1][dynamicAllocation - 1].x /= 2;
//		imagePos[Switch2][dynamicAllocation - 1].x /= 2;
//
//		scale[Switch1][dynamicAllocation].x = 0.5;
//		scale[Switch1][dynamicAllocation].y = 0.5;
//
//		imagePos[Switch1][dynamicAllocation].x =
//			(int)(WIDTH / 2 + imageSize[Switch1][dynamicAllocation].x * (scale[Switch1][dynamicAllocation].x / 2));
//		imagePos[Switch1][dynamicAllocation].y =
//			(int)(HEIGHT - imageSize[Switch1][dynamicAllocation].y * scale[Switch1][dynamicAllocation].y);
//
//		scale[Switch2][dynamicAllocation].x = 0.5;
//		scale[Switch2][dynamicAllocation].y = 0.5;
//
//		imagePos[Switch2][dynamicAllocation].x =
//			(int)(WIDTH / 2 + imageSize[Switch2][dynamicAllocation].x * (scale[Switch2][dynamicAllocation].x / 2));
//		imagePos[Switch2][dynamicAllocation].y =
//			(int)(HEIGHT - imageSize[Switch2][dynamicAllocation].y * scale[Switch2][dynamicAllocation].y);
//		break;
//
//	case STAGE_3:
//		imagePos[Switch1][0].x = (int)(WIDTH / 3 - imageSize[Switch1][0].x * (scale[Switch1][0].x / 2));
//		break;
//	}
//}
//void GraphicData::SetGraph(const char** imageFile, const char** soundFile, const char** videoFile, int dynamicAllocation) {			//全てのデータを、引数の中にあるファイル名で探し出して格納する。
//	const char** saveImageFile = imageFile;																		//また、それぞれの位置をSet(データ)Posメソッドで倍率と位置を設定する。
//	const char** savesoundFile = soundFile;																		//その後、ErrorCheckメソッドに移行する。
//	const char** saveVideoFile = videoFile;										
//
//	for (int i = 0; i < IMAGESIZE * (dynamicAllocation + 1); i++) {
//		data[IMAGE][i] = LoadGraph(*imageFile);
//		GetGraphSize(data[IMAGE][i], &imageSize[i / dynamicAllocation][i].x, &imageSize[i / dynamicAllocation][i].y);
//
//		imageFile++;
//	}
//
//	SetImagePos();
//
//	for (int i = 0; i < SOUNDSIZE; i++) {
//		data[SOUND][i] = LoadSoundMem(*soundFile);
//
//		soundFile++;
//	}
//
//	SetSoundPos();
//
//	for (int i = 0; i < VIDEOSIZE; i++) {
//		data[VIDEO][i] = LoadGraph(*videoFile);
//		GetGraphSize(data[VIDEO][i], &videoSize[i].x, &videoSize[i].y);
//
//		videoSize[i].x += WIDTH - videoSize[i].x;
//		videoSize[i].y += HEIGHT - videoSize[i].y;
//		
//		videoFile++;
//	}
//
//	SetVideoPos();
//
//	imageFile = saveImageFile;
//	soundFile = savesoundFile;
//	videoFile = saveVideoFile;
//
//	ErrorCheck(imageFile,soundFile,videoFile);
//}
//
//void GraphicData::SetImagePos() {										//画像の位置を設定する。
//	scale[Switch1][0].x = 0.5;
//	scale[Switch1][0].y = 0.5;
//
//	imagePos[Switch1][0].x = (int)(WIDTH / 2 - imageSize[Switch1][0].x * (scale[Switch1][0].x / 2));
//	imagePos[Switch1][0].y = (int)(HEIGHT - imageSize[Switch1][0].y * scale[Switch1][0].y);
//
//	scale[Switch2][0].x = 0.5;
//	scale[Switch2][0].y = 0.5;
//
//	imagePos[Switch2][0].x = (int)(WIDTH / 2 - imageSize[Switch2][0].x * (scale[Switch2][0].x / 2));
//	imagePos[Switch2][0].y = (int)(HEIGHT - imageSize[Switch2][0].y * scale[Switch2][0].y);
//}
//
//void GraphicData::SetSoundPos() {	//音楽の位置を設定する。
//
//}
//
//void GraphicData::SetVideoPos() {	//映像の位置を設定する。
//	videoPos[EXPROSSION].x = 0;
//	videoPos[EXPROSSION].y = 0;
//}
//
//void GraphicData::ErrorCheck(const char** imageFile, const char** soundFile, const char** videoFile) {						//それぞれのデータを1つずつ調べ、もし格納されていない場合はErrorメソッドへ移行する。
//	int* dataSave = new int[DATASIZE];									//その際、Escapeキーを押されたらDeleteメソッドへ移行し、処理を終了する。
//	int* save = dataSave;												//すべて格納されていれば正常に動作され、Game関数へと移行する。
//
//	for (int i = 0; i < IMAGESIZE; i++) {
//		if (data[IMAGE][i] == -1) {
//			*dataSave = data[IMAGE][i];
//			dataSave++;
//		}
//	}
//
//	for (int i = 0; i < SOUNDSIZE; i++) {
//		if (data[SOUND][i] == -1) {
//			*dataSave = data[SOUND][i];
//			dataSave++;
//		}
//	}
//
//	for (int i = 0; i < VIDEOSIZE; i++) {
//		if (data[VIDEO][i] == -1) {
//			*dataSave = data[VIDEO][i];
//			dataSave++;
//		}
//	}
//
//	if (dataSave != save) {
//		dataSave = save;
//
//		while(!CheckHitKey(KEY_INPUT_ESCAPE)) Error(dataSave,imageFile,soundFile,videoFile);
//
//		delete[] dataSave;
//
//		exit(EXIT_FAILURE);
//	}
//}
//
//void GraphicData::Error(const int* save, const char** imageFile, const char** soundFile, const char** videoFile) {												//引数に渡された格納されていないデータ群と、ファイルを元に表示する。
//	SetBackgroundColor(0, 0, 0);
//	ClearDrawScreen();
//
//	SetFontSize(60);
//	DrawString(0, 0, "[NOT FOUND]", color[GREEN]);
//	SetFontSize(40);
//	DrawString(0, 60, "IMAGE:", color[GREEN]);
//	SetFontSize(20);
//
//	for (int i = 0; i < IMAGESIZE; i++){
//		if (*save == data[IMAGE][i]) DrawString(0, i * 20 + 100, *imageFile, color[WHITE]);
//
//		imageFile++;
//	}
//
//	SetFontSize(40);
//	DrawString(WIDTH / 2 - 40 * 4, 60, "SOUND:", color[GREEN]);
//	SetFontSize(20);
//
//	for (int i = 0; i < SOUNDSIZE; i++){
//		if (*save == data[SOUND][i]) DrawString(WIDTH / 2 - 40 * 4, i * 20 + 100, *soundFile, color[WHITE]);
//
//		soundFile++;
//	}
//
//	SetFontSize(40);
//	DrawString(WIDTH / 2 + 40 * 6, 60, "VIDEO:", color[GREEN]);
//	SetFontSize(20);
//
//	for (int i = 0; i < VIDEOSIZE; i++){
//		if (*save == data[VIDEO][i]) DrawString(WIDTH / 2 + 40 * 6, i * 20 + 100, *videoFile, color[WHITE]);
//
//		videoFile++;
//	}
//
//	SetFontSize(50);
//	DrawString(WIDTH - 50 * 7, HEIGHT - 50, "ESCキーで終了", color[WHITE]);
//
//	ScreenFlip();
//}
//
//GraphicData::~GraphicData() {											//全てのデータと、それを保管する配列を返却する。
//	for (int i = 0; i < IMAGESIZE; i++) DeleteGraph(data[IMAGE][i]);
//
//	for (int i = 0; i < SOUNDSIZE; i++) DeleteSoundMem(data[SOUND][i]);
//
//	for (int i = 0; i < VIDEOSIZE; i++) DeleteGraph(data[VIDEO][i]);
//
//	delete[] imagePos[Switch1];
//	delete[] imagePos[Switch2];
//
//	delete[] imagePos;
//	imagePos = nullptr;
//
//	delete[] imageSize[Switch1];
//	delete[] imageSize[Switch2];
//
//	delete[] imageSize;
//	imageSize = nullptr;
//
//	delete[] scale[Switch1];
//	delete[] scale[Switch2];
//
//	delete[] scale;
//	scale = nullptr;
//
//	delete[] soundPos;
//	soundPos = nullptr;
//
//	delete[] videoPos;
//	videoPos = nullptr;
//
//	delete[] videoSize;
//	videoSize = nullptr;
//	
//	delete[] data[IMAGE];
//	delete[] data[SOUND];
//	delete[] data[VIDEO];
//
//	delete[] data;
//	data = nullptr;
//}
