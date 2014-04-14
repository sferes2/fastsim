#include <boost/foreach.hpp>
#include "simu_fastsim.hpp"

using namespace sferes;
struct Params
{
  struct simu
  {
    SFERES_STRING(map_name, "modules/fastsim/cuisine.pbm");
  };
};



int main(int argc, char *argv[])
{
  using namespace fastsim;
  typedef simu::Fastsim<Params> simu_t;
  simu_t s;
  s.robot().set_pos(Posture(250, 250, 0));
  s.robot().use_camera();
  s.robot().add_laser(Laser(M_PI / 3, 50));
  s.robot().add_laser(Laser(0, 50));
  s.robot().add_laser(Laser(-M_PI / 3, 50));

  Map::ill_sw_t s1 = Map::ill_sw_t(new IlluminatedSwitch(1, 10, 300, 251, true));
  Map::ill_sw_t s2 = Map::ill_sw_t(new IlluminatedSwitch(2, 10, 530, 150, true));
  Map::ill_sw_t s3 = Map::ill_sw_t(new IlluminatedSwitch(3, 10, 200, 150, true));
  Map::ill_sw_t s4 = Map::ill_sw_t(new IlluminatedSwitch(4, 10, 400, 350, true));

  s.map()->add_illuminated_switch(s1);
  s.map()->add_illuminated_switch(s2);
  s.map()->add_illuminated_switch(s3);
  s.map()->add_illuminated_switch(s4);


  s.init_view();

  int numkey;
  while(true)
    {
      SDL_PumpEvents();
      Uint8* keys = SDL_GetKeyState(&numkey);
      if (keys[SDLK_UP])
	s.move_robot(1.0, 1.0);
      if (keys[SDLK_DOWN])
	s.move_robot(-1.0, -1.0);
      if (keys[SDLK_LEFT])
       	s.move_robot(1.0, -1.0);
      if (keys[SDLK_RIGHT])
       	s.move_robot(-1.0, 1.0);
      s.refresh();
      s.refresh_view();
    }

  return 0;
}
