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

Class
    Foam::Brackbill

Description
    estimates the curvature from the volume fraction field similiar to the
    mode of Brackbill et al.

SourceFiles
    Brackbill.C

\*---------------------------------------------------------------------------*/

#ifndef Brackbill_H
#define Brackbill_H

#include "typeInfo.H"
#include "volFields.H"
#include "dimensionedScalar.H"
#include "autoPtr.H"




#include "surfaceTensionForceModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                Class Brackbill Declaration
\*---------------------------------------------------------------------------*/

template<class interfaceCapturing>
class Brackbill
    : public surfaceTensionForceModel
{

private:

    //-
        //- Stabilisation for normalisation of the interface normal
        const dimensionedScalar deltaN_;

    // Private Member Functions

        virtual void correctContactAngle
        (
            surfaceVectorField::Boundary& nHat,
            surfaceVectorField::Boundary& Brackbillf
        );


        //- Disallow copy construct
        Brackbill(const Brackbill&);

        //- Disallow default bitwise assignment
        void operator=(const Brackbill&);

public:

    //- Runtime type information
    TypeName("Brackbill");


    // Constructors

        //- Construct from dictionary
        Brackbill
        (
            const dictionary& dict,
            const volScalarField& alpha1,
            const surfaceScalarField& phi,
            const volVectorField& U
        );


    //- Destructor
    virtual ~Brackbill()
    {}

    virtual void correct();

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include "Brackbill.C"
#endif


#endif

// ************************************************************************* //
