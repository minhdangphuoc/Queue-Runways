#ifndef _Plane_cpp_
#define _Plane_cpp_
#include "Plane.hpp"



void Plane::refuse() const
/*
Post: Processes a Plane wanting to use Runway, when
      the Queue is full.
*/

{
   std::cout << "Plane number " << flt_num;
   if (state == arriving)
      std::cout << " directed to another airport" << std::endl;
   else
      std::cout << " told to try to takeoff again later" << std::endl;
}


void Plane::land(int time) const
/*
Post: Processes a Plane that is landing at the specified time.
*/

{
   int wait = time - clock_start;
   std::cout << time << ": Plane number " << flt_num << " landed after "
        << wait << " time unit" << ((wait == 1) ? "" : "s")
        << " in the landing queue." << std::endl;
}


void Plane::fly(int time) const
/*
Post: Process a Plane that is taking off at the specified time.
*/

{
   int wait = time - clock_start;
   std::cout << time << ": Plane number " << flt_num << " took off after "
        << wait << " time unit" << ((wait == 1) ? "" : "s")
        << " in the takeoff queue." << std::endl;
}


int Plane::started() const
/*
Post: Return the time that the Plane entered the airport system.
*/
{
   return clock_start;
}
#endif // _Plane_cpp_