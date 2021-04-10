#pragma once
typedef struct _TTF_Font TTF_Font;

namespace dae
{
	class Font
	{
	public:
		Font(const std::string& fullPath, unsigned int size);
		~Font();

		Font(const Font &) = delete;
		Font(Font &&) = delete;
		Font & operator= (const Font &) = delete;
		Font & operator= (const Font &&) = delete;

		TTF_Font* GetFont() const;
		void SetSize(unsigned int size);
	
	private:
		TTF_Font* m_font;
		const std::string m_path;
		unsigned int m_size;
	};

}
