#$Header: /nfs/slac/g/glast/ground/cvs/GlastRelease-scons/idents/identsLib.py,v 1.1 2008/07/09 21:13:47 glastrm Exp $
def generate(env, **kw):
    if not kw.get('depsOnly', 0):
        env.Tool('addLibrary', library = ['idents'])

        if env['PLATFORM'] == "win32" and env.get('CONTAINERNAME','') == 'GlastRelease':
            env.Tool('findPkgPath', package = 'idents') 
            env.Tool('findPkgPath', package = 'facilities') 

    if kw.get('incsOnly', 0) == 1: 
        env.Tool('findPkgPath', package = 'facilities')         
        return

    env.Tool('addLibrary', library = ['facilities'])

def exists(env):
    return 1;

