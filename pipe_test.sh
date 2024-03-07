#!/bin/bash

# This script will receive a SIGPIPE signal
# because "echo" is writing to a closed pipe.

# Run this script in a pipeline like: ./script.sh | head

echo "Hello, this is a message from the script."