import casefoam

case = [['isoAlpha', 'plicRDF','MULES'],
        ['x32', 'x64', 'x128', 'x256', 'x512']]


def updateScheme(advect,recon,sub_steps):
        return {
                'system/simulationParameter': {
                    "ADVECTSCHEME": advect,
                    "RECONSCHEME": recon,
                    "SUBCYL": str(sub_steps)
                }
            }


def changeBlockMesh(Nx):
    return {
                'system/simulationParameter': {
                    "nx": str(Nx),
                    "ny": "1",
                    "nz": str(Nx)
                }
            }

data = {'isoAlpha': updateScheme("isoAdvection","isoAlpha",1),
        'plicRDF': updateScheme("isoAdvection","plicRDF",1),
        'MULES': updateScheme("MULESScheme","isoSurface",1),
        'x32': changeBlockMesh(32),
        'x64': changeBlockMesh(64),
        'x128': changeBlockMesh(128),
        'x256': changeBlockMesh(256),
        'x512': changeBlockMesh(512)}

casefoam.mkCases('vortexShearedDisc', case, data, 'tree', writeDir='Cases')
