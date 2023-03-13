#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;
int main()
{
    ifstream image;
    ofstream newimage;

    image.open("image.ppm");
    newimage.open("newimage.ppm");

    string type = "", width = "", height = "", RGB = "";
    image >> type;
    image >> width;
    image >> height;
    image >> RGB;

   /* if (width != "128" && height != "64") {
        std::cout << "error";
        return 0;
    }*/

    newimage << type << endl;
    newimage << width << " " << height << endl;
    newimage << RGB << endl;

    string red = "", green = "", blue = "";
    int r = 0, b = 0, g = 0;
    int itterator = 0;

    while (!image.eof()) {
        image >> red;
        image >> green;
        image >> blue;

        stringstream redstream(red);
        stringstream greenstream(green);
        stringstream bluestream(blue);

        redstream >> r;
        greenstream >> g;
        bluestream >> b;

        std::ostringstream rr;
        rr << "0x" << std::hex << r;
        std::string resultred = rr.str();
        std::ostringstream gg;
        gg << "0x" << std::hex << g;
        std::string resultgreen = gg.str();
        std::ostringstream bb;
        bb << "0x" << std::hex << b;
        std::string resultblue = bb.str();

        if (resultred == "0xff") {
            resultred = "0x00";
        }
        if (resultgreen == "0xff") {
            resultgreen = "0x00";
        }
        if (resultblue == "0xff") {
            resultblue = "0x00";
        }
        itterator++;
        newimage << resultred << "," /* << resultgreen << "," << resultblue*/;
        if (itterator == 128) {
            newimage << std::endl;
            itterator = 0;
        }
    }
    image.close();
    newimage.close();
    //cout << type << width << height << RGB<<endl;
    return 0;
}
