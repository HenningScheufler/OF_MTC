/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2017 OpenCFD Ltd.
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

\*---------------------------------------------------------------------------*/

#ifndef makeInterfaceCapturingMethodTypes_H
#define makeInterfaceCapturingMethodTypes_H

#include "addToRunTimeSelectionTable.H"
#include "interfaceCapturing.H"
#include "dictionary.H"


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeInterfaceCapturingMethodTypes(advectType, reconType)         \
                                                                            \
    namespace Foam                                                          \
    {                                                                       \
        typedef Foam::advection::advectType                                 \
            <                                                               \
                Foam::reconstruction::reconType                             \
            >                                                               \
            advectType##_##reconType;                                       \
                                                                            \
        defineTemplateTypeNameAndDebug                                      \
        (                                                                   \
            advectType##_##reconType,                                       \
            0                                                               \
        );                                                                  \
                                                                            \
        addNamedToRunTimeSelectionTable                                     \
        (                                                                   \
            interfaceCapturing,                                             \
            advectType##_##reconType,                                       \
            dictionary,                                                     \
            advectType##_##reconType                                        \
        );                                                                  \
    }

#endif

// ************************************************************************* //
