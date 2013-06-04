/*
 * move_through_place_poses.cpp
 *
 *  Created on: Jun 3, 2013
 *      Author: ros-industrial
 */

#include <pick_and_place_exercise/pick_and_place.h>

void move_through_place_poses(move_group_interface::MoveGroup& move_group,GraspActionClient& grasp_action_client,
                              std::vector<geometry_msgs::Pose>& place_poses)
{
  /* MOVE ARM THROUGH PLACE POSES
    Goal:
      - Move the robot to each place pose.
      - Open gripper after reaching the target pose
    Hints:
      - Use the methods seen so far such as 'move', 'sendGoal', 'waitForResult' as needed
    Complete code below: */

  // task variables
  object_manipulation_msgs::GraspHandPostureExecutionGoal grasp_goal;
  bool success;

  // setting end-effector link and reference frame
  move_group.setEndEffectorLink(cfg.WRIST_LINK_NAME);
  move_group.setPoseReferenceFrame(cfg.WORLD_FRAME_ID);

  // move the robot to each wrist place pose
  for(unsigned int i = 0; i < place_poses.size(); i++)
  {
    // set the current place pose as the target
    /* Fill Code: [ use the 'setPoseTarget' method in the 'move_group' object and pass the current pose in 'wrist_pick_poses'] */
    move_group.setPoseTarget(place_poses[i],cfg.WRIST_LINK_NAME);

    // moving arm to current place pose
    success = move_group.move();

    if(success)
    {
      ROS_INFO_STREAM("Place Move " << i <<" Succeeded");
    }
    else
    {
      ROS_INFO_STREAM("Place Move " << i <<" Failed");
      ros::shutdown();
      return;
    }

    // turn off gripper suction (RELEASE) after reaching target pose
    if(i == 1)
    {
      set_gripper(grasp_action_client, false);
    }
  }
}


