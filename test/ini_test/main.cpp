#include "ini/ini.h"
int main() {
    inih::INIReader r{"C:/Users/Jianh/Desktop/ini_test/config.ini"};
    // Get and parse the ini value
    const auto& v1 = r.Get<std::string>("section1", "any"); // "5"
    const auto& v2 = r.Get<int>("section1", "any"); // 5
    const auto& v3 = r.Get<double>("section1", "any"); // 5.0
    const auto& v4 = r.GetVector<float>("section2", "any_vec"); // [1.0, 2.0, 3.0]
    const auto& v5 = r.GetVector<std::string>("section2", "any_vec"); // ["1", "2", "3"]
    // And also support writing to new ini file.
    r.InsertEntry("new_section", "key1", 5); // Create new entry
    inih::INIWriter::write("output.ini", r); // Dump ini to file
    return 0;
}
