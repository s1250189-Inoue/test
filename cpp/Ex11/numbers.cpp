#include<iostream>
#include<iterator>
#include<fstream>

int main()
{
    const char *filename = "number.txt";
    std::ofstream ofs(filename);

    std::cout << "Input ctr -c or not int type will exit" << std::endl;
    std::istream_iterator<int> numberIn(std::cin);
    std::istream_iterator<int> numberEnd;
    std::ostream_iterator<int> out(ofs," ");

    for (numberIn; numberIn != numberEnd; numberIn++ ) {
        if(*numberIn % 5 == 0) out = *numberIn;
    }
    return 0;
}