# include<iostream>
# include<fstream>
# include<cmath>

using namespace std;

#pragma pack(push, 1)
struct fileHeader {
    unsigned short fileType;
    unsigned int fileSize;
    unsigned short fileZero1;
    unsigned short fileZero2;
    unsigned int biasis;
};

struct messageHeader {
    unsigned int biSize;
    int biWidth;
    int biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned int biCompression;
    unsigned int biSizeImage;
    int biXPelsPerMeter;
    int biYPelsPerMeter;
    unsigned int biClrUsed;
    unsigned int biClrImportant;
};
#pragma pack(pop)

int main(int argc, char* argv[]) {
    if(argc != 3) {return 1;}

    ifstream in(argv[1], ios::binary|ios::in);

    fileHeader f;
    messageHeader m;

    in.read((char*) &f, sizeof(f));
    in.read((char*) &m, sizeof(m));

    int old_w = m.biWidth;
    int old_h = abs(m.biHeight);
    int old_rowbyte = ((old_w * 24 + 31) / 32) * 4;

    char* old_p = new char[old_rowbyte * old_h];
    in.seekg(f.biasis, ios::beg);
    in.read(old_p, old_h * old_rowbyte);
    in.close();

    ofstream out(argv[2], ios::binary|ios::out);
    
    int new_w = old_h;
    int new_h = old_w;
    int new_rowbyte = ((new_w * 24 + 31) / 32) * 4;
    m.biHeight = new_h;
    m.biWidth = new_w;
    m.biSizeImage = new_rowbyte * new_h;
    f.biasis = sizeof(f) + sizeof(m);
    f.fileSize = f.biasis + m.biSizeImage;
    out.write((char*) &f, sizeof(f));
    out.write((char*) &m, sizeof(m));

    char* new_p = new char[new_rowbyte * new_h]();

    for (int y = 0; y < old_h; y ++) {
        for (int x = 0; x < old_w; x++) {
            int old_index = y * old_rowbyte + 3 * x;

            int new_x = y;
            int new_y = old_w - 1 - x;
            
            int new_index = new_y * new_rowbyte + 3 * new_x;
            new_p[new_index] = old_p[old_index];
            new_p[new_index + 1] = old_p[old_index + 1];
            new_p[new_index + 2] = old_p[old_index + 2];
        }
    }
    out.write(new_p, new_rowbyte * new_h);
    delete [] old_p;delete [] new_p;
    out.close();
    return 0;
}