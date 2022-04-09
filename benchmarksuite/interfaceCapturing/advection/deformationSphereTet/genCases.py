import casefoam

case = [['isoAlpha', 'plicRDF','MULES'],
        ['x16','x32', 'x64' ]] #, 'x128']]


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
                'triBlock.geo': 
                { '#!stringManipulation': 
                    {
                        "nx=32;": f"nx={Nx};",
                        "nz=64;": f"nz={2*Nx};"
                    }
                }
            }

data = {'isoAlpha': updateScheme("isoAdvection","isoAlpha",1),
        'plicRDF': updateScheme("isoAdvection","plicRDF",1),
        'MULES': updateScheme("MULESScheme","isoSurface",1),
        'x16': changeGeoFile(16),
        'x32': changeGeoFile(32),
        'x64': changeGeoFile(64)}

casefoam.mkCases('deformationSphereTet', case, data, 'tree', writeDir='Cases')
