#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from setuptools import setup, find_packages, Extension

ext = Extension(
    name                = 'ruapu',
    sources             = ['ruapu-py.c'],
    py_limited_api      = True
)

setup_args = dict(
    packages        = find_packages(where="."),
    package_dir     = {"": "."},
    ext_modules     = [ext],
)

setup(**setup_args)
