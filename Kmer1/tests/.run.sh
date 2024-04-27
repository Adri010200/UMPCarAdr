touch tests//.timeout
CMD=" /home/adri/Escritorio/MP/UMPCarAdr/Kmer1/dist/Debug/MinGW-Windows/kmer1  < data/zeroPairs.k1in 1> tests//.out7 2>&1"
eval $CMD
rm tests//.timeout
