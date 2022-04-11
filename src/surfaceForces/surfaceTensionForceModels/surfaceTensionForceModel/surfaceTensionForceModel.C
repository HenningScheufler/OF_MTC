/*---------------------------------------------------------------------------*\
            Copyright (c) 2017-2019, German Aerospace Center (DLR)
-------------------------------------------------------------------------------
License
    This file is part of the VoFLibrary source code library, which is an
	unofficial extension to OpenFOAM.
    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.
    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "surfaceTensionForceModel.H"
#include "stringOps.H"
#include "wordIOList.H"
// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(surfaceTensionForceModel, 0);
    defineRunTimeSelectionTable(surfaceTensionForceModel, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

 
Foam::surfaceTensionForceModel::surfaceTensionForceModel
(
    const word& type,
    const dictionary& dict,
    const volScalarField& alpha1,
    const surfaceScalarField& phi,
    const volVectorField& U
)
:
    alpha1_(alpha1),
    phi_(phi),
    U_(U),
    surfTenModel_(nullptr),
    deltaFunctionModel_(nullptr),
    nHatf_
    (
        IOobject
        (
            "nHatf_",
            alpha1_.time().timeName(),
            alpha1_.mesh()
        ),
        alpha1_.mesh(),
        dimensionedScalar("nHatf", dimArea, 0.0)
    ),
    K_
    (
        IOobject
        (
            "K_",
            alpha1_.time().timeName(),
            alpha1_.mesh(),
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        alpha1_.mesh(),
        dimensionedScalar("K", dimless/dimLength, 0.0),
        "zeroGradient"
    ),
    Kf_
    (
        IOobject
        (
            "Kf_",
            alpha1_.time().timeName(),
            alpha1_.mesh()
        ),
        alpha1_.mesh(),
        dimensionedScalar("Kf", dimless/dimLength, 0.0)
    )

{

    surfTenModel_ = surfaceTensionModel::New(dict,alpha1.mesh());
    word deltaFunctionType =
        dict.lookupOrDefault<word>("deltaFunctionModel","alphaCSF");
    deltaFunctionModel_ = deltaFunctionModel::New(deltaFunctionType,dict,alpha1);
}


Foam::Ostream& Foam::surfaceTensionForceModel::printSurfaceForceModels
(
    Ostream& os,
    const wordList& cmptNames,
    const wordList& surfaceForceNames
)
{
    const int nCmpt = cmptNames.size();

    // Build a table of constituent parts by split name into constituent parts
    // - remove incompatible entries from the list
    // - note: row-0 contains the names of constituent parts (ie, the header)

    DynamicList<wordList> outputTbl;
    outputTbl.resize(surfaceForceNames.size()+1);

    label rowi = 0;

    // Header
    outputTbl[rowi] = cmptNames;
    if (!outputTbl[rowi].empty())
    {
        ++rowi;
    }

    for (const word& name : surfaceForceNames)
    {
        const auto splitted = stringOps::split<string>(name, '_');
        DynamicList<std::string> splittedString;
        for (std::string s: splitted)
        {
            splittedString.append(s);
        }
        wordList splittedNames(3,"any");
        splittedNames[2] = splittedString.last();
        if (splittedString.size() == 2)
        {
            splittedNames[0] = splittedString[0];
        }
        else if (splittedString.size() == 3)
        {
            splittedNames[0] = splittedString[0];
            splittedNames[1] = splittedString[1];
        }
        
        outputTbl[rowi] = splittedNames;
        if (!outputTbl[rowi].empty())
        {
            ++rowi;
        }
    }

    if (rowi > 1)
    {
        outputTbl.resize(rowi);
        Foam::printTable(outputTbl, os);
    }

    return os;
}



// ************************************************************************* //
