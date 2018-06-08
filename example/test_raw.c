#include "ip_api.h"
#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <set>
#include <exception>
#include <iostream>

namespace pt = boost::property_tree;
const int MAX_LEN = 1024 * 2;
/*
struct ip_getter
{
   std::
};
*/
int main()
{
   const char* argv[] = {"ip", "-json", "addr"}; 

   char buffer[MAX_LEN];
   int c = main_entry_point3(SIZEOF(argv), argv, buffer, MAX_LEN);
   if (c)
   {
      std::cout << "error when calling main_entry_point3 with " << c << std::endl;
      return c;
   }

   std::cout << "read code " << buffer << std::endl;
   std::stringstream ss;
   ss << buffer;

   pt::ptree pt;
   pt::read_json(ss, pt); 
   
   for(auto&& v : tree.get_child(""))
   {
   }
}
