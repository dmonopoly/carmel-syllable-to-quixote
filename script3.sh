#!/bin/sh
#PBS -l walltime=1:00:00
cd $PBS_O_WORKDIR
# Like script2, except now we deal with N, S, and V - the end of the 06 paper!
# cipher_file='Ciphers/spanish.written_short.quoted.txt'
# cipher_file='Ciphers/spanish.written_one_third.txt'
cipher_file='Ciphers/spanish.written.quoted.txt'

clang++ SyllableGenerator.cc -o 1.out
./1.out
clang++ SyllableToTypeFST.cc -o 2.out
./2.out
clang++ OnsetMaximizingFilter.cc -o 2a.out
./2a.out
clang++ TypeToMorePhonemesFST.cc -o 3.out
./3.out
clang++ DiphthongGenerator2.cc -o 3a.out
./3a.out
clang++ PhonemeToLetterNSV_FST.cc CypherReader.cc -o 4.out
./4.out $cipher_file

carmel --train-cascade -HJ -X .99999 -! 20 -: $cipher_file syllables.wfsa syll_to_type.fst onset_maximizing_filter.fst type_to_more_phonemes.fst diphthong_generator2.fst phoneme_to_letter_nsv.fst
# carmel --project-right --project-identity-fsa -HJ syllables.wfsa > syllables.wfsa.noe 
awk 'NF>0' $cipher_file > cipher.data.noe 
# Remove last machine's input. Why is this needed for the
# last machine on the left? Answer: This makes x:a to a:a, so you drop any x
# after this a. The output we want to see is the "a".
carmel --project-right --project-identity-fsa -HJ type_to_more_phonemes.fst.trained > type_to_more_phonemes.fst.noe 
cat cipher.data.noe | carmel -qbsriWEIk 1 type_to_more_phonemes.fst.noe diphthong_generator2.fst.trained phoneme_to_letter_nsv.fst.trained
