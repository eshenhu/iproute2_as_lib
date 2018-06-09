#include "ip_api.h"
#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/exceptions.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <exception>

namespace pt = boost::property_tree;
const int MAX_LEN = 1024 * 2;

enum class iproute2_exception : int
{
   enum_iproute2_excep_bad_path = 1,
   enum_iproute2_excep_bad_data = 2,
   enum_iproute2_excep_bad      = 3,
   enum_iproute2_excep_other    = 4
};

int main()
{
   int code_main = 0;
   const char* argv[] = {"ip", "-4", "-json", "addr"}; 

   char buffer[MAX_LEN] = {0};
   int c = main_entry_point3(SIZEOF(argv), argv, buffer, MAX_LEN);
   if (c)
   {
      std::cerr << "error when calling main_entry_point3 with " << c << std::endl;
      return c;
   }

   std::cout << buffer << std::endl;
   std::stringstream ss;
   ss << buffer;

   try {
      pt::ptree pt;
      pt::read_json(ss, pt); 
      
      for(auto&& item : pt.get_child(""))
      {
          std::cout << "ifname -> " << item.second.get<std::string>("ifname") << std::endl;
          for(auto&& addr_info : item.second.get_child("addr_info"))
          {
             std::cout << "   family : " << addr_info.second.get<std::string>("family")
           	  << " ip : " << addr_info.second.get<std::string>("local")
           	  << std::endl;
          }
      }
   }
   catch(pt::ptree_bad_path& e)
   {
      std::cerr << "Exception: bad_path " << e.what() << std::endl;
      code_main = static_cast<int>(iproute2_exception::enum_iproute2_excep_bad_path);
   }
   catch(pt::ptree_bad_data& e)
   {
      std::cerr << "Exception: bad_data " << e.what() << std::endl;
      code_main = static_cast<int>(iproute2_exception::enum_iproute2_excep_bad_data); 
   }
   catch(pt::ptree_error& e)
   {
      std::cerr << "Exception: error " << e.what() << std::endl;
      code_main = static_cast<int>(iproute2_exception::enum_iproute2_excep_bad);
   }
   catch(std::exception& e)
   {
      std::cerr << "Exception:  " << e.what() << std::endl;
      code_main = static_cast<int>(iproute2_exception::enum_iproute2_excep_other);
   }
   return code_main;
}
