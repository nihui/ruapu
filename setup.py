#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import time
from setuptools import setup, find_packages, Extension

ext = Extension(
    name                = 'ruapu',
    sources             = ['ruapu-py.c'],
    py_limited_api      = True
)

setup_args = dict(
    name            = 'ruapu',
    version         = time.strftime("%Y%m%d", time.localtime())
    packages        = find_packages(where="."),
    package_dir     = {"": "."},
    ext_modules     = [ext],
)

setup(**setup_args)
