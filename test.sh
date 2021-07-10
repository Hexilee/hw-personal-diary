#!/bin/sh

if [[ ! -d $1 ]]; then
    echo "argument($1) is not a directory"
    exit 1
fi

if [[ ! -x "$1/pdadd" ]]; then
    echo "$1/pdadd is not a executable file"
    exit 1
fi

if [[ ! -x "$1/pdshow" ]]; then
    echo "$1/pdshow is not a executable file"
    exit 1
fi


if [[ ! -x "$1/pdlist" ]]; then
    echo "$1/pdlist is not a executable file"
    exit 1
fi


if [[ ! -x "$1/pdremove" ]]; then
    echo "$1/pdremove is not a executable file"
    exit 1
fi

# diary should be not found
expect="Diary Not Found"
result=$($1/pdshow "2021-7-10")
if [[ "$expect" != "$result" ]]; then
    echo "expect '$expect'; get '$result'"
    rm data.txt
    exit 1
fi

echo "2021-7-10 Hello World!" | $1/pdadd # add diary

expect="Hello World!"
result=$($1/pdshow "2021-7-10")
if [[ "$expect" != "$result" ]]; then
    echo "expect '$expect'; get '$result'"
    rm data.txt
    exit 1
fi

echo "2021-7-10 Hello World Again!" | $1/pdadd # override diary
expect="Hello World Again!"
result=$($1/pdshow "2021-7-10")
if [[ "$expect" != "$result" ]]; then
    echo "expect '$expect'; get '$result'"
    rm data.txt
    exit 1
fi

echo "2021-7-11 Hello World Again Again!" | $1/pdadd # add another diary
expect="Hello World Again Again!"
result=$($1/pdshow "2021-7-11")
if [[ "$expect" != "$result" ]]; then
    echo "expect '$expect'; get '$result'"
    rm data.txt
    exit 1
fi

# list without range
expect="2021-7-10 Hello World Again!
2021-7-11 Hello World Again Again!"
result=$($1/pdlist)                  
if [[ "$expect" != "$result" ]]; then
    echo "expect '$expect'; get '$result'"
    rm data.txt
    exit 1
fi

# list with start
expect="2021-7-11 Hello World Again Again!"
result=$($1/pdlist "2021-7-11")
if [[ "$expect" != "$result" ]]; then
    echo "expect '$expect'; get '$result'"
    rm data.txt
    exit 1
fi

# list with start
expect=""
result=$($1/pdlist "2021-7-12")
if [[ "$expect" != "$result" ]]; then
    echo "expect '$expect'; get '$result'"
    rm data.txt
    exit 1
fi

# list with start and end
expect="2021-7-10 Hello World Again!"
result=$($1/pdlist "2021-7-9" "2021-7-10")
if [[ "$expect" != "$result" ]]; then
    echo "expect '$expect'; get '$result'"
    rm data.txt
    exit 1
fi

# remove should success
expect="0"
$1/pdremove "2021-7-10"
result="$?"
if [[ "$expect" != "$result" ]]; then
    echo "expect '$expect'; get '$result'"
    rm data.txt
    exit 1
fi

# rdiary should be not found
expect="Diary Not Found"
result=$($1/pdshow "2021-7-10")
if [[ "$expect" != "$result" ]]; then
    echo "expect '$expect'; get '$result'"
    rm data.txt
    exit 1
fi

# remove should fail
expect="255"
$1/pdremove "2021-7-10"
result="$?"
if [[ "$expect" != "$result" ]]; then
    echo "expect '$expect'; get '$result'"
    rm data.txt
    exit 1
fi

rm data.txt