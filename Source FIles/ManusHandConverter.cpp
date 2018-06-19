///////////////////////////////////////////////////////////////////////////////
//
//  Original System: ManusGlove.cpp or Source.cpp
//  Subsystem:       Human-Robot Interaction
//  Workfile:        ManusHandConverter.cpp
//  Revision:        1.0 - 6/5/2018
//  Author:          Esteban Segarra
//
//  Description
//  ===========
//  Data structure design for the Manus hand devices. Designed to be readily called as a API wrapper to the Manus.h SDK.
//
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string>
#include <iostream>
#include <windows.h>
#include "..\..\Libs\Manus\Manus.h"
#include <vector>
#include "ManusHandConverter.h"
#include "Manus_interpreter.h"
#include "Manus_hand_obj.h"


	//namespace ManusPub {
using namespace std;
using std::vector;
using namespace manus_interface;

void print_quat(quarternion quart) {
	cout << "Printing Quarternion: "
		"X: " << quart.x <<
		"Y: " << quart.y <<
		"Z: " << quart.z <<
		"W: " << quart.w <<
		endl;
}

void print_vector(vector_manus vec) {
	cout << "Printing Vector: "
		"X: " << vec.x <<
		"Y: " << vec.y <<
		"Z: " << vec.z <<
		endl;
}

void print_arm(Manus_hand_obj* hand) {
	vector<double> data = hand->get_arm_lenghts();

	cout << "Printing arm data." << endl;
	cout << "arm_lenght: " << data[0] << endl;
	cout << "upper_arm_length: " << data[1] << endl;
	cout << "lower_arm_length: " << data[2] << endl;
	cout << "upper_arm_neck: " << data[3] << endl;
	cout << "lower_arm_neck: " << data[4] << endl;
	Sleep(1000);
	system("cls");
}


//Print out the quarternion and vector angles of the manus hand
void print_my_hand(Manus_hand_obj* hand) {
	vector<Finger> fingers = hand->get_hand();
	for (int i = 0; i < 5; i++) {
		Finger finger = fingers[i];
		for (int bn = 0; bn < 5; bn++) {
			pose my_bone = finger.get_finger_data()[bn];
			cout << "Hand data with array number  " << i << endl;
			print_vector(my_bone.translation);
			print_quat(my_bone.rotation);
			cout << endl;
		}
		cout << endl;
	}system("cls");
}

//Prints out Manus_profile data for the hand
void print_my_manus_profile_hand(Manus_hand_obj* hand) {
	vector<Finger> my_fingers = hand->get_hand_profile_manus();
	for (int i = 0; i < 5; i++) {
		Finger finger = my_fingers[i];
		for (int bn = 0; bn < 5; bn++) {
			double my_bone = finger.get_fingers_manus()[bn];
			cout << "The bone with ID:  " << i + 1 << " has double variable: " << my_bone << endl;
			cout << endl;
		}
		cout << endl;
	}system("cls");
}


//Printer Function for raw data hand 
void print_my_raw_hand(Manus_hand_obj* hand) {
	vector<double> raw = hand->get_raw_hand();
	for (int i = 0; i < 5; i++) {
		cout << "Bone number " << i << " has value: " << raw[i] << endl;
	}
	system("cls");
}




//######################################################################################################################################
//Default run main program
int main() {
	//blank session pointer
	manus_session_t sess_t;
	manus_session_t* sess = &sess_t;
	manus_session_t* sessp;
	sessp = new manus_session_t();
	delete sessp;

	//hand pointers
	manus_hand_t  lefth, righth;
	manus_hand_t* leftpt = &lefth;
	manus_hand_t* rightpt = &righth;

	//Raw pointers
	manus_hand_raw_t  rightraw, leftraw;
	manus_hand_raw_t* rightrpt = &rightraw;
	manus_hand_raw_t* leftrpt = &leftraw;

	//Arm Pointers
	ik_body_t left_arm, right_arm;
	ik_body_t* left_armp = &left_arm;
	ik_body_t* right_armp = &right_arm;

	//IK Pointers
	ik_profile_t myProfileL, myProfileR;
	ik_profile_t* profileL = &myProfileL;
	ik_profile_t* profileR = &myProfileR;

	//Checking for connected hands L/R
	bool isL, isR;

	//initialize Manus SDK
	ManusInit(sess);

	//Initialize Manus Hand data type
	Manus_interpreter interpreter(sess);

	//Manus_hand_obj hands_type = new ManusPub::Manus_hand_obj(sess);
	int inp;

	//Add left and right hands for the data structure

	while (ManusIsConnected(*sess, GLOVE_LEFT)) {
		isL = ManusIsConnected(*sess, GLOVE_LEFT);
		cout << isL << endl;
		cout << "Press a key." << endl;
		cin >> inp;
		break;
	}
	while (ManusIsConnected(*sess, GLOVE_RIGHT)) {
		isR = ManusIsConnected(*sess, GLOVE_RIGHT);
		cout << isR << endl;
		cout << "Press a key." << endl;
		cin >> inp;
		break;
	}
	inp = 2566;

	while (!inp == 0) {
		interpreter.add_manus_hand(leftpt, leftrpt, GLOVE_LEFT, left_armp, profileL);
		interpreter.add_manus_hand(rightpt, rightrpt, GLOVE_RIGHT, right_armp, profileR);
		//print_my_raw_hand(interpreter.get_hand(GLOVE_LEFT));
		print_my_hand(interpreter.get_hand(GLOVE_LEFT));
		//print_my_manus_profile_hand(interpreter.get_hand(GLOVE_LEFT));
		//uint16_t i = 200;
		//interpreter.rumble_my_hand(GLOVE_LEFT, .75, i);
		//print_arm(interpreter.get_hand(GLOVE_LEFT));
		//cout << "Press a key." << endl;
		//cin >> inp;
		//timer.
		///Sleep(250);
	}
	//Tentative websocket functions
	//void startBroadcast() {}
	//void closeBroadcast() {}
	return 0;
}


//######################################################################################################################################
