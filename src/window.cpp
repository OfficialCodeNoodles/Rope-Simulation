#include "../hdr/window.hpp"

namespace engine {
	namespace render {
		namespace window {
			const gs::Vec2i windowSize = gs::Vec2i(1920, 1080);

			sf::RenderWindow* winmain = nullptr;
			bool isFullScreen = false; 
			int frameRate = 60;
			int virtualFrameRate = 30;
			sf::Image icon;

			void createWindow(bool fullScreen) {
				//Sets the isFullScreen flag to whatever is sent to this 
				//function. 
				isFullScreen = fullScreen; 

				//If the window has not been created allocate a new 
				//RenderWindow to be used. 
				if (winmain == nullptr) {
					winmain = new sf::RenderWindow(
						sf::VideoMode(windowSize.x, windowSize.y),
						"Rope Simulation",
						mGetStyle(isFullScreen)
					);

					icon.loadFromFile("logo.png");
				}
				//Otherwise call the create window instead. 
				else {
					winmain->create(
						sf::VideoMode(windowSize.x, windowSize.y),
						"Rope Simulation",
						mGetStyle(isFullScreen)
					);
				}

				initWindowStates(); 
			}
			void initWindowStates() {
				gs::input::setWindow(winmain); 

				if (icon.getSize().x > 0)
					winmain->setIcon(
						icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()
					); 
			}
			void updateWindow() {
				sf::Event action; 

				gs::input::updateInputs(); 

				while (winmain->pollEvent(action)) {
					gs::input::updateEvents(action); 

					switch (action.type) {
					case sf::Event::Closed:
						winmain->close();
						break;
					case sf::Event::KeyPressed:
						switch (action.key.code) {
						case sf::Keyboard::Escape:
							winmain->close(); 
							break; 
						case sf::Keyboard::F11:
							createWindow(!isFullScreen); 
							break; 
						}

						break;
					}
				}
			}
			void closeWindow() {
				if (winmain->isOpen())
					winmain->close();

				delete winmain; 
			}

			void begin(gs::Color clearColor) {
				winmain->clear(clearColor); 
			}
			void end() {
				winmain->display(); 
			}
		}
	}
}