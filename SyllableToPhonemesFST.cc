// Part of the final 3rd task that only uses 3 machines: syllable generator ->
// syllable to phonemes (this file) -> phoneme to letter
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

const string FST_FILE = "syll_to_phonemes.fst";
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

int main(int argc, char *argv[]) {
  if (argc != 1) {
    cerr << "Usage: ./<exec> " << endl;
    return 0;
  }
  // Get all Spanish phonemes.
  vector<string> phonemes;
  // Categories of consonant phonemes - A, B, C. See picture.
  vector<string> a_phons, b_phons, c_phons, d_phons, vowels;
  vowels.push_back("a");
  vowels.push_back("e");
  vowels.push_back("i");
  vowels.push_back("o");
  vowels.push_back("u");
  a_phons.push_back("J");
  a_phons.push_back("L");
  a_phons.push_back("T");
  a_phons.push_back("b");
  a_phons.push_back("d");
  a_phons.push_back("m");
  a_phons.push_back("n");
  a_phons.push_back("rr");
  a_phons.push_back("s");
  a_phons.push_back("tS");
  a_phons.push_back("x");
  b_phons.push_back("B");
  b_phons.push_back("G");
  b_phons.push_back("f");
  b_phons.push_back("k");
  b_phons.push_back("p");
  c_phons.push_back("t");
  c_phons.push_back("D");
  d_phons.push_back("r");
  d_phons.push_back("l");
  string start = "START";
//   string end = "END";
  string one = "1";
  string two = "2";
  string twoA = "2a";
  string three = "3";
  string four = "4";
  string five = "5";
  string syll = "S";
  // Begin writing the FST.
  ofstream fout;
  fout.open(FST_FILE.c_str());
  fout << start << endl;
  WriteLine(fout, start, one, syll, EMPTY);
  // Generate syllable onset.
  WriteLine(fout, one, two, EMPTY, EMPTY);
  // A phonemes
  for (int i = 0; i < a_phons.size(); ++i) {
    string phon = a_phons[i];
    WriteLine(fout, one, three, EMPTY, phon);
  }
  // B and D phonemes
  for (int i = 0; i < b_phons.size(); ++i) {
    string phon = b_phons[i];
    WriteLine(fout, one, two, EMPTY, phon);
  }
  for (int i = 0; i < d_phons.size(); ++i) {
    string phon = d_phons[i];
    WriteLine(fout, two, three, EMPTY, phon);
  }
  WriteLine(fout, two, three, EMPTY, EMPTY);
  // C phonemes
  for (int i = 0; i < c_phons.size(); ++i) {
    string phon = c_phons[i];
    WriteLine(fout, one, twoA, EMPTY, phon);
  }
  WriteLine(fout, twoA, three, EMPTY, "r");  // Manually write in.
  WriteLine(fout, twoA, three, EMPTY, EMPTY);

  // Generate nucleus.
  string threeA = "3a";
  string threeE = "3e";
  string threeI = "3i";
  string threeO = "3o";
  string threeU = "3u";
  for (int i = 0; i < vowels.size(); ++i) {
    string phon = vowels[i];
    stringstream ss;
    ss << three << phon;
    string midstate = ss.str();
    WriteLine(fout, three, midstate, EMPTY, phon);
    WriteLine(fout, midstate, four, EMPTY, EMPTY);
    if (midstate == "3a") {
      WriteLine(fout, midstate, four, EMPTY, "i");
    } else if (midstate == "3e") {
      WriteLine(fout, midstate, four, EMPTY, "i");
      WriteLine(fout, midstate, four, EMPTY, "u");
    } else if (midstate == "3i") {
      WriteLine(fout, midstate, four, EMPTY, "e");
      WriteLine(fout, midstate, four, EMPTY, "a");
      WriteLine(fout, midstate, four, EMPTY, "u");
    } else if (midstate == "3o") {
      WriteLine(fout, midstate, four, EMPTY, "i");
    } else if (midstate == "3u") {
      WriteLine(fout, midstate, four, EMPTY, "i");
      WriteLine(fout, midstate, four, EMPTY, "e");
      WriteLine(fout, midstate, four, EMPTY, "a");
      WriteLine(fout, midstate, four, EMPTY, "o");
    }
  }

  // Generate coda.
  WriteLine(fout, four, five, EMPTY, EMPTY);
  for (int i = 0; i < a_phons.size(); ++i) {
    string phon = a_phons[i];
    WriteLine(fout, four, five, EMPTY, phon);
  }
  for (int i = 0; i < b_phons.size(); ++i) {
    string phon = b_phons[i];
    WriteLine(fout, four, five, EMPTY, phon);
  }
  for (int i = 0; i < c_phons.size(); ++i) {
    string phon = c_phons[i];
    WriteLine(fout, four, five, EMPTY, phon);
  }
  for (int i = 0; i < d_phons.size(); ++i) {
    string phon = d_phons[i];
    WriteLine(fout, four, five, EMPTY, phon);
  }

  // Back to beginning.
  WriteLine(fout, five, start, EMPTY, EMPTY);
  // To end, which is start.
  WriteLine(fout, five, start, EMPTY, EMPTY);
  WriteLine(fout, one, start, EMPTY, EMPTY);
  WriteLine(fout, start, start, EMPTY, EMPTY);
  WriteLine(fout, start, start, SPACE, SPACE);

  fout.close();
  cout << "Written to " << FST_FILE << endl;
  return 0;
}
