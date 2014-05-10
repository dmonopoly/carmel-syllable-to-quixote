#!/bin/sh
#PBS -l walltime=7:00:00
cd $PBS_O_WORKDIR
# After 1-3a, add 4p (4 prime): phoneme class to phoneme, and 5p: phoneme to letter
# cipher_file='Ciphers/spanish.written_short.quoted.txt'
# cipher_file='Ciphers/spanish.written_one_third.txt'
cipher_file='Ciphers/spanish.written.quoted.txt'

clang++ SyllableGenerator.cc -o 1.out
./1.out
clang++ SyllableToTypeFST.cc -o 2.out
./2.out
clang++ OnsetMaximizingFilter.cc -o 2a.out
./2a.out
clang++ TypeToMorePhonemeClassesFST.cc -o 3.out
./3.out
clang++ DiphthongGenerator2.cc -o 3a.out
./3a.out
clang++ PhonemeClassToPhonemeFST.cc -o 4p.out
./4p.out
clang++ PhonemeToLetterFST.cc CypherReader.cc -o 5p.out
./5p.out $cipher_file

carmel --train-cascade -HJ -X .99999 -! 100 -: $cipher_file syllables.wfsa syll_to_type.fst onset_maximizing_filter.fst type_to_more_phoneme_classes.fst diphthong_generator2.fst phoneme_class_to_phoneme.fst phoneme_to_letter.fst
# carmel --project-right --project-identity-fsa -HJ syllables.wfsa > syllables.wfsa.noe 
awk 'NF>0' $cipher_file > cipher.data.noe 
# Remove last machine's input. Why is this needed for the
# last machine on the left? Answer: This makes x:a to a:a, so you drop any x
# after this a. The output we want to see is the "a".
# carmel --project-right --project-identity-fsa -HJ type_to_more_phonemes.fst.trained > type_to_more_phonemes.fst.noe 
cat cipher.data.noe | carmel -qbsriWEIk 1 phoneme_to_letter.fst.trained
# cat cipher.data.noe | carmel -qbsriWEIk 1 onset_maximizing_filter.fst.trained type_to_more_phonemes.fst.trained diphthong_generator2.fst.trained phoneme_class_to_phoneme.fst.trained phoneme_to_letter.fst.trained
