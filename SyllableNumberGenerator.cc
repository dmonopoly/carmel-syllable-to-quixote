#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>

#define MAX_NUM_SYLLABLES 10

using namespace std;

const string WFSA_FILE = "cipher.wfsa";
const string EMPTY = "*e*";
const string SPACE = "_";

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
  // Begin writing out the WFSA.
  ofstream fout;
  fout.open(WFSA_FILE.c_str());
  fout << "END" << endl;
  double unif_prob = (double) 1 / MAX_NUM_SYLLABLES;
  double prob_to_end = .0001;
  double lambda = .9;
  // Draw transitions to each mid node.
  for (int i = 0; i < MAX_NUM_SYLLABLES; ++i) {
    string mid_node = "N" + to_string(i);
    WriteLine(fout, "START", mid_node, EMPTY, "S", unif_prob, "!");
  }
  // Draw from last mid node to END node.
  string last_mid_node = "N" + to_string(MAX_NUM_SYLLABLES - 1);
  WriteLine(fout, last_mid_node, "END", EMPTY, EMPTY, 1 - lambda, "!");
  // Draw from last mid node to START node.
  WriteLine(fout, last_mid_node, "START", EMPTY, SPACE, lambda, "!");
  // Draw transitions between mid nodes.
  for (int i = 0; i < MAX_NUM_SYLLABLES - 1; ++i) {
    string mid_node = "N" + to_string(i);
    string next_node = "N" + to_string(i + 1);
    WriteLine(fout, mid_node, next_node, EMPTY, "S", 1, "!");
  }
  fout.close();
  cout << "Written to " << WFSA_FILE << endl;
  return 0;
}
