#!/bin/sh
#PBS -l walltime=10:00:00
# Part of the final 3rd task that only uses ~3 machines: syllable generator ->
# syllable to phonemes (this file) -> phoneme to letter
cd $PBS_O_WORKDIR
# cipher_file='Ciphers/spanish.written_short.quoted.txt'
# cipher_file='Ciphers/spanish.written_one_third.txt'
cipher_file='Ciphers/spanish.written.quoted.txt'

clang++ SyllableGenerator.cc -o 1.out
./1.out
clang++ SyllableToPhonemesFST.cc -o 2.out
./2.out
clang++ PhonemeToLetterFST.cc CypherReader.cc -o 3.out
./3.out $cipher_file

carmel --train-cascade -HJ -X .99999 -! 100 -:  $cipher_file syllables.wfsa syll_to_phonemes.fst phoneme_to_letter.fst
# carmel --project-right --project-identity-fsa -HJ syllables.wfsa > syllables.wfsa.noe 
awk 'NF>0' $cipher_file > cipher.data.noe 
cat cipher.data.noe | carmel -qbsriWEIk 1  phoneme_to_letter.fst.trained
