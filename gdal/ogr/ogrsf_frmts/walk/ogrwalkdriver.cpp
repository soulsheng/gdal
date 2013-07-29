/******************************************************************************
 * $Id: ogrwalkdriver.cpp
 *
 * Project:  OpenGIS Simple Features Reference Implementation
 * Purpose:  Implements OGRWalkDriver class.
 * Author:   Xian Chen, chenxian at walkinfo.com.cn
 *
 ******************************************************************************
 * Copyright (c) 2013,  ZJU Walkinfo Technology Corp., Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ****************************************************************************/

#include "ogrwalk.h"

/************************************************************************/
/*                          ~OGRWalkDriver()                            */
/************************************************************************/

OGRWalkDriver::~OGRWalkDriver()

{
}

/************************************************************************/
/*                              GetName()                               */
/************************************************************************/

const char *OGRWalkDriver::GetName()

{
    return "Walk";
}

/************************************************************************/
/*                                Open()                                */
/************************************************************************/

OGRDataSource *OGRWalkDriver::Open( const char * pszFilename, int bUpdate )
{

    if( EQUALN(pszFilename, "PGEO:", strlen("PGEO:")) )
        return NULL;

    if( EQUALN(pszFilename, "GEOMEDIA:", strlen("GEOMEDIA:")) )
        return NULL;

    if( !EQUALN(pszFilename,"WALK:", strlen("WALK:"))
        && !EQUAL(CPLGetExtension(pszFilename), "MDB") )
        return NULL;

    OGRWalkDataSource  *poDS = new OGRWalkDataSource();

    if( !poDS->Open( pszFilename, bUpdate ) )
    {
        delete poDS;
        return NULL;
    }
    else
        return poDS;
}

/************************************************************************/
/*                          CreateDataSource()                          */
/************************************************************************/

OGRDataSource *OGRWalkDriver::CreateDataSource( const char * pszName,
                                                 char **papszOptions )

{
    //if( !EQUAL(CPLGetExtension(pszName), "MDB") )
    //    return NULL;

    OGRWalkDataSource  *poDS = new OGRWalkDataSource();
    
    if( !poDS->Open( pszName, TRUE ) )
    {
        delete poDS;
        CPLError( CE_Failure, CPLE_AppDefined, 
         "Walk driver doesn't currently support database creation.\n"
                  "Please create database with the `createdb' command." );
        return NULL;
    }
    else
        return poDS;
}

/************************************************************************/
/*                           TestCapability()                           */
/************************************************************************/

int OGRWalkDriver::TestCapability( const char * pszCap )

{
    if( EQUAL(pszCap,ODrCCreateDataSource) )
        return TRUE;
    else if( EQUAL(pszCap,ODrCDeleteDataSource) )
        return FALSE;
    else
        return FALSE;
}

/************************************************************************/
/*                          RegisterOGRWalk()                           */
/************************************************************************/

void RegisterOGRWalk()

{
    OGRSFDriverRegistrar::GetRegistrar()->RegisterDriver( new OGRWalkDriver );
}

