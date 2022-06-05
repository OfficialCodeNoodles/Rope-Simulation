#include "../hdr/render.hpp"

namespace engine {
	namespace render {
		float pointRadius = 12.0f; 
		gs::Color pointColor = gs::Color(120, 120, 125);
		gs::Color anchorPointColor = gs::Color(180, 60, 60); 
		gs::Color selectedPointColor = gs::Color(0, 255, 255); 
		float pointOutlineThickness = 0.0f; 
		gs::Color pointOutlineColor = gs::Color();
		float segmentThickness = 5.0f; 
		gs::Color segmentColor = gs::Color(100, 100, 105);
		bool pointsEnabled = true; 
		bool simulationFrozen = false; 

		sf::Font fonts[mNumOfFonts];
		sf::Text text;
		sf::RectangleShape uiOutline;
		float uiOffset = 1500.0f; 
		gs::Color uiOutlineColor = gs::Color(40, 40, 45);
		gs::Color inactiveTextColor = gs::Color(220, 220, 220); 
		gs::Button exitButton;
		gs::Slider flexibilitySlider;
		gs::Slider gravitySlider;
		gs::Slider dampeningSlider;
		gs::Button generatePointButton;
		gs::Button disablePointsButton;
		gs::Button zeroVelocityButton;
		gs::Button freezeSimulationButton;
		gs::Button frameRateButton;

		void updateUI() {
			//Buttons 
			exitButton.update(); 
			generatePointButton.update(); 
			disablePointsButton.update(); 
			zeroVelocityButton.update(); 
			freezeSimulationButton.update(); 
			frameRateButton.update(); 

			if (exitButton.isSelected && exitButton.isClickedOn)
				window::winmain->close();

			if (generatePointButton.isSelected &&
				generatePointButton.isClickedOn) {
				++currentPointIndex;
				currentPointIndex %= 5; 

				generatePoints(currentPointIndex);
			}

			if (disablePointsButton.isSelected &&
				disablePointsButton.isClickedOn) {
				pointsEnabled = !pointsEnabled;

				if (!pointsEnabled) {
					disablePointsButton.setInactiveFillColor(
						disablePointsButton.getSelectedFillColor()
					);
					disablePointsButton.setInactiveTextFillColor(
						disablePointsButton.getSelectedTextFillColor()
					);
				}
				else {
					disablePointsButton.setInactiveFillColor(
						exitButton.getInactiveFillColor()
					);
					disablePointsButton.setInactiveTextFillColor(
						exitButton.getInactiveTextFillColor()
					);
				}
			}

			if (freezeSimulationButton.isSelected &&
				freezeSimulationButton.isClickedOn) {
				simulationFrozen = !simulationFrozen;

				if (simulationFrozen) {
					freezeSimulationButton.setInactiveFillColor(
						freezeSimulationButton.getSelectedFillColor()
					);
					freezeSimulationButton.setInactiveTextFillColor(
						freezeSimulationButton.getSelectedTextFillColor()
					);
				}
				else {
					freezeSimulationButton.setInactiveFillColor(
						exitButton.getInactiveFillColor()
					);
					freezeSimulationButton.setInactiveTextFillColor(
						exitButton.getInactiveTextFillColor()
					);
				}
			}

			if (zeroVelocityButton.isSelected &&
				zeroVelocityButton.isClickedOn) {
				for (int pointIndex = 0; pointIndex < mMaxNumOfPoints; ++pointIndex) {
					Point& currentPoint = points[pointIndex];

					currentPoint.previousPosition = currentPoint.position; 
				}
			}

			if (frameRateButton.isSelected &&
				frameRateButton.isClickedOn) {
				if (window::virtualFrameRate == 30)
					window::virtualFrameRate = 60;
				else
					window::virtualFrameRate = 30; 
			}

			//Sliders
			flexibilitySlider.update(); 
			gravitySlider.update(); 
			dampeningSlider.update(); 

			Segment::flexibility = 0.5f - (flexibilitySlider.getPercentage(1.0f) * 0.5f);
			Segment::flexibility = std::max(Segment::flexibility, 0.01f); 

			Point::gravitationalForce = gravitySlider.getPercentage(1.0f) * 2.0f;
		}
		
		void loadAssets() {
			for (int fontIndex = 0; fontIndex < mNumOfFonts; ++fontIndex) {
				if (!fonts[fontIndex].loadFromFile(
					std::to_string(fontIndex) + ".ttf"
				))
					break; 
			}

			handleAssets(); 
		}
		void handleAssets() {
			//UI Outline
			uiOutline.setSize(gs::Vec2f(
				window::windowSize.x - uiOffset + 3.0f, 
				window::windowSize.y
			)); 
			uiOutline.setPosition(uiOffset, 0.0f);
			uiOutline.setFillColor(uiOutlineColor); 
			uiOutline.setOutlineThickness(3.0f);
			uiOutline.setOutlineColor(gs::Color::White); 

			//Exit Button
			exitButton.setSize(200.0f, 70.0f);
			exitButton.setCenter(
				uiOffset + ((window::windowSize.x - uiOffset) / 2.0f),
				1000.0f
			); 
			exitButton.setOutlineThickness(1.0f);
			exitButton.setOutlineColor(gs::Color::Black); 
			exitButton.setSelectedScaleModifier(1.0f); 
			exitButton.setSelectedTextScaleModifier(1.0f); 
			exitButton.setClickedScaleModifier(1.0f);
			exitButton.setClickedTextScaleModifier(1.0f);
			exitButton.setFont(fonts[1]);
			exitButton.setString("Exit"); 

			//Flexibility Slider
			flexibilitySlider.setSize(320.0f, 15.0f); 
			flexibilitySlider.setPosition(1550.0f, 220.0f); 
			flexibilitySlider.setPercentage(50.0f); 

			//Gravity Slider 
			gravitySlider = flexibilitySlider; 
			gravitySlider.move(0.0f, 140.0f);
			gravitySlider.setPercentage(25.0f); 

			//Generate Mesh Button
			generatePointButton = exitButton; 
			generatePointButton.setSize(360.0f, 70.0f); 
			generatePointButton.setPosition(1530.0f, 420.0f);
			generatePointButton.setString("Generate New Points"); 

			//Disable Points Button
			disablePointsButton = generatePointButton; 
			disablePointsButton.move(0.0f, 100.0f); 
			disablePointsButton.setString("Disable Points"); 

			//Zero Velocity Button
			zeroVelocityButton = generatePointButton; 
			zeroVelocityButton.setPosition(disablePointsButton.getPosition()); 
			zeroVelocityButton.move(0.0f, 100.0f); 
			zeroVelocityButton.setString("Zero Velocity"); 

			//Freeze Simulation Button
			freezeSimulationButton = generatePointButton; 
			freezeSimulationButton.setPosition(zeroVelocityButton.getPosition()); 
			freezeSimulationButton.move(0.0f, 100.0f); 
			freezeSimulationButton.setString("Freeze Simulation"); 

			//Framerate Button
			frameRateButton = generatePointButton; 
			frameRateButton.setPosition(freezeSimulationButton.getPosition()); 
			frameRateButton.move(0.0f, 100.0f); 
			frameRateButton.setString("Change Framerate"); 
		}

		void renderPoint(Point& point) {
			static sf::CircleShape pointCircle; 

			//Only render point if the radius is greater than 0. 
			if (pointRadius > 0.0f) {
				pointCircle.setRadius(pointRadius); 
				pointCircle.setFillColor( 
					pointSelected == &point ? selectedPointColor : 
						(point.inMotion ? pointColor : anchorPointColor)
				); 
				pointCircle.setOutlineThickness(pointOutlineThickness); 
				pointCircle.setOutlineColor(pointOutlineColor); 
			
				pointCircle.setPosition(point.position); 
				pointCircle.setOrigin(pointRadius, pointRadius); 

				window::winmain->draw(pointCircle); 
			}
		}
		void renderPoints() {
			for (Segment& segment : segments) {
				if (segment.point1 != nullptr)
					renderPoint(*segment.point1);
				if (segment.point2 != nullptr)
					renderPoint(*segment.point2);
			}
		}
		void renderSegment(Segment& segment) {
			static sf::RectangleShape segmentLine;

			gs::Vec2f midPoint = gs::Vec2f(
				(segment.point1->position.x + segment.point2->position.x) 
					/ 2.0f,
				(segment.point1->position.y + segment.point2->position.y)
					/ 2.0f
			);
			float angleBetween = gs::util::toDegrees(std::atan2(
				segment.point1->position.y - segment.point2->position.y,
				segment.point1->position.x - segment.point2->position.x
			)); 

			segmentLine.setSize(gs::Vec2f(
				gs::util::distance(
					segment.point1->position, segment.point2->position
				), segmentThickness
			)); 
			segmentLine.setPosition(midPoint);
			segmentLine.setOrigin(
				segmentLine.getSize().x / 2.0f, segmentLine.getSize().y / 2.0f
			); 
			segmentLine.setRotation(angleBetween); 
			segmentLine.setFillColor(gs::Color(
				std::min(255.0f, segmentColor.r + segment.tension),
				std::min(255.0f, 
					segmentColor.g + std::max(
						0.0f, -std::pow((segment.tension / 10.0f) - 8.0f, 2.0f)
							+ 64.0f
					)
				),
				std::min(255.0f,
					segmentColor.b + std::max(0.0f, (segment.tension - 200.0f) 
						* 2.0f)
				)
			));
			//segmentLine.setFillColor(segmentColor);

			window::winmain->draw(segmentLine); 
		}
		void renderSegments() {
			for (Segment& segment : segments) {
				if (segment.point1 != nullptr &&
					segment.point2 != nullptr) {
					renderSegment(segment); 
				}
			}
		}
		void renderText(
			const std::string& string, gs::Vec2f position, float scale, 
			int fontId, gs::Color fillColor, float outlineThickness,
			gs::Color outlineColor
		) {
			text.setString(string); 
			text.setPosition(position); 
			text.setScale(scale, scale); 
			text.setFont(fonts[fontId]); 
			text.setFillColor(fillColor); 
			text.setOutlineThickness(outlineThickness); 
			text.setOutlineColor(outlineColor); 

			window::winmain->draw(text); 
		}
		void renderUI() {
			//UI Outline 
			window::winmain->draw(uiOutline); 

			//Text
			renderText(
				"CodeNoodles 2022", gs::Vec2f(20.0f, 1030.0f), 1.0f, 0,
				gs::Color::White
			);

			renderText(
				"Settings", gs::Vec2f(1610.0f, 40.0f), 1.5f, 1, 
				gs::Color::White, 1.0f
			);
			renderText(
				"Flexibility", gs::Vec2f(1550.0f, 140.0f), 1.0f, 1,
				inactiveTextColor, 1.0f
			);
			renderText(
				"Gravity Strength", gs::Vec2f(1550.0f, 280.0f), 1.0f, 1,
				inactiveTextColor, 1.0f
			);
			renderText(
				std::to_string(window::virtualFrameRate), 
				gs::Vec2f(1690.0f, 910.0f), 1.0f, 1, inactiveTextColor, 1.0f
			);

			//Buttons
			gs::draw(window::winmain, exitButton);
			gs::draw(window::winmain, generatePointButton); 
			gs::draw(window::winmain, disablePointsButton); 
			gs::draw(window::winmain, zeroVelocityButton); 
			gs::draw(window::winmain, freezeSimulationButton); 
			gs::draw(window::winmain, frameRateButton); 

			//Sliders
			gs::draw(window::winmain, flexibilitySlider); 
			gs::draw(window::winmain, gravitySlider);
		}
	}
}