///////////////////////////////////////////////////////////////////////////////
//
//  Original System: ManusGlove.cpp or Source.cpp
//  Subsystem:       Human-Robot Interaction
//  Workfile:        Finger.cpp
//  Revision:        1.0 - 6/7/2018
//  Author:          Esteban Segarra
//
//  Description
//  ===========
//  Data structure for a finger
//
///////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <iostream>
#include "..\..\Libs\Manus\Manus.h"
#include <vector>
#include "ManusHandConverter.h"
#include "Manus_hand_obj.h"
#include "Finger.h"
namespace manus_interface{
	//######################################################################################################################################
	//A finger class
		//Template for Manus data boned
Finger::Finger() {}

Finger::Finger(vector<pose> array_in) {
	bones = array_in;
}
Finger::Finger(vector<double> array_in) {
	bones_doubles = array_in;
}

//Template for single double band finger (raw)
Finger::Finger(double bone_band) {
	bandstrech = bone_band;
}

//Getter for raw finger data
double Finger::get_fingers_raw() {
	return bandstrech;
}

vector<double> Finger::get_fingers_manus() {
	return bones_doubles;
}

//Could be doubles, could be pose data. 
vector<pose> Finger::get_finger_data() {
	return bones;
}
}