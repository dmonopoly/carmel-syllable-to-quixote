#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

const string FST_FILE = "phoneme_class_to_phoneme.fst";
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
    cerr << "Usage: ./<exec>" << endl;
    return 0;
  }
  vector<string> phoneme_classes;
  phoneme_classes.push_back("S");
  phoneme_classes.push_back("N");
  phoneme_classes.push_back("V");

  // Get all Spanish phonemes, grouped into N, S, or V.
  vector<string> n_phonemes;
  vector<string> v_phonemes;
  vector<string> s_phonemes;
  n_phonemes.push_back("B");
  n_phonemes.push_back("D");
  n_phonemes.push_back("G");
  n_phonemes.push_back("T");
  n_phonemes.push_back("p");
  n_phonemes.push_back("tS");
  n_phonemes.push_back("t");
  n_phonemes.push_back("b");
  n_phonemes.push_back("d");
  n_phonemes.push_back("k");
  n_phonemes.push_back("x");

  v_phonemes.push_back("a");
  v_phonemes.push_back("e");
  v_phonemes.push_back("i");
  v_phonemes.push_back("o");
  v_phonemes.push_back("u");

  s_phonemes.push_back("J");
  s_phonemes.push_back("L");
  s_phonemes.push_back("f");
  s_phonemes.push_back("l");
  s_phonemes.push_back("m");
  s_phonemes.push_back("n");
  s_phonemes.push_back("r");
  s_phonemes.push_back("rr");
  s_phonemes.push_back("s");
  // Begin writing the FST.
  ofstream fout;
  fout.open(FST_FILE.c_str());
  string only_node = "0";
  fout << only_node << endl;
  WriteLine(fout, only_node, only_node, "_", "_");
  for (int i = 0; i < phoneme_classes.size(); ++i ) {
    string ph_class = phoneme_classes[i];
    if (ph_class == "S") {
      for (int j = 0; j < s_phonemes.size(); ++j) {
        string ph = s_phonemes[j];
        WriteLine(fout, only_node, only_node, ph_class, ph);
      }
    } else if (ph_class == "N") {
      for (int j = 0; j < n_phonemes.size(); ++j) {
        string ph = n_phonemes[j];
        WriteLine(fout, only_node, only_node, ph_class, ph);
      }
    } else if (ph_class == "V") {
      for (int j = 0; j < v_phonemes.size(); ++j) {
        string ph = v_phonemes[j];
        WriteLine(fout, only_node, only_node, ph_class, ph);
      }
    } else {
      cerr << "Unknown phoneme class." << endl;
      return 0;
    }
  }
  fout.close();
  cout << "Written to " << FST_FILE << endl;
  return 0;
}
