import casefoam

case = [['isoAlpha', 'plicRDF','MULES'],
        ['CFL005', 'CFL01', 'CFL02', 'CFL05'],
        ['x010', 'x020', 'x040', 'x080', 'x160']]


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

def changeGeoFile(Nx):
    return {
                'triSquare.geo': 
                { '#!stringManipulation': 
                    {
                        "nx=10;": f"nx={Nx};"
                    }
                }
            }

data = {'isoAlpha': updateScheme("isoAdvection","isoAlpha",1),
        'plicRDF': updateScheme("isoAdvection","plicRDF",1),
        'MULES': updateScheme("MULESScheme","isoSurface",1),
        'CFL005': updateCFL(0.05),
        'CFL01': updateCFL(0.1),
        'CFL02': updateCFL(0.2),
        'CFL05': updateCFL(0.5),
        'x010': changeGeoFile(10),
        'x020': changeGeoFile(20),
        'x040': changeGeoFile(40),
        'x080': changeGeoFile(80),
        'x160': changeGeoFile(160)}

casefoam.mkCases('discUniFlowTet', case, data, 'tree', writeDir='Cases')
