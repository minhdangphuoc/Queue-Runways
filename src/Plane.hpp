#ifndef _Plane_hpp_
#define _Plane_hpp_

#include <iostream>

enum Plane_status {null, arriving, departing};

class Plane {
public:
   Plane() {
      flt_num = -1;
      clock_start = -1;
      fuel = -1;
      state = null;
   }

   Plane operator= (const Plane &copy){
      this -> fuel = copy.fuel;
      this -> flt_num = copy.flt_num;
      this -> clock_start = copy.clock_start;
      this -> state = copy.state;
      return *this;
   }

   Plane(int flt, int time, Plane_status status, int fuel)
   /*
   Post:  The Plane data members flt_num, clock_start, state
         and fuel are set to the values of the parameters flt,
         time and status, respectively.
   */

   {
      this -> fuel = fuel;
      this -> flt_num = flt;
      this -> clock_start = time;
      this -> state = status;
      std::cout << "Plane number " << flt << " ready to ";
      if (status == arriving)
         std::cout << "land." << std::endl;
      else
         std::cout << "take off." << std::endl;
   }

   Plane(int flt, int time, Plane_status status)
   /*
   Post:  The Plane data members flt_num, clock_start,
         and state are set to the values of the parameters flt,
         time and status, respectively.
   */

   {
      this -> flt_num = flt;
      this -> clock_start = time;
      this -> state = status;
      std::cout << "Plane number " << flt << " ready to ";
      if (status == arriving)
         std::cout << "land." << std::endl;
      else
         std::cout << "take off." << std::endl;
   }

   void refuse() const;
   void land(int time) const;
   void fly(int time) const;
   int started() const;
   int get_fly_num() const {return this -> flt_num;}
   int check_fuel() const {return this -> fuel;}

private:
   int flt_num;
   int clock_start;
   Plane_status state;
   int fuel;
};


#endif // _Plane_hpp_