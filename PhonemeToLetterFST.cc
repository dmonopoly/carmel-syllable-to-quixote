#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "CypherReader.h"

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
  if (argc != 2) {
    cerr << "Usage: ./<exec> <cipher-file>" << endl;
    return 0;
  }
  string filename_for_cypher = argv[1];
  vector<string> observed_data;
  set<string> letters;
  bool got_obs_data = CypherReader::GetObservedData(filename_for_cypher,
                                                    &observed_data,
                                                    &letters);
  // Remove the _ that was read in!
  letters.erase("_");
  if (!got_obs_data) {
    cerr << "Error getting observed data." << endl;
    return 1;
  }
  // Get all Spanish phonemes.
  vector<string> phonemes;
  phonemes.push_back("B");
  phonemes.push_back("D");
  phonemes.push_back("G");
  phonemes.push_back("J");
  phonemes.push_back("L");
  phonemes.push_back("T");
  phonemes.push_back("a");
  phonemes.push_back("b");
  phonemes.push_back("d");
  phonemes.push_back("e");
  phonemes.push_back("f");
  phonemes.push_back("i");
  phonemes.push_back("k");
  phonemes.push_back("l");
  phonemes.push_back("m");
  phonemes.push_back("n");
  phonemes.push_back("o");
  phonemes.push_back("p");
  phonemes.push_back("r");
  phonemes.push_back("rr");
  phonemes.push_back("s");
  phonemes.push_back("t");
  phonemes.push_back("tS");
  phonemes.push_back("u");
  phonemes.push_back("x");
  // Begin writing the FST.
  ofstream fout;
  fout.open(FST_FILE.c_str());
  string only_node = "0";
  fout << only_node << endl;
  WriteLine(fout, only_node, only_node, "_", "_");
  for (int i = 0; i < phonemes.size(); ++i ) {
    string in = phonemes[i];
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

