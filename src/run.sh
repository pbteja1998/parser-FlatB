#!/bin/sh
if [ $# -ne 1 ]
then
echo "This script needs one argument which is the input file"
echo "Usage ./run.sh input_file"
exit 0
fi
echo "Compiling..."
make veryclean
make # Compile the code
./bcc $1
echo "Done"