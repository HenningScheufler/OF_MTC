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
        'x32': changeGeoFile(32),
        'x64': changeGeoFile(64),
        'x128': changeGeoFile(128),
        'x256': changeGeoFile(256),
        'x512': changeGeoFile(512)}

casefoam.mkCases('vortexShearedDiscTet', case, data, 'tree', writeDir='Cases')
