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
    Foam::interfaceCapturingMethod

Description
    Base class for advection schemes

SourceFiles
    interfaceCapturingMethod.C
    newinterfaceCapturingMethodMethod.C

\*---------------------------------------------------------------------------*/

#ifndef interfaceCapturingMethod_H
#define interfaceCapturingMethod_H

#include "typeInfo.H"
#include "runTimeSelectionTables.H"
#include "interfaceCapturing.H"
#include "volFields.H"
#include "surfaceFields.H"
#include "dimensionedScalar.H"
#include "autoPtr.H"
#include "IOdictionary.H"




// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                Class interfaceCapturingMethod Declaration
\*---------------------------------------------------------------------------*/
template<class reconstructionScheme>
class interfaceCapturingMethod
    : public interfaceCapturing
{
    // Private Member Functions

        

        //- Disallow copy construct
        interfaceCapturingMethod(const interfaceCapturingMethod&);

        //- Disallow default bitwise assignment
        void operator=(const interfaceCapturingMethod&);
protected:

    reconstructionScheme surf_;

public:

    typedef reconstructionScheme reconScheme;

    // Selectors

        //- Return a reference to the selected phaseChange model
        static autoPtr<interfaceCapturingMethod> New
        (
            volScalarField& alpha1,
            const surfaceScalarField& phi,
            const volVectorField& U
        );


    // Constructors

        //- Construct from dictionary
        interfaceCapturingMethod
        (
            volScalarField& alpha1,
            const surfaceScalarField& phi,
            const volVectorField& U
        );


    //- Destructor
    virtual ~interfaceCapturingMethod();


    // Member Functions

        //- advection of the interface
        virtual void advect() = 0;

        //- advection of the interface with source terms
        virtual void advect
        (
            const volScalarField::Internal& Sp,
            const volScalarField::Internal& Su
        ) = 0;

        const reconScheme& surf() const
        {
            return surf_;
        }

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

#ifdef NoRepository
#   include "interfaceCapturingMethod.C"
#endif
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
