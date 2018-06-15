///////////////////////////////////////////////////////////////////////////////
//
//  Original System: ManusGlove.cpp or Source.cpp
//  Subsystem:       Human-Robot Interaction
//  Workfile:        Finger.h
//  Revision:        1.0 - 6/7/2018
//  Author:          Esteban Segarra
//
//  Description
//  ===========
//  Data structure for a finger
//
///////////////////////////////////////////////////////////////////////////////

#pragma once
namespace manus_interface {
	class Finger {
		double bandstrech;	//For Raw sensor data only. 
		vector<pose> bones;	//Bone Data -  pose data
		vector<double> bones_doubles;//More Data, for use when using the profile_manus_bone option

	public:
		Finger();

		//Constructor for Manus_profile fingers
		Finger(vector<double> array_in);

		//Constructor for Manus data boned
		Finger(vector<pose> array_in);

		//Template for single double band finger (raw)
		Finger(double bone_band);

		//Get a manus_profile array of doubles
		vector<double> Finger::get_fingers_manus();

		//Getter for raw finger data
		double get_fingers_raw();

		//Could be doubles, could be pose data. 
		vector<pose> get_finger_data();
	};
}