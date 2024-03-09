#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <map>
#include <string>

class Texture_manager
{
public:
	//This function is used to initialize Texture_manger object.
	//You need to call this function whenever you want to access Texture_manger member function.
	static Texture_manager* instance();
	//Destructor
	~Texture_manager();
	//Load image
	bool load(std::string file_name, std::string id, SDL_Renderer* renderer);

	//Draw texture to screen. Use this for drawing texture.
	//Parameters:
	//id: id of texture
	//x,y: postion to draw texture
	//w,h: size of texture
	//renderer: renderer to copy to
	//flip: how picture is displayed (SDL_FLIP_NONE by default)
	void draw(std::string id, int x, int y, int w, int h, SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Draw texture to screen. Use this for drawing sprite sheet.
	//Parameters:
	//id: id of texture
	//x,y: postion to draw texture
	//w,h: size of texture
	//current_row: row in which texture is located
	//current_frame: frame in which texture is located in a row.
	//renderer: renderer to copy to
	//flip: how picture is displayed (SDL_FLIP_NONE by default)
	void draw_frame(std::string id, int x, int y, int w, int h, int current_row, int current_frame, SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	//remove texture from map
	//Parameters:
	//texture_id: id of texture to remove
	void remove_from_texture_map(std::string texture_id);
	//Create texture from string
	//Parameters:
	//string: string to create texture from
	//id: id of texture
	//r,g,b,a: color of text
	//font: font to use (0 for level font, 1 for strength font, 2 for result font)
	//renderer: renderer to copy to
	bool create_texture_from_string(std::string string, std::string id, int r, int b, int g, int a, int font, SDL_Renderer* renderer);
	//Get text height
	int get_text_height(std::string id) { return m_text_size[id].h; }
	//Get text width
	int get_text_width(std::string id) { return m_text_size[id].w; }
	bool is_texture_in_map(std::string id) { return m_texture.find(id) != m_texture.end()&&m_texture[id]!=nullptr; }
private:
	std::map<std::string, SDL_Texture*> m_texture{};
	//Ensure that Texture_manager can be initialized only once
	Texture_manager() : m_level_font{ TTF_OpenFont("pic/ChangaOne-Regular.ttf",60) }, m_strength_font{ TTF_OpenFont("pic/ChangaOne-Regular.ttf", 30) }, result_font{ TTF_OpenFont("pic/ChangaOne-Regular.ttf", 80) } {}
	//Check whether object is instanced. Note: Static member variable cannot be initialized in declaration.
	static Texture_manager* m_instance;
	TTF_Font* m_level_font{};
	TTF_Font* m_strength_font{};
	TTF_Font* result_font{};
	struct Text_size
	{
		int w;
		int h;
	};
	std::map<std::string, Text_size> m_text_size{};
};

#endif // !TEXTURE_MANAGER_H


