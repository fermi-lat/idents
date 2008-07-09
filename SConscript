# -*- python -*-
# $Header$
# Authors: Joanne Bogart <jrb@slac.stanford.edu>
# Version: idents-02-19-01
import os
Import('baseEnv')
Import('listFiles')
Import('packages')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('identsLib', depsOnly = 1)
identsLib = libEnv.StaticLibrary('idents', listFiles(['src/*.cxx']))

progEnv.Tool('identsLib')
test_idents = progEnv.Program('test_idents', 'src/test/test_idents.cxx')

progEnv.Tool('registerObjects', package = 'idents', libraries = [identsLib], testApps = [test_idents], includes = listFiles(['idents/*.h']))
