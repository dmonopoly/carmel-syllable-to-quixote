#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

const string FST_FILE = "type_to_phoneme_class.fst";
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
  vector<string> syl_types{"V", "CV", "CVC", "VC", "CCV", "CCVC", "CVCC", "VCC", "CCVCC"};
  // Begin writing the FST.
  ofstream fout;
  fout.open(FST_FILE.c_str());
  string start_node = "0";
  fout << start_node << endl;
  WriteLine(fout, start_node, start_node, "_", "_", 1, "!");
  WriteLine(fout, start_node, start_node, "V", "V", 1, "!");
  int i = 1;
  for (string type : syl_types) {
    if (type == "CV") {
      string one;
      stringstream ss; ss << i;
      ss >> one;
      WriteLine(fout, start_node, one, type, "C", 1, "!");
      WriteLine(fout, one, start_node, EMPTY, "V", 1, "!");
      ++i;
    } else if (type == "CVC") {
      string one, two;
      stringstream ss; ss << i; 
      ss >> one;
      ++i; ss.clear(); ss.str(""); ss << i;
      ss >> two;
      WriteLine(fout, start_node, one, type, "C", 1, "!");
      WriteLine(fout, one, two, EMPTY, "V", 1, "!");
      WriteLine(fout, two, start_node, EMPTY, "C", 1, "!");
      ++i;
    } else if (type == "VC") {
      string one;
      stringstream ss; ss << i;
      ss >> one;
      WriteLine(fout, start_node, one, type, "V", 1, "!");
      WriteLine(fout, one, start_node, EMPTY, "C", 1, "!");
      ++i;
    } else if (type == "CCV") {
      string one, two;
      stringstream ss; ss << i; 
      ss >> one;
      ++i; ss.clear(); ss.str(""); ss << i;
      ss >> two;
      WriteLine(fout, start_node, one, type, "C", 1, "!");
      WriteLine(fout, one, two, EMPTY, "C", 1, "!");
      WriteLine(fout, two, start_node, EMPTY, "V", 1, "!");
      ++i;
    } else if (type == "CCVC") {
      string one, two, three;
      stringstream ss; ss << i; 
      ss >> one;
      ++i; ss.clear(); ss.str(""); ss << i;
      ss >> two;
      ++i; ss.clear(); ss.str(""); ss << i;
      ss >> three;
      WriteLine(fout, start_node, one, type, "C", 1, "!");
      WriteLine(fout, one, two, EMPTY, "C", 1, "!");
      WriteLine(fout, two, three, EMPTY, "V", 1, "!");
      WriteLine(fout, three, start_node, EMPTY, "C", 1, "!");
      ++i;
    } else if (type == "CVCC") {
      string one, two, three;
      stringstream ss; ss << i; 
      ss >> one;
      ++i; ss.clear(); ss.str(""); ss << i;
      ss >> two;
      ++i; ss.clear(); ss.str(""); ss << i;
      ss >> three;
      WriteLine(fout, start_node, one, type, "C", 1, "!");
      WriteLine(fout, one, two, EMPTY, "V", 1, "!");
      WriteLine(fout, two, three, EMPTY, "C", 1, "!");
      WriteLine(fout, three, start_node, EMPTY, "C", 1, "!");
      ++i;
    } else if (type == "VCC") {
      string one, two;
      stringstream ss; ss << i; 
      ss >> one;
      ++i; ss.clear(); ss.str(""); ss << i;
      ss >> two;
      WriteLine(fout, start_node, one, type, "V", 1, "!");
      WriteLine(fout, one, two, EMPTY, "C", 1, "!");
      WriteLine(fout, two, start_node, EMPTY, "C", 1, "!");
      ++i;
    } else if (type == "CCVCC") {
      string one, two, three, four;
      stringstream ss; ss << i; 
      ss >> one;
      ++i; ss.clear(); ss.str(""); ss << i;
      ss >> two;
      ++i; ss.clear(); ss.str(""); ss << i;
      ss >> three;
      ++i; ss.clear(); ss.str(""); ss << i;
      ss >> four;
      WriteLine(fout, start_node, one, type, "C", 1, "!");
      WriteLine(fout, one, two, EMPTY, "C", 1, "!");
      WriteLine(fout, two, three, EMPTY, "V", 1, "!");
      WriteLine(fout, three, four, EMPTY, "C", 1, "!");
      WriteLine(fout, four, start_node, EMPTY, "C", 1, "!");
      ++i;
    }
  }
  fout.close();
  cout << "Written to " << FST_FILE << endl;
  return 0;
}

