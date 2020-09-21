#pragma once

namespace core_renderer {
	class Texture {
	private:
		int m_id;
		unsigned char* m_data;
		int m_width;
		int m_height;
		int m_channels;
	public:
		Texture();
		Texture(const char*);
		~Texture();

		int getId();
		unsigned char* getData();
		int getWidth();
		int getHeight();
		bool isValid();
	};
}
