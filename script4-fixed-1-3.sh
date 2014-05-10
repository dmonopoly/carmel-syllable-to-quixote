#!/bin/sh
#PBS -l walltime=7:00:00
# cd $PBS_O_WORKDIR
# Fix machines 1-3a with output trained models from 1-4 results. Then only train 4 and 5.
cipher_file='Ciphers/spanish.written_short.quoted.txt'
# cipher_file='Ciphers/spanish.written_one_third.txt'
# cipher_file='Ciphers/spanish.written.quoted.txt'

clang++ PhonemeClassToPhonemeFST.cc -o 4p.out
./4p.out
clang++ PhonemeToLetterFST.cc CypherReader.cc -o 5p.out
./5p.out $cipher_file

# *.trained files should have ! probabilities everywhere.
carmel --train-cascade -HJ -X .99999 -! 10 -: $cipher_file syllables.wfsa.trained syll_to_type.fst.trained onset_maximizing_filter.fst.trained type_to_more_phoneme_classes.fst.trained diphthong_generator2.fst.trained phoneme_class_to_phoneme.fst phoneme_to_letter.fst
# carmel --project-right --project-identity-fsa -HJ syllables.wfsa > syllables.wfsa.noe 
awk 'NF>0' $cipher_file > cipher.data.noe 
# Remove last machine's input. Why is this needed for the
# last machine on the left? Answer: This makes x:a to a:a, so you drop any x
# after this a. The output we want to see is the "a".
# carmel --project-right --project-identity-fsa -HJ type_to_more_phonemes.fst.trained > type_to_more_phonemes.fst.noe 

# cat cipher.data.noe | carmel -qbsriWEIk 1 phoneme_to_letter.fst.trained

# cat cipher.data.noe | carmel -qbsriWEIk 1 onset_maximizing_filter.fst.trained type_to_more_phonemes.fst.trained diphthong_generator2.fst.trained phoneme_class_to_phoneme.fst.trained phoneme_to_letter.fst.trained
