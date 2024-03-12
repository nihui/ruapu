#!/bin/bash

set -e

cp -f ../ruapu.h ./c_src/
rebar3 hex publish
rm -f ./c_src/ruapu.h
