#include	"../h/File.h"
#include	"../h/ErrorMessage.h"

#include	<cstring>
#include	<utility>
#include	<algorithm>

namespace fs = std::filesystem; //省略するため用意

File::File(const std::string& file_name) : m_size(NULL){
	if (!file_name.empty()) { //文字列が空でない時
		if (!(file_name.front() == '.')) { //最初の文字が「.」でない時(ファイル名のみ)
			if (m_file_name == file_name) throw ErrorMassage("Error::「" + file_name + "」は存在しているため、開けません。");

			m_file.open(file_name, BINARY | IN | OUT);

			m_file_name = file_name;
		}
		else if (file_name.find("../") != std::string::npos) { //相対パスの後にファイルがあった時
			fs::path project = fs::path(__FILE__).parent_path(); //このソースコードがあるファイルのパスを返す。(_FILE_がそれ)
			fs::path clean_path = fs::canonical(project / file_name); //canonical→絶対パスへ変換したものを省略されている「../」を除く
			std::string generic = clean_path.generic_string(); //絶対パスでは「＼＼」が区切りとして入っているため、generic_string関数で「/」に戻す

			if (m_file_name == generic) throw ErrorMassage("Error::「" + generic + "」は存在しているため、開けません。");

			m_file.open(generic, BINARY | IN | OUT);

			m_file_name = generic;
		}
	}

	if (!m_file.is_open()) throw ErrorMassage("Error::「" + m_file_name + "」を読み込めませんでした。");

	m_file.seekg(std::ios::end); //ファイルポインタの位置を最後尾へ
	m_size = m_file.tellg(); //ファイルのメモリサイズを取得(先頭から何バイト目か)
	m_file.seekg(std::ios::beg); //ファイルポインタの位置を先頭へ

	size_t save_buf = m_buf.size();
	m_buf.resize(save_buf + sizeof(size_t)); //スペースを空けておく。
	std::memcpy(&m_buf[save_buf], &m_size, sizeof(size_t)); //サイズをコピー

	m_file.read((char*)m_buf.data(), m_size);
	if (m_size == NULL) throw ErrorMassage("Error::ファイルのサイズを取得できませんでした。");

	m_file.close();
}

void File::operator=(File* other) {
	if (this != other) {
		this->m_file = std::move(other->m_file);
		this->m_file_name = other->m_file_name;
		this->m_buf = other->m_buf;
		this->m_size = other->m_size;
	}
}

File& File::operator=(File&& other) noexcept {
	if (this != &other) {
		this->m_file = std::move(other.m_file);
		this->m_file_name = other.m_file_name;
		this->m_buf = other.m_buf;
		this->m_size = other.m_size;
	}

	return *this;
}

template <typename T> void File::Save(const T& data) {
	if (m_file.is_open()) throw ErrorMassage("Error::ファイルを読み込めませんでした。");

	m_file << data;
}

template <typename T> void File::Load(T* data) {
	if (m_file.is_open()) throw ErrorMassage("Error::ファイルを読み込めませんでした。");

	*data << m_file;
}

SoundFile::SoundFile(const std::string& file_name) : File(file_name) {
	size_t divide_format = m_file_name.find_last_of(".");
	if (divide_format == std::string::npos) throw ErrorMassage("Error::「" + m_file_name + "」の形式を入れてください。");

	std::string format = m_file_name.substr(divide_format + 1);
	std::transform(format.begin(), format.end(), format.begin(), ::tolower);

	if (format == "mp3" || format == "wav" || format == "ogg") m_sound_file = LoadSoundMem(m_file_name.c_str());
	else throw ErrorMassage("Error::「" + m_file_name + "」の形式が音声ではありませんでした。");

	if (!CheckSetSoundFile()) throw ErrorMassage("Error::「" + m_file_name + "」を読み込みましたが、音声を確保できませんでした。");
}

void SoundFile::operator=(const SoundFile& other) {
	if (other.m_file_name != "\0") LoadFile(other.m_file_name);
}

SoundFile& SoundFile::operator=(const SoundFile&& other) noexcept {
	if (this != &other) if (other.m_file_name != "\0") LoadFile(other.m_file_name);

	return *this;
}

int SoundFile::Base_LoadFile(const std::string& file_name, bool get) {
	if (!file_name.empty()) { //文字列が空でない時
		if (!(file_name.front() == '.')) { //最初の文字が「.」でない時(ファイル名のみ)
			if (m_file_name == file_name) throw ErrorMassage("Error::「" + file_name + "」は存在しているため、開けません。");

			m_file.open(file_name, BINARY | IN | OUT);

			m_file_name = file_name;
		}
		else if (file_name.find("../") != std::string::npos) { //相対パスの後にファイルがあった時
			fs::path project = fs::path(__FILE__).parent_path(); //このソースコードがあるファイルのパスを返す。(_FILE_がそれ)
			fs::path clean_path = fs::canonical(project / file_name); //canonical→絶対パスへ変換したものを省略されている「../」を除く
			std::string generic = clean_path.generic_string(); //絶対パスでは「＼＼」が区切りとして入っているため、generic_string関数で「/」に戻す
			
			if (m_file_name == generic) throw ErrorMassage("Error::「" + generic + "」は存在しているため、開けません。");

			m_file.open(generic, BINARY | IN | OUT);

			m_file_name = generic;
		}
	}

	if (!m_file.is_open()) throw ErrorMassage("Error::「" + m_file_name + "」を読み込めませんでした。");

	m_file.seekg(std::ios::end); //ファイルポインタの位置を最後尾へ
	m_size = m_file.tellg(); //ファイルのメモリサイズを取得(先頭から何バイト目か)
	m_file.seekg(std::ios::beg); //ファイルポインタの位置を先頭へ

	size_t save_buf = m_buf.size();
	m_buf.resize(save_buf + sizeof(size_t)); //スペースを空けておく。
	std::memcpy(&m_buf[save_buf], &m_size, sizeof(size_t)); //サイズをコピー

	m_file.read((char*)m_buf.data(), m_size);
	if (m_size == NULL) throw ErrorMassage("Error::ファイルのサイズを取得できませんでした。");

	m_file.close();

	if (CheckSetSoundFile()) DeleteSoundMem(m_sound_file);

	size_t divide_format = m_file_name.find_last_of(".");
	if (divide_format == std::string::npos) throw ErrorMassage("Error::「" + m_file_name + "」の形式を入れてください。");

	std::string format = m_file_name.substr(divide_format + 1);
	std::transform(format.begin(), format.end(), format.begin(), ::tolower);

	if (format == "mp3" || format == "wav" || format == "ogg") m_sound_file = LoadSoundMem(m_file_name.c_str());
	else throw ErrorMassage("Error::「" + m_file_name + "」の形式が音声ではありませんでした。");

	if (!CheckSetSoundFile()) throw ErrorMassage("Error::「" + m_file_name + "」を読み込みましたが、音声を確保できませんでした。");

	return get ? m_sound_file : NULL;
}

ImageFile::ImageFile(const std::string& file_name) : File(file_name){
	size_t divide_format = m_file_name.find_last_of(".");
	if (divide_format == std::string::npos) throw ErrorMassage("Error::「" + m_file_name + "」の形式を入れてください。");

	std::string format = m_file_name.substr(divide_format + 1);
	std::transform(format.begin(), format.end(), format.begin(), ::tolower);

	if (format == "png" || format == "jpeg" || format == "bmp" || format == "dds" || format == "argb" || format == "tga")
		m_image_file = LoadGraph(m_file_name.c_str());
	else throw ErrorMassage("Error::「" + m_file_name + "」の形式が画像ではありませんでした。");

	if (!CheckSetImageFile()) throw ErrorMassage("Error::「" + m_file_name + "」を読み込みましたが、画像を確保できませんでした。");
}

int ImageFile::Base_LoadFile(const std::string& file_name, bool get) {
	if (!file_name.empty()) { //文字列が空でない時
		if (!(file_name.front() == '.')) { //最初の文字が「.」でない時(ファイル名のみ)
			if (m_file_name == file_name) throw ErrorMassage("Error::「" + file_name + "」は存在しているため、開けません。");

			m_file.open(file_name, BINARY | IN | OUT);

			m_file_name = file_name;
		}
		else if (file_name.find("../") != std::string::npos) { //相対パスの後にファイルがあった時
			fs::path project = fs::path(__FILE__).parent_path(); //このソースコードがあるファイルのパスを返す。(_FILE_がそれ)
			fs::path clean_path = fs::canonical(project / file_name); //canonical→絶対パスへ変換したものを省略されている「../」を除く
			std::string generic = clean_path.generic_string(); //絶対パスでは「＼＼」が区切りとして入っているため、generic_string関数で「/」に戻す
			
			if (m_file_name == generic) throw ErrorMassage("Error::「" + generic + "」は存在しているため、開けません。");

			m_file.open(generic, BINARY | IN | OUT);

			m_file_name = generic;
		}
	}

	if (!m_file.is_open()) throw ErrorMassage("Error::「" + m_file_name + "」を読み込めませんでした。");

	m_file.seekg(std::ios::end); //ファイルポインタの位置を最後尾へ
	m_size = m_file.tellg(); //ファイルのメモリサイズを取得(先頭から何バイト目か)
	m_file.seekg(std::ios::beg); //ファイルポインタの位置を先頭へ

	size_t save_buf = m_buf.size();
	m_buf.resize(save_buf + sizeof(size_t)); //スペースを空けておく。
	std::memcpy(&m_buf[save_buf], &m_size, sizeof(size_t)); //サイズをコピー

	m_file.read((char*)m_buf.data(), m_size);
	if (m_size == NULL) throw ErrorMassage("Error::ファイルのサイズを取得できませんでした。");

	m_file.close();

	if (m_image_file != -1) DeleteGraph(m_image_file);

	size_t divide_format = m_file_name.find_last_of(".");
	if (divide_format == std::string::npos) throw ErrorMassage("Error::「" + m_file_name + "」の形式を入れてください。");

	std::string format = m_file_name.substr(divide_format + 1);
	std::transform(format.begin(), format.end(), format.begin(), ::tolower);

	if (format == "png" || format == "jpeg" || format == "bmp" || format == "dds" || format == "argb" || format == "tga")
		m_image_file = LoadGraph(m_file_name.c_str());
	else throw ErrorMassage("Error::「" + m_file_name + "」の形式が画像ではありませんでした。");

	if (!CheckSetImageFile()) throw ErrorMassage("Error::「" + m_file_name + "」を読み込みましたが、画像を確保できませんでした。");

	return get ? m_image_file : NULL;
}

void ImageFile::operator=(const ImageFile& other) {
	if (other.m_file_name != "\0") LoadFile(other.m_file_name);
}

ImageFile& ImageFile::operator=(const ImageFile&& other) noexcept {
	if(this != &other) if (other.m_file_name != "\0") LoadFile(other.m_file_name);

	return *this;
}

MovieFile::MovieFile(const std::string& file_name) : File(file_name){
	size_t divide_format = file_name.find_last_of(".");
	if (divide_format == std::string::npos) throw ErrorMassage("Error::「" + m_file_name + "」の形式を入れてください。");

	std::string format = file_name.substr(divide_format + 1);
	std::transform(format.begin(), format.end(), format.begin(), ::tolower);

	if (format == "mp4") {
		m_movie_file = LoadGraph(file_name.c_str());
		if (!CheckSetMovieFile()) throw ErrorMassage("Error::「" + m_file_name + "」を読み込みましたが、映像を確保できませんでした。");

		m_movie_frame = GetMovieTotalFrameToGraph(m_movie_file);
		if (m_movie_frame == -1 || m_movie_frame == NULL) throw ErrorMassage("Error::「" + m_file_name + "」の再生時間を取得できませんでした。");
	}
	else throw ErrorMassage("Error::「" + m_file_name + "」の形式が映像ではありませんでした。");
}

int MovieFile::Base_LoadFile(const std::string& file_name, bool get) {
	if (!file_name.empty()) { //文字列が空でない時
		if (!(file_name.front() == '.')) { //最初の文字が「.」でない時(ファイル名のみ)
			if (m_file_name == file_name) throw ErrorMassage("Error::「" + file_name + "」は存在しているため、開けません。");

			m_file.open(file_name, BINARY | IN | OUT);

			m_file_name = file_name;
		}
		else if (file_name.find("../") != std::string::npos) { //相対パスの後にファイルがあった時
			fs::path project = fs::path(__FILE__).parent_path(); //このソースコードがあるファイルのパスを返す。(_FILE_がそれ)
			fs::path clean_path = fs::canonical(project / file_name); //canonical→絶対パスへ変換したものを省略されている「../」を除く
			std::string generic = clean_path.generic_string(); //絶対パスでは「＼＼」が区切りとして入っているため、generic_string関数で「/」に戻す
			
			if (m_file_name == generic) throw ErrorMassage("Error::「" + generic + "」は存在しているため、開けません。");

			m_file.open(generic, BINARY | IN | OUT);

			m_file_name = generic;
		}
	}

	if (!m_file.is_open()) throw ErrorMassage("Error::「" + m_file_name + "」を読み込めませんでした。");

	m_file.seekg(std::ios::end); //ファイルポインタの位置を最後尾へ
	m_size = m_file.tellg(); //ファイルのメモリサイズを取得(先頭から何バイト目か)
	m_file.seekg(std::ios::beg); //ファイルポインタの位置を先頭へ

	size_t save_buf = m_buf.size();
	m_buf.resize(save_buf + sizeof(size_t)); //スペースを空けておく。
	std::memcpy(&m_buf[save_buf], &m_size, sizeof(size_t)); //サイズをコピー

	m_file.read((char*)m_buf.data(), m_size);
	if (m_size == NULL) throw ErrorMassage("Error::ファイルのサイズを取得できませんでした。");

	m_file.close();

	if (m_movie_file != -1) DeleteGraph(m_movie_file); //既に映像が設定されている場合、メモリから削除する。

	size_t divide_format = m_file_name.find_last_of(".");
	if (divide_format == std::string::npos) throw ErrorMassage("Error::「" + m_file_name + "」の形式を入れてください。");

	std::string format = m_file_name.substr(divide_format + 1);
	std::transform(format.begin(), format.end(), format.begin(), ::tolower);

	if (format == "mp4") {
		m_movie_file = LoadGraph(m_file_name.c_str());
		if (!CheckSetMovieFile()) throw ErrorMassage("Error::「" + m_file_name + "」を読み込みましたが、映像を確保できませんでした。");

		m_movie_frame = GetMovieTotalFrameToGraph(m_movie_file);
		if (m_movie_frame == -1 || m_movie_frame == NULL) throw ErrorMassage("Error::「" + m_file_name + "」の再生時間を取得できませんでした。");

	}
	else throw ErrorMassage("Error::「" + m_file_name + "」の形式が映像ではありませんでした。");

	return get ? m_movie_file : NULL;
}

void MovieFile::operator=(const MovieFile& other) {
	if(other.m_file_name != "\0") LoadFile(other.m_file_name);
}

MovieFile& MovieFile::operator=(const MovieFile&& other) noexcept{
	if(this != &other) if (other.m_file_name != "\0") LoadFile(other.m_file_name);

	return *this;
}