#include <iostream>

#include "Runway.hpp"
#include "RANDOM.H"
#include "RANDOM.CPP"

const int MIN_FUEL = 1;
const int MAX_FUEL = 3;

namespace Programs
{
   void main_1();
   void main_2();
   void main_3();
   void main_4();
   void main_5();
}

namespace Utilities
{
   void initialize(int &, int &, double &, double &);
   void run_idle(int);
   char options();
}

int main() 
{
   switch(Utilities::options())
   {
      case '1':
         Programs::main_1();
         break;
      case '2':
         Programs::main_2();
         break;
      case '3':
         Programs::main_3();
         break;
      case '4':
         Programs::main_4();
         break;
      case '5':
         Programs::main_5();
         break;
      default:
         std::cout << "Wrong input, exit program." << std::endl;
   }
}


char Utilities::options()
{
   char opt = null;
   while (opt == null || opt == '\n')
   {
      std::cout << "1.Run P1 version of Airport simulator\n2.Run P2 version of Airport simulator\n3.Run P3 version of Airport simulator\n4.Run P4 version of Airport simulator\n5.Run P5 version of Airport simulator\n6.Quit the program\nYour choice: " << std::flush;
      opt = std::getchar();
   }
   return opt;
}

void Programs::main_1()     //  Airport simulation program
/*
Pre:  The user must supply the number of time intervals the simulation is to
      run, the expected number of planes arriving, the expected number
      of planes departing per time interval, and the
      maximum allowed size for runway queues.
Post: The program performs a random simulation of the airport, showing
      the status of the runway at each time interval, and prints out a
      summary of airport operation at the conclusion.
Uses: Classes Runway, Plane, Random and functions run_idle, initialize.
*/

{
   int end_time;            //  time to run simulation
   int queue_limit;         //  size of Runway queues
   int flight_number = 0;
   double arrival_rate, departure_rate;

   std::cout << "This program simulates an airport with only one runway." << std::endl
        << "One plane can land or depart in each unit of time." << std::endl;
   Utilities::initialize(end_time, queue_limit, arrival_rate, departure_rate);
   
   Random variable;
   Runway small_airport(queue_limit);
   for (int current_time = 0; current_time < end_time; current_time++) { //  loop over time intervals
      int number_arrivals = variable.poisson(arrival_rate);  //  current arrival requests
      for (int i = 0; i < number_arrivals; i++) {
         Plane current_plane(flight_number++, current_time, arriving);
         if (small_airport.can_land(current_plane) != success)
            current_plane.refuse();
      }

      int number_departures= variable.poisson(departure_rate); //  current departure requests
      for (int j = 0; j < number_departures; j++) {
         Plane current_plane(flight_number++, current_time, departing);
         if (small_airport.can_depart(current_plane) != success)
            current_plane.refuse();
      }

      Plane moving_plane;

      std::cout << "- small_airport: ";

      switch (small_airport.activity(current_time, moving_plane)) {
        //  Let at most one Plane onto the Runway at current_time.
      case land:
         moving_plane.land(current_time);
         break;
      case take_off:
         moving_plane.fly(current_time);
         break;
      case idle:
         Utilities::run_idle(current_time);
      }
   }
   std::cout << "- small_airport -" << std::endl;
   small_airport.shut_down(end_time);
}

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void Programs::main_2()     //  Airport simulation program
{
   int end_time;            //  time to run simulation
   int queue_limit;         //  size of Runway queues
   int flight_number = 0;
   double arrival_rate, departure_rate;
   
   std::cout << "This program simulates an airport with only two runways." << std::endl
        << "One plane can land or depart in each unit of time." << std::endl;
   Utilities::initialize(end_time, queue_limit, arrival_rate, departure_rate);
   
   Random variable;
   
   Runway landing_runway(queue_limit); // add landing runway
   Runway takeoff_runway(queue_limit); // add takeoff runway
   
   for (int current_time = 0; current_time < end_time; current_time++) { //  loop over time intervals
      int number_arrivals = variable.poisson(arrival_rate);  //  current arrival requests
      for (int i = 0; i < number_arrivals; i++) {
         Plane current_plane(flight_number++, current_time, arriving);
         if (landing_runway.can_land(current_plane) != success)
            current_plane.refuse();
      }

      int number_departures= variable.poisson(departure_rate); //  current departure requests
      for (int j = 0; j < number_departures; j++) {
         Plane current_plane(flight_number++, current_time, departing);
         if (takeoff_runway.can_depart(current_plane) != success)
            current_plane.refuse();
      }

      Plane moving_plane;

        std::cout << "- landing_runway: ";
      switch (landing_runway.activity(current_time, moving_plane)) { //
        //  Let at most one Plane onto the Runway at current_time.
      case land:
         moving_plane.land(current_time);
         break;
      case take_off:
         moving_plane.fly(current_time);
         break;
      case idle:
         Utilities::run_idle(current_time);
      }

         std::cout << "- takeoff_runway: ";
      switch (takeoff_runway.activity(current_time, moving_plane)) { //
        //  Let at most one Plane onto the Runway at current_time.
      case land:
         moving_plane.land(current_time);
         break;
      case take_off:
         moving_plane.fly(current_time);
         break;
      case idle:
         Utilities::run_idle(current_time);
      }
   }
   std::cout << "- landing_runway -" << std::endl;
   landing_runway.shut_down(end_time);
   std::cout << "- takeoff_runway -" << std::endl;
   takeoff_runway.shut_down(end_time);
}

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void Programs::main_3()
{
   int end_time;            //  time to run simulation
   int queue_limit;         //  size of Runway queues
   int flight_number = 0;
   double arrival_rate, departure_rate;
   
   std::cout << "This program simulates an airport with only two direction runways which can be changed." << std::endl
        << "One plane can land or depart in each unit of time." << std::endl;
   Utilities::initialize(end_time, queue_limit, arrival_rate, departure_rate);
   
   Random variable;
   
   Runway landing_runway(queue_limit); // add landing runway
   Runway takeoff_runway(queue_limit); // add takeoff runway
   
   for (int current_time = 0; current_time < end_time; current_time++) { //  loop over time intervals
      int number_arrivals = variable.poisson(arrival_rate);  //  current arrival requests
      for (int i = 0; i < number_arrivals; i++) {
         Plane current_plane(flight_number++, current_time, arriving);
         if (landing_runway.can_land(current_plane) != success)
         if (takeoff_runway.can_land(current_plane) != success)
         current_plane.refuse();
      }

      int number_departures= variable.poisson(departure_rate); //  current departure requests
      for (int j = 0; j < number_departures; j++) {
         Plane current_plane(flight_number++, current_time, departing);
         if (takeoff_runway.can_depart(current_plane) != success)
         if (landing_runway.can_depart(current_plane) != success)
         current_plane.refuse();
      }

      Plane moving_plane;

      std::cout << "- landing_runway: ";
      switch (landing_runway.activity(current_time, moving_plane)) { //
        //  Let at most one Plane onto the Runway at current_time.
      case land:
         moving_plane.land(current_time);
         break;
      case take_off:
         moving_plane.fly(current_time);
         break;
      case idle:
         Utilities::run_idle(current_time);
      }

      std::cout << "- takeoff_runway: ";
      switch (takeoff_runway.activity(current_time, moving_plane)) { //
        //  Let at most one Plane onto the Runway at current_time.
      case land:
         moving_plane.land(current_time);
         break;
      case take_off:
         moving_plane.fly(current_time);
         break;
      case idle:
         Utilities::run_idle(current_time);
      }
   }
   std::cout << "- landing_runway: " << std::endl;
   landing_runway.shut_down(end_time);
   std::cout << "- takeoff_runway: " << std::endl;
   takeoff_runway.shut_down(end_time);
}

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void Programs::main_4()
{
   int end_time;            //  time to run simulation
   int queue_limit;         //  size of Runway queues
   int flight_number = 0;
   double arrival_rate, departure_rate;
   
   std::cout << "This program simulates an airport with only two direction runways and one backup runways." << std::endl
        << "One plane can land or depart in each unit of time." << std::endl;
   Utilities::initialize(end_time, queue_limit, arrival_rate, departure_rate);
   
   Random variable;
   
   Runway landing_runway(queue_limit); // add landing runway
   Runway takeoff_runway(queue_limit); // add takeoff runway
   Runway backup_runway(queue_limit); // add takeoff runway
   
   for (int current_time = 0; current_time < end_time; current_time++) { //  loop over time intervals
      int number_arrivals = variable.poisson(arrival_rate);  //  current arrival requests
      for (int i = 0; i < number_arrivals; i++) {
         Plane current_plane(flight_number++, current_time, arriving);
         if (landing_runway.can_land(current_plane) != success)
         if (backup_runway.can_land(current_plane) != success)
         current_plane.refuse();
      }

      int number_departures= variable.poisson(departure_rate); //  current departure requests
      for (int j = 0; j < number_departures; j++) {
         Plane current_plane(flight_number++, current_time, departing);
         if (takeoff_runway.can_depart(current_plane) != success)
         if (backup_runway.can_depart(current_plane) != success)
         current_plane.refuse();
      }

      Plane moving_plane;

      std::cout << "- landing_runway: ";
      switch (landing_runway.activity(current_time, moving_plane)) { //
        //  Let at most one Plane onto the Runway at current_time.
      case land:
         moving_plane.land(current_time);
         break;
      case take_off:
         moving_plane.fly(current_time);
         break;
      case idle:
         Utilities::run_idle(current_time);
      }

      std::cout << "- takeoff_runway: ";
      switch (takeoff_runway.activity(current_time, moving_plane)) { //
        //  Let at most one Plane onto the Runway at current_time.
      case land:
         moving_plane.land(current_time);
         break;
      case take_off:
         moving_plane.fly(current_time);
         break;
      case idle:
         Utilities::run_idle(current_time);
      }

      std::cout << "- backup_runway: ";
      switch (backup_runway.activity(current_time, moving_plane)) { //
        //  Let at most one Plane onto the Runway at current_time.
      case land:
         moving_plane.land(current_time);
         break;
      case take_off:
         moving_plane.fly(current_time);
         break;
      case idle:
         Utilities::run_idle(current_time);
      }
   }
   std::cout << "- landing_runway: " << std::endl;
   landing_runway.shut_down(end_time);
   std::cout << "- takeoff_runway: " << std::endl;
   takeoff_runway.shut_down(end_time);
   std::cout << "- backup_runway: " << std::endl;
   backup_runway.shut_down(end_time);
}

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void Programs::main_5()
{
   int end_time;            //  time to run simulation
   int queue_limit;         //  size of Runway queues
   int flight_number = 0;
   double arrival_rate, departure_rate;


   std::cout << "This program simulates an airport with only one runway and plane has fuel." << std::endl
        << "One plane can land or depart in each unit of time." << std::endl;
   Utilities::initialize(end_time, queue_limit, arrival_rate, departure_rate);
   
   Random variable;
   Runway small_airport(queue_limit);
   for (int current_time = 0; current_time < end_time; current_time++) { //  loop over time intervals
      int fuel;
      int number_arrivals = variable.poisson(arrival_rate);  //  current arrival requests
      for (int i = 0; i < number_arrivals; i++) {
         fuel = variable.random_integer(MIN_FUEL, MAX_FUEL); // Random fuel value for landing plane
         Plane current_plane(flight_number++, current_time, arriving, fuel);
         if (small_airport.can_land(current_plane) != success)
            current_plane.refuse();
      }

      int number_departures= variable.poisson(departure_rate); //  current departure requests
      for (int j = 0; j < number_departures; j++) {
         Plane current_plane(flight_number++, current_time, departing);
         if (small_airport.can_depart(current_plane) != success)
            current_plane.refuse();
      }

      small_airport.enough_fuel(current_time);
      
      Plane moving_plane;
      
      switch (small_airport.activity(current_time, moving_plane)) {
      //  Let at most one Plane onto the Runway at current_time.
      case land:
         moving_plane.land(current_time);
         break;
      case take_off:
         moving_plane.fly(current_time);
         break;
      case idle:
         Utilities::run_idle(current_time);
      }

      
   }
   std::cout << "- small_airport -" << std::endl;
   small_airport.shut_down(end_time);
}

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void Utilities::initialize(int &end_time, int &queue_limit,
                double &arrival_rate, double &departure_rate)
/*
Pre:  The user specifies the number of time units in the simulation,
      the maximal queue sizes permitted,
      and the expected arrival and departure rates for the airport.
Post: The program prints instructions and initializes the parameters
      end_time, queue_limit, arrival_rate, and departure_rate to
      the specified values.
Uses: utility function user_says_yes
*/

{
   std::cout << "Up to what number of planes can be waiting to land "
        << "or take off at any time? " << std::flush;
   std::cin  >> queue_limit;

   std::cout << "How many units of time will the simulation run?" << std::flush;
   std::cin  >> end_time;

   bool acceptable;
   do {
      std::cout << "Expected number of arrivals per unit time?" << std::flush;
      std::cin  >> arrival_rate;
      std::cout << "Expected number of departures per unit time?" << std::flush;
      std::cin  >> departure_rate;
      if (arrival_rate < 0.0 || departure_rate < 0.0)
         std::cerr << "These rates must be nonnegative." << std::endl;
      else
         acceptable = true;

      if (acceptable && arrival_rate + departure_rate > 1.0)
         std::cerr << "Safety Warning: This airport will become saturated. " << std::endl;

   } while (!acceptable);
}

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void Utilities::run_idle(int time)
/*
Post: The specified time is printed with a message that the runway is idle.
*/
{
   cout << time << ": Runway is idle." << endl;
}

