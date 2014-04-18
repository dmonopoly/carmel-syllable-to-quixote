#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

const string FST_FILE = "diphthong_generator2.fst";
const string EMPTY = "*e*";

void WriteLine(ofstream &fout, const string &node1, const string &node2,
    const string &first, const string &second) {
  string input = first; // x in x:y
  string output = second; // y in x:y
  if (first != EMPTY) {
    stringstream ss;
    ss << "\"" << first << "\"";
    input = ss.str();
  }
  if (second != EMPTY) {
    stringstream ss;
    ss << "\"" << second << "\"";
    output = ss.str();
  }
  fout << "(" << node1 << " (" << node2 << " " << input << " " << output << "))"
    << endl;
}

void WriteLine(ofstream &fout, const string &node1, const string &node2,
    const string &first, const string &second, double prob, const string &end) {
  string input = first; // x in x:y
  string output = second; // y in x:y
  if (first != EMPTY) {
    stringstream ss;
    ss << "\"" << first << "\"";
    input = ss.str();
  }
  if (second != EMPTY) {
    stringstream ss;
    ss << "\"" << second << "\"";
    output = ss.str();
  }
  fout << "(" << node1 << " (" << node2 << " " << input << " " << output << " " 
    << prob << end << "))" << endl;
}

int main(int argc, char *argv[]) {
  if (argc != 1) {
    cerr << "Usage: ./<exec> " << endl;
    return 0;
  }
  // Begin writing the FST.
  ofstream fout;
  fout.open(FST_FILE.c_str());
  string start_node = "0";
  fout << start_node << endl;
  WriteLine(fout, start_node, start_node, "_", "_", 1, "!");
  WriteLine(fout, start_node, start_node, "S", "S", 1, "!");
  WriteLine(fout, start_node, start_node, "N", "N", 1, "!");
  WriteLine(fout, start_node, start_node, "V", "V", .5, "");
  WriteLine(fout, start_node, start_node, "V", "VV", .5, "");
  fout.close();
  cout << "Written to " << FST_FILE << endl;
  return 0;
}

