#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>

using namespace std;

const string FST_FILE = "cipher.fst";
const string EMPTY = "*e*";

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
  string only_node = "0";
  double unif_prob = (double) 1 / syl_types.size();
  fout << only_node << endl;
  WriteLine(fout, only_node, only_node, "_", "_", unif_prob, "!");
  for (string type : syl_types) {
    WriteLine(fout, only_node, only_node, "S", type, unif_prob, "!");
  }
  fout.close();
  cout << "Written to " << FST_FILE << endl;
  return 0;
}
