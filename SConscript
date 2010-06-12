# -*- python -*-
# $Header: /nfs/slac/g/glast/ground/cvs/idents/SConscript,v 1.7 2010/06/11 00:46:02 jrb Exp $
# Authors: Joanne Bogart <jrb@slac.stanford.edu>
# Version: idents-02-20-03
import os
Import('baseEnv')
Import('listFiles')
Import('packages')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

identsLib = libEnv.StaticLibrary('idents', listFiles(['src/*.cxx']))

progEnv.Tool('identsLib')
test_idents = progEnv.Program('test_idents',[ 'src/test/test_idents.cxx'])

progEnv.Tool('registerTargets', package = 'idents',
             staticLibraryCxts = [[identsLib, libEnv]],
             testAppCxts = [[test_idents, progEnv]],
             includes = listFiles(['idents/*.h']))

