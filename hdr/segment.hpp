#pragma once

//Dependencies
#include "point.hpp"

namespace engine {
	struct Segment {
		Point* point1;
		Point* point2;
		float length; 
		float tension; 

		Segment(); 

		void update(); 

		static float flexibility; 
	};

	extern Segment segments[mMaxNumOfSegments]; 
	extern int currentPointIndex; 

	void updatePoints(); 
	void updateSegments(); 
	void addSegment(Point* point1, Point* point2, float length); 
	void generatePoints(int index); 
}