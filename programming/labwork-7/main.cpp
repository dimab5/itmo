#include "Frames.h"

/*
void Extra_Task() {
    std::vector<std::string> File_Names {"test.mp3", "tag.mp3", "Hair-Trigger-WST011601.mp3", "Here Comes A Big Black Cloud!! - Black Mold.mp3"};
    std::ofstream CSV_File("CSV_Table.csv");

    CSV_File << "File / Frame;";
    for (const std::string& str : All_Frames) {
        CSV_File << str << ";";
    }

    CSV_File << "\n";

    for (const std::string& file : File_Names) {
        MP3_Parser* Parser = new MP3_Parser;

        Parser->Parse_File(file);

        CSV_File << file << ";";

        for (const std::string& frame : All_Frames) {
            if (Parser->Get(frame).empty()) CSV_File << ";";
            else CSV_File << Parser->Get(frame)[0] << ";";
        }

        CSV_File << "\n";
    }
}
*/

int main(int argc, char *argv[]) {

    MP3_Parser* p = new MP3_Parser("tag.mp3");
    p->Parse_File();
    p->Print_All_Frames();

    delete p;
    return 0;

}