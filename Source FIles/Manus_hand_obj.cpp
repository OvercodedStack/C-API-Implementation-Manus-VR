///////////////////////////////////////////////////////////////////////////////
//
//  Original System: ManusGlove.cpp or Source.cpp
//  Subsystem:       Human-Robot Interaction
//  Workfile:        Manus_hand_obj.cpp 
//  Revision:        1.0 - 6/7/2018
//  Author:          Esteban Segarra
//
//  Description
//  ===========
//  Data structure for a manus_hand object
//
///////////////////////////////////////////////////////////////////////////////



#include <stdio.h>
#include <iostream>
#include "..\..\Libs\Manus\Manus.h"
#include <vector>
#include "ManusHandConverter.h"
#include "Manus_hand_obj.h"
#include "Finger.h"


namespace manus_interface {
	//######################################################################################################################################
	//A Manus hand object class - Assume it's a hand.  
		//Constructor
	Manus_hand_obj::Manus_hand_obj() {};

	//Set all lenghts for arm as needed 
	void Manus_hand_obj::set_lenghts_arm(double l, double ual, double uan, double lal, double lan, vector_manus upN) {
		arm_lenght = l;
		upper_arm_length = ual;
		upper_arm_neck = uan;
		lower_arm_length = lal;
		lower_arm_neck = lan;
		upperNeckOffset = upN;
	};

	//Set the hand data arry to the array in this object with the poses. 
	//void set_hand(finger *hand[]) {
	//	*hand_fingers = hand;
	//}

	/*void Manus_hand_obj::add_finger(Finger fingr) {
		hand_fingers.push_back(fingr);
	}*/

	void Manus_hand_obj::add_vector_fingers_manus_profile(vector<Finger> fingr) {
		hand_fingers_manus_profile = fingr;
	}
	void Manus_hand_obj::add_vector_fingers(vector<Finger> fingr) {
		hand_fingers = fingr;
	}

	//Set the raw hand data array to the private array in this object. 
	void Manus_hand_obj::set_hand_raw(vector<double> raw_hand) {
		hand_measurements_raw = raw_hand;
	}

	//Get the data for the arm lenghts sent in an array
	vector<double> Manus_hand_obj::get_arm_lenghts() {
		vector<double> lengths = { arm_lenght, upper_arm_length,lower_arm_length, upper_arm_neck,lower_arm_neck };
		return lengths;
	}

	//Set the manus_profile hand data 
	void Manus_hand_obj::set_hand_profile_manus(vector<Finger> fingers) {
		hand_fingers_manus_profile = fingers;
	}

	//Get the data for a hand
	vector<Finger> Manus_hand_obj::get_hand() {
		return hand_fingers;
	}

	vector<Finger> Manus_hand_obj::get_hand_profile_manus() {
		return hand_fingers_manus_profile;
	}

	vector<double> Manus_hand_obj::get_raw_hand() {
		return hand_measurements_raw;
	}

	//######################################################################################################################################
}