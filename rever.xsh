######################################################################
#  This file is part of gmpxxll.
#
#        Copyright (C) 2020-2025 Julian Rüth
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
#####################################################################

# Check that we are on the master branch
branch=$(git branch --show-current)
if branch.strip() != "master":
  raise Exception("You must be on the master branch to release.")
# and that it is up to date with origin/master
git fetch https://github.com/flatsurf/gmpxxll.git
git reset FETCH_HEAD
git diff --exit-code
git diff --cached --exit-code

import sys

sys.path.insert(0, 'tools/rever')

import autodist

$PROJECT = 'gmpxxll'

$ACTIVITIES = [
    'version_bump',
    'changelog',
    'autodist',
    'tag',
    'push_tag',
    'ghrelease',
]

$VERSION_BUMP_PATTERNS = [
    ('configure.ac', r'AC_INIT', r'AC_INIT([gmpxxll], [$VERSION], [julian.rueth@fsfe.org])'),
]

$CHANGELOG_FILENAME = 'ChangeLog'
$CHANGELOG_TEMPLATE = 'TEMPLATE.rst'
$CHANGELOG_NEWS = 'doc/news'
$CHANGELOG_CATEGORIES = ('Added', 'Changed', 'Deprecated', 'Removed', 'Fixed', 'Performance')
$PUSH_TAG_REMOTE = 'git@github.com:flatsurf/gmpxxll.git'

$GITHUB_ORG = 'flatsurf'
$GITHUB_REPO = 'gmpxxll'

$GHRELEASE_ASSETS = ['gmpxxll-' + $VERSION + '.tar.gz']
