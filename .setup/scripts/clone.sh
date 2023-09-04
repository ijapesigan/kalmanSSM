#!/bin/bash

git clone git@github.com:ijapesigan/kalmanSSM.git
rm -rf "$PWD.git"
mv kalmanSSM/.git "$PWD"
rm -rf kalmanSSM
