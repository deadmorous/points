#!/bin/bash

cd "$( dirname "${BASH_SOURCE[0]}" )"

git submodule init
git submodule sync
git submodule update

