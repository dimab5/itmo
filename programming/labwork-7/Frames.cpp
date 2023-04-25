#include "Frames.h"


void MP3_Parser::Parse_File() {
    std::vector<Frame*> v;
    v = Creat_All_Classes();

    for (const auto& it : v) {
        it->Fill_Methods(this);
    }

    this->Parsing_Frames(this->_file_name);
}

void Frame::Fill_Methods(MP3_Parser* Obj) {
    for (const std::string& str : this->List_Frames)
        Parse_Methods[Obj][str] = this;
}

std::vector<std::string> MP3_Parser::Get(const std::string& Frame) {
    return Parse_Methods[this][Frame]->Parse(Frame, this);
}

std::vector<std::string> Unique_file_identifier::Parse(std::string name_of_frame, MP3_Parser* Obj) {
    return Obj->Frames_Data[name_of_frame];
}

std::vector<std::string> Text_information_frames::Parse(std::string name_of_frame, MP3_Parser* Obj) {
    std::vector<std::string> new_vec;
    std::map<unsigned char, std::string> encoding { {0x00, "ASCII"}, {0x01, "UCS-2"}, {0x02, "UTF-16BE"}, {0x03, "UTF-8"} };
    for (std::string& str : Obj->Frames_Data[name_of_frame]) {
        new_vec.push_back("encoding: " + encoding[str[0]] + "   ");
        if (name_of_frame == "TPRO") new_vec.back() += "text: (P) " + str.substr(8, str.length());
        else new_vec.back() += "text: " + str.substr(1, str.length());
    }

    return new_vec;
}

std::vector<std::string> URL_link_frames::Parse(std::string name_of_frame, MP3_Parser* Obj) {
    return Obj->Frames_Data[name_of_frame];
}

std::vector<std::string> Event_timing_codes::Parse(std::string name_of_frame, MP3_Parser* Obj) {
    return Obj->Frames_Data[name_of_frame];
}

std::vector<std::string> Unsynchronised_lyrics::Parse(std::string name_of_frame, MP3_Parser* Obj) {
    std::vector<std::string> new_vec;
    std::map<unsigned char, std::string> encoding { {0x00, "ASCII"}, {0x01, "UCS-2"}, {0x02, "UTF-16BE"}, {0x03, "UTF-8"} };
    for (std::string& str : Obj->Frames_Data[name_of_frame]) {
        new_vec.push_back("encoding: " + encoding[str[0]] + "   ");
        new_vec.back() += "language: " + str.substr(1, 3) + "   ";
        new_vec.back() += "text: " + str.substr(4, str.length());
    }

    return new_vec;
}

std::vector<std::string> Synchronised_lyrics::Parse(std::string name_of_frame, MP3_Parser* Obj) {
    std::vector<std::string> new_vec;
    for (std::string& str : Obj->Frames_Data[name_of_frame]) {
        new_vec.push_back("language: " + str.substr(1, 3) + "   ");
        new_vec.back() += "text: " + str.substr(6, str.length());
    }

    return new_vec;
}

std::vector<std::string> Comments::Parse(std::string name_of_frame, MP3_Parser* Obj) {
    std::vector<std::string> new_vec;
    std::map<unsigned char, std::string> encoding { {0x00, "ASCII"}, {0x01, "UCS-2"}, {0x02, "UTF-16BE"}, {0x03, "UTF-8"} };
    for (std::string& str : Obj->Frames_Data[name_of_frame]) {
        new_vec.push_back("encoding: " + encoding[str[0]] + "   ");
        new_vec.back() += "language: " + str.substr(1, 3) + "   ";
        new_vec.back() += "text: " + str.substr(4, str.length());
    }

    return new_vec;
}

std::vector<std::string> Relative_volume_adjustment::Parse(std::string name_of_frame, MP3_Parser* Obj) {
    return Obj->Frames_Data[name_of_frame];
}

std::vector<std::string> Equalisation::Parse(std::string name_of_frame, MP3_Parser* Obj) {
    return Obj->Frames_Data[name_of_frame];
}

//std::vector<std::string> Attached_picture::Parse(std::string name_of_frame, MP3_Parser* Obj) {
//    return Obj->Frames_Data[name_of_frame];
//}

std::vector<std::string> Play_counter::Parse(std::string name_of_frame, MP3_Parser* Obj) {
    return Obj->Frames_Data[name_of_frame];
}

std::vector<std::string> Popularimeter::Parse(std::string name_of_frame, MP3_Parser* Obj) {

    return Obj->Frames_Data[name_of_frame];
}

std::vector<std::string> Recommended_buffer_size::Parse(std::string name_of_frame, MP3_Parser* Obj) {
    return Obj->Frames_Data[name_of_frame];
}

std::vector<std::string> Linked_information::Parse(std::string name_of_frame, MP3_Parser* Obj) {
    return Obj->Frames_Data[name_of_frame];
}

std::vector<std::string> Position_synchronisation_frame::Parse(std::string name_of_frame, MP3_Parser* Obj) {
    return Obj->Frames_Data[name_of_frame];
}

std::vector<std::string> Terms_of_use::Parse(std::string name_of_frame, MP3_Parser* Obj) {
    return Obj->Frames_Data[name_of_frame];
}

std::vector<std::string> Ownership_frame::Parse(std::string name_of_frame, MP3_Parser* Obj) {
    return Obj->Frames_Data[name_of_frame];
}

std::vector<std::string> Commercial_frame::Parse(std::string name_of_frame, MP3_Parser* Obj) {
    return Obj->Frames_Data[name_of_frame];
}

std::vector<std::string> Encryption_method_registration::Parse(std::string name_of_frame, MP3_Parser* Obj) {
    return Obj->Frames_Data[name_of_frame];
}

std::vector<std::string> Group_identification_registration::Parse(std::string name_of_frame, MP3_Parser* Obj) {
    return Obj->Frames_Data[name_of_frame];
}

std::vector<std::string> Private_frame::Parse(std::string name_of_frame, MP3_Parser* Obj) {
    return Obj->Frames_Data[name_of_frame];
}

std::vector<std::string> Seek_frame::Parse(std::string name_of_frame, MP3_Parser* Obj) {
    return Obj->Frames_Data[name_of_frame];
}


void MP3_Parser::Parsing_Frames(const std::string& file_name) {
    std::ifstream file;
    file.open(file_name, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "File is not open!!" << '\n';
        exit(1);
    }

    char buff[10];
    file.read(buff, sizeof(buff));
    char *sz= buff + 6;
    unsigned size = ((sz[0] << 21) | (sz[1] << 14) | (sz[2] << 7) | sz[3]) + 10;

//    std::cout << size << "\n";

    file.seekg(10, std::ios::beg);

    while (file.tellg() < size) {
        char buff_name[4];
        file.read(buff_name, 4);
        std::string name = "";
        for (int i = 0; i < 4; i++)
            name += buff_name[i];

        unsigned char c[4];
        for (int i = 0; i < 4; i++)
            file.get(reinterpret_cast<char &>(c[i]));

        unsigned cnt = ((c[0] << 21) | (c[1] << 14) | (c[2] << 7) | c[3]);

        file.seekg(2, std::ios::cur);

        if (!std::count(All_Frames.begin(), All_Frames.end(), name)) {
            file.seekg(cnt, std::ios::cur);
            continue;
        }

        unsigned char *buff_data = new unsigned char[cnt];
        file.read(reinterpret_cast<char *>(buff_data), cnt);
        std::string data = "";

        for (int i = 0; i < cnt; i++)
            data += buff_data[i];

        delete[] buff_data;

        Frames_Data[name].push_back(data);
    }

    file.close();
}


void MP3_Parser::Print_All_Frames() {
    for (const std::string& frame : All_Frames)
        for (const std::string& str : this->Get(frame))
            std::cout << frame << " : " << str << '\n';
}


void MP3_Parser::Print_List_Frames() {
    for (const std::string& frame : All_Frames)
        std::cout << frame << '\n';
}


std::vector<Frame*> Creat_All_Classes() {
    std::vector<Frame*> All_Classes;
    All_Classes.push_back(new Unique_file_identifier);
    All_Classes.back()->List_Frames = {"UFID"};
    All_Classes.push_back(new Text_information_frames);
    All_Classes.back()->List_Frames= {"TALB", "TBPM", "TCMP", "TCOM", "TCON", "TCOP", "TDEN", "TDLY", "TDOR",
                                        "TDRC", "TDRL", "TDTG", "TENC", "TEXT", "TIPL", "TIT1", "TIT2",
                                        "TIT3", "TKEY", "TLAN", "TLEN", "TMCL", "TMOO", "TOAL", "TOFN",
                                        "TOLY", "TOPE", "TOWN", "TPE1", "TPE2", "TPE3", "TPE4", "TPOS", "TPRO",
                                        "TPUB", "TRCK", "TRSN", "TRSO", "TSOA", "TSOP", "TSOT", "TSRC", "TSSE",
                                        "TSST", "TXXX"};
    All_Classes.push_back(new URL_link_frames);
    All_Classes.back()->List_Frames = {"WCOM", "WCOP", "WOAF", "WOAR", "WOAS", "WORS", "WPAY", "WPUB", "WXXX"};
    All_Classes.push_back(new Event_timing_codes);
    All_Classes.back()->List_Frames = {"ETCO"};
    All_Classes.push_back(new Unsynchronised_lyrics);
    All_Classes.back()->List_Frames = {"USLT"};
    All_Classes.push_back(new Synchronised_lyrics);
    All_Classes.back()->List_Frames = {"SYLT"};
    All_Classes.push_back(new Comments);
    All_Classes.back()->List_Frames = {"COMM"};
    All_Classes.push_back(new Relative_volume_adjustment);
    All_Classes.back()->List_Frames = {"RVA2"};
    All_Classes.push_back(new Equalisation);
    All_Classes.back()->List_Frames = {"EQU2"};
//    All_Classes.push_back(new Attached_picture);
//    All_Classes.back()->List_Frames = {"APIC"};
    All_Classes.push_back(new Play_counter);
    All_Classes.back()->List_Frames = {"PCNT"};
    All_Classes.push_back(new Popularimeter);
    All_Classes.back()->List_Frames = {"POPM"};
    All_Classes.push_back(new Recommended_buffer_size);
    All_Classes.back()->List_Frames = {"RBUF"};
    All_Classes.push_back(new Linked_information);
    All_Classes.back()->List_Frames = {"LINK"};
    All_Classes.push_back(new Position_synchronisation_frame);
    All_Classes.back()->List_Frames = {"POSS"};
    All_Classes.push_back(new Terms_of_use);
    All_Classes.back()->List_Frames = {"USER"};
    All_Classes.push_back(new Ownership_frame);
    All_Classes.back()->List_Frames = {"OWNE"};
    All_Classes.push_back(new Commercial_frame);
    All_Classes.back()->List_Frames = {"COMR"};
    All_Classes.push_back(new Encryption_method_registration);
    All_Classes.back()->List_Frames = {"ENCR"};
    All_Classes.push_back(new Group_identification_registration);
    All_Classes.back()->List_Frames = {"GRID"};
    All_Classes.push_back(new Private_frame);
    All_Classes.back()->List_Frames = {"PRIV"};
    All_Classes.push_back(new Seek_frame);
    All_Classes.back()->List_Frames = {"SEEK"};

    return All_Classes;
}


std::ostream& operator <<(std::ostream& output, std::vector<std::string> vec) {
    for (const std::string& str : vec)
        output << str << '\n';

    return output;
}