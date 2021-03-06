
#include <catch_ros/catch.hpp>
#include <rigid2d/rigid2d.hpp>
#include <rigid2d/diff_drive.hpp>
#include <cmath>
#include <iostream>
#include <sstream>

/*
* Compile command: g++ -Wall -Wextra -g -std=c++17 -o test test.cpp rigid2d.cpp
*
* Contributors:
* Arun Kumar
* Nathaniel Nyberg
* Sarah Ziselman
* Lin Liu
* Edoardo, Rundeddu
*/ 


TEST_CASE("Default constructor creates identity transform","[default_constructor]"){ // Arun, Kumar
    using namespace rigid2d;

    Transform2D trans = Transform2D();
        
    REQUIRE(almost_equal(trans.getX(),0));
    REQUIRE(almost_equal(trans.getY(),0));
    REQUIRE(almost_equal(trans.getCtheta(),1));
    REQUIRE(almost_equal(trans.getStheta(),0));
}

TEST_CASE("Constructor using only radians component","[rad_constructor]"){ // Nathaniel, Nyberg
    using namespace rigid2d;

    Transform2D trans = Transform2D(PI);
        
    REQUIRE(almost_equal(trans.getCtheta(),cos(PI)));
    REQUIRE(almost_equal(trans.getStheta(),sin(PI)));
    REQUIRE(almost_equal(trans.getX(),0));
    REQUIRE(almost_equal(trans.getY(),0));
}

TEST_CASE("Constructor using only vector component","[vector_constructor]"){ // Nathaniel, Nyberg
    using namespace rigid2d;

    Vector2D v;
    v.x = 2;
    v.y = 3;
    Transform2D trans = Transform2D(v);
        
    REQUIRE(almost_equal(trans.getCtheta(),1));
    REQUIRE(almost_equal(trans.getStheta(),0));
    REQUIRE(almost_equal(trans.getX(),2));
    REQUIRE(almost_equal(trans.getY(),3));
}

TEST_CASE("Constructor using both components","[full_constructor]"){ // Nathaniel, Nyberg
    using namespace rigid2d;

    Vector2D v;
    v.x = 2;
    v.y = 3;
    Transform2D trans = Transform2D(v,PI);
        
    REQUIRE(almost_equal(trans.getCtheta(),cos(PI)));
    REQUIRE(almost_equal(trans.getStheta(),sin(PI)));
    REQUIRE(almost_equal(trans.getX(),2));
    REQUIRE(almost_equal(trans.getY(),3));
}


TEST_CASE("Input a Transform from istream","[input]"){ // Nathaniel, Nyberg
    using namespace rigid2d;

    Transform2D trans;

    std::unique_ptr<std::istream> is;
    is = std::make_unique<std::istringstream>(std::istringstream{"-30 2 3"});
    *is >> trans;

    REQUIRE(almost_equal(trans.getCtheta(),cos(deg2rad(-30))));
    REQUIRE(almost_equal(trans.getStheta(),sin(deg2rad(-30))));
    REQUIRE(almost_equal(trans.getX(),2));
    REQUIRE(almost_equal(trans.getY(),3));
}

TEST_CASE("Outpt a Transform to ostream","[ouput]"){ // Nathaniel, Nyberg
    using namespace rigid2d;

    Transform2D trans = Transform2D();
    double test;
    std::stringstream ss;
    ss << trans;

    ss >> test;
    while(ss.fail()){
        ss.clear();
        ss.ignore(1);
        ss >> test;
    }

    REQUIRE(almost_equal(test,0));

    ss >> test;
    while(ss.fail()){
        ss.clear();
        ss.ignore(1);
        ss >> test;
    }

    REQUIRE(almost_equal(test,0));

    ss >> test;
    while(ss.fail()){
        ss.clear();
        ss.ignore(1);
        ss >> test;
    }

    REQUIRE(almost_equal(test,0));
}

TEST_CASE("Transformation applied to Vector2D", "[transform]") // Lin, Liu 
{
    using namespace rigid2d; 
    Vector2D v; 
    v.x = -1;
    v.y = 2;

    Transform2D trans21 = Transform2D(v,PI); 

    Vector2D v1; 
    v1.x = -3; 
    v1.y = 1; 

    Vector2D v2; 
    v2 = trans21.operator()(v1);

    REQUIRE(almost_equal(v2.x, 2)); 
    REQUIRE(almost_equal(v2.y, 1));
}

TEST_CASE("Inverse of Transform Matrix", "[transform]"){ // Sarah, Ziselman
    using namespace rigid2d;

    Vector2D v;
    v.x = 1;
    v.y = 2;

    Transform2D transMat = Transform2D(v, PI);
    Transform2D invTransMat = transMat.inv();

    REQUIRE(almost_equal(invTransMat.getCtheta(), cos(PI)));
    REQUIRE(almost_equal(invTransMat.getStheta(), -sin(PI)));
    REQUIRE(almost_equal(invTransMat.getX(), 1));
    REQUIRE(almost_equal(invTransMat.getY(), 2));
}

TEST_CASE("Transform Composition Operator (*=)", "[transform]"){ // Arun, Kumar
    using namespace rigid2d;

    Vector2D v;
    v.x = 3;
    v.y = 9;

    Transform2D transMat = Transform2D(v, PI/9);
    Transform2D invTransMat = transMat.inv();

    transMat*=invTransMat;

    REQUIRE(almost_equal(transMat.getCtheta(), 1));
    REQUIRE(almost_equal(transMat.getStheta(), 0));
    REQUIRE(almost_equal(transMat.getX(), 0));
    REQUIRE(almost_equal(transMat.getY(), 0));
}

TEST_CASE("Change twist reference frame", "[transform]"){ // Edoardo, Rundeddu
	using namespace rigid2d;
	
	Vector2D p;
	p.x = 1;
	p.y = 2;
	
	Transform2D transMat = Transform2D(p, PI/2);
	Transform2D invTransMat = transMat.inv();
	
    Twist2D tw;
    tw.w = 2;
    tw.x_dot = 3;
    tw.y_dot = 5;

	Twist2D tw_out = invTransMat(tw);
	REQUIRE(almost_equal(tw_out.w, 2));
	REQUIRE(almost_equal(tw_out.x_dot, 7));
	REQUIRE(almost_equal(tw_out.y_dot, 1));
}

TEST_CASE("Integrate twist pure rotation", "[integrateTwist]"){ // Arun, Kumar
	using namespace rigid2d;

    Twist2D twist;
    Transform2D Tbb_;

    twist.w = PI;
    Tbb_ = integrateTwist(twist);

    REQUIRE(almost_equal(Tbb_.getX(), 0));
	REQUIRE(almost_equal(Tbb_.getY(), 0));
	REQUIRE(almost_equal(Tbb_.getTheta(), PI));
}

TEST_CASE("Integrate twist pure translation", "[integrateTwist]"){ // Arun, Kumar
	using namespace rigid2d;

    Twist2D twist;
    Transform2D Tbb_;

    twist.x_dot = 1;
    twist.y_dot = 2;
    Tbb_ = integrateTwist(twist);

    REQUIRE(almost_equal(Tbb_.getX(), 1));
	REQUIRE(almost_equal(Tbb_.getY(), 2));
	REQUIRE(almost_equal(Tbb_.getTheta(), 0));
}

TEST_CASE("Integrate twist translation and rotation", "[integrateTwist]"){ // Arun, Kumar
	using namespace rigid2d;

    Twist2D twist;
    Transform2D Tbb_;

    twist.x_dot = 10;
    twist.y_dot = 0;
    twist.w = 2*PI;
    Tbb_ = integrateTwist(twist);

    REQUIRE(almost_equal(Tbb_.getX(), 0));
	REQUIRE(almost_equal(Tbb_.getY(), 0));
	REQUIRE(almost_equal(normalize_angle(Tbb_.getTheta()), 0));
}

TEST_CASE("Calculate wheel controls given body twist", "[calculateControls]"){ // Arun, Kumar
	using namespace rigid2d;

    DiffDrive dd;
    Twist2D Vb;
    Vector2D controls;

    dd = DiffDrive(2,1);
    Vb.w = PI;
    Vb.x_dot = 0;
    controls = dd.calculateControls(Vb);

    REQUIRE(almost_equal(controls.x, -PI));
	REQUIRE(almost_equal(controls.y, PI));
}

TEST_CASE("Calculate body twist given wheel controls", "[calculateTwist]"){ // Arun, Kumar
	using namespace rigid2d;

    DiffDrive dd;
    Twist2D Vb;
    Vector2D controls;
    Twist2D Vb_;

    dd = DiffDrive(2,1);
    Vb.w = PI;
    Vb.x_dot = 32;
    controls = dd.calculateControls(Vb);
    Vb_ = dd.calculateTwist(controls);

    REQUIRE(almost_equal(Vb_.w, PI));
	REQUIRE(almost_equal(Vb_.x_dot, 32));
}

TEST_CASE("Odometry used to update robot configuration", "[updateConfiguration]"){ // Arun, Kumar
	using namespace rigid2d;

    DiffDrive dd;
    Twist2D Vb;
    Vector2D controls;
    Twist2D Vb_;

    dd = DiffDrive(2,1);
    Vb.w = 2*PI;
    Vb.x_dot = 10;
    controls = dd.calculateControls(Vb);
    dd.updateConfiguration(controls);

    REQUIRE(almost_equal(dd.getTransform().getX(), 0));
	REQUIRE(almost_equal(dd.getTransform().getY(), 0));
    REQUIRE(almost_equal(dd.getTransform().getTheta(), 0));
}