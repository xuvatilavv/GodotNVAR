/*
 * Copyright 1993-2019 NVIDIA Corporation.  All rights reserved.
 *
 * Please refer to the NVIDIA end user license agreement (EULA) associated
 * with this source code for terms and conditions that govern your use of
 * this software.  Any use, reproduction, disclosure, or distribution of
 * this software and related documentation outside the terms of the EULA
 * is strictly prohibited.
 *
 */

#ifndef __NVAR_OSSIC_H__
#define __NVAR_OSSIC_H__

#include <nvar.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Type used for source details
 *
 * This is the type used to return position, distance,
 * and occlusion information about occlusion, 
 * 
 *
 */
typedef struct nvarSourceDetails_st
{
    nvarFloat3_t sourceToListener; /**< vector from source to listener, units in meters */
    float        distance;         /**< distance from source to listener, units in meters*/
    float        azimuth;          /**< azimuth of source with respect to listener. Units in degrees.*/
    float        elevation;        /**< elevation of source with respect to listener. Units in degrees. */
    float        occlusionAttenuation; /**< attenuation due to occlusion. Unitless value between 0.0 and 1.0.*/

} nvarSourceDetails_t;


 /**
 * \brief Gets relative position, distance, and occlusion information for a source
 *
 * This function returns data about the indicated source through
 * the structure pointer passed as the second argument. 
 
 * \param source [this] The sound source
 * \param details [out] Returned array of source details
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called
 * \retval ::NVAR_STATUS_INVALID_VALUE \p source is not a valid
 *      context or \p details \p is NULL
 * \retval ::NVAR_STATUS_NOT_READY The tracer geometry is not
 *         ready 
 * \retval ::NVAR_STATUS_ERROR A generic error has occurred
 */
nvarStatus_t NVAR_API
nvarGetSourceDetails(nvarSource_t source, nvarSourceDetails_t* details );

}


#endif