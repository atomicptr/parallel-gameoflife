#include <utils.hpp>

using namespace std;

vector<string> utils::get_lines(string str) {
    ifstream file;

    file.open(str);

    auto lines = get_lines(file);

    file.close();

    return lines;
}

vector<string> utils::get_lines(ifstream &is) {
    vector<string> lines;
    string line;

    while (getline(is, line)) {
        lines.push_back(line);
    }

    return lines;
}

vector<string> utils::split(string str, char delimeter) {
    vector<string> strings;

    istringstream f(str);
    string s;

    while (getline(f, s, delimeter)) {
        strings.push_back(s);
    }

    return strings;
}

vector<int> utils::get_size(vector<string> lines) {
    vector<int> size;

    int width = -1;
    int height = lines.size();

    for_each(lines.begin(), lines.end(), [&](string &s) {
        auto result = split(s, ' ');

        if(width == -1) {
            width = result.size();
        }

        if(width != result.size()) {
            cerr << "ERR: Your input file format is invalid" << endl;
            exit(1);
        }
    });

    size.push_back(width);
    size.push_back(height);

    return size;
}
