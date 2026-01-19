#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

namespace constants
{
    // Constants
   	constexpr int gScreenWidth   { 640 };
   	constexpr int gScreenHeight  { 480 };


   	// PATH TO RESOURCE FOLDER 'resources', 'gResPath'
   	const std::string gResPath { "./resources/" };


	// PATH'S TO ALL EXTERNAL RESOURCES using 'gResPath'
	const std::string bg_str  { gResPath + "images/bg.jpg" };
    const std::string sample_str { gResPath + "sounds/sample.wav"};
	
	const std::string paddle_str { gResPath + "images/paddle.png" };
	const std::string ball_str { gResPath + "images/ball.png" };
	const std::string brick_red_str { gResPath + "images/brick_red.png" };
	const std::string brick_orange_str { gResPath + "images/brick_orange.png" };
	const std::string brick_yellow_str { gResPath + "images/brick_yellow.png" };
	const std::string brick_green_str { gResPath + "images/brick_green.png" };
	const std::string brick_blue_str { gResPath + "images/brick_blue.png" };
	
	const std::string ballbounce_str { gResPath + "sounds/BallBounce.wav" };
	const std::string destroybrick_str { gResPath + "sounds/DestroyBrick.wav" };
	
	const std::string arial_font { gResPath + "fonts/ARIAL.TTF" };

}

#endif