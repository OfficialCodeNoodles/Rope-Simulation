#pragma once

//Dependencies
#include "include.hpp"

namespace engine {
	struct Point {
		gs::Vec2f position, previousPosition;
		gs::Vec2f appliedForce;
		bool inMotion;
		bool isActive;

		Point(); 

		void applyForce(gs::Vec2f force); 
		void update(); 

		static float gravitationalForce; 
	};

	extern Point points[mMaxNumOfPoints];
	extern Point* pointSelected; 

	int addPoint(gs::Vec2f position, bool inMotion = true); 
	void removePoint(int index); 
}