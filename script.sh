# Without onset maximizing and diphthongs
clang++ -stdlib=libc++ -std=c++11 SyllableGenerator.cc -o 1.out
./1.out
clang++ -stdlib=libc++ -std=c++11 SyllableToTypeFST.cc -o 2.out
./2.out
clang++ -stdlib=libc++ -std=c++11 TypeToPhonemeClassFST.cc -o 3.out
./3.out
clang++ -stdlib=libc++ -std=c++11 PhonemeClassToLetterFST.cc -o 4.out
./4.out
# cipher_file='Ciphers/spanish.written_short.quoted.txt'
cipher_file='Ciphers/spanish.written_one_third.txt'
carmel --train-cascade -HJ -X .99999 -! 30 -: $cipher_file syllables.wfsa syll_to_type.fst type_to_phoneme_class.fst phoneme_class_to_letter.fst
# carmel --project-right --project-identity-fsa -HJ syllables.wfsa > syllables.wfsa.noe 
awk 'NF>0' $cipher_file > cipher.data.noe 
carmel --project-right --project-identity-fsa -HJ syll_to_type.fst.trained > syll_to_type.fst.noe 
cat cipher.data.noe | carmel -qbsriWEIk 1 syll_to_type.fst.noe type_to_phoneme.fst.trained phoneme_to_letter.fst.trained
