/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2011, Willow Garage, Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Willow Garage nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

/* Author: Ioan Sucan */

#pragma once

#include <moveit/collision_detection_fcl/collision_robot_fcl.h>
#include <moveit/collision_detection_fcl/fcl_compat.h>

#if (MOVEIT_FCL_VERSION >= FCL_VERSION_CHECK(0, 6, 0))
#include <fcl/broadphase/broadphase_collision_manager.h>
#else
#include <fcl/broadphase/broadphase.h>
#endif

#include <memory>

namespace collision_detection
{
class CollisionWorldFCL : public CollisionWorld
{
public:
  CollisionWorldFCL();
  explicit CollisionWorldFCL(const WorldPtr& world);
  CollisionWorldFCL(const CollisionWorldFCL& other, const WorldPtr& world);
  ~CollisionWorldFCL() override;

  void checkRobotCollision(const CollisionRequest& req, CollisionResult& res, const CollisionRobot& robot,
                           const robot_state::RobotState& state) const override;
  void checkRobotCollision(const CollisionRequest& req, CollisionResult& res, const CollisionRobot& robot,
                           const robot_state::RobotState& state, const AllowedCollisionMatrix& acm) const override;
  void checkRobotCollision(const CollisionRequest& req, CollisionResult& res, const CollisionRobot& robot,
                           const robot_state::RobotState& state1, const robot_state::RobotState& state2) const override;
  void checkRobotCollision(const CollisionRequest& req, CollisionResult& res, const CollisionRobot& robot,
                           const robot_state::RobotState& state1, const robot_state::RobotState& state2,
                           const AllowedCollisionMatrix& acm) const override;
  void checkWorldCollision(const CollisionRequest& req, CollisionResult& res,
                           const CollisionWorld& other_world) const override;
  void checkWorldCollision(const CollisionRequest& req, CollisionResult& res, const CollisionWorld& other_world,
                           const AllowedCollisionMatrix& acm) const override;

  void distanceRobot(const DistanceRequest& req, DistanceResult& res, const CollisionRobot& robot,
                     const robot_state::RobotState& state) const override;

  void distanceWorld(const DistanceRequest& req, DistanceResult& res, const CollisionWorld& world) const override;

  void setWorld(const WorldPtr& world) override;

protected:
  void checkWorldCollisionHelper(const CollisionRequest& req, CollisionResult& res, const CollisionWorld& other_world,
                                 const AllowedCollisionMatrix* acm) const;
  void checkRobotCollisionHelper(const CollisionRequest& req, CollisionResult& res, const CollisionRobot& robot,
                                 const robot_state::RobotState& state, const AllowedCollisionMatrix* acm) const;

  void constructFCLObject(const World::Object* obj, FCLObject& fcl_obj) const;
  void updateFCLObject(const std::string& id);

  std::unique_ptr<fcl::BroadPhaseCollisionManagerd> manager_;
  std::map<std::string, FCLObject> fcl_objs_;

private:
  void initialize();
  void notifyObjectChange(const ObjectConstPtr& obj, World::Action action);
  World::ObserverHandle observer_handle_;
};
}
