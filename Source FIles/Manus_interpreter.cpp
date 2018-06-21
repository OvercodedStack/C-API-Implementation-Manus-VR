///////////////////////////////////////////////////////////////////////////////
//
//  Original System: ManusGlove.cpp or Source.cpp
//  Subsystem:       Human-Robot Interaction
//  Workfile:        Manus_interpreter.cpp
//  Revision:        1.0 - 6/7/2018
//  Author:          Esteban Segarra
//
//  Description
//  ===========
//  Data phraser for the manus_hand and finger objects. Sorts and compiles the data adquired from the Manus device. 
//
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <iostream>
#include "..\..\Libs\Manus\Manus.h"
#include <vector>
#include "ManusHandConverter.h"
#include "Manus_hand_obj.h"
#include "Finger.h"
#include "Manus_interpreter.h"

namespace manus_interface {
	//######################################################################################################################################
	//Class to phrase the data on a manus device hand.

	//Constructor
	Manus_interpreter::Manus_interpreter(manus_session_t* robot_session) {
		session = robot_session;
	}

	//Function that phrases in a single finger 
	void Manus_interpreter::add_manus_hand(manus_hand_t* hand, manus_hand_raw_t* raw_hand, device_type_t which_hand_side, ik_body_t* body_side, ik_profile_t* my_profile) {
		//Manus Hand Objects
		Manus_hand_obj* hand_in_use = new Manus_hand_obj();

		//Process data for the left hand, including raw data. 
		ManusGetHandRaw(*session, which_hand_side, raw_hand);



		ManusGetProfile(*session, my_profile);
		add_arm_calc(hand, body_side, my_profile, hand_in_use);

		//Set the raw_double finger data from manus 
		add_hand_fingers_raw(raw_hand, which_hand_side, hand_in_use);

		//Set manus_profile finger data
		add_manus_profile_hands(my_profile, hand_in_use);

		ManusGetHand(*session, which_hand_side, hand);
		//Set regular Manus hand data
		add_hand_fingers(hand, which_hand_side, hand_in_use);

		//Add relevant data to the hands array
		if (which_hand_side == GLOVE_LEFT) {
			//hands->insert(hands->begin(),hand_in_use); //Left Glove
			hands[0] = hand_in_use;
		}
		else {
			//hands.assign(1, hand_in_use); //Right Glove
			hands[1] = hand_in_use;
		}
	}

	void Manus_interpreter::rumble_my_hand(device_type_t side, double power, uint16_t time) {
		ManusSetVibration(*session, side, power,time);
	}

	//Get a hand from the list 
	Manus_hand_obj* Manus_interpreter::get_hand(device_type_t side) {
		if (side == GLOVE_LEFT) {
			return hands[0];
		}
		else {
			return hands[1];
		}
	}

	//Add the calcuations for the arm calculations on the manus API
	void Manus_interpreter::add_arm_calc(manus_hand_t* hand, ik_body_t* body_side, ik_profile_t* my_profile, Manus_hand_obj* my_hand) {
		//double arm_calcs[2];
		ManusUpdateIK(*session, body_side);
		//Hand function to set the profile characteristics of the arm. 
		my_hand->set_lenghts_arm(my_profile->shoulderLength, my_profile->upperArmLength, my_profile->upperNeckLength, my_profile->lowerArmLength,
			my_profile->lowerNeckLength, process_vector(my_profile->upperNeckOffset));
		
	}

	//Add the finger calculations from the Manus API
	void Manus_interpreter::add_hand_fingers(manus_hand_t* device, device_type_t side, Manus_hand_obj* manus_hand) {
		vector<Finger> single_hand_array;	//Finger array
		pose temp_pose;						//Temporary pose format.
		vector<pose> temp_finger;			//Temporary array for bones.

		//###################Index finger ###################################
		{
			temp_pose.rotation = process_quat(device->index.carpal.rotation);
			temp_pose.translation = process_vector(device->index.carpal.translation);
			temp_finger.push_back(temp_pose);

			temp_pose.rotation = process_quat(device->index.metacarpal.rotation);
			temp_pose.translation = process_vector(device->index.metacarpal.translation);
			temp_finger.push_back(temp_pose);

			temp_pose.rotation = process_quat(device->index.proximal.rotation);
			temp_pose.translation = process_vector(device->index.proximal.translation);
			temp_finger.push_back(temp_pose);

			temp_pose.rotation = process_quat(device->index.intermediate.rotation);
			temp_pose.translation = process_vector(device->index.intermediate.translation);
			temp_finger.push_back(temp_pose);

			temp_pose.rotation = process_quat(device->index.distal.rotation);
			temp_pose.translation = process_vector(device->index.distal.translation);
			temp_finger.push_back(temp_pose);

			Finger index_bone(temp_finger);
			single_hand_array.push_back(index_bone);
		}
		//###################Middle finger ###################################
		{
			temp_pose.rotation = process_quat(device->middle.carpal.rotation);
			temp_pose.translation = process_vector(device->middle.carpal.translation);
			temp_finger.push_back(temp_pose);

			temp_pose.rotation = process_quat(device->middle.metacarpal.rotation);
			temp_pose.translation = process_vector(device->middle.metacarpal.translation);
			temp_finger.push_back(temp_pose);

			temp_pose.rotation = process_quat(device->middle.proximal.rotation);
			temp_pose.translation = process_vector(device->middle.proximal.translation);
			temp_finger.push_back(temp_pose);

			temp_pose.rotation = process_quat(device->middle.intermediate.rotation);
			temp_pose.translation = process_vector(device->middle.intermediate.translation);
			temp_finger.push_back(temp_pose);

			temp_pose.rotation = process_quat(device->middle.distal.rotation);
			temp_pose.translation = process_vector(device->middle.distal.translation);
			temp_finger.push_back(temp_pose);

			Finger middle_finger(temp_finger);
			single_hand_array.push_back(middle_finger);
		}
		//###################Ring finger ###################################
		{
			temp_pose.rotation = process_quat(device->ring.carpal.rotation);
			temp_pose.translation = process_vector(device->ring.carpal.translation);
			temp_finger.push_back(temp_pose);

			temp_pose.rotation = process_quat(device->ring.metacarpal.rotation);
			temp_pose.translation = process_vector(device->ring.metacarpal.translation);
			temp_finger.push_back(temp_pose);

			temp_pose.rotation = process_quat(device->ring.proximal.rotation);
			temp_pose.translation = process_vector(device->ring.proximal.translation);
			temp_finger.push_back(temp_pose);

			temp_pose.rotation = process_quat(device->ring.intermediate.rotation);
			temp_pose.translation = process_vector(device->ring.intermediate.translation);
			temp_finger.push_back(temp_pose);

			temp_pose.rotation = process_quat(device->ring.distal.rotation);
			temp_pose.translation = process_vector(device->ring.distal.translation);
			temp_finger.push_back(temp_pose);

			Finger ring_finger(temp_finger);
			single_hand_array.push_back(ring_finger);
		}
		//###################Pinky finger ###################################
		{
			temp_pose.rotation = process_quat(device->pinky.carpal.rotation);
			temp_pose.translation = process_vector(device->pinky.carpal.translation);
			temp_finger.push_back(temp_pose);

			temp_pose.rotation = process_quat(device->pinky.metacarpal.rotation);
			temp_pose.translation = process_vector(device->pinky.metacarpal.translation);
			temp_finger.push_back(temp_pose);

			temp_pose.rotation = process_quat(device->pinky.proximal.rotation);
			temp_pose.translation = process_vector(device->pinky.proximal.translation);
			temp_finger.push_back(temp_pose);

			temp_pose.rotation = process_quat(device->pinky.intermediate.rotation);
			temp_pose.translation = process_vector(device->pinky.intermediate.translation);
			temp_finger.push_back(temp_pose);

			temp_pose.rotation = process_quat(device->pinky.distal.rotation);
			temp_pose.translation = process_vector(device->pinky.distal.translation);
			temp_finger.push_back(temp_pose);

			Finger pinky_finger(temp_finger);
			single_hand_array.push_back(pinky_finger);
		}
		//###################Thunb finger ###################################
		{
			temp_pose.rotation = process_quat(device->thumb.carpal.rotation);
			temp_pose.translation = process_vector(device->thumb.carpal.translation);
			temp_finger.push_back(temp_pose);

			temp_pose.rotation = process_quat(device->thumb.metacarpal.rotation);
			temp_pose.translation = process_vector(device->thumb.metacarpal.translation);
			temp_finger.push_back(temp_pose);

			temp_pose.rotation = process_quat(device->thumb.proximal.rotation);
			temp_pose.translation = process_vector(device->thumb.proximal.translation);
			temp_finger.push_back(temp_pose);

			temp_pose.rotation = process_quat(device->thumb.intermediate.rotation);
			temp_pose.translation = process_vector(device->thumb.intermediate.translation);
			temp_finger.push_back(temp_pose);

			temp_pose.rotation = process_quat(device->thumb.distal.rotation);
			temp_pose.translation = process_vector(device->thumb.distal.translation);
			temp_finger.push_back(temp_pose);

			Finger thumb_finger(temp_finger);
			single_hand_array.push_back(thumb_finger);
		}
		manus_hand->add_vector_fingers(single_hand_array);
	}


	//Utillity methods used to compile ManusVR data into vector and quaternion struts. 
	vector_manus Manus_interpreter::process_vector(vector_t vect) {
		vector_manus vec_out;
		vec_out.x = vect.x;
		vec_out.y = vect.y;
		vec_out.z = vect.z;
		return vec_out;
	}

	quarternion Manus_interpreter::process_quat(quat_t quat) {
		quarternion quat_out;
		quat_out.x = quat.x;
		quat_out.y = quat.y;
		quat_out.z = quat.z;
		quat_out.w = quat.w;
		return quat_out;
	}


	//This was a misinterpretation of the Manus Profile data, collected under the assumption that it provides realtime data.
	//It does not provide real-time data
	void Manus_interpreter::add_manus_profile_hands(ik_profile_t* my_profile, Manus_hand_obj* my_hand) {
		vector<double> temporary_finger_array; //Temporary array for doubles to insert into finger.
		vector<Finger> fingers;

		//Horrible method of phrasing, but what happens is that a vector array is phrased over from the manus array
		//Index Finger

		for (int c = 0; c < 4; c++) {
			temporary_finger_array.push_back(my_profile->handProfile.index.bones[c]);
		}
		Finger index_bone(temporary_finger_array);    // Array is inserted into the finger object. 
		temporary_finger_array.clear();
		fingers.push_back(index_bone);//Finger is added into hand. 


		//Middle Finger
		for (int c = 0; c < 4; c++) {
			temporary_finger_array.push_back(my_profile->handProfile.middle.bones[c]);
		}
		Finger middle_bone(temporary_finger_array);    // Array is inserted into the finger object. 
		temporary_finger_array.clear();
		fingers.push_back(middle_bone);//Finger is added into hand. 


		//Ring Finger
		for (int c = 0; c < 4; c++) {
			temporary_finger_array.push_back(my_profile->handProfile.index.bones[c]);
		}
		Finger ring_bone(temporary_finger_array);    // Array is inserted into the finger object. 
		temporary_finger_array.clear();
		fingers.push_back(ring_bone);//Finger is added into hand. 


		//Pinky Finger
		for (int c = 0; c < 4; c++) {
			temporary_finger_array.push_back(my_profile->handProfile.index.bones[c]);
		}
		Finger pinky_bone(temporary_finger_array);    // Array is inserted into the finger object. 
		temporary_finger_array.clear();
		fingers.push_back(pinky_bone);//Finger is added into hand. 


		//Thumb Finger
		for (int c = 0; c < 4; c++) {
			temporary_finger_array.push_back(my_profile->handProfile.index.bones[c]);
		}
		Finger thumb_bone(temporary_finger_array);    // Array is inserted into the finger object. 
		temporary_finger_array.clear();
		fingers.push_back(thumb_bone); //Finger is added into hand. 

		my_hand->add_vector_fingers_manus_profile(fingers);
	}

	//Add finger calculations that are stated to be raw decimal calculations from the Manus SDK
	//Phrase the array of raw finger calculations from the Manus SDK.
	void Manus_interpreter::add_hand_fingers_raw(manus_hand_raw_t* hand, device_type_t side, Manus_hand_obj* manus_hand) {
		vector<double> single_hand_array_raw;
		for (int h = 0; h < 10; h++) {
			single_hand_array_raw.push_back(hand->finger_sensor[h]);
		}
		manus_hand->set_hand_raw(single_hand_array_raw);
	}

	//######################################################################################################################################
}