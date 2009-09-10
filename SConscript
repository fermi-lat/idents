# -*- python -*-
# $Header: /nfs/slac/g/glast/ground/cvs/GlastRelease-scons/idents/SConscript,v 1.5 2009/08/07 00:00:24 jrb Exp $
# Authors: Joanne Bogart <jrb@slac.stanford.edu>
# Version: idents-02-20-02
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




