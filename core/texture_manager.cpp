#include "texture_manager.h"
#include "game.h"
Texture_manager* Texture_manager::m_instance{ nullptr };

Texture_manager* Texture_manager::instance()
{
    if (m_instance == nullptr) {
        m_instance = new Texture_manager();
    }
    return m_instance;
}

Texture_manager::~Texture_manager()
{
    for (auto p : m_texture) {
        if (p.second != nullptr)
        {
            SDL_DestroyTexture(p.second);
            p.second = nullptr;
        }
    }
    delete m_instance;
    m_instance = nullptr;
    TTF_CloseFont(m_level_font);
    TTF_CloseFont(m_strength_font);
}

bool Texture_manager::load(const std::string& file_name, const std::string& id, SDL_Renderer* renderer)
{
    try {
        SDL_Surface* temp_surface = IMG_Load(file_name.c_str());
        if (temp_surface == nullptr) {
            throw -1;
        }
        SDL_Texture* temp_texture = SDL_CreateTextureFromSurface(renderer, temp_surface);
		if (temp_texture == nullptr) {
			throw -2;
		}
        m_texture[id] = temp_texture;
        SDL_FreeSurface(temp_surface);
        return true;
    }
    catch (int x) {
		if (x==-1) game::instance()->get_log_file() <<"Error: "<< IMG_GetError() << '\n';
        if (x==-2) game::instance()->get_log_file() << "Error: " << SDL_GetError() << '\n';
		return false;
	}
}

void Texture_manager::draw(const std::string& id, int x, int y, int w, int h, SDL_Renderer* renderer, SDL_RendererFlip flip)
{
    try {
        if (m_texture.find(id) == m_texture.end()) {
			throw id;
		}
    }
    catch (const std::string &e) {
		game::instance()->get_log_file() << "Error: Cannot find id: "<<e <<" in texture map.\n";
		exit(EXIT_FAILURE);
	}
    SDL_Rect source_rect{};
    SDL_Rect destination_rect{};

    source_rect.x = source_rect.y = 0;
    destination_rect.x = x;
    destination_rect.y = y;
    source_rect.w = destination_rect.w = w;
    source_rect.h = destination_rect.h = h;
    SDL_RenderCopyEx(renderer, m_texture[id], &source_rect, &destination_rect, 0.0, NULL, flip);
}

void Texture_manager::draw_frame(const std::string& id, int x, int y, int w, int h, int current_row, int current_frame, SDL_Renderer* renderer, SDL_RendererFlip flip)
{
    try {
		if (m_texture.find(id) == m_texture.end()) {
			throw id;
		}
	}
	catch (const std::string &e) {
		game::instance()->get_log_file() << "Error: Cannot find id: " << e << " in texture map.\n";
		exit(EXIT_FAILURE);
	}
    SDL_Rect source_rect{};
    SDL_Rect destination_rect{};

    source_rect.x = w * (current_frame);
    source_rect.y = h * (current_row - 1);
    destination_rect.x = x;
    destination_rect.y = y;
    destination_rect.w = source_rect.w = w;
    destination_rect.h = source_rect.h = h;
    SDL_RenderCopyEx(renderer, m_texture[id], &source_rect, &destination_rect, 0.0, NULL, flip);
}

void Texture_manager::remove_from_texture_map(const std::string& texture_id)
{
    if (m_texture.find(texture_id) != m_texture.end() && m_texture[texture_id] != nullptr) {
        SDL_DestroyTexture(m_texture[texture_id]);
        m_texture[texture_id] = nullptr;
    }
    m_texture.erase(texture_id);
}

bool Texture_manager::create_texture_from_string(const std::string& string, const std::string& id, int r, int b, int g, int a,int font, SDL_Renderer* renderer)
{
    SDL_Color color{ r,b,g,a };
    TTF_Font* temp_font{ nullptr };
    switch (font)
    {
    case 0:
		temp_font = m_level_font;
		break;
    case 1:
        temp_font = m_strength_font;
        break;
    case 2:
        temp_font = m_result_font;
		break;
    default:
        game::instance()->get_log_file() << "Error: Cannot find font id: " << font << " in texture map.\n";
        exit(EXIT_FAILURE);
    }
    try
    {
        SDL_Surface* temp_surface{ TTF_RenderText_Blended(temp_font,string.c_str(),color) };
        if (temp_surface == nullptr) {
            throw - 1;
        }
        SDL_Texture* temp_texture{ SDL_CreateTextureFromSurface(renderer,temp_surface) };
        if (temp_texture == nullptr) {
            throw -2;
        }
        m_texture[id] = temp_texture;
        m_text_size[id].h = temp_surface->h;
        m_text_size[id].w = temp_surface->w;
        SDL_FreeSurface(temp_surface);
        return true;
    }
    catch (int x)
    {
        if (x == -1) {
            game::instance()->get_log_file() << TTF_GetError() << '\n';
        }
        if (x == -2) {
			game::instance()->get_log_file() << SDL_GetError() << '\n';
		}
        return false;
    }
}
