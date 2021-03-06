#pragma once

//SDL Libraries
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
//Utilities
#include <string>
#include <chrono>

namespace clf {
	// ----------------------------------------------------------------
	// - Engine Specification                                         -
	// ----------------------------------------------------------------
	class Engine {
	public:
		Engine() = default;
		virtual ~Engine() = default;
	public:
		bool Build(const char* title, size_t screen_width, size_t screen_height, int subsystemFlags, int windowFlags, const char* iconPath);
		static int ScreenWidth();
		static int ScreenHeight();
		static int HalfScreenWidth();
		static int HalfScreenHeight();
		static SDL_Renderer* GetRenderer();
	protected:
		//Initialize your stuff here
		virtual void OnStart();
		//Modify your stuff based in the input here
		virtual void OnInput(const Uint8* keystates);
		//Modify your stuff at a constant time step here
		virtual void OnUpdate(float deltaTime);
		//Draw your stuff in the screen here
		virtual void OnRender();
		//Free your stuff here
		virtual void OnFinish();
	private:
		bool Initialize(const char* title, size_t screen_width, size_t screen_height, int subsystemFlags, int windowFlags, const char* iconPath);
		static SDL_Renderer* renderer;
		static SDL_Window* window;
		const float MAX_DELTA_TIME{ 0.02f };
		float deltaTime{ 0.0f };
		bool isRunning{ false };
		static int screenWidth;
		static int screenHeight;
		SDL_Event event;
	};

	// ----------------------------------------------------------------
	// - Info Specification                                           -
	// ----------------------------------------------------------------
	//Useful info about SDL classes
	class Info {
	private:
		Info() = default;
		~Info() = default;
	public:
		static int GetTextureWidth(SDL_Texture* texture);
		static int GetTextureHeight(SDL_Texture* texture);
	};

	// ----------------------------------------------------------------
	// - Color Constants		                                      -
	// ----------------------------------------------------------------
	class Color {
	private:
		Color() = default;
		~Color() = default;
	public:
		static constexpr SDL_Color METALLIC_BRONZE{ 76, 57, 26, 255 };
		static constexpr SDL_Color HOT_PINK{ 255, 102, 209, 255 };
		static constexpr SDL_Color POMEGRANATE{ 239, 52, 52, 255 };
		static constexpr SDL_Color MALIBU{ 94, 150, 255, 255 };
		static constexpr SDL_Color PORTAFINO{ 255, 249, 186, 255 };
		static constexpr SDL_Color SCREAMIN_GREEN{ 87, 249, 84, 255 };
		static constexpr SDL_Color TURQUOISE{ 68, 229, 162, 255 };
		static constexpr SDL_Color ROYAL_BLUE{ 114, 66, 237, 255 };
	};

	// ----------------------------------------------------------------
	// - Asset Specification                                          -
	// ----------------------------------------------------------------
	class Asset {
	private:
		Asset() = default;
		~Asset() = default;
	public:
		static SDL_Texture* LoadSprite(const char* filepath);
		static SDL_Texture* LoadText(const char* filepath, int size, const char* text, const SDL_Color& color, int outline, int style);
		static SDL_Texture* ChangeText(SDL_Texture* texture, const char* filepath, int size, const char* text, const SDL_Color& color, int outline, int style);
		static Mix_Music* LoadMusic(const char* filepath);
		static Mix_Chunk* LoadSound(const char* filepath);
		static void FreeTexture(SDL_Texture* texture);
		static void FreeMusic(Mix_Music* music);
		static void FreeSound(Mix_Chunk* sound);
		static void FreeChannel(size_t channel);
	};

	// ----------------------------------------------------------------
	// - Render Specification		                                  -
	// ----------------------------------------------------------------
	class Render {
	private:
		Render() = default;
		~Render() = default;
	public:
		static void Clear(const SDL_Color& color);
		static void DrawLine(const SDL_Point& start, const SDL_Point& end, const SDL_Color& color);
		static void DrawTriangle(const SDL_Point& v1, const SDL_Point& v2, const SDL_Point& v3, const SDL_Color& color);
		static void DrawFillRect(const SDL_Rect& destination, const SDL_Color& color);
		static void DrawRect(const SDL_Rect& destination, const SDL_Color& color);
		static void DrawCircle(const SDL_FPoint& topLeft, double radius, const SDL_Color& color);
		static void DrawFillCircle(const SDL_Point& topLeft, int radius, const SDL_Color& color);
		static void DrawSprite(SDL_Texture* texture, const SDL_Rect& source, const SDL_Rect& destination);
		static void DrawSpriteRot(SDL_Texture* texture, const SDL_Rect& source, const SDL_Rect& destination, const double angle, const SDL_Point* center, const SDL_RendererFlip& flip);
		static void DrawText(SDL_Texture* texture, const SDL_Rect& destination);
		static void DrawTextRot(SDL_Texture* texture, const SDL_Rect& destination, const double angle, const SDL_Point* center, const SDL_RendererFlip& flip);
	};

	// ----------------------------------------------------------------
	// - Sound Specification		                                  -
	// ----------------------------------------------------------------
	class Sound {
	private:
		Sound() = default;
		~Sound() = default;
	public:
		//Music Methods
		static bool IsPlayingMusic(); 
		static int GetMusicVolume();
		static void SetMusicVolume(size_t volume); 
		static void PauseMusic(); 
		static void ResumeMusic(); 
		static void PlayMusic(Mix_Music* music, int repeat); 
		static void PlayFadeInMusic(Mix_Music* music, int repeat, size_t miliseconds); //
		static void FadeOutMusic(size_t miliseconds); 
		static void ChangeMusic(Mix_Music* newMusic, int repeat);
		static void ChangeFadeInMusic(Mix_Music* newMusic, int repeat, size_t miliseconds);
		static void ChangeFadeOutMusic(Mix_Music* newMusic, int repeat, size_t miliseconds);
		static void ChangeFadeOutFadeInMusic(Mix_Music* newMusic, int repeat, size_t inMS, size_t outMS);
		//Channel Methods (For sound effects)
		static bool IsPlayingChannel(int channel);
		static int GetChannelVolume(int channel);
		static void SetChannelVolume(int channel, size_t volume);
		static void PauseChannel(int channel);
		static void ResumeChannel(int channel);
		static void PlayChannel(int channel, Mix_Chunk* sound, int repeat);
		static void PlayFadeInChannel(int channel, Mix_Chunk* sound, int repeat, size_t miliseconds);
		static void FadeOutChannel(int channel, size_t miliseconds);
	};
		
}


