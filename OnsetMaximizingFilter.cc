#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#define MAX_NUM_SYLLABLES 10

using namespace std;

const string FST_FILE = "onset_maximizing_filter.fst";
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
  vector<string> syl_types{"V", "CV", "CVC", "VC", "CCV", "CCVC", "CVCC", "VCC", "CCVCC"};
  // Begin writing out the WFSA.
  ofstream fout;
  fout.open(FST_FILE.c_str());
  fout << "END" << endl;
  double prob_to_end = .001;
  double lambda = .9;
  // Allow spaces to start string sometimes.
  WriteLine(fout, "PRE-START", "START", EMPTY, SPACE, 1, "!");
//   WriteLine(fout, "PRE-START", "START", EMPTY, EMPTY, .5, "!");
  string cv = "CV"; // This means the syllable starts with C and ends in V.
  string cc = "CC"; // Etc.
  string vc = "VC"; // Etc.
  string vv = "VV"; // Etc.
  // Draw One of main 4 nodes->END.
  WriteLine(fout, vv, "END", EMPTY, EMPTY, prob_to_end, "");
  WriteLine(fout, cv, "END", EMPTY, EMPTY, prob_to_end, "");
  WriteLine(fout, vc, "END", EMPTY, EMPTY, prob_to_end, "");
  WriteLine(fout, cc, "END", EMPTY, EMPTY, prob_to_end, "");
  // Allow spaces to end string sometimes.
  WriteLine(fout, vv, "END", EMPTY, SPACE, prob_to_end, "");
  WriteLine(fout, cv, "END", EMPTY, SPACE, prob_to_end, "");
  WriteLine(fout, vc, "END", EMPTY, SPACE, prob_to_end, "");
  WriteLine(fout, cc, "END", EMPTY, SPACE, prob_to_end, "");

  // Draw END back to START
  WriteLine(fout, "END", "START", "_", "_", 1, "!");
  // Draw START->One of main 4 nodes.
  for (string type : syl_types) {
    if (type == "V") {
      WriteLine(fout, "START", vv, type, type, 1, "!");
    } else if (type == "CV") {
      WriteLine(fout, "START", cv, type, type, 1, "!");
    } else if (type == "CVC") {
      WriteLine(fout, "START", cc, type, type, 1, "!");
    } else if (type == "VC") {
      WriteLine(fout, "START", vc, type, type, 1, "!");
    } else if (type == "CCV") {
      WriteLine(fout, "START", cv, type, type, 1, "!");
    } else if (type == "CCVC") {
      WriteLine(fout, "START", cc, type, type, 1, "!");
    } else if (type == "CVCC") {
      WriteLine(fout, "START", cc, type, type, 1, "!");
    } else if (type == "VCC") {
      WriteLine(fout, "START", vc, type, type, 1, "!");
    } else if (type == "CCVCC") {
      WriteLine(fout, "START", cc, type, type, 1, "!");
    }
  }
  // Draw transitions that disallow vowel-initial syllables following
  // consonant-final syllables. So, all except cc vc, cc vv, vc vv, vc vc.
  for (string type : syl_types) {
    if (type == "V") {
      WriteLine(fout, cv, vv, type, type, 1, "!");
      WriteLine(fout, vv, vv, type, type, 1, "!");
    } else if (type == "CV" || type == "CCV") {
      WriteLine(fout, cc, cv, type, type, 1, "!");
      WriteLine(fout, cv, cv, type, type, 1, "!");
      WriteLine(fout, vc, cv, type, type, 1, "!");
      WriteLine(fout, vv, cv, type, type, 1, "!");
    } else if (type == "CVC" || type == "CCVC" || type == "CVCC" || type == "CCVCC") {
      WriteLine(fout, cc, cc, type, type, 1, "!");
      WriteLine(fout, cv, cc, type, type, 1, "!");
      WriteLine(fout, vc, cc, type, type, 1, "!");
      WriteLine(fout, vv, cc, type, type, 1, "!");
    } else if (type == "VC" || type == "VCC") {
      WriteLine(fout, cv, vc, type, type, 1, "!");
      WriteLine(fout, vv, vc, type, type, 1, "!");
    } else if (type == "CCV") {
      // above
      cerr << "shouldn't be reached" << endl;
      return 0;
    } else if (type == "CCVC") {
      // above
      cerr << "shouldn't be reached" << endl;
      return 0;
    } else if (type == "CVCC") {
      // above
      cerr << "shouldn't be reached" << endl;
      return 0;
    } else if (type == "VCC") {
      // above
      cerr << "shouldn't be reached" << endl;
      return 0;
    } else if (type == "CCVCC") {
      // above
      cerr << "shouldn't be reached" << endl;
      return 0;
    }
  }

  fout.close();
  cout << "Written to " << FST_FILE << endl;
  return 0;
}

