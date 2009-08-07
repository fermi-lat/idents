# -*- python -*-
# $Header: /nfs/slac/g/glast/ground/cvs/GlastRelease-scons/idents/SConscript,v 1.4 2009/01/23 00:07:47 ecephas Exp $
# Authors: Joanne Bogart <jrb@slac.stanford.edu>
# Version: idents-02-20-01
import os
Import('baseEnv')
Import('listFiles')
Import('packages')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('identsLib', depsOnly = 1)
identsLib = libEnv.StaticLibrary('idents', listFiles(['src/*.cxx']))

progEnv.Tool('identsLib')
test_idents = progEnv.Program('test_idents',[ 'src/test/test_idents.cxx'])

progEnv.Tool('registerTargets', package = 'idents',
             staticLibraryCxts = [[identsLib, libEnv]],
             testAppCxts = [[test_idents, progEnv]],
             includes = listFiles(['idents/*.h']))




