#include "../hdr/render.hpp"

int ticks = 0;

gs::util::Clock timer; 

void events() {
	engine::render::window::updateWindow();

	engine::render::updateUI(); 
	if (!engine::render::simulationFrozen) {
		engine::updatePoints();
		engine::updateSegments();
	}
}
void graphics() {
	engine::render::window::begin(gs::Color(20, 20, 25));

	engine::render::renderSegments(); 
	if (engine::render::pointsEnabled)
		engine::render::renderPoints();
	engine::render::renderUI(); 

	engine::render::window::end(); 
}

 int main() {
	engine::render::window::createWindow(false); 
	engine::render::loadAssets();
	engine::generatePoints(engine::currentPointIndex); 

	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, 0);

	while (engine::render::window::winmain->isOpen()) {
		timer.begin(); 
		
		events(); 

		if (engine::render::window::virtualFrameRate !=
			engine::render::window::frameRate) {
			if (ticks % (engine::render::window::frameRate /
				engine::render::window::virtualFrameRate) == 0)
				graphics(); 
		}
		else 
			graphics(); 

		timer.end();
		timer.wait(engine::render::window::frameRate);
		++ticks; 
	}

	engine::render::window::closeWindow(); 

	return 0; 
}

 /*
 Settings

 Change Flexibility
 Change Gravity
 Change Dampening

 Generate Mesh

 Disable Points
 Zero Velocity
 Freeze Simulation
 Change FrameRate  

 Exit Button
 */