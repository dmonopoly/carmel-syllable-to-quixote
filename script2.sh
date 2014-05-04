# With onset maximizing and diphthongs
clang++ -stdlib=libc++ -std=c++11 SyllableGenerator.cc -o 1.out
./1.out
clang++ -stdlib=libc++ -std=c++11 SyllableToTypeFST.cc -o 2.out
./2.out
clang++ -stdlib=libc++ -std=c++11 OnsetMaximizingFilter.cc -o 2a.out
./2a.out
clang++ -stdlib=libc++ -std=c++11 TypeToPhonemeClassFST.cc -o 3.out
./3.out
clang++ -stdlib=libc++ -std=c++11 DiphthongGenerator.cc -o 3a.out
./3a.out
clang++ -stdlib=libc++ -std=c++11 PhonemeClassToLetterFST.cc -o 4.out
./4.out
# cipher_file='Ciphers/spanish.written_short.quoted.txt'
cipher_file='Ciphers/spanish.written_one_third.txt'
carmel --train-cascade -HJ -X .99999 -! 30 -: $cipher_file syllables.wfsa syll_to_type.fst onset_maximizing_filter.fst type_to_phoneme_class.fst diphthong_generator.fst phoneme_class_to_letter.fst
# carmel --project-right --project-identity-fsa -HJ syllables.wfsa > syllables.wfsa.noe 
awk 'NF>0' $cipher_file > cipher.data.noe 
# Take 2's trained machine and remove it's input. Why is this needed for the
# last machine on the left? Answer: This makes x:a to a:a, so you drop any x
# after this a. The output we want to see is the "a".
carmel --project-right --project-identity-fsa -HJ syll_to_type.fst.trained > syll_to_type.fst.noe 
cat cipher.data.noe | carmel -qbsriWEIk 1 syll_to_type.fst.noe onset_maximizing_filter.fst.trained type_to_phoneme.fst.trained diphthong_generator.fst.trained phoneme_to_letter.fst.trained
