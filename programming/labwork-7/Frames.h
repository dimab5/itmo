#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>


static std::vector<std::string> All_Frames = {"COMM", "COMR", "ENCR", "EQU2", "ETCO", "GRID", "LINK",
                                              "OWNE", "PRIV", "PCNT", "POPM", "POSS", "RBUF", "RVA2", "SEEK",
                                              "SYLT", "TALB", "TBPM", "TCMP", "TCOM", "TCON", "TCOP", "TDEN", "TDLY", "TDOR",
                                              "TDRC", "TDRL", "TDTG", "TENC", "TEXT", "TIPL", "TIT1", "TIT2", "TIT3", "TKEY",
                                              "TLAN", "TLEN", "TMCL", "TMOO", "TOAL", "TOFN", "TOLY", "TOPE", "TOWN", "TPE1",
                                              "TPE2", "TPE3", "TPE4", "TPOS", "TPRO", "TPUB", "TRCK", "TRSN", "TRSO", "TSOA", "TSOP",
                                              "TSOT", "TSRC", "TSSE", "TSST", "TXXX", "UFID", "USER", "USLT", "WCOM", "WCOP", "WOAF",
                                              "WOAR", "WOAS", "WORS", "WPAY", "WPUB", "WXXX"};


class MP3_Parser {
public:
    MP3_Parser(const std::string& file_name) {
        _file_name = file_name;
    }

    void Parsing_Frames(const std::string& file_name);
    void Parse_File();
    std::vector<std::string> Get(const std::string& Frame);
    void Print_All_Frames();
    void Print_List_Frames();

    std::map<std::string, std::vector<std::string>> Frames_Data;

private:
    std::string _file_name;

};


class Frame {
public:
    virtual std::vector<std::string> Parse(std::string Name_Of_Frame, MP3_Parser* Obj) = 0;
    void Fill_Methods(MP3_Parser* Obj);

    std::vector<std::string> List_Frames;

    virtual ~Frame() = default;

};

class Unique_file_identifier : public Frame {
public:
    std::vector<std::string> Parse(std::string name_of_frame, MP3_Parser* Obj) override;

};

class Text_information_frames : public Frame {
public:
    std::vector<std::string> Parse(std::string name_of_frame, MP3_Parser* Obj) override;

};

class URL_link_frames : public Frame {
public:
    std::vector<std::string> Parse(std::string name_of_frame, MP3_Parser* Obj) override;

};

class Event_timing_codes : public Frame {
public:
    std::vector<std::string> Parse(std::string name_of_frame, MP3_Parser* Obj) override;

};

class Unsynchronised_lyrics : public Frame {
public:
    std::vector<std::string> Parse(std::string name_of_frame, MP3_Parser* Obj) override;

};

class Synchronised_lyrics : public Frame {
public:
    std::vector<std::string> Parse(std::string name_of_frame, MP3_Parser* Obj) override;

};

class Comments : public Frame {
public:
    std::vector<std::string> Parse(std::string name_of_frame, MP3_Parser* Obj) override;

};

class Relative_volume_adjustment : public Frame {
public:
    std::vector<std::string> Parse(std::string name_of_frame, MP3_Parser *Obj) override;

};
class Equalisation : public Frame {
public:
    std::vector<std::string> Parse(std::string name_of_frame, MP3_Parser* Obj) override;

};

//class Attached_picture : public Frame {
//public:
//    std::vector<std::string> Parse(std::string name_of_frame, MP3_Parser* Obj) override;
//
//};

class Play_counter : public Frame {
public:
    std::vector<std::string> Parse(std::string name_of_frame, MP3_Parser* Obj) override;

};

class Popularimeter : public Frame {
public:
    std::vector<std::string> Parse(std::string name_of_frame, MP3_Parser* Obj) override;

};

class Recommended_buffer_size : public Frame {
public:
    std::vector<std::string> Parse(std::string name_of_frame, MP3_Parser* Obj) override;

};

class Linked_information : public Frame {
public:
    std::vector<std::string> Parse(std::string name_of_frame, MP3_Parser* Obj) override;

};

class Position_synchronisation_frame : public Frame {
public:
    std::vector<std::string> Parse(std::string name_of_frame, MP3_Parser* Obj) override;

};

class Terms_of_use : public Frame {
public:
    std::vector<std::string> Parse(std::string name_of_frame, MP3_Parser* Obj) override;

};

class Ownership_frame : public Frame {
public:
    std::vector<std::string> Parse(std::string name_of_frame, MP3_Parser* Obj) override;

};

class Commercial_frame : public Frame {
public:
    std::vector<std::string> Parse(std::string name_of_frame, MP3_Parser* Obj) override;

};

class Encryption_method_registration : public Frame {
public:
    std::vector<std::string> Parse(std::string name_of_frame, MP3_Parser* Obj) override;

};

class Group_identification_registration : public Frame {
public:
    std::vector<std::string> Parse(std::string name_of_frame, MP3_Parser* Obj) override;

};

class Private_frame : public Frame {
public:
    std::vector<std::string> Parse(std::string name_of_frame, MP3_Parser* Obj) override;

};

class Seek_frame : public Frame {
public:
    std::vector<std::string> Parse(std::string name_of_frame, MP3_Parser* Obj) override;

};


std::ostream& operator <<(std::ostream& output, std::vector<std::string> vec);

std::vector<Frame*> Creat_All_Classes();

static std::map<MP3_Parser*, std::map<std::string, Frame*>> Parse_Methods;