#pragma once

//Dependencies
#include "include.hpp"

namespace engine {
	namespace render {
		namespace window {
			/// Size of window for creation. 
			extern const gs::Vec2i windowSize; 

			/// Pointer to the RenderWindow used by this program. 
			extern sf::RenderWindow* winmain; 
			/// FullScreen is true when window is fullScreen, false otherwise. 
			extern bool isFullScreen; 
			extern int frameRate; 
			extern int virtualFrameRate;
			extern sf::Image icon;

			void createWindow(bool fullScreen = false); 
			void initWindowStates(); 
			void updateWindow(); 
			void closeWindow(); 

			void begin(gs::Color clearColor = gs::Color()); 
			void end(); 
		}
	}
}