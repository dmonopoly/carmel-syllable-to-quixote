clang++ -stdlib=libc++ -std=c++11 SyllableGenerator.cc -o 1.out
./1.out
clang++ -stdlib=libc++ -std=c++11 SyllableToTypeFST.cc -o 2.out
./2.out
clang++ -stdlib=libc++ -std=c++11 OnsetMaximizingFilter.cc -o 2a.out
./2a.out
clang++ -stdlib=libc++ -std=c++11 TypeToPhonemeFST.cc -o 3.out
./3.out
clang++ -stdlib=libc++ -std=c++11 DiphthongGenerator.cc -o 3a.out
./3a.out
clang++ -stdlib=libc++ -std=c++11 PhonemeToLetterFST.cc -o 4.out
./4.out
# cipher_file='Ciphers/spanish.written_short.quoted.txt'
cipher_file='Ciphers/spanish.written_one_third.txt'
carmel --train-cascade -HJ -X .99999 -! 5 $cipher_file syllables.wfsa syll_to_type.fst onset_maximizing_filter.fsa type_to_phoneme.fst diphthong_generator.fst phoneme_to_letter.fst

# carmel --project-right --project-identity-fsa -HJ syllables.wfsa > syllables.wfsa.noe 
awk 'NF>0' $cipher_file > cipher.data.noe 
# Take 2's trained machine and remove it's input. TODO: ask why needed for last
# machine on left... 
carmel --project-right --project-identity-fsa -HJ syll_to_type.fst.trained > syll_to_type.fst.noe 

# TODO: this works, but do I left out the onset maximizing filter here... it's
# only above. should I add it here? should I make it .noe?
cat cipher.data.noe | carmel -qbsriWEIk 1 syll_to_type.fst.noe type_to_phoneme.fst.trained diphthong_generator.fst.trained phoneme_to_letter.fst.trained
