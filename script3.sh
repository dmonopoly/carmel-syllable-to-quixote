# Like script2, except now we deal with N, S, and V - the end of the 06 paper!
clang++ -stdlib=libc++ -std=c++11 SyllableGenerator.cc -o 1.out
./1.out
clang++ -stdlib=libc++ -std=c++11 SyllableToTypeFST.cc -o 2.out
./2.out
clang++ -stdlib=libc++ -std=c++11 OnsetMaximizingFilter.cc -o 2a.out
./2a.out
clang++ -stdlib=libc++ -std=c++11 TypeToMorePhonemesFST.cc -o 3.out
./3.out
# clang++ -stdlib=libc++ -std=c++11 TypeToPhonemeFST.cc -o 3.out
# ./3.out

clang++ -stdlib=libc++ -std=c++11 PhonemeToLetterNSV_FST.cc -o 4.out
./4.out
# clang++ -stdlib=libc++ -std=c++11 PhonemeToLetterFST.cc -o 4.out
# ./4.out

# cipher_file='Ciphers/spanish.written_short.quoted.txt'
cipher_file='Ciphers/spanish.written_one_third.txt'
carmel --train-cascade -HJ -X .99999 -! 30 -: $cipher_file syllables.wfsa syll_to_type.fst onset_maximizing_filter.fst type_to_more_phonemes.fst phoneme_to_letter_nsv.fst
# carmel --project-right --project-identity-fsa -HJ syllables.wfsa > syllables.wfsa.noe 
awk 'NF>0' $cipher_file > cipher.data.noe 
# Take 2's trained machine and remove it's input. Why is this needed for the
# last machine on the left? Answer: This makes x:a to a:a, so you drop any x
# after this a. The output we want to see is the "a".

# carmel --project-right --project-identity-fsa -HJ syll_to_type.fst.trained > syll_to_type.fst.noe 
# cat cipher.data.noe | carmel -qbsriWEIk 1 syll_to_type.fst.noe type_to_more_phonemes.fst.trained phoneme_to_letter_nsv.fst.trained

carmel --project-right --project-identity-fsa -HJ type_to_more_phonemes.fst.trained > type_to_more_phonemes.fst.noe 
cat cipher.data.noe | carmel -qbsriWEIk 1 type_to_more_phonemes.fst.noe phoneme_to_letter_nsv.fst.trained
