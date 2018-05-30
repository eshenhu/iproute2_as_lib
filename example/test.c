//#include "ip.h"
#include "options.h"

using namespace iproute2_lib;

extern "C" int main_entry_point(int argc, char **argv);

int main()
{
   Options opt = FactoryOptions::make_ip_addr_basic();
   OptionsArgs args = opt.format_one_line();

   //char* argvv[] = {"ip", "-json", "addr"}; 
   //main_entry_point(3, argvv);   
   //
   main_entry_point(args.argc, args.argv);
}

