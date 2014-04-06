#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

const string FST_FILE = "phoneme_to_letter.fst";
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
  vector<string> v_or_c{"V", "C"};
  vector<string> letters{"A", "I", "N", "O", "U", "a", "b", "c", "d", "e",
"f", "g", "h", "i", "j", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v",
"y", "z" };
//   vector<string> tag_list{"B", "D", "G", "J", "L", "T", "a", "b", "d", "e", "f",
//     "g", "i", "k", "l", "m", "n", "o", "p", "r", "rr", "s", "t", "tS", "u",
//     "h"};
  // Begin writing the FST.
  ofstream fout;
  fout.open(FST_FILE.c_str());
  string only_node = "0";
  fout << only_node << endl;
  WriteLine(fout, only_node, only_node, "_", "_");
  for (string cv : v_or_c) {
    for (string tag : letters) {
      WriteLine(fout, only_node, only_node, cv, tag);
    }
  }
  fout.close();
  cout << "Written to " << FST_FILE << endl;
  return 0;
}

