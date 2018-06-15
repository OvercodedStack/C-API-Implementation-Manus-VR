///////////////////////////////////////////////////////////////////////////////
//
//  Original System: ManusGlove.cpp or Source.cpp
//  Subsystem:       Human-Robot Interaction
//  Workfile:        ManusHandConverter.h
//  Revision:        1.0 - 6/5/2018
//  Author:          Esteban Segarra
//
//  Description
//  ===========
//  Data structure design for the Manus hand devices. Designed to be readily called as a API wrapper to the Manus.h SDK.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once	
#include <stdio.h>
#include <iostream>
#include "..\..\Libs\Manus\Manus.h"
#include <set>
#include <vector>


namespace manus_interface {

	using std::vector;
	//Common struts for design
	typedef struct quarternion Quarternion;
	typedef struct vector_manus Vector_manus;
	typedef struct pose Pose;


	struct quarternion {
		double x, y, z, w;
	};

	struct vector_manus {
		double x, y, z;
	};

	struct pose {
		vector_manus  translation;
		quarternion  rotation;
	};
}