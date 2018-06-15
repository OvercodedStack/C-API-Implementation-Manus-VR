///////////////////////////////////////////////////////////////////////////////
//
//  Original System: ManusGlove.cpp or Source.cpp
//  Subsystem:       Human-Robot Interaction
//  Workfile:        Manus_hand_obj.h
//  Revision:        1.0 - 6/7/2018
//  Author:          Esteban Segarra
//
//  Description
//  ===========
// Data structure for a manus_hand object
//
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Manus_interpreter.h"
#include "Finger.h"

namespace manus_interface {
	class Manus_hand_obj {
	private:
		//Arm data from manus
		double arm_lenght;
		double upper_arm_length, upper_arm_neck;
		double lower_arm_length, lower_arm_neck;
		vector_manus upperNeckOffset;

		//In practive, there are 10 bands (Resistive elastic sensors) for each finger on the manus.
		//This array contains all of those measurements starting from the left to rightmsot finger.  
		//double *hand_measurements_raw[10];
		vector<double> hand_measurements_raw;


		//For each finger, a specific bone and position is given by manus to interpret. 
		vector<Finger> hand_fingers;
		vector<Finger> hand_fingers_manus_profile;

	public:
		//Constructor
		Manus_hand_obj();

		//Set all lenghts for arm as needed 
		void set_lenghts_arm(double l, double ual, double uan, double lal, double lan, vector_manus upN);


		//Add either a single finger or many fingers. 
		//void add_finger(Finger fingr);
		void add_vector_fingers(vector<Finger> fingr);
		void add_vector_fingers_manus_profile(vector<Finger> fingr);

		//Set the hand data arry to the array in this object with the poses. 
		void set_hand(Finger *hand[]);

		//Set the raw hand data array to the private array in this object. 
		void set_hand_raw(vector<double> raw_hand);

		//Set the manus_profile hand data 
		void set_hand_profile_manus(vector<Finger> fingers);

		//Get the data for the arm lenghts sent in an array
		vector<double> get_arm_lenghts();

		//Get the data for a hand
		vector<Finger> get_hand();
		vector<Finger> get_hand_profile_manus();
		vector<double> get_raw_hand();
	};
}