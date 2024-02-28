#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from setuptools import setup, find_packages, Extension
from wheel.bdist_wheel import bdist_wheel

class bdist_wheel_abi3(bdist_wheel):
    def get_tag(self):
        python, abi, plat = super().get_tag()

        if python.startswith("cp"):
            # on CPython, our wheels are abi3 and compatible back to 3.6
            return "cp36", "abi3", plat

        return python, abi, plat

ext = Extension(
    name                = 'ruapu',
    sources             = ['ruapu-binding.c'],
    py_limited_api      = True
)

setup_args = dict(
    name            = 'ruapu',
    packages        = find_packages(where="."),
    package_dir     = {"": "."},
    ext_modules     = [ext],
    cmdclass        = {"bdist_wheel": bdist_wheel_abi3},
)

setup(**setup_args)
