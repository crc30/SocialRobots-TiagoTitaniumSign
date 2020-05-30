/*
 * Copyright 1996-2020 Cyberbotics Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Description: Simple controller to make an "Hello" mouvement with the
 *              hand showing the peace symbol.
 *              It is also possible to move the robot with the keyboard arrows.
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <webots/keyboard.h>
#include <webots/motor.h>
#include <webots/robot.h>

#define MAX_SPEED 7.0  // [rad/s]
#define N_PARTS 45
#define MOTOR_LEFT N_PARTS - 2
#define MOTOR_RIGHT N_PARTS - 1

static WbDeviceTag robot_parts[N_PARTS];

static void check_keyboard() {
  double speeds_left = 0.0, speeds_right = 0.0;

  int key = wb_keyboard_get_key();
  if (key >= 0) {
    switch (key) {
      case WB_KEYBOARD_UP:
      
        speeds_left = MAX_SPEED;
        speeds_right = MAX_SPEED;
        break;
      case WB_KEYBOARD_DOWN:
        speeds_left = -MAX_SPEED;
        speeds_right = -MAX_SPEED;
        break;
      case WB_KEYBOARD_RIGHT:
        speeds_left = MAX_SPEED;
        speeds_right = -MAX_SPEED;
        break;
      case WB_KEYBOARD_LEFT:
        speeds_left = -MAX_SPEED;
        speeds_right = MAX_SPEED;
        break;
    }
  }
  wb_motor_set_velocity(robot_parts[MOTOR_LEFT], speeds_left);
  wb_motor_set_velocity(robot_parts[MOTOR_RIGHT], speeds_right);
}

int main(int argc, char **argv) {
  // init webots stuff
  wb_robot_init();

  const int time_step = wb_robot_get_basic_time_step();

  // get devices
  // initialize the robot's information
  const char *names[N_PARTS] = {"head_2_joint", //0
                                "head_1_joint", //1
                                "torso_lift_joint", //2
                                //motori del braccio
                                "arm_1_joint", //3
                                "arm_2_joint", //4
                                "arm_3_joint", //5
                                "arm_4_joint", //6
                                "arm_5_joint", //7
                                "arm_6_joint", //8
                                "arm_7_joint", //9
                                //pollice
                                "hand_right_thumb_abd_joint", //10
                                "hand_right_thumb_virtual_1_joint", //11
                                "hand_right_thumb_flex_1_joint", //12
                                "hand_right_thumb_virtual_2_joint", //13
                                "hand_right_thumb_flex_2_joint", //14
                                //indice
                                "hand_right_index_abd_joint", //15
                                "hand_right_index_virtual_1_joint", //16
                                "hand_right_index_flex_1_joint", //17
                                "hand_right_index_virtual_2_joint", //18
                                "hand_right_index_flex_2_joint", //19
                                "hand_right_index_virtual_3_joint", //20
                                "hand_right_index_flex_3_joint", //21
                                //medio
                                "hand_right_middle_abd_joint", //22
                                "hand_right_middle_virtual_1_joint", //23
                                "hand_right_middle_flex_1_joint", //24
                                "hand_right_middle_virtual_2_joint", //25
                                "hand_right_middle_flex_2_joint", //26
                                "hand_right_middle_virtual_3_joint", //27
                                "hand_right_middle_flex_3_joint", //28
                                //anulare
                                "hand_right_ring_abd_joint", //29
                                "hand_right_ring_virtual_1_joint", //30
                                "hand_right_ring_flex_1_joint", //31
                                "hand_right_ring_virtual_2_joint", //32
                                "hand_right_ring_flex_2_joint", //33
                                "hand_right_ring_virtual_3_joint", //34
                                "hand_right_ring_flex_3_joint", //35
                                //mignolo
                                "hand_right_little_abd_joint", //36
                                "hand_right_little_virtual_1_joint", //37
                                "hand_right_little_flex_1_joint", //38
                                "hand_right_little_virtual_2_joint", //39
                                "hand_right_little_flex_2_joint", //40
                                "hand_right_little_virtual_3_joint", //41
                                "hand_right_little_flex_3_joint", //42
                                //
                                "wheel_left_joint", //43
                                "wheel_right_joint" //44
                               };

  /*double target_pos[N_PARTS] = {0.24,  -0.67, 0.09, 0.07, 0.26, -3.16, 1.27, 1.32,     0.00,    1.41, 1.55,  0.79,
                                0.68,  0.00,  0.00, 0.00, 0.00, 0.00,  0.00, 0.00,     0.00,    0.00, -0.08, 0.00,
                                0.00,  0.00,  0.00, 0.00, 0.00, -0.22, 0.00, 0.32,     0.79,    0.42, 0.79,  0.79,
                                -0.52, 0.00,  0.79, 0.79, 0.37, 0.79,  0.62, INFINITY, INFINITY};*/
                                
/*double target_pos[N_PARTS] = {0.24,  -0.67, 0.09, //testa 0-2

                              0.07, 0.26, -3.16, 1.27, 1.32, 0.00, 1.41, //braccio 3-9
                              
                              1.55,  0.79, 0.68,  0.00,  0.00, //pollice 10-14
                              
                              0.00, 0.00, 0.00,  0.00, 0.00, 0.00, 0.00, //indice 15-21
                              
                              -0.08, 0.00, 0.00,  0.00,  0.00, 0.00, 0.00, //medio 22-28
                              
                              -0.22, 0.00, 0.32, 0.79, 0.42, 0.79,  0.79, //anulare 29-35
                              
                              -0.52, 0.00,  0.79, 0.79, 0.37, 0.79,  0.62, //mignolo 36-42
                              
                              INFINITY, INFINITY //ruote 43-44
                              }; */
double target_pos[N_PARTS] = {0.24,  -0.67, 0.09, //testa 0-2

                              0.07, 0.26, -3.16, 0.00, -2.07, 0.00, 0.00, //braccio 3-9
                              
                              1.55,  0.40, 0.68,  0.00,  0.00, //pollice 10-14
                              
                              0.52, 0.79, 0.00,  0.79, 0.00, 0.60, 0.30, //indice 15-21
                              
                              -0.22, 0.79, 0.00,  0.79, 0.00, 0.60, 0.30, //medio 22-28
                              
                              -0.32, 0.79, 0.00,  0.79, 0.00, 0.60, 0.30, //anulare 29-35
                              
                              -0.49, 0.79, 0.00,  0.79, 0.00, 0.60, 0.30, //mignolo 36-42
                              
                              INFINITY, INFINITY //ruote 43-44
                              }; 

  // configures and achieves the robot's position desired
  for (int i = 0; i < N_PARTS; i++) {
    robot_parts[i] = wb_robot_get_device(names[i]);
    wb_motor_set_velocity(robot_parts[i], wb_motor_get_max_velocity(robot_parts[i]) / 2.0);
    wb_motor_set_position(robot_parts[i], target_pos[i]);
  }

  // print user instructions
  printf("AeQQQQYou can drive this robot by selecting the 3D window and pressing the keyboard arrows.\n");

  // enable keyboard
  wb_keyboard_enable(time_step);

  const double initialTime = wb_robot_get_time();

  while (wb_robot_step(time_step) != -1) {
    check_keyboard();

    // Hello mouvement
    const double time = wb_robot_get_time() - initialTime;
    wb_motor_set_position(robot_parts[8], 0.3 * sin(5.0 * time) - 0.3);
  };

  wb_robot_cleanup();
  return 0;
}