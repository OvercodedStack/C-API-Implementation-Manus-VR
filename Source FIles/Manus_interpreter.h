///////////////////////////////////////////////////////////////////////////////
//
//  Original System: ManusGlove.cpp or Source.cpp
//  Subsystem:       Human-Robot Interaction
//  Workfile:        Manus_interpreter.h
//  Revision:        1.0 - 6/7/2018
//  Author:          Esteban Segarra
//
//  Description
//  ===========
//  Data phraser for the manus_hand and finger objects. Sorts and compiles the data adquired from the Manus device. 
//
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "ManusHandConverter.h"
 
#include <vector>

namespace manus_interface {
	class Manus_hand_obj;
	//######################################################################################################################################
	//Class to phrase the data on a manus device hand.
	class Manus_interpreter {
	private:
		//Private session stamp for the manus device. 
		manus_session_t * session;

		//Create a Hand array for each hand. Each hand is an data structure.
		Manus_hand_obj *hands[2];
	public:
		//Save a manus_session 
		Manus_interpreter(manus_session_t* robot_session);

		//Function that phrases in a single finger 
		void add_manus_hand(manus_hand_t* hand, manus_hand_raw_t* raw_hand, device_type_t which_hand_side, ik_body_t* body_side, ik_profile_t* my_profile);

		//Function to rumble a hand if need be. 
		void rumble_my_hand(device_type_t side, double power, uint16_t time);

		//Add the calcuations for the arm calculations on the manus API
		void add_arm_calc(manus_hand_t* hand, ik_body_t* body_side, ik_profile_t* my_profile, Manus_hand_obj* my_hand);

		//Add the finger calculations from the Manus API
		void add_hand_fingers(manus_hand_t* device, device_type_t side, Manus_hand_obj* manus_hand);

		//Phrasing the array of finger calculations.
		double * phrase_bones(manus_hand_t* hand, device_type_t side);

		//Return a hand from the hands array; 
		Manus_hand_obj* get_hand(device_type_t side);

		//Process a vector from manus to own strut
		vector_manus Manus_interpreter::process_vector(vector_t vect);

		//Process a manus quaternion into own strut
		quarternion Manus_interpreter::process_quat(quat_t quat);

		//Method to process a manus profile hands data type 
		void add_manus_profile_hands(ik_profile_t* my_profile, Manus_hand_obj* my_hand);

		//Add finger calculations that are stated to be raw decimal calculations from the Manus SDK
		//Phrase the array of raw finger calculations from the Manus SDK.
		void add_hand_fingers_raw(manus_hand_raw_t* hand, device_type_t side, Manus_hand_obj* manus_hand);
	};
	//######################################################################################################################################
}