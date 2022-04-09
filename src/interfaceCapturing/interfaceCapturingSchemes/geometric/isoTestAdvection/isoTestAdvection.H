/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2016-2017 DHI
    Modified code Copyright (C) 2016-2019 OpenCFD Ltd.
    Modified code Copyright (C) 2018 Johan Roenby
    Modified code Copyright (C) 2019 DLR
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

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
    Foam::isoTestAdvection

Description
    Calculates the new VOF (alpha) field after time step dt given the initial
    VOF field and a velocity field U and face fluxes phi. The fluid transport
    calculation is based on an idea of using isosurfaces to estimate the
    internal distribution of fluid in cells and advecting such isosurfaces
    across the mesh faces with the velocity field interpolated to the
    isosurfaces.

    Reference:
    \verbatim
        Roenby, J., Bredmose, H. and Jasak, H. (2016).
        A computational method for sharp interface advection
        Royal Society Open Science, 3
        doi 10.1098/rsos.160405
    \endverbatim

    Original code supplied by Johan Roenby, DHI (2016)
    Modified Henning Scheufler, DLR

SourceFiles
    isoTestAdvection.C
    isoTestAdvectionTemplates.C

\*---------------------------------------------------------------------------*/

#ifndef isoTestAdvection_H
#define isoTestAdvection_H

#include "geoInterfaceCapturingSchemes.H"
#include "fvMesh.H"
#include "volFieldsFwd.H"
#include "surfaceFields.H"
#include "fvc.H"
#include "className.H"
#include "reconstructionSchemes.H"
#include "cutFaceAdvect.H"
#include "bitSet.H"
#include "zeroField.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace advection
{


/*---------------------------------------------------------------------------*\
                        Class isoTestAdvection Declaration
\*---------------------------------------------------------------------------*/

template<class reconstructionScheme>
class isoTestAdvection
    : public geoInterfaceCapturingSchemes<reconstructionScheme>
{
    // Private data types

     // Private Member Functions

        //- No copy construct
        isoTestAdvection(const isoTestAdvection&) = delete;

        //- No copy assignment
        void operator=(const isoTestAdvection&) = delete;


        // Advection functions
public:

    //- Runtime type information
    ClassName("isoTestAdvection");

    //- Constructors

        //- Construct given alpha, phi and velocity field. Note: phi should be
        // divergence free up to a sufficient tolerance
        isoTestAdvection
        (
            volScalarField& alpha1,
            const surfaceScalarField& phi,
            const volVectorField& U
        );


    //- Destructor
    virtual ~isoTestAdvection() = default;


    // Member functions

        //- Advect the free surface. Updates alpha field, taking into account
        //  multiple calls within a single time step.
        template < class SpType, class SuType >
        void advect(const SpType& Sp, const SuType& Su)
        {

        } 

        //- advection of the interface
        virtual void advect()
        {
            zeroField Sp;
            zeroField Su;
            advect<zeroField,zeroField>(Sp,Su);
        }

        //- advection of the interface with source terms
        virtual void advect
        (
            const volScalarField::Internal& Sp,
            const volScalarField::Internal& Su
        )
        {
            advect<volScalarField::Internal,volScalarField::Internal>(Sp,Su);
        }


};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End advection Foam
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
