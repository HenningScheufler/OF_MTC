import casefoam

case = [['isoAlpha', 'plicRDF','MULES'],
        ['CFL005', 'CFL01', 'CFL02', 'CFL05'],
        ['x010', 'x020', 'x040', 'x080', 'x160', 'x320']]


def updateScheme(advect,recon,sub_steps):
        return {
                'system/simulationParameter': {
                    "ADVECTSCHEME": advect,
                    "RECONSCHEME": recon,
                    "SUBCYL": str(sub_steps)
                }
            }

def updateCFL(CFL):
        return {
                'system/simulationParameter': {
                    "MAXCFL": str(CFL)
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
        'CFL005': updateCFL(0.05),
        'CFL01': updateCFL(0.1),
        'CFL02': updateCFL(0.2),
        'CFL05': updateCFL(0.5),
        'x010': changeBlockMesh(10),
        'x020': changeBlockMesh(20),
        'x040': changeBlockMesh(40),
        'x080': changeBlockMesh(80),
        'x160': changeBlockMesh(160),
        'x320': changeBlockMesh(320),
        'x640': changeBlockMesh(640)}

casefoam.mkCases('discUniFlow', case, data, 'tree', writeDir='Cases')
