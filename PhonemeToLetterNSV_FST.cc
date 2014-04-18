#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "CypherReader.h"

using namespace std;

const string FST_FILE = "phoneme_to_letter_nsv.fst";
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
  if (argc != 2) {
    cerr << "Usage: ./<exec> <cipher file>" << endl;
    return 0;
  }
  vector<string> inputs;
  inputs.push_back("S");
  inputs.push_back("N");
  inputs.push_back("V");
  string filename_for_cypher = argv[1];
  vector<string> observed_data;
  set<string> letters;
  bool got_obs_data = CypherReader::GetObservedData(filename_for_cypher,
                                                    &observed_data,
                                                    &letters);
  if (!got_obs_data) {
    cerr << "Error getting observed data." << endl;
    return 1;
  }
  // Begin writing the FST.
  ofstream fout;
  fout.open(FST_FILE.c_str());
  string only_node = "0";
  fout << only_node << endl;
  // Remove the _ that was read in!
  letters.erase("_");
  WriteLine(fout, only_node, only_node, "_", "_");
  for (int i = 0; i < inputs.size(); ++i ) {
    string in = inputs[i];
    set<string>::iterator it;
    for (it = letters.begin(); it != letters.end(); ++it) {
      string letter = *it;
      WriteLine(fout, only_node, only_node, in, letter);
    }
  }
  fout.close();
  cout << "Written to " << FST_FILE << endl;
  return 0;
}

