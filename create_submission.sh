#!/bin/bash

clear

rm -rf submission
mkdir submission
mkdir submission/libft
mkdir submission/src
mkdir submission/include
mkdir submission/build

chmod +777 submission
chmod +777 submission/libft
chmod +777 submission/src

find ./libft/src -name \*.c -exec cp {} submission/libft \;
find ./libft/include -name \*.h -exec cp {} submission/libft \;

cp ./libft/Makefile_submit.submit ./submission/libft/Makefile
cp ./libft/Makefile_src ./submission/libft/Makefile_src

cp ./Makefile ./submission/Makefile
cp ./main.c ./submission/main.c


source_dir="./src/"

# Use find to locate all .c files in the source directory and its subdirectories
find "$source_dir" -type f -name "*.c" -exec bash -c '
    # Get the relative path of the source file
    source_file="$1"
    source_dir=$(dirname "$source_file")
    destination_dir="./submission/"

    mkdir "${destination_dir}${source_dir}"

    # Copy the source file to the destination directory
    cp "$source_file" "${destination_dir}${source_file}"
' bash {} \;

find ./include -name \*.h -exec cp {} submission/include/ \;



pwd
