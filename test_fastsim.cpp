
#ifndef APPLE
#define BOOST_TEST_DYN_LINK 
#define BOOST_TEST_MODULE fastsim



#include <boost/test/unit_test.hpp>
#endif

#include <boost/foreach.hpp>
#include <sferes/fit/fitness_simu.hpp>
#include "simu_fastsim.hpp"

using namespace sferes;
//using namespace sferes::ctrl;
struct Params
{
  struct simu
  {
    SFERES_STRING(map_name, "modules/fastsim/cuisine.pbm");
  };
};


BOOST_AUTO_TEST_CASE(fastsim_intersection)
{
  using namespace fastsim;
  typedef simu::Fastsim<Params> simu_t;
  simu_t s;
  s.robot().set_pos(Posture(200, 100, 0));
  s.robot().use_camera();
  Map::ill_sw_t s1 = Map::ill_sw_t(new IlluminatedSwitch(1, 10, 300, 250, true)); 
  Map::ill_sw_t s2 = Map::ill_sw_t(new IlluminatedSwitch(2, 30, 500, 250, true));
  Map::ill_sw_t s3 = Map::ill_sw_t(new IlluminatedSwitch(3, 10, 200, 150, true));
  Map::ill_sw_t s4 = Map::ill_sw_t(new IlluminatedSwitch(4, 10, 400, 350, true));
  s.map()->add_illuminated_switch(s1);
  s.map()->add_illuminated_switch(s2);
  s.map()->add_illuminated_switch(s3);
  s.map()->add_illuminated_switch(s4);
  
  int c1 = s.map()->check_inter_is(250, 250, 1000, 250);
  BOOST_CHECK_EQUAL(c1, 1);
  
  int c2 = s.map()->check_inter_is(250, 250, 250, 0);
  BOOST_CHECK_EQUAL(c2, -1);
  
  int c3 = s.map()->check_inter_is(200, 350, 200, 100);
  BOOST_CHECK_EQUAL(c3, 3);
  
  // s.init_view();
  // while(true)
  //   {
  //     s.refresh();
  //     s.refresh_view();
  //   }
}

#ifdef APPLE 
int main(int argc, char *argv[])
{
	std::cout<<"WARNING: BOOST TEST framework desactivated on macos to avoid problems with SDL."<<std::endl;
#else
BOOST_AUTO_TEST_CASE(fastsim_simu_refresh)
{
#endif
  using namespace fastsim;
  typedef simu::Fastsim<Params> simu_t;
  simu_t s;
  s.robot().set_pos(Posture(250, 250, 0));

  s.robot().add_laser(Laser(M_PI / 3, 50));
  s.robot().add_laser(Laser(0, 50));
  s.robot().add_laser(Laser(-M_PI / 3, 50));

  Map::ill_sw_t s1 = Map::ill_sw_t(new IlluminatedSwitch(1, 10, 300, 251, true));
  Map::ill_sw_t s2 = Map::ill_sw_t(new IlluminatedSwitch(2, 10, 530, 150, false));
  Map::ill_sw_t s3 = Map::ill_sw_t(new IlluminatedSwitch(3, 10, 200, 150, false));
  Map::ill_sw_t s4 = Map::ill_sw_t(new IlluminatedSwitch(4, 10, 400, 350, false));
  s1->link(s2);
  s1->link(s3);
  s2->link(s4);
  s.map()->add_illuminated_switch(s1);
  s.map()->add_illuminated_switch(s2);
  s.map()->add_illuminated_switch(s3);
  s.map()->add_illuminated_switch(s4);
  
  s.robot().add_light_sensor(LightSensor(1, M_PI / 3, M_PI / 3));
  s.robot().add_light_sensor(LightSensor(1, -M_PI / 3, M_PI / 3));
  s.robot().add_light_sensor(LightSensor(2, M_PI / 3, M_PI / 3));
  s.robot().add_light_sensor(LightSensor(2, -M_PI / 3, M_PI / 3));
			     

  s.init_view();
  for (size_t i = 0; i < 10000; ++i)
    {
      if (s.robot().get_left_bumper())
	s.move_robot(2.0, -2.0);
      else if (s.robot().get_right_bumper())
	s.move_robot(2.0, -2.0);
      else if (rand()/(RAND_MAX + 1.0) < 0.05)
	s.move_robot(3.0, -3.0);
      else if (rand()/(RAND_MAX + 1.0) < 0.05)
	s.move_robot(-3.0, 3.0);
      else
	s.move_robot(2.0, 2.0);
	std::cout<<"i="<<i<<std::endl;
      s.refresh();
      s.refresh_view();
    }
#ifdef APPLE
	return 0;
#endif
}
