#include <ad/map/access/Factory.hpp>
#include <ad/map/access/Operation.hpp>
#include <ad/map/config/MapConfigFileHandler.hpp>
#include <ad/map/lane/Lane.hpp>
#include <ad/map/lane/LaneOperation.hpp>
#include <ad/map/match/AdMapMatching.hpp>
#include <ad/map/match/Types.hpp>
#include <ad/map/point/Operation.hpp>
#include <ad/map/route/LaneInterval.hpp>
#include <ad/map/route/Planning.hpp>
#include <ad/map/route/RouteAStar.hpp>
#include <ad/map/route/RouteOperation.hpp>
#include <ament_index_cpp/get_package_share_directory.hpp>
#include <iostream>

#include "lane_utils.h"
#include "map_util.h"

using namespace ::ad;
using namespace ::ad::map;
using namespace ::ad::map::point;
using namespace std;

map_server::LaneUtils laneUtil;

struct pos3 {
  double x;
  double y;
  double z;
  pos3() {}
  pos3(double tx, double ty, double tz) {
    x = tx;
    y = ty;
    z = tz;
  }
  pos3 operator*(double ts) {
    return pos3(this->x * ts, this->y * ts, this->z * ts);
  }
  pos3 operator*(pos3 tp) {
    return pos3(this->x * tp.x, this->y * tp.y, this->z * tp.z);
  }
  pos3 operator+(pos3 tp) {
    return pos3(this->x + tp.x, this->y + tp.y, this->z + tp.z);
  }
  pos3 operator-(pos3 tp) {
    return pos3(this->x - tp.x, this->y - tp.y, this->z - tp.z);
  }
};

void testRouting() {
  std::cout << "routing test started!" << std::endl;
  std::cout << "case 1:" << std::endl;
  pos3 startPoint_map;
  startPoint_map.x = -234.138;
  startPoint_map.y = -6363.8;
  startPoint_map.z = 297.734;

  // find the end point in the map
  pos3 endPoint_map;
  endPoint_map.x = 681.497;
  endPoint_map.y = 6656.96;
  endPoint_map.z = 408.513;

  auto startParaPoint = laneUtil.ENU2PARA(
      createENUPoint(startPoint_map.x, startPoint_map.y, startPoint_map.z));
  auto endParaPoint = laneUtil.ENU2PARA(
      createENUPoint(endPoint_map.x, endPoint_map.y, endPoint_map.z));

  //   route::FullRoute routeResult = route::planning::planRoute(
  //       startParaPoint, endParaPoint, route::RouteCreationMode::Undefined);
  auto routingStart = route::planning::createRoutingPoint(startParaPoint);
  auto routingDest = route::planning::createRoutingPoint(endParaPoint);
  route::planning::RouteAstar routePlanning(
      routingStart, routingDest, route::planning::Route::Type::SHORTEST);
  route::planning::Route::RawRoute rawRoute;
  if (routePlanning.calculate()) {
    rawRoute = routePlanning.getRawRoute();
  }
  std::cout << " rawRoute paraPointList " << rawRoute.paraPointList.size()
            << std::endl;
  route::FullRoute routeResult = route::planning::createFullRoute(
      rawRoute, route::RouteCreationMode::Undefined);

  route::RoadSegmentList roads = routeResult.roadSegments;
  cout << "road number: " << roads.size() << endl;

  std::cout << "case 2:" << std::endl;
  std::cout << "routing test finished!" << std::endl;
}
void testDistance() {
  std::cout << "Distance test started!" << std::endl;
  ENUPoint startPoint = createENUPoint(-236.136, -6367.09, 297.734);
  ENUPoint endPoint = createENUPoint(681.497, 6656.96, 408.513);

  double distance;
  clock_t start = clock();
  laneUtil.getDistance(startPoint, endPoint, &distance);
  clock_t end = clock();
  double time = (end - start) / (double)CLOCKS_PER_SEC;
  std::cout << "distance: " << distance << " time: " << time << std::endl;

  ENUPoint startPoint2 = createENUPoint(-236.136, -6367.09, 297.734);
  ENUPoint endPoint2 = createENUPoint(-675.082, -6087.03, 295.446);
  double distance2;
  clock_t start2 = clock();
  laneUtil.getDistance(startPoint2, endPoint2, &distance2);
  clock_t end2 = clock();
  double time2 = (end2 - start2) / (double)CLOCKS_PER_SEC;
  std::cout << "distance: " << distance2 << " time: " << time2 << std::endl;
  std::cout << "Distance test finished!" << std::endl;
}

void testDistance_2() {
  std::cout << "Distance test started!" << std::endl;
  ENUPoint startPoint = createENUPoint(-253.154, -6357.24, 297.498);
  ENUPoint endPoint = createENUPoint(-379.251, -6278.15, 295.592);

  double distance;
  clock_t start = clock();
  laneUtil.getDistance(startPoint, endPoint, &distance);
  clock_t end = clock();
  double time = (end - start) / (double)CLOCKS_PER_SEC;
  std::cout << "distance: " << distance << " time: " << time << std::endl;

  ENUPoint startPoint2 = createENUPoint(-253.154, -6357.24, 297.498);
  ENUPoint endPoint2 = createENUPoint(30.7996, 1372.91, 407.306);
  double distance2;
  clock_t start2 = clock();
  laneUtil.getDistance(startPoint2, endPoint2, &distance2);
  clock_t end2 = clock();
  double time2 = (end2 - start2) / (double)CLOCKS_PER_SEC;
  std::cout << "distance: " << distance2 << " time: " << time2 << std::endl;
  std::cout << "Distance test finished!" << std::endl;
}

void testGetZ() {
  std::cout << "getZ test started!" << std::endl;
  ENUPoint point1 = createENUPoint(-236.136, -6367.09, 297.734);
  ENUPoint point2 = createENUPoint(681.497, 6656.96, 408.513);
  ENUPoint point3 = createENUPoint(-675.082, -6087.03, 295.446);
  clock_t start1 = clock();
  double z1 = laneUtil.getZ(point1.x, point1.y);
  clock_t end1 = clock();
  double dur1 = (end1 - start1) / (double)CLOCKS_PER_SEC;
  std::cout << "Z 1 ref: 297.734 result: " << z1 << " time: " << dur1
            << std::endl;
  clock_t start2 = clock();
  double z2 = laneUtil.getZ(point2.x, point2.y);
  clock_t end2 = clock();
  double dur2 = (end2 - start2) / (double)CLOCKS_PER_SEC;
  std::cout << "Z 2 ref: 408.513 result: " << z2 << " time: " << dur2
            << std::endl;
  clock_t start3 = clock();
  double z3 = laneUtil.getZ(point3.x, point3.y);
  clock_t end3 = clock();
  double dur3 = (end3 - start3) / (double)CLOCKS_PER_SEC;
  std::cout << "Z 3 ref: 295.446 result: " << z3 << " time: " << dur3
            << std::endl;
  clock_t start4 = clock();
  double z4 = laneUtil.getZ(968.4853, 3374.7655);
  clock_t end4 = clock();
  double dur4 = (end4 - start4) / (double)CLOCKS_PER_SEC;
  std::cout << "Z 4 ref: not known result: " << z4 << " time: " << dur4
            << std::endl;
  std::cout << "getZ test finished!" << std::endl;
}

void testGetZ_2() {
  std::cout << "getZ test started!" << std::endl;
  ENUPoint point1 = createENUPoint(-253.154, -6357.24, 297.498);
  ENUPoint point2 = createENUPoint(-379.251, -6278.15, 295.592);
  ENUPoint point3 = createENUPoint(30.7996, 1372.91, 407.306);
  clock_t start1 = clock();
  double z1 = laneUtil.getZ(point1.x, point1.y);
  clock_t end1 = clock();
  double dur1 = (end1 - start1) / (double)CLOCKS_PER_SEC;
  std::cout << "Z 1 ref: 297.734 result: " << z1 << " time: " << dur1
            << std::endl;
  clock_t start2 = clock();
  double z2 = laneUtil.getZ(point2.x, point2.y);
  clock_t end2 = clock();
  double dur2 = (end2 - start2) / (double)CLOCKS_PER_SEC;
  std::cout << "Z 2 ref: 408.513 result: " << z2 << " time: " << dur2
            << std::endl;
  clock_t start3 = clock();
  double z3 = laneUtil.getZ(point3.x, point3.y);
  clock_t end3 = clock();
  double dur3 = (end3 - start3) / (double)CLOCKS_PER_SEC;
  std::cout << "Z 3 ref: 295.446 result: " << z3 << " time: " << dur3
            << std::endl;
  clock_t start4 = clock();
  std::cout << "getZ test finished!" << std::endl;
}

void testSlop() {
  std::cout << "getSlop test started!" << std::endl;
  ENUPoint point1 = createENUPoint(-236.136, -6367.09, 297.734);
  ENUPoint point2 = createENUPoint(681.497, 6656.96, 408.513);
  ENUPoint point3 = createENUPoint(-675.082, -6087.03, 295.446);
  double s1 = laneUtil.getSlop(point1);
  std::cout << "result: " << s1 << std::endl;
  double s2 = laneUtil.getSlop(point2);
  std::cout << "result: " << s2 << std::endl;
  double s3 = laneUtil.getSlop(point3);
  std::cout << "result: " << s3 << std::endl;
  std::cout << "getSlop test finished!" << std::endl;
}

void testSlop_2() {
  std::cout << "getSlop test started!" << std::endl;
  ENUPoint point1 = createENUPoint(-236.136, -6367.09, 297.734);
  ENUPoint point2 = createENUPoint(681.497, 6656.96, 408.513);
  ENUPoint point3 = createENUPoint(-675.082, -6087.03, 295.446);
  double s1 = laneUtil.getSlop(point1);
  std::cout << "result: " << s1 << std::endl;
  double s2 = laneUtil.getSlop(point2);
  std::cout << "result: " << s2 << std::endl;
  double s3 = laneUtil.getSlop(point3);
  std::cout << "result: " << s3 << std::endl;
  std::cout << "getSlop test finished!" << std::endl;
}

// void testYaw() {
//   std::cout << "getYaw test started!" << std::endl;
//   ENUPoint point1 = createENUPoint(-236.136, -6367.09, 297.734);
//   ENUPoint point2 = createENUPoint(681.497, 6656.96, 408.513);
//   ENUPoint point3 = createENUPoint(-675.082, -6087.03, 295.446);
//   double y1 = laneUtil.getYaw(point1);
//   std::cout << "result: " << y1 << std::endl;
//   double y2 = laneUtil.getYaw(point2);
//   std::cout << "result: " << y2 << std::endl;
//   double y3 = laneUtil.getYaw(point3);
//   std::cout << "result: " << y3 << std::endl;
//   std::cout << "getYaw test finished!" << std::endl;
// }

void testDistance_3() {
  std::cout << "Distance test started!" << std::endl;
  ENUPoint startPoint = createENUPoint(-232.699, -6363.77, 297.703);
  ENUPoint endPoint = createENUPoint(-492.744, -6200.77, 293.956);

  double distance;
  clock_t start = clock();
  laneUtil.getDistance(startPoint, endPoint, &distance);
  clock_t end = clock();
  double time = (end - start) / (double)CLOCKS_PER_SEC;
  std::cout << "distance: " << distance << " time: " << time << std::endl;

  ENUPoint startPoint2 = createENUPoint(-232.699, -6363.77, 297.703);
  ENUPoint endPoint2 = createENUPoint(725.121, 6486.22, 408.233);

  double distance2;
  clock_t start2 = clock();
  laneUtil.getDistance(startPoint2, endPoint2, &distance2);
  clock_t end2 = clock();
  double time2 = (end2 - start2) / (double)CLOCKS_PER_SEC;
  std::cout << "distance: " << distance2 << " time: " << time2 << std::endl;
  std::cout << "Distance test finished!" << std::endl;
}

void testGetZ_3() {
  std::cout << "getZ test started!" << std::endl;
  ENUPoint point1 = createENUPoint(-232.699, -6363.77, 297.703);
  ENUPoint point2 = createENUPoint(-492.744, -6200.77, 293.956);
  ENUPoint point3 = createENUPoint(685.476, 6643.98, 408.661);
  clock_t start1 = clock();
  double z1 = laneUtil.getZ(point1.x, point1.y);
  clock_t end1 = clock();
  double dur1 = (end1 - start1) / (double)CLOCKS_PER_SEC;
  std::cout << "Z 1 ref: 297.734 result: " << z1 << " time: " << dur1
            << std::endl;
  clock_t start2 = clock();
  double z2 = laneUtil.getZ(point2.x, point2.y);
  clock_t end2 = clock();
  double dur2 = (end2 - start2) / (double)CLOCKS_PER_SEC;
  std::cout << "Z 2 ref: 408.513 result: " << z2 << " time: " << dur2
            << std::endl;
  clock_t start3 = clock();
  double z3 = laneUtil.getZ(point3.x, point3.y);
  clock_t end3 = clock();
  double dur3 = (end3 - start3) / (double)CLOCKS_PER_SEC;
  std::cout << "Z 3 ref: 295.446 result: " << z3 << " time: " << dur3
            << std::endl;
  clock_t start4 = clock();
  std::cout << "getZ test finished!" << std::endl;
}

void testSlop_3() {
  std::cout << "getSlop test started!" << std::endl;
  ENUPoint point1 = createENUPoint(-232.699, -6363.77, 297.703);
  ENUPoint point2 = createENUPoint(-492.744, -6200.77, 293.956);
  ENUPoint point3 = createENUPoint(685.476, 6643.98, 408.661);
  double s1 = laneUtil.getSlop(point1);
  std::cout << "result: " << s1 << std::endl;
  double s2 = laneUtil.getSlop(point2);
  std::cout << "result: " << s2 << std::endl;
  double s3 = laneUtil.getSlop(point3);
  std::cout << "result: " << s3 << std::endl;
  std::cout << "getSlop test finished!" << std::endl;
}

int main() {
  std::string package_share_directory =
      ament_index_cpp::get_package_share_directory("map_test");

  // const std::string mapConfigPath =
  //     package_share_directory + "/resource/jinan_link_V3_D11_3_config.txt";
  // laneUtil.initialize(mapConfigPath);
  // // testRouting();
  // testDistance();
  // testGetZ();
  // testSlop();
  // // testYaw();

  // const std::string mapConfigPath =
  //     package_share_directory + "/resource/jinan_mean_20201111_config.txt";
  // laneUtil.initialize(mapConfigPath);
  // testDistance_2();
  // testGetZ_2();
  // testSlop_2();

  // const std::string mapConfigPath =
  //     package_share_directory +
  //     "/resource/jinan_mean_link_elevation_20201117_config.txt";
  const std::string mapConfigPath =
      package_share_directory + "/resource/move_lane_fix_config.txt";
  clock_t start, end;
  start = clock();
  laneUtil.initialize(mapConfigPath);
  end = clock();
  double duration = (end - start) / (double)CLOCKS_PER_SEC;
  std::cout << "read map time: " << duration << std::endl;
  testDistance_3();
  testGetZ_3();
  testSlop_3();

  return 0;
}