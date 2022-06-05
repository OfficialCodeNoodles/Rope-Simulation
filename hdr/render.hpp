#pragma once

//Dependencies
#include "window.hpp"
#include "segment.hpp"

namespace engine {
	namespace render {
		extern float pointRadius; 
		extern gs::Color pointColor; 
		extern gs::Color anchorPointColor; 
		extern gs::Color selectedPointColor;
		extern float pointOutlineThickness; 
		extern gs::Color pointOutlineColor; 
		extern float segmentThickness; 
		extern gs::Color segmentColor; 
		extern bool pointsEnabled; 
		extern bool simulationFrozen; 

		extern sf::Font fonts[mNumOfFonts]; 
		extern sf::Text text; 
		extern sf::RectangleShape uiOutline;
		extern float uiOffset; 
		extern gs::Color uiOutlineColor;
		extern gs::Color inactiveTextColor;
		extern gs::Button exitButton; 
		extern gs::Slider flexibilitySlider; 
		extern gs::Slider gravitySlider; 
		extern gs::Button generatePointButton; 
		extern gs::Button disablePointsButton; 
		extern gs::Button zeroVelocityButton; 
		extern gs::Button freezeSimulationButton; 
		extern gs::Button frameRateButton; 
		
		void updateUI(); 

		void loadAssets(); 
		void handleAssets(); 

		void renderPoint(Point& point);
		void renderPoints();
		void renderSegment(Segment& segment);
		void renderSegments(); 
		void renderText(
			const std::string& string, gs::Vec2f position, float scale,
			int fontId, gs::Color fillColor = gs::Color::White,
			float outlineThickness = 0.0f,
			gs::Color outlineColor = gs::Color::Black
		); 
		void renderUI(); 
	}
}