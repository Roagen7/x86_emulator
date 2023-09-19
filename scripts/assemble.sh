#!/bin/sh

# assembles asm code from test/data/asm directory

TEST_ASM_DIR=test/data/asm
TEST_BIN_DIR=test/data/compiled

mkdir $TEST_BIN_DIR

for f in $TEST_ASM_DIR/*.asm; do
    filename=$(basename -- "$f")
    filename="${filename%.*}"
    echo "assembling... ".$f &&
    as --32 -msyntax=intel -mnaked-reg $f -o a.out &&
    objcopy -I elf32-little -j .text -O binary a.out $TEST_BIN_DIR/$filename
done

rm a.out