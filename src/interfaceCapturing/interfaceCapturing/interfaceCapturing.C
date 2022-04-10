/*---------------------------------------------------------------------------*\
    Modified work | Copyright (c) 2017-2019, German Aerospace Center (DLR)
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

#include "interfaceCapturing.H"


// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(interfaceCapturing, 0);
    defineRunTimeSelectionTable(interfaceCapturing, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::interfaceCapturing::interfaceCapturing
(
    volScalarField& alpha1,
    const surfaceScalarField& phi,
    const volVectorField& U
)
:
  IOdictionary
  (
      IOobject
      (
          interfaceCapturing::typeName,
          alpha1.time().constant(),
          alpha1.db(),
          IOobject::NO_READ,
          IOobject::NO_WRITE
      )
  ),
  interfaceCapturingCoeffs_(alpha1.mesh().solverDict(alpha1.name())),

  alpha1_(alpha1),
  phi_(phi),
  U_(U),
  alphaPhi_
  (
      IOobject
      (
          "alphaPhi_",
          alpha1_.mesh().time().timeName(),
          alpha1_.mesh(),
          IOobject::NO_READ,
          IOobject::NO_WRITE
      ),
      alpha1_.mesh(),
      dimensionedScalar("zero", dimVol/dimTime, 0)
  )
{


}

// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::interfaceCapturing::~interfaceCapturing()
{}

// * * * * * * * * * * * * * * Public Access Member Functions  * * * * * * * * * * * * * * //


const Foam::dictionary&
Foam::interfaceCapturing::modelDict() const
{
    return interfaceCapturingCoeffs_;
}

Foam::dictionary&
Foam::interfaceCapturing::modelDict()
{
    return interfaceCapturingCoeffs_;
}

// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //



// ************************************************************************* //
