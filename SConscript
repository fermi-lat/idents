# -*- python -*-
# $Header: /nfs/slac/g/glast/ground/cvs/idents/SConscript,v 1.9 2012/08/16 23:56:37 jrb Exp $
# Authors: Joanne Bogart <jrb@slac.stanford.edu>
# Version: idents-02-21-00
import os
Import('baseEnv')
Import('listFiles')
Import('packages')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('addLinkDeps', package = 'idents', toBuild='static')
identsLib = libEnv.StaticLibrary('idents', listFiles(['src/*.cxx']))

progEnv.Tool('identsLib')
test_idents = progEnv.Program('test_idents',[ 'src/test/test_idents.cxx'])

progEnv.Tool('registerTargets', package = 'idents',
             staticLibraryCxts = [[identsLib, libEnv]],
             testAppCxts = [[test_idents, progEnv]],
             includes = listFiles(['idents/*.h']))

