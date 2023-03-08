#ifndef __CONVERT_
#define __CONVERT_
#include "json.h"
#include <iostream>
#include <string>
#include <map>
#include <iterator>
#include <sstream>


    std::string map2jsonstr(const std::map<std::string, std::string> &map_info);

    std::string itoa_self(int i);

    std::map<std::string, std::string> jsonstr2map(const std::string &json);


#endif