#include "lib/parser.h"

using namespace omfl;

int main(int, char**) {

    OMFL_Parser Parser;

    std::string Parse_Int = R"(
        [section-int]
        key1 = 22
        key2 = -11
        key3 = 0)";

    std::string Parse_Float = R"(
        [section-float]
        key1 = 12.2
        key2 = -23.2)";

    std::string Parse_Bool = R"(
        [section-bool]
        key1 = true
        key2 = false)";

    std::string Parse_String = R"(
        [sectoin-string]
        key1 = \"string1\"
        key2 = \"string2\")";

    std::string Parse_Array = R"(
        [section-array]
        key1 = [1, 2, 3, 4]
        key2 = ["str1", "str2", "str3"])";

    std::ofstream xml("C:\\prog\\labwork6\\Xml.xml");
//    std::ifstream omfl("C:\\prog\\labwork6\\OMFL.txt");
//    std::string s;
//    std::string tmp = R"(
//        )";
//    getline(omfl, s);
//    tmp = tmp + s + "\n";
//    while (!omfl.eof()) {
//        getline(omfl, s);
//        if (!Parser.is_section(s)) tmp += '\t', tmp = tmp + s + "\n";
//        else {
////            std::cout << tmp;
//            Parser = parse(tmp);
//            xml << Parser.Section << "\n";
//            for (const auto &map: Parser.values) {
//                xml << map.first.substr(map.first.rfind('.') + 1, map.first.length()) << "=" << map.second << "\n";
//                std::cout << map.second;
//            }
//            xml << "\n";
//            tmp = R"(
//        )";
//            tmp = "\n" + tmp + s + "\n";
//        }
//    }

    Parser = parse(Parse_Int);
    xml << '<' << Parser.Section << '>' <<  "\n";
    for (const auto &map : Parser.values)
        xml << '\t' << '<' + map.first.substr(map.first.rfind('.') + 1, map.first.length()) + '>' << map.second << "</" + map.first.substr(map.first.rfind('.') + 1, map.first.length()) + '>' <<  "\n";
    xml << "</" << Parser.Section << ">" << "\n";

    Parser = parse(Parse_Float);
    xml << '<' << Parser.Section << '>' <<  "\n";
    for (const auto &map : Parser.values)
        xml << '\t' << '<' + map.first.substr(map.first.rfind('.') + 1, map.first.length()) + '>' << map.second << "</" + map.first.substr(map.first.rfind('.') + 1, map.first.length()) + '>' <<  "\n";
    xml << "</" << Parser.Section << ">" << "\n";

    Parser = parse(Parse_Bool);
    xml << '<' << Parser.Section << '>' <<  "\n";
    for (const auto &map : Parser.values)
        xml << '\t' << '<' + map.first.substr(map.first.rfind('.') + 1, map.first.length()) + '>' << map.second << "</" + map.first.substr(map.first.rfind('.') + 1, map.first.length()) + '>' <<  "\n";
    xml << "</" << Parser.Section << ">" << "\n";

    Parser = parse(Parse_String);
    xml << '<' << Parser.Section << '>' <<  "\n";
    for (const auto &map : Parser.values)
        xml << '\t' << '<' + map.first.substr(map.first.rfind('.') + 1, map.first.length()) + '>' << map.second << "</" + map.first.substr(map.first.rfind('.') + 1, map.first.length()) + '>' <<  "\n";
    xml << "</" << Parser.Section << ">" << "\n";

    Parser = parse(Parse_Array);
    xml << '<' << Parser.Section << '>' <<  "\n";
    for (const auto &map : Parser.values)
        xml<< '\t' << '<' + map.first.substr(map.first.rfind('.') + 1, map.first.length()) + '>' << map.second << "</" + map.first.substr(map.first.rfind('.') + 1, map.first.length()) + '>' <<  "\n";
    xml << "</" << Parser.Section << ">" << "\n";

    return 0;

}