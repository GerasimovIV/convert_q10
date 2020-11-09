#pragma once

#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace Q10 {

#pragma pack(push, 1)
struct Header {
	char flags{};

	int32_t rows_number{};
	int32_t columns_number{};

	int32_t param_upk_1{};
    int32_t param_upk_2{};
    uint8_t param_upk_3{};
    uint16_t param_upk_4{};
    uint16_t param_upk_5{};
    double param_upk_6{};

    uint16_t year{};
    uint16_t month{};
    uint16_t day{};

    uint16_t hours{};
    uint16_t minutes{};
    double seconds{};
};
#pragma pack(pop)

using Element = int16_t;
using Row = std::vector<Element>;
using Matrix = std::vector<Row>;

inline Matrix Read(const std::string& filename) {
    std::ifstream file(filename, std::ios_base::binary);
    if (!file.is_open()) {
		std::cerr << ("can not open file " + filename) << std::endl;
		return {};
	}

    Header q10_header;
    file.read(reinterpret_cast<char*>(&q10_header), sizeof(Header));

    int n = q10_header.rows_number;
    int m = q10_header.columns_number;
    Matrix data(n, Row(m));
    for (Row& row : data) {
        for (Element& element : row) {
            file.read(reinterpret_cast<char*>(&element), sizeof(Element));
        }
    }

    return data;
}

inline void Write(const Matrix& data, const std::string& myfilename) {
    if (data.empty()) {
        std::cerr << "matrix is empty" << std::endl;
        return;
    }

    //std::ofstream file(filename, std::ios_base::binary);
    //if (!file.is_open()) {
		//std::cerr << ("can not open file " + filename) << std::endl;
		//return;
	//}

    Header q10_header;
    q10_header.rows_number = data.size();
    q10_header.columns_number = data[0].size();
    //file.write(reinterpret_cast<const char*>(&q10_header), sizeof(Header));
    
    
    std::ofstream out;          // поток для записи
    out.open(myfilename); // окрываем файл для записи
    if (!out.is_open())
    {
        std::cerr << ("can not open file " + myfilename) << std::endl;
	return;
    }
     
    //std::cout << "End of program" << std::endl;
    
    for (const Row& row : data) {
        for (Element element : row) {
            //std::cout<< element << std::endl;
            out << element << " ";
            //file.write(reinterpret_cast<const char*>(&element), sizeof(Element));
        }
        out << "\n";
    }
}

} // Q10
