#include <fstream>
#include <iostream>

using namespace std;

static void test_ofstream1() {
    ofstream out("out.txt");
    if (out.is_open()) {
        out << "1234.\n";
        out.close();
    }

    ofstream out_app("out_app.txt", ios::app);
    if (out_app.is_open()) {
        out_app << "5678.\n";
        out_app.close();
    }
}

static void test_ofstream2() {
    ofstream out;
    out.open("out.txt", ios::trunc);
    if (out.is_open()) {
        out << "1234.\n";
        out.close();
    }

    ofstream out_app;
    out_app.open("out_app.txt", ios::app);
    if (out_app.is_open()) {
        out_app << "5678\n";
        out_app.close();
    }
}

static void test_ifstream() {
    char buffer[256];
    ifstream in("out.txt");
    if (!in.is_open()) {
        cout << "Error opening file";
        exit(1);
    }
    while (!in.eof()) {
        in.getline(buffer,100);
        cout << buffer << endl;
    }

    ifstream in_app;
    // in_app.open("out_app.txt", ios::ate);
    in_app.open("out_app.txt");
    if (!in_app.is_open()) {
        cout << "Error opening file";
        exit(1);
    }
    while (!in_app.eof()) {
        in_app.getline(buffer,100);
        cout << buffer << endl;
    }
}

static void file_size() {
    const char * filename = "out_app.txt";
    long start, end;
    ifstream in(filename, ios::in | ios::binary);
    start = in.tellg();
    in.seekg(0, ios::end);
    end = in.tellg();
    in.close();
    cout << "start = " << start << ", end = " << end << endl;
    cout << "size of " << filename;
    cout << " is " << (end - start) << " bytes.\n";
}

static void ifstream_read_ofstream_write() {
    const char * filename = "out_app.txt";
    long size;

    ifstream in(filename, ios::in | ios::binary | ios::ate);
    size = in.tellg();
    in.seekg (0, ios::beg);
    char *buffer = new char [size];
    in.read (buffer, size);
    in.close();
    cout << buffer << endl;

    ofstream out(filename, ios::out | ios::binary | ios::app);
    out.write(buffer, size);

    delete [] buffer;
}

static void write_read_binary_file() {
    string binary_file = "array.bin";
    float array[4] = { 1.0, 2.0, 3.0, 4.0 };
    ofstream out;
    out.open(binary_file, ofstream::binary);
    out.write(reinterpret_cast<const char*>(array), 4 * sizeof(float));
    out.close();

    float array_read[4];
    ifstream in;
    in.open(binary_file, ifstream::binary);
    in.read(reinterpret_cast<char*>(array_read), 4 * sizeof(float));
    in.close();

    for (float i : array_read) {
        cout << i << "\t";
    }
    cout << endl;
}

int main() {
    // test_ofstream2();
    test_ifstream();
    file_size();
    // ifstream_read_ofstream_write();
    write_read_binary_file();

    return 0;
}
