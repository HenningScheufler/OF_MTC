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

Class
    Foam::geoInterfaceCapturingSchemes

Description
    Base class for advection schemes

SourceFiles
    geoInterfaceCapturingSchemes.C
    newgeoInterfaceCapturingSchemes.C

\*---------------------------------------------------------------------------*/

#ifndef geoInterfaceCapturingSchemes_H
#define geoInterfaceCapturingSchemes_H

#include "typeInfo.H"
#include "runTimeSelectionTables.H"
#include "interfaceCapturingSchemes.H"
#include "volFields.H"
#include "surfaceFields.H"
#include "dimensionedScalar.H"
#include "autoPtr.H"
#include "IOdictionary.H"




// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                Class geoInterfaceCapturingSchemes Declaration
\*---------------------------------------------------------------------------*/

class geoInterfaceCapturingSchemes
    : public interfaceCapturingSchemes
{
    // Private Member Functions

        //- Disallow copy construct
        geoInterfaceCapturingSchemes(const geoInterfaceCapturingSchemes&);

        //- Disallow default bitwise assignment
        void operator=(const geoInterfaceCapturingSchemes&);

public:

    //- Runtime type information
    ClassName("geoInterfaceCapturingSchemes");

    // Selectors

        //- Return a reference to the selected phaseChange model
        static autoPtr<interfaceCapturingSchemes> New
        (
            volScalarField& alpha1,
            const surfaceScalarField& phi,
            const volVectorField& U
        );


    // Constructors

        //- Construct from dictionary
        geoInterfaceCapturingSchemes
        (
            volScalarField& alpha1,
            const surfaceScalarField& phi,
            const volVectorField& U
        );


    //- Destructor
    virtual ~geoInterfaceCapturingSchemes();


    // Member Functions

        //- advection of the interface
        virtual void advect() = 0;

        //- advection of the interface with source terms
        virtual void advect
        (
            const volScalarField::Internal& Sp,
            const volScalarField::Internal& Su
        ) = 0;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
