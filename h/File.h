#pragma once
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include	<fstream>
#include	<filesystem>
#include	<string>
#include	<vector>
#include	<cstdio>
#include	<memory>
#include	<utility>

#include	"DxLib.h"
#include	"Vector.h"

#define BINARY std::ios::binary
#define IN std::ios::in
#define OUT std::ios::out
#define TRUNC std::ios::trunc


  class File {
	public:
		int LoadFile(const std::string& file_name, bool get = false) { return Base_LoadFile(file_name, get); }
		template<typename T> void LoadFile_Save(const std::string& file_name, const T& data) { LoadFile(file_name); m_file << data; }

		template<typename T> void Save(const T& data); //テンプレートでどの型でもセーブと
		template<typename T> void Load(T* data);	   //ロードできるようにする。

		const std::fstream& GetFile() { return std::move(m_file); }
		const std::string& GetFileName() const { return m_file_name; }
		size_t GetSize() const { return m_size; }

		File() : m_file(""), m_size(0), m_buf(NULL) {}
		File(const std::string& file_name);
		File(File&& other) noexcept : m_file(std::move(other.m_file)), m_buf(other.m_buf), m_size(other.m_size) {}

		virtual ~File() { Destroy(); }

		void operator=(File* other);
		File& operator=(File&& other) noexcept; //この代入演算子オーバーロードは、引数が&&であって、一時的なデータやstd::move関数で情報を失ってもよい。
												//noexceptは確実にエラーを発生させないためにする。

		bool operator==(const File& other) const { return this->m_file_name == other.m_file_name; }
	protected:
		size_t m_size;

		std::fstream m_file;

		std::string m_file_name;

		std::vector<unsigned char> m_buf;

		virtual int Base_LoadFile(const std::string& file_name, bool get) = 0;

	private:
		virtual void Destroy() {}
  };

  class SoundFile : public File {
  public:
	  SoundFile() : File(){}
	  SoundFile(const std::string& file_name);
	  SoundFile(SoundFile&& other) noexcept : File(std::move(other)){}

	  virtual ~SoundFile(){}

	  void operator=(const SoundFile& other);
	  SoundFile& operator=(const SoundFile&& other) noexcept;

	  bool operator==(const SoundFile& other) { return this->m_sound_file == other.m_sound_file; }

	  int GetSoundFile() const { return m_sound_file; }

	  bool CheckSetSoundFile() const { return m_sound_file != -1 && m_sound_file != NULL; }

	  void Destroy() override { if (CheckSetSoundFile()) DeleteSoundMem(m_sound_file); }

  private:
	  int m_sound_file = NULL;

	  int Base_LoadFile(const std::string& file_name, bool get) override;

  };
  class ImageFile : public File {
	public:
		ImageFile() : File() {}
		ImageFile(const std::string& file_name);
		ImageFile(ImageFile&& other) noexcept : File(std::move(other)) {}

		virtual ~ImageFile() {}

		void operator=(const ImageFile& other);
		ImageFile& operator=(const ImageFile&& other) noexcept;

		bool operator==(const ImageFile& other) { return this->m_image_file == other.m_image_file; }

		int GetImageFile() const { return m_image_file; }

		bool CheckSetImageFile() const { return m_image_file != -1 && m_image_file != NULL; }

		void Destroy() override { if (CheckSetImageFile()) { DeleteGraph(m_image_file); m_image_file = -1; } }

	private:
		int m_image_file = NULL;

		int Base_LoadFile(const std::string& file_name, bool get) override;

  };

  class MovieFile : public File {
	public:
		MovieFile() : File() {}
		MovieFile(const std::string& file_name);
		MovieFile(const MovieFile& other) { operator=(other); }

		virtual ~MovieFile() {}

		void operator=(const MovieFile& other);
		MovieFile& operator=(const MovieFile&& other) noexcept;

		bool operator==(const MovieFile& other) { return this->m_movie_file == other.m_movie_file; }

		int GetMovieFile() const { return m_movie_file; }
		int GetFrame() const { return m_movie_frame - 1; }

		bool CheckSetMovieFile() const { return m_movie_file != -1 && m_movie_file != NULL; }

		void Destroy() override { if (CheckSetMovieFile()) { DeleteGraph(m_movie_file); m_movie_file = -1; } }
	private:
		int m_movie_file = NULL;
		int m_movie_frame = NULL;

		int Base_LoadFile(const std::string& file_name, bool get) override;
  };
