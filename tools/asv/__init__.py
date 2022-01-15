# -*- coding: utf-8 -*-
#*********************************************************************
#  This file is part of gmpxxll.
#
#        Copyright (C) 2019-2021 Julian Rüth
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.
#*********************************************************************

import os
from os.path import join

from cppasv import create_wrappers

ASV_PROJECT_DIR = os.environ.get('ASV_PROJECT_DIR', None)

if not ASV_PROJECT_DIR:
    ASV_ENV_DIR = os.environ.get('ASV_ENV_DIR', None)
    if ASV_ENV_DIR:
        ASV_PROJECT_DIR = join(ASV_ENV_DIR, "project")
    else:
        ASV_PROJECT_DIR = join(os.path.dirname(os.path.abspath(__file__)), "..", "..")

locals().update(create_wrappers(join(ASV_PROJECT_DIR, "benchmark", "benchmark")))
