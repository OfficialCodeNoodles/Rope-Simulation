#include "../hdr/segment.hpp"
#include "../hdr/render.hpp"

namespace engine {
	Segment::Segment() :
		point1(nullptr), point2(nullptr), length(0.0f), tension(0.0f) {
	}

	void Segment::update() {
		const float deltaX = point1->position.x - point2->position.x; 
		const float deltaY = point1->position.y - point2->position.y; 
		
		float distance = std::sqrt(std::pow(deltaX, 2) + std::pow(deltaY, 2));
		
		distance = (length - distance) / distance; 
		
		float translateX = deltaX * distance * flexibility; 
		float translateY = deltaY * distance * flexibility; 

		tension = (std::abs(translateX) + std::abs(translateY)) * 3.0f; 

		if (point1->inMotion) {
			point1->position.x += translateX;
			point1->position.y += translateY;
		}

		if (point2->inMotion) {
			point2->position.x -= translateX;
			point2->position.y -= translateY;
		}
	}

	float Segment::flexibility = 0.25f; 

	Segment segments[mMaxNumOfSegments];
	int currentPointIndex = 0; 

	void updatePoints() {
		for (Segment& segment : segments) {
			if (segment.point1 != nullptr) 
				segment.point1->update(); 
			if (segment.point2 != nullptr)
				segment.point2->update(); 
		}
	}
	void updateSegments() {
		for (Segment& segment : segments) {
			if (segment.point1 != nullptr) {
				if (segment.point1->isActive == false) {
					segment.point1 = nullptr;
					segment.point2 = nullptr;
				}
			}
			if (segment.point2 != nullptr) {
				if (segment.point2->isActive == false) {
					segment.point1 = nullptr;
					segment.point2 = nullptr;
				}
			}

			if (segment.point1 != nullptr &&
				segment.point2 != nullptr) {
				segment.update(); 
			}
			else if (segment.point1 == nullptr ||
				segment.point2 == nullptr) {
				segment.point1 = nullptr; 
				segment.point2 = nullptr; 
			}
		}
	}
	void addSegment(Point* point1, Point* point2, float length) {
		for (int segmentIndex = 0; segmentIndex < mMaxNumOfSegments;
			++segmentIndex) {
			Segment& currentSegment = segments[segmentIndex];

			if (currentSegment.point1 != nullptr &&
				currentSegment.point2 != nullptr)
				continue; 

			currentSegment.point1 = point1; 
			currentSegment.point2 = point2; 
			currentSegment.length = length; 

			break; 
		}
	}

	void generatePoints(int index) {
		static const float centerX = render::uiOffset / 2.0f; 
		static const float centerY = render::window::windowSize.y / 2.0f; 

		for (int pointIndex = 0; pointIndex < mMaxNumOfPoints; ++pointIndex) 
			removePoint(pointIndex); 

		updateSegments(); 

		switch (index) {
		case 0:
		{
			int index = 1;

			engine::addPoint(gs::Vec2f(centerX, 100.0f), false);

			for (float ypos = 250.0f; ypos < 800.0f; ypos += 50.0f) {
				engine::addPoint(gs::Vec2f(centerX, ypos)); 

				engine::addSegment(
					&points[index - 1],
					&points[index],
					50.0f
				);

				++index; 
			}
		}
			break; 
		case 1:
			engine::addSegment(
				&engine::points[engine::addPoint(gs::Vec2f(
					centerX, centerY
				), false)],
				&engine::points[engine::addPoint(gs::Vec2f(
					centerX, centerY + 300.0f
				))],
				300.0f
			);
			engine::addSegment(
				&engine::points[0],
				&engine::points[engine::addPoint(gs::Vec2f(
					centerX - 50.0f, centerY + 380.0f
				))],
				100.0f
			);
			engine::addSegment(
				&engine::points[2],
				&engine::points[engine::addPoint(gs::Vec2f(
					centerX + 50.0f, centerY + 380.0f
				))],
				100.0f
			);
			engine::addSegment(
				&engine::points[3],
				&engine::points[0],
				100.0f
			);

			break; 
		case 2:
			engine::addSegment(
				&engine::points[engine::addPoint(gs::Vec2f(
					centerX-600.0f, 100.0f
				), false)],
				&engine::points[engine::addPoint(gs::Vec2f(
					centerX-550, 400.0f
				))],
				300.0f
			);
			engine::addSegment(
				&engine::points[engine::addPoint(gs::Vec2f(
					centerX + 600.0f, 100.0f
				), false)],
				&engine::points[engine::addPoint(gs::Vec2f(centerX + 550, 400.0f))],
				300.0f
			);
			engine::addSegment(
				&engine::points[0], 
				&engine::points[2],
				550.0f * 2.0f
			);

			break; 
		case 3:
		{
			int index = 0; 

			for (float xpos = 0.0f; xpos <= render::uiOffset; xpos += 50.0f) {
				addPoint(gs::Vec2f(
					xpos, 
					100.0f
				), xpos > 0.0f && (xpos < render::uiOffset));

				if (xpos != 0.0f) {
					addSegment(
						&points[index - 1],
						&points[index],
						50.0f
					);
				}

				++index; 
			}
		}
			break; 
		case 4:
		{
			int index = 0;

			for (float angle = 0.0f; angle < 360.0f; angle += 10.0f) {
				addPoint(gs::Vec2f(
					centerX + (300.0f * std::cos(gs::util::toRadians(angle))),
					centerY + (300.0f * std::sin(gs::util::toRadians(angle)))
				), true);

				if (angle != 0.0f) {
					addSegment(
						&points[index - 1],
						&points[index],
						300.0f * gs::util::toRadians(10.0f)
					);
				}  

				++index;
			}

			addSegment(
				&points[index - 1],
				&points[0],
				300.0f * gs::util::toRadians(10.0f)
			);
		}
			break; 
		}
	}
}