#include "../hdr/point.hpp"
#include "../hdr/render.hpp"

namespace engine {
	Point::Point() :
		inMotion(true), isActive(false) {
	}

	void Point::applyForce(gs::Vec2f force) {
		appliedForce += force; 
	}
	void Point::update() {
		gs::Vec2f velocity = gs::Vec2f(
			position.x - previousPosition.x, 
			position.y - previousPosition.y
		);

		//If the mouse is clicked and no point is selected. 
		if (gs::input::activeMouseClickL && pointSelected == nullptr && 
			inMotion) {
			//The distance between the currentPoint and the mousePosition. 
			float distance = gs::util::distance(
				position, gs::input::mousePosition
			);

			//If the mouse is within the point, select it. 
			if (distance < render::pointRadius + 8.0f) 
				pointSelected = this;
		}
		//If the mouse isn't clicked unselect any selected points. 
		else if (!gs::input::activeMouseClickL)
			pointSelected = nullptr; 

		if (inMotion) {
			//Force of gravity. 
			applyForce(gs::Vec2f(0.0f, gravitationalForce));
			
			//If point is selected apply force in its direction.
			if (this == pointSelected) {
				gs::Vec2f direction = gs::Vec2f(
					gs::input::mousePosition.x - position.x, 
					gs::input::mousePosition.y - position.y
				);

				appliedForce = gs::Vec2f(0.0f, 0.0f); 
				applyForce(gs::Vec2f(
					direction.x / 2.0f,
					direction.y / 2.0f
				));
			}
		}

		previousPosition = position; 
		position += velocity + appliedForce; 
		appliedForce = gs::Vec2f(0.0f, 0.0f); 

		gs::util::clamp(&position.x, 0.0f, render::uiOffset);
		gs::util::clamp(
			&position.y, 0.0f, static_cast<float>(render::window::windowSize.y)
		);
	}

	float Point::gravitationalForce = 0.5f;

	Point points[mMaxNumOfPoints];
	Point* pointSelected = nullptr;

	int addPoint(gs::Vec2f position, bool inMotion) {
		for (int pointIndex = 0; pointIndex < mMaxNumOfPoints; ++pointIndex) {
			Point& currentPoint = points[pointIndex]; 

			if (currentPoint.isActive)
				continue; 

			currentPoint.position = position; 
			currentPoint.previousPosition = currentPoint.position; 
			currentPoint.appliedForce = gs::Vec2f(0.0f, 0.0f);
			currentPoint.inMotion = inMotion; 
			currentPoint.isActive = true;

			return pointIndex; 
		}

		return -1; 
	}
	void removePoint(int index) {
		points[index].isActive = false; 
	}
}