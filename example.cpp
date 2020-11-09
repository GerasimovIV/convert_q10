#include "q10.h"

int main(int argc, char* argv[]) {
	//std::cout << argv[1] << std::endl;
    //Q10::Matrix matrix = Q10::Read("input.q10");

    Q10::Matrix matrix = Q10::Read(argv[1]);

    Q10::Write(matrix, argv[2]);

    return 0;
}
