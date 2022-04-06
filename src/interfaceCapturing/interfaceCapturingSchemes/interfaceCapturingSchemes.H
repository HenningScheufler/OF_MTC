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
    Foam::interfaceCapturingSchemes

Description
    Base class for advection schemes

SourceFiles
    interfaceCapturingSchemes.C
    newinterfaceCapturingSchemes.C

\*---------------------------------------------------------------------------*/

#ifndef interfaceCapturingSchemes_H
#define interfaceCapturingSchemes_H

#include "typeInfo.H"
#include "runTimeSelectionTables.H"
#include "volFields.H"
#include "surfaceFields.H"
#include "dimensionedScalar.H"
#include "autoPtr.H"
#include "IOdictionary.H"




// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                Class interfaceCapturingSchemes Declaration
\*---------------------------------------------------------------------------*/

class interfaceCapturingSchemes
    : public IOdictionary
{

private:

    //-
        dictionary interfaceCapturingSchemesCoeffs_;

protected:

        // reference to the VoF Field
        volScalarField& alpha1_;

        // reference to the face fluxes
        const surfaceScalarField& phi_;

        // reference to the velocity field
        const volVectorField& U_;

        //- Face volumetric transport
        surfaceScalarField alphaPhi_;

    // Private Member Functions

        //- Disallow copy construct
        interfaceCapturingSchemes(const interfaceCapturingSchemes&);

        //- Disallow default bitwise assignment
        void operator=(const interfaceCapturingSchemes&);


public:

    //-
    dictionary& modelDict();

    //-
    const dictionary& modelDict() const;


public:

    //- Runtime type information
    ClassName("interfaceCapturingSchemes");


    //- Declare run-time constructor selection table
        declareRunTimeSelectionTable
        (
            autoPtr,
            interfaceCapturingSchemes,
            dictionary,
            (
                volScalarField& alpha1,
                const surfaceScalarField& phi,
                const volVectorField& U
            ),
            (alpha1, phi,U)
        );


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
        interfaceCapturingSchemes
        (
            volScalarField& alpha1,
            const surfaceScalarField& phi,
            const volVectorField& U
        );


    //- Destructor
    virtual ~interfaceCapturingSchemes();


    // Member Functions

        //- advection of the interface
        virtual void advect() = 0;

        //- advection of the interface with source terms
        virtual void advect
        (
            const volScalarField::Internal& Sp,
            const volScalarField::Internal& Su
        ) = 0;

        template < class Type >
        tmp<surfaceScalarField> getRhoPhi
        (
            const Type rho1,
            const Type rho2
        ) const
        {
            return tmp<surfaceScalarField>
            (
                new surfaceScalarField
                (
                    "rhoPhi",
                    (rho1 - rho2)*alphaPhi_ + rho2*phi_
                )
            );
        }
        
        const surfaceScalarField& alphaPhi() const
        {
            return alphaPhi_;
        }

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
