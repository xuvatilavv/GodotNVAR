/*
 * Copyright 1993-2019 NVIDIA Corporation.  All rights reserved.
 *
 * Please refer to the NVIDIA end user license agreement (EULA) associated
 * with this source code for terms and conditions that govern your use of
 * this software.  Any use, reproduction, disclosure, or distribution of
 * this software and related documentation outside the terms of the EULA
 * is strictly prohibited.
 *
 *
 */

#ifndef __NVAR_H__
#define __NVAR_H__

#include <stdlib.h>
#include <limits.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * \file nvar.h
 * \brief Header file for the NVIDIA Acoustic Raytracer (NVAR)
 *        VRWorks Audio application programming interface (API). 
 */

/**
 * \defgroup NVAR_TYPES NVAR API Data Types
 * @{
 */

 /**
 * \brief NVAR Library Version
 *
 *  NVAR Library version is broken into major and minor components
 *  usually denoted major.minor.  These components can be determined
 *  from NVAR_API_VERSION according to the following formulas:
 * 
 * \code{.c}
 *        int major =  NVAR_API_VERSION/1000;
 *        int minor = (NVAR_API_VERSION%1000);
 * \endcode
 *
 */
 #define NVAR_API_VERSION 2000

/**
 * The maximum length of the NVAR processing context name
 */
#define NVAR_CREATE_NAME_LENGTH 16

/**
 * The suggested reverb length in seconds
 */
#define NVAR_DEFAULT_REVERB_LENGTH 1.0f

/**
 * The minimum allowed sample rate 
 */
#define NVAR_MIN_SAMPLE_RATE 22050

/**
 * The suggested sample rate of all sound sources 
 */
#define NVAR_DEFAULT_SAMPLE_RATE 48000

/**
 * The default output format
 */
#define NVAR_DEFAULT_OUTPUT_FORMAT NVAR_OUTPUT_FORMAT_STEREO_HEADPHONES

/**
 * The default ratio of geometry units per meter
 */
#define NVAR_DEFAULT_UNIT_LENGTH_PER_METER_RATIO 1.0f

/**
* The default material reflection coefficient
*/
#define NVAR_DEFAULT_REFLECTION_COEFFICIENT 0.9f

/**
* The default material transmission coefficient
*/
#define NVAR_DEFAULT_TRANSMISSION_COEFFICIENT 0.0f

/**
* The lower limit on material coefficients
*/
#define NVAR_MIN_MATERIAL_COEFFICIENT 0.0f

/**
* The upper limit on material coefficients
*/
#define NVAR_MAX_MATERIAL_COEFFICIENT 1.0f

    /**
 * The default indirect path gain
 */
#define NVAR_DEFAULT_INDIRECT_PATH_GAIN 1.0f

/**
 * The default direct path gain 
 */
#define NVAR_DEFAULT_DIRECT_PATH_GAIN 1.0f

/**
* The default decay factor, which affects filter smoothing
*/
#define NVAR_DEFAULT_DECAY_FACTOR 0.9f

/**
 * \brief All NVAR APIs return one of these error codes.
 * Refer to each individual error code for a
 * detailed explanation.
 *
 */
typedef enum NVAR_STATUS_enum
{
    /**
     * The API call returned with no errors.
     */
    NVAR_STATUS_SUCCESS = 0,

    /**
     * The NVAR library has not been initialized
     * with ::nvarInitialize() or an attempt to initialize 
     * the library failed.
     */
    NVAR_STATUS_NOT_INITIALIZED = 1,

    /**
     * The operation is not supported due to a mismatch between the
     * operation requested and the state of one or more objects.
     */
    NVAR_STATUS_NOT_SUPPORTED = 2,

    /**
     * The API is not implemented by the current installation.
     */
    NVAR_STATUS_NOT_IMPLEMENTED = 3,

    /**
     * One or more of the parameters passed to the API call
     * is not an acceptable value or is not within the range of acceptable
     * values.
     */
    NVAR_STATUS_INVALID_VALUE = 4,

    /**
     * The API call failed because it was unable to allocate enough
     * memory or other required resource to perform the requested
     * operation.
     */
    NVAR_STATUS_OUT_OF_RESOURCES = 5,

    /**
     * The operation is not available at this time.  The reason could be
     * incomplete setup, an active asynchronous operation, or other
     * unspecified reason.
     */
    NVAR_STATUS_NOT_READY = 6,

    /**
     * The API returned an unspecified error.
     */
    NVAR_STATUS_ERROR = 7,

    NUM_NVAR_STATUS_CODES, /**< The number of NVAR status codes. */

    NVAR_STATUS_RESERVED = INT_MAX,  /**< Reserved for internal use by NVAR */

} nvarStatus_t;

/**
 * \brief Supported output formats
 *
 * These formats describe the types of audio device playing 
 * the audio output, for example, a pair of stereo headphones.
 */
typedef enum NVAR_OUTPUT_FORMAT_enum
{
    NVAR_OUTPUT_FORMAT_STEREO_HEADPHONES = 0, /**< 2-channel format intended for headphones */

    NUM_NVAR_OUTPUT_FORMATS,                /**< The number of output formats */

    NVAR_OUTPUT_FORMAT_RESERVED = INT_MAX,  /**< Reserved for internal use by NVAR */

} nvarOutputFormat_t;

/**
 * \brief Predefined material types
 *
 * A list of materials whose acoustic properties are available for direct
 * use or to form the basis of materials which a user can modify after 
 * creating. 
 */
typedef enum NVAR_PREDEFINED_MATERIAL_enum
{
    NVAR_PREDEFINED_MATERIAL_CONCRETE = 0,     /**< Concrete */
    NVAR_PREDEFINED_MATERIAL_METAL,        /**< Metal */
    NVAR_PREDEFINED_MATERIAL_PLASTIC,      /**< Plastic */
    NVAR_PREDEFINED_MATERIAL_CARPET,       /**< Carpet */
    NVAR_PREDEFINED_MATERIAL_GLASS,        /**< Glass */
    NVAR_PREDEFINED_MATERIAL_WOOD,         /**< Wood */
    NVAR_PREDEFINED_MATERIAL_CLOTH,        /**< Cloth */
    NVAR_PREDEFINED_MATERIAL_ABSORBER, /**< No reflections, all sound is absorbed by the material */

    NUM_NVAR_PREDEFINED_MATERIALS,         /**< The number of predefined materials */

    NVAR_PREDEFINED_MATERIAL_RESERVED = INT_MAX, /**< Reserved for internal use by NVAR */

} nvarPredefinedMaterial_t;

/**
* \brief Compute presets
*/
typedef enum NVAR_COMPUTE_PRESET_enum
{
    NVAR_COMPUTE_HIGH = 0,           /**< High compute */
    NVAR_COMPUTE_LOW,                /**< Low compute */
    NVAR_COMPUTE_PRO,                /**< Professional Compute */
    NVAR_NUM_COMPUTE_PRESETS,       /**<  The number of compute presets */
    NVAR_COMPUTE_PRESET_RESERVED = INT_MAX,  /**< Reserved for internal use by NVAR */
} nvarPreset_t;

/**
* The default compute preset
*/
#define  NVAR_COMPUTE_PRESET_DEFAULT NVAR_COMPUTE_HIGH 

/**
* \brief Effect strength presets
*/
typedef enum NVAR_EFFECT_PRESET_enum
{
    NVAR_EFFECT_LOW = 0,            /**< Low effects strength */
    NVAR_EFFECT_MEDIUM,             /**< Medium effects strength */
    NVAR_EFFECT_HIGH,               /**< High effects strength */
    NVAR_EFFECT_PRO,                /**< Professional strength */
    NVAR_NUM_EFFECT_PRESETS,        /**< The number of effects strength levels */
    NVAR_EFFECT_PRESET_RESERVED = INT_MAX  /**< Reserved for internal use by NVAR */
} nvarEffect_t;

/**
* The default effect preset
*/
#define NVAR_EFFECT_PRESET_DEFAULT NVAR_EFFECT_MEDIUM

/**
 * \brief An opaque handle to the NVAR processing context handle
 */
typedef struct nvar_st* nvar_t;

/**
 * \brief An opaque handle to a user defined acoustic material
 */
typedef struct nvarMaterial_st* nvarMaterial_t;

/**
 * \brief An opaque handle to an acoustic mesh
 */
typedef struct nvarMesh_st* nvarMesh_t;

/**
 * \brief An opaque handle to a sound source
 * 
 */
typedef struct nvarSource_st* nvarSource_t;

/**
 * \brief Type used to store a transformation matrix
 *
 * This type describes the affine transformation matrix of the 
 * geometry objects in the scene. Transformation matrices are specified
 * to NVAR in row major ordering  where a[3], a[7], and a[11] 
 * are the translation components. If vIn is a 4x1
 * input vector and mat4x4 is the 4x4 transformtion matrix, the output 
 * vector vOut = mat4x4 * Vin.
 *
 */
typedef struct nvarMatrix4x4_st
{
    float a[16]; /**< 4 rows by 4 columns */

} nvarMatrix4x4_t;

/**
 * \brief 3D positions and vectors
 *
 * This type is used to pass 3D positions and vectors to the
 * NVAR API.  The NVAR API coordinate system does not have a
 * handed preference, but expects the caller to be consistent
 * with its coordinate system for the listener, geometry, 
 * and sources. 
 *
 */
typedef struct nvarFloat3_st
{
    float x;    /**< x */
    float y;    /**< y */
    float z;    /**< z */

} nvarFloat3_t;

/** @} */ /* END NVAR_TYPES */

/**
 * \internal
 *
 */

/**
 * \brief Define HANDLE type
 *
 * Define the HANDLE type which is normally defined in Winnt.h (#include Windows.h)
 *
 */
#ifndef NVAR_NOHANDLEDEF
typedef void* HANDLE;
#endif
/**
 * \endinternal
 *
 */

/**
 * Calling conventions
 */
#ifndef NVAR_API
#define NVAR_API
#endif

/**
 * \defgroup nvarStatus_t Error Handling
 *
 *
 * This section describes the error handling functions of the
 * NVAR API.
 *
 * @{
 */

/**
 * \brief Gets the string representation of a status code enum
 *
 * This function sets \p *pStr to the address of a
 * NULL-terminated string representation of the name of the
 * status code enumeration \p status.
 *
 * \param pStr [out] Returned address of the string pointer
 * \param status [in] The status code of the enum string
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p pStr is NULL or
 *         \p status is an invalid value.
 *
 * \sa ::nvarStatus_t
 */
nvarStatus_t NVAR_API
nvarGetStatusString(const char** pStr, const nvarStatus_t status);

/**
 * \brief Gets the string description of a status code
 *
 * This function sets \p *pStr to the address of a
 * NULL-terminated string containing a description of the 
 * status code enumeration \p status.
 *
 * \param pStr [out] Returned address of the string pointer
 * \param status [in] Status code of the description string
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p pStr is NULL or
 *         \p status is an invalid value.
 *
 * \sa ::nvarStatus_t
 */
nvarStatus_t NVAR_API
nvarGetStatusDescription(const char** pStr, const nvarStatus_t status);

/** @} */ /* END nvarStatus_t */

/**
 * \defgroup NVAR_GENERAL General Functions
 *
 *
 * This section describes the general entry points of the NVIDIA Acoustic Raytracer
 * application programming interface.
 *
 * @{
 */

/**
 * \brief Gets the NVAR API version
 *
 * Returns the version number of the installed NVAR API.
 *
 * \param pVersion [out] Returns the NVAR API version.
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p pVersion is NULL.
 */
nvarStatus_t NVAR_API 
nvarGetVersion(int* pVersion);

/**
 * \brief Gets the number of channels
 *
 * Returns the number of audio channels in the specified
 * output format.
 *
 * \param outputFormat [in] Output format enumeration
 * \param pChannels [out] Returned number of audio channels
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p outputFormat is an invalid
 *         value or \p pChannels is NULL.
 */
nvarStatus_t NVAR_API
nvarGetOutputFormatChannels(nvarOutputFormat_t outputFormat, int* pChannels);

/**
 * \brief Initializes the NVAR API
 *
 *  Initializes the API and must be called before any other function that can return 
 * ::NVAR_STATUS_NOT_INITIALIZED. However, functions that do not return 
 * ::NVAR_STATUS_NOT_INITIALIZED  may be called before this function.
 *
 * \param flags [in] Initialization flags
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_SUPPORTED The underlying NVAR
 *         support libraries are incompatible.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p flags is not zero as
 *         there are no current initialization flags.
 */
nvarStatus_t NVAR_API 
nvarInitialize(const int flags);

/**
 * \brief Finalizes the NVAR API
 *
 * Finalize resets the API to the default state. After this
 * call, any calls requiring the API to be initialized will
 * return ::NVAR_STATUS_NOT_INITIALIZED.
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 */
nvarStatus_t NVAR_API 
nvarFinalize(void);

/**
 * \brief Gets the flags used to initialize the API
 *
 * Returns the flags used to initialize the API.
 *
 * \param pFlags [out] Returned initialize flags
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called
 * \retval ::NVAR_STATUS_INVALID_VALUE \p pFlags is NULL
 */
nvarStatus_t NVAR_API 
nvarGetInitializeFlags(int* pFlags);

/**
* \brief Gets the number of nvar supported devices 
*
* Returns the number of devices in the system that NVAR can use.
*
* \param pDeviceCount [out] Returned device count
*
* \retval ::NVAR_STATUS_SUCCESS No error has occurred
* \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
*         not been called.
* \retval ::NVAR_STATUS_INVALID_VALUE \p pDeviceCount is NULL.
*/
nvarStatus_t NVAR_API 
nvarGetDeviceCount(int* pDeviceCount);

/**
* \brief Gets the list of NVAR supported CUDA device ordinals
*
* Returns an array of the CUDA ordinals (CUDA device numbers) of
* devices in this system which NVAR can use. On input, \p pDeviceCount
* should contain the length of the array passed in \pPDevices. On return,
* \p pDeviceCount will contain the number of valid entries in \p pDevices.
*
* \param pDevices [out] Pointer an array of integers where device array
*       will be written.
* \param pDeviceCount [in, out] Pointer to provide the size of \p pDevice 
*       array and to return copied device count
*
* \retval ::NVAR_STATUS_SUCCESS No error has occurred
* \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
*         not been called.
* \retval ::NVAR_STATUS_INVALID_VALUE \p pDevices or \p pDeviceCountis is NULL.
*/
nvarStatus_t NVAR_API 
nvarGetDevices(int* pDevices, int* pDeviceCount);

/**
* \brief Returns an identifer string for a device
*
* Returns a NULL-terminated ASCII string identifying the device whose CUDA ordinal
* is passed as \p device in \p name. \p length specifies the size of the \p device
* array, that is, maximum length of the string that may be returned.
*
* \param device[in]  - CUDA device ordinal of the requested device
* \param name[in] - Returned identifier string for the device
* \param length[in]  - Maximum length of string to store in \p name
*
*
* \retval ::NVAR_STATUS_SUCCESS No error has occurred.
* \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
*         not been called.
* \retval ::NVAR_STATUS_INVALID_VALUE \p deviceId is not the CUDA ordinal of a device
          that supports NVAR, \p name is NULL, or \p length is 0.
*/
nvarStatus_t NVAR_API 
nvarGetDeviceName(int device, char* name, int length);

/**
* \brief Gets the prefered NVAR device
*
* Returns CUDA ordinal of the prefered NVAR device. If a valid \p pDXGIAdapter
*        is passed, NVAR will prefer to use a supported not in use for
*        graphical rendering. If more than one supported device is available,
*        the first device not being used for graphics is returned.
*        If there is only one supported device, its CUDA ordinal is returned. 
*
* \param pDXGIAdapter [optional, in] Pointer to the IDXGIAdapter 
*        corresponding to the rendering device. 
* \param pDevice [out] On return, the CUDA ordinal of the prefered device for NVAR.
*
* \retval ::NVAR_STATUS_SUCCESS No error has occurred
* \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
*         not been called
* \retval ::NVAR_STATUS_INVALID_VALUE \p pDXGIAdapter is not a valid 
           DGXIAdaptor or \p pDevice is NULL.
*/
nvarStatus_t NVAR_API 
nvarGetPreferedDevice(void* pDXGIAdapter, int* pDevice);

/** @} */ /* END NVAR_GENERAL */

/**
 * \defgroup NVAR_CONTEXT Processing Context Functions
 *
 * This section describes the processing context functions of the NVIDIA 
 * Acoustic Raytracer application programming interface.
 *
 * @{
 */

/**
 * \brief Creates an NVAR processing context
 *
 * Creates and initializes an NVAR processing context.  If no
 * \p name string is passed, a default context will be created.  If the
 * context to be created already exists, the existing handle
 * will be returned to the caller the context's internal reference count
 * will be incremented when the function call succeeds. Only one unnamed 
 * and one named context are simultaneously supported.
 *
 * \param pNvar [out] Returned NVAR processing context
 * \param name [in] The name of the context, which may be up to
 *        ::NVAR_CREATE_NAME_LENGTH characters
 * \param nameLength [in] The number of characters in \p name
 * \param preset [in] NVAR compute preset that  controls performance of the
           acoustic trace.
 * \param pDeviceNum [optional, in, out] Pointer to the CUDA device number;
 *        if NULL, the device 0 will be used
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called
 * \retval ::NVAR_STATUS_NOT_SUPPORTED The context has already been created
 *         with a different parameter set (for example the CUDA device num).
 *         Mismatched parameters will be returned through parameters
 *         marked as [optional, in, out] with the values of the existing 
 *         NVAR processing context. The contents of \p pNvar will be will be invalid.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p pNvar is NULL
 * \retval ::NVAR_STATUS_OUT_OF_RESOURCES The processing context allocation
 *         failed.  This error will also be returned for a second named context
 *         if another named context already exists.
 * \retval ::NVAR_STATUS_ERROR A generic error has occurred
 */
nvarStatus_t NVAR_API
nvarCreate(nvar_t* pNvar,
           const char name[], const size_t nameLength,
           nvarPreset_t preset, int* pDeviceNum);

/**
 * \brief Destroys an NVAR processing context
 *
 * Decrements the reference count on an NVAR
 * context and, if the reference cound becomes zero, destroys 
*  the processing context and frees any associated resources.
 *
 * \param nvar [this] The NVAR processing context to be
 *        destroyed
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called
 * \retval ::NVAR_STATUS_INVALID_VALUE \p nvar is not a valid
 *         context
 */
nvarStatus_t NVAR_API 
nvarDestroy(nvar_t nvar);

/**
 * \brief Gets the CUDA device number from the NVAR processing
 *        context
 *
 * Returns the CUDA device number specified to
 * create the NVAR processing context.
 *
 * \param nvar [this] The NVAR processing context
 * \param pDeviceNum [out] Returned device number
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called
 * \retval ::NVAR_STATUS_INVALID_VALUE \p nvar is not a valid
 *         context or \p pDeviceNum is NULL
 */
nvarStatus_t NVAR_API
nvarGetDeviceNum(nvar_t nvar, int* pDeviceNum);

/**
 * \brief Gets the reverb length
 *
 * Returns the reverb length, in seconds, from the
 * NVAR processing context.
 *
 * \param nvar [this] The NVAR processing context
 * \param pReverbLength [out] Returned reverb length
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p nvar is not a valid
 *         context or \p pReverbLength is NULL.
 */
nvarStatus_t NVAR_API
nvarGetReverbLength(nvar_t nvar, float* pReverbLength);

/**
 * \brief Sets the reverb length
 *
 * Sets the reverb length, in seconds, in the NVAR
 * processing context.  If this function is not called, the
 * default reverb length given by ::NVAR_DEFAULT_REVERB_LENGTH
 * is used. This function can be expensive because of reallocation
 * of internal buffers. It should ideally called once before any 
 * sources exist.  Audio continuity is not guaranteed across
 * calls to this function. The API does not restrict the reverb length
*  to enable non-realtime uses. Real-time applications should take care
 * in setting this value.
 *
 * \param nvar [this] The NVAR processing context
 * \param reverbLength [in] Reverb length, in seconds. Must be in the range 
 *        (0.0, Inf).
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p nvar is not a valid
 *         context or \p reverbLength is not in the range (0.0f,
 *         inf).
 * \retval ::NVAR_STATUS_OUT_OF_RESOURCES An internal allocation
 *         has failed.
 */
nvarStatus_t NVAR_API
nvarSetReverbLength(nvar_t nvar, const float reverbLength);

/**
 * \brief Gets the sample rate
 *
 * Returns the sample rate in samples per second of sound
 * sources in the NVAR processing context.
 *
 * \param nvar [this] The NVAR processing context
 * \param pSampleRate [out] Returned sample rate in samples per second
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called
 * \retval ::NVAR_STATUS_INVALID_VALUE \p nvar is not a valid
 *         context or \p pSampleRate is NULL
 */
nvarStatus_t NVAR_API
nvarGetSampleRate(nvar_t nvar, int* pSampleRate);

/**
 * \brief Sets the sample rate
 *
 * Sets the sample rate in samples per second of  sound
 * sources in the NVAR processing context.  The default
 * sample rate if this function is not called is
 * ::NVAR_DEFAULT_SAMPLE_RATE hertz. This function can be 
 * expensive because of reallocation
 * of internal buffers. It should ideally called once before any 
 * sources exist.  Audio continuity is not guaranteed across
 * calls to this function. 
 *
 * \param nvar [this] The NVAR processing context
 * \param sampleRate [in] Sample rate. Must be in the range 
 * [::NVAR_MIN_SAMPLE_RATE, inf).
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p nvar is not a valid
 *         context or \p sampleRate is not in the range
 *         [::NVAR_MIN_SAMPLE_RATE, inf].
 * \retval ::NVAR_STATUS_OUT_OF_RESOURCES An internal allocation
 *         has failed.
 */
nvarStatus_t NVAR_API
nvarSetSampleRate(nvar_t nvar, const int sampleRate);

/**
 * \brief Gets the output format
 *
 * Returns the output format of filters or 
 * filtered audio from the NVAR processing context.
 *
 * \param nvar [this] The NVAR processing context
 * \param pOutputFormat [out] Returned output format
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p nvar is not a valid
 *         context or \p pOutputFormat is NULL.
 */
nvarStatus_t NVAR_API
nvarGetOutputFormat(nvar_t nvar, nvarOutputFormat_t* pOutputFormat);

/**
 * \brief Sets the output format
 *
 * Sets the output format of filters or filtered audio
 * from the NVAR processing context. If this function is not called,
 * the default output format
 * ::NVAR_OUTPUT_FORMAT_STEREO_HEADPHONES is used.
 * This function can be expensive because of reallocation
 * of internal buffers; it should ideally called only once,
 *  before any sources have been created. 
 * Audio continuity is not guaranteed across calls to this function.
 *
 * \param nvar [this] The NVAR processing context
 * \param outputFormat [in] The output format
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p nvar is not a valid
 *         context or \p outputFormat is not a valid output
 *         format.
 * \retval ::NVAR_STATUS_OUT_OF_RESOURCES An internal allocation
 *         has failed.
 */
nvarStatus_t NVAR_API
nvarSetOutputFormat(nvar_t nvar, const nvarOutputFormat_t outputFormat);

/**
* \brief Gets the decay factor
*
* Returns the reverb decay factor from the
* NVAR processing context
*
* \param nvar [this] The NVAR processing context
* \param pDecayFactor [out] Returned decay factor
*
* \retval ::NVAR_STATUS_SUCCESS No error has occurred.
* \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
*         not been called.
* \retval ::NVAR_STATUS_INVALID_VALUE \p nvar is not a valid
*         context or \p pDecayFactor is NULL.
*/
nvarStatus_t NVAR_API
nvarGetDecayFactor(nvar_t nvar, float* pDecayFactor);

/**
* \brief Sets the decay factor
*
* Sets the decay factor for sources in this processing context. The
* decay factor controls the longevity of energy from reflections 
* according to the equation (1-decayFactor)^N 
* where N is the number of traces. A decay factor of 0.8, for example,
* results in a path's contributed energy being reducing to < 1% within 21
* traces from the trace when the path is originally discovered.
*
* The default decay factor is ::NVAR_DEFAULT_DECAY_FACTOR if
* this function is not called.
*
* \param nvar [this] The NVAR processing context
* \param decayFactor [in] Decay factor. Must be in the range (0.0, 1.0].
*
* \retval ::NVAR_STATUS_SUCCESS No error has occurred.
* \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
*         not been called.
* \retval ::NVAR_STATUS_INVALID_VALUE \p nvar is not a valid
*         context or \p decayFactor is not in the range
*         (0.0f, 1.0f].
* \retval ::NVAR_STATUS_ERROR A generic error has occurred.
*/
nvarStatus_t NVAR_API
nvarSetDecayFactor(nvar_t nvar, const float decayFactor);

/**
 * \brief Gets the units per meter from the NVAR processing
 *        context
 *
 * Returns the units per meter from the NVAR
 * processing context. The default unit length per meter ratio
 * is ::NVAR_DEFAULT_UNIT_LENGTH_PER_METER_RATIO.
 *
 * \param nvar [this] The NVAR processing context
 * \param pRatio [out] Returned unit length per meter ratio
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p nvar is not a valid
 *         context or \p pRatio is NULL.
 */
nvarStatus_t NVAR_API 
nvarGetUnitLength(nvar_t nvar, float* pRatio);

/**
 * \brief Sets the unit length per meter ratio of the NVAR
 *        processing context
 *
 * Sets the unit length per meter ratio of the
 * NVAR processing context. If each unit in the geometry passed
 * to the NVAR processing context is specified in centimeters, for example,
 * a unit length per meter of 0.01 units per meter gives the processing
 * context the appropriate scale. If this function is not called,
 * the default unit length per meter ratio
 *  ::NVAR_DEFAULT_UNIT_LENGTH_PER_METER_RATIO is used.
 *
 * \param nvar [this] The NVAR processing context
 * \param ratio [in] The new unit length per meter ratio. Must be in
 *        the range (0.0, Inf).
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p nvar is not a valid
 *         context or \p ratio is not in the range
 *         (0.0f, inf).
 * \retval ::NVAR_STATUS_ERROR A generic error has occurred.
 */
nvarStatus_t NVAR_API 
nvarSetUnitLength(nvar_t nvar, const float ratio);

/**
 * \brief Updates the processing engine with changes to the
 *        geometry
 *
 * Updates the scene's acoustic geometry. Because this
 * update can be an expensive operation,
 * this function provides a mechanism to update the geometry 
 * outside of calling ::nvarTraceAudio. If the geometry has changed
 * and this function has not been not called before a call to ::nvarTraceAudio,
 * the geometry changes will be automatically updated in the call
 * to ::nvarTraceAudio.
 *
 * \param nvar [this] The NVAR processing context
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p nvar is not a valid
 *         context.
 * \retval ::NVAR_STATUS_NOT_READY Audio trace is in progress.
 * \retval ::NVAR_STATUS_ERROR A generic error has occurred.
 */
nvarStatus_t NVAR_API 
nvarCommitGeometry(nvar_t nvar);

/**
* \brief Exports NVAR geometry to Wavefront .obj file.
*
* Dumps the current state of the scene geometry in the NVAR context
* to a Wavefront .obj file with a generic .mtl material file. 
* This function involves disk I/O and is heavyweight as a result.
*
* \param nvar [this] The NVAR processing context
* \param objFileBaseName [in] The base file name of the generated Wavefront .obj and .mtl 
        files to which the NVAR geometry will be exported.
*
* \retval ::NVAR_STATUS_SUCCESS No error has occurred.
* \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
*         not been called.
* \retval ::NVAR_STATUS_INVALID_VALUE \p nvar is not a valid
*         context or objFileBaseName is NULL.
* \retval ::NVAR_STATUS_ERROR A generic error has occurred.
*/
nvarStatus_t NVAR_API 
nvarExportOBJs(nvar_t nvar, const char* objFileBaseName);

/**
 * \brief Gets the location of the listener
 *
 * Returns the location of the listener in the
 * scene.
 *
 * \param nvar [this] The NVAR processing context
 * \param pLocation [out] Returned location of the listener
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p nvar is not a valid
 *         context or if \p pLocation is NULL.
 */
nvarStatus_t NVAR_API
nvarGetListenerLocation(nvar_t nvar, nvarFloat3_t* pLocation);

/**
 * \brief Sets the location of the listener
 *
 * Sets the location of the listener in the scene. 
 * The default orientation of the listener is (0.0f,
 * 0.0f, -1.0f) for the forward vector and (0.0f, 1.0f, 0.0f)
 * for the up vector. These defaults do not imply a prefered 
 * coordinate system.
 *
 * \param nvar [this] The NVAR processing context
 * \param location [in] The location of the listener
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p nvar is not a valid
 *         context.
 * \retval ::NVAR_STATUS_ERROR A generic error has occurred.
 */
nvarStatus_t NVAR_API
nvarSetListenerLocation(nvar_t nvar, const nvarFloat3_t location);

/**
 * \brief Gets the orientation of the listener
 *
 * Returns the orientation of the listener in the
 * scene.  
 *
 * \param nvar [this] The NVAR processing context
 * \param pForward [out] Returned forward orientation of the
 *        listener
 * \param pUp [out] Returned up orientation of the listener
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p nvar is not a valid
 *         context, or \p pForward or \p pUp is NULL.
 */
nvarStatus_t NVAR_API
nvarGetListenerOrientation(nvar_t nvar, nvarFloat3_t* pForward, nvarFloat3_t* pUp);

/**
 * \brief Sets the orientation of the listener
 *
 * Sets the forward and up orthogonal orientation
 * vectors of the listener in the scene.  The forward vector is
 * directed away from the listener in the direction the listener
 * is facing. The up vector is directed away from the top of
 * listener. The specified vectors must be orthogonal.
 *
 * \param nvar [this] The NVAR processing context
 * \param forward [in] The forward orientation of the listener
 * \param up [in] The up orientation of the listener
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p nvar is not a valid
 *         context, or \p forward and \p up are not orthogonal.
 * \retval ::NVAR_STATUS_ERROR A generic error has occurred.
 */
nvarStatus_t NVAR_API
nvarSetListenerOrientation(nvar_t nvar, const nvarFloat3_t forward, const nvarFloat3_t up);

/**
 * \brief Traces the audio paths between the listener and the
 *        sound sources
 *
 * Schedule an acoustic trace. Acoustic traces are the main 
 * computation of NVAR that trace paths between all sources and 
 * the listener in the specified geometry. The result of an acoustic
 * trace is a set of filters.
 *
 * ::nvarTraceAudio returns once the trace has been added to the
 * asynchronous command queue. The trace will be run asynchronously to the
 * calling thread. If \p traceDoneEvent is not NULL, the Windows event passed
 * in that argument will be signaled by a call to SetEvent()
 * once the trace scheduled by this call is completeted. 
 *
 * Because traceAudio commands are enqueued, applications should use
 * the \p traceDoneEvent or ::nvarSynchronize to
 * ensure that previously started traces are completed before issuing 
 * new traces. If ::nvarTraceAudio is called faster  
 * than traces complete, a backlog of traces will accumulate
 * in the command queue.
 * 
 * \param nvar [this] The NVAR processing context
 * \param traceDoneEvent [optional, in] Windows event object
 *        that will be signaled when tracing is complete.
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p nvar is not a valid
 *         context.
  * \retval ::NVAR_STATUS_OUT_OF_RESOURCES An internal allocation
 *         has failed.
 * \retval ::NVAR_STATUS_ERROR A generic error has occurred.
 */
nvarStatus_t NVAR_API 
nvarTraceAudio(nvar_t nvar, HANDLE traceDoneEvent);

/**
* \brief Records an event in nvar command queue.
*
* Adds an event to the asynchronous command queue and triggers
* the specified windows event once all commands in the queue prior
* to the event have been executed. 
*
* \param nvar [this] The NVAR processing context
* \param hEvent [in] The event which is signaled
*
* \retval ::NVAR_STATUS_SUCCESS No error has occurred.
* \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
*         not been called.
* \retval ::NVAR_STATUS_INVALID_VALUE \p nvar is not a valid context
          or \p hEvent is not a valid Windows event.
* \retval ::NVAR_STATUS_ERROR A generic error has occurred.
*/
nvarStatus_t NVAR_API
nvarEventRecord(nvar_t nvar, HANDLE hEvent);

/**
* \brief Wait for nvar command stream to idle
*
* Blocks the calling thread until all activity in the 
* asynchronous command queue has been completed. Can be used
* to ensure synchronization between the NVAR processing context
* and the calling thread. 
*
* \param nvar [this] The NVAR processing context
*
* \retval ::NVAR_STATUS_SUCCESS No error has occurred.
* \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
*         not been called.
* \retval ::NVAR_STATUS_INVALID_VALUE \p nvar is not a valid context
* \retval ::NVAR_STATUS_ERROR A generic error has occurred.
*/
nvarStatus_t NVAR_API
nvarSynchronize(nvar_t nvar);


/** @} */ /* END NVAR_CONTEXT */

/**
 * \defgroup NVAR_MATERIALS Acoustic Material Functions
 *
 *
 * This section describes the material functions of the NVIDIA Acoustic
 * Raytracer application programming interface.
 *
 * @{
 */


/**
 * \brief Creates an acoustic material
 *
 *  Creates an acoustic material with default properties.
 *
 * \param nvar [this] The NVAR processing context
 * \param pMaterial [out] Returned material handle
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p nvar is not a valid context
 *         or \p pMaterial is NULL.
 * \retval ::NVAR_STATUS_OUT_OF_RESOURCES The API is not
 *         able to allocate a new material object.
 */
nvarStatus_t NVAR_API
nvarCreateMaterial(nvar_t nvar, nvarMaterial_t* pMaterial);

/**
 * \brief Creates a predefined acoustic material
 *
 * This function creates an acoustic material with predefined
 * acoustic properties.
 *
 * \param nvar [this] The NVAR processing context
 * \param pMaterial [out] Returned material object
 * \param predefinedMaterial [in] Enumerated predefined
 *        material value
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED \p nvar is not a
 *         valid context, \p pMaterial is NULL, or
 *         \p predefinedMaterial is not in the range
 *         [::NVAR_PREDEFINED_MATERIAL_ABSORBER,
 *         ::NUM_NVAR_PREDEFINED_MATERIALS).
 * \retval ::NVAR_STATUS_OUT_OF_RESOURCES The API is not able to
 *         allocate a new material object.
 */
nvarStatus_t NVAR_API
nvarCreatePredefinedMaterial(nvar_t nvar, nvarMaterial_t* pMaterial,
                             const nvarPredefinedMaterial_t predefinedMaterial);

/**
 * \brief Destroys the specified acoustic material
 *
 * Destroys the specified acoustic material.  The
 * material should not be currently attached to a mesh object.
 *
 * \param material [this] The material object
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p material is not a
 *         valid material object.
 * \retval ::NVAR_STATUS_NOT_READY The material is still
 *         attached to a mesh object.
 */
nvarStatus_t NVAR_API
nvarDestroyMaterial(nvarMaterial_t material);

/**
 * \brief Gets the reflection coefficient of the acoustic
 *        material
 *
 * This function gets the reflection coefficient of the acoustic
 *        material.
 *
 * \param material [this] The material object
 * \param pReflection [out] Returned reflection coefficient
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p material is not a
 *         valid material or \p pReflection is NULL.
 */
nvarStatus_t NVAR_API
nvarGetMaterialReflection(nvarMaterial_t material, float* pReflection);

/**
 * \brief Sets the reflection coefficient of the acoustic
 *        material
 *
 * This function sets the reflection coefficient of the acoustic
 *        material. Physically, this value should be in the range 
 *        [0, 1], and the reflection coefficient and transmission
 *        coefficients should have a sum <= 1.0. The API does not 
 *        enforce this restriction
 *        
 *
 * \param material [this] The material object
 * \param reflection [in] Reflection coefficient
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p material is not a
 *         valid material or \p reflection is not in the range [0.0, 1.0].
 */
nvarStatus_t NVAR_API
nvarSetMaterialReflection(nvarMaterial_t material, const float reflection);


/**
 * \brief Gets the transmission coefficient of the acoustic
 *        material
 *
 * Returns the transmission coefficient of the acoustic
 *        material.
 *
 * \param material [this] The material object
 * \param pReflection [out] Returned transmission coefficient
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p material is not a
 *         valid material or \p pTransmission is NULL.
 */
nvarStatus_t NVAR_API
nvarGetMaterialTransmission(nvarMaterial_t material, float* pTransmission);

/**
 * \brief Sets the transmission coefficient of the acoustic
 *        material
 *
 * This function sets the transmission coefficient of the acoustic
 *        material. Physically, this value should be in the range 
 *        [0, 1], and the reflection coefficient and transmission
 *        coefficients should have a sum <= 1.0. The API does not 
 *        enforce this restriction.
 *
 * \param material [this] The material object
 * \param reflection [in] Transmission coefficient
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p material is not a
 *         valid material or \p transmission is not in the range [0.0, 1.0].
 */
nvarStatus_t NVAR_API
nvarSetMaterialTransmission(nvarMaterial_t material, const float transmission);

/** @} */ /* END NVAR_MATERIAL */


/**
 * \defgroup NVAR_MESH Acoustic Mesh Functions
 *
 *
 * This section describes the acoustic mesh functions of the NVIDIA Acoustic
 * Raytracer application programming interface.
 *
 * @{
 */

/**
 * \brief Creates an acoustic mesh
 *
 * Creates an acoustic mesh from the vertices, faces, and acoustic
 * material. The function scales and places the mesh in the scene
 * using the specified transformation matrix. Changes will be incorporated 
 * into the scene when the next call to ::nvarCommitGeometry 
 * or ::nvarTraceAudio is executed.
 *
 * \param nvar [this] The NVAR processing context
 * \param pMesh [out] Returned mesh object
 * \param transform [in] The transform of the mesh
 * \param vertices [in] The array of vertices
 * \param numVertices [in] The number of \p vertices
 * \param faces [in] The array of faces
 * \param numFaces [in] The number of \p faces
 * \param material [in] The material applied to the mesh
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_INVALID_VALUE Possible causes: \p nvar is not a valid context;
 *         \p pMesh, \p transform, \p vertices, or \p faces
 *         is NULL; the number of \p numVertices is not valid; the number of \p numFaces
 *         is not valid; or the \p material value is not valid.
 * \retval ::NVAR_STATUS_OUT_OF_RESOURCES The API is not able to allocate
 *         a new mesh object.
 */
nvarStatus_t NVAR_API
nvarCreateMesh(nvar_t nvar, nvarMesh_t* pMesh,
               const nvarMatrix4x4_t transform,
               const nvarFloat3_t vertices[],
               const int numVertices,
               const int faces[], const int numFaces,
               nvarMaterial_t material);

/**
 * \brief Destroys the specified acoustic mesh
 *
 * Destroys the specified acoustic mesh and
 * releases any associated resources.  The mesh will be removed from
 * the scene when the next call to ::nvarCommitGeometry or
 * ::nvarTraceAudio is executed.
 *
 * \param mesh Valid mesh handle
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p mesh is not a valid
 *         mesh object.
 */
nvarStatus_t NVAR_API 
nvarDestroyMesh(nvarMesh_t mesh);

/**
 * \brief Gets the acoustic material of the mesh
 *
 * Returns the acoustic material applied to the specified mesh.
 *
 * \param mesh [this] Valid mesh handle
 * \param pMaterial [out] Returned material object
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p mesh is not a valid
 *         mesh or \p pMaterial is NULL.
 */
nvarStatus_t NVAR_API
nvarGetMeshMaterial(nvarMesh_t mesh, nvarMaterial_t* pMaterial);

/**
 * \brief Sets the acoustic material of the mesh
 *
 * Sets acoustic material of the specified mesh.
 *
 * \param mesh [this] Valid mesh handle
 * \param material [in] Valid material handle
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p mesh is not a valid
 *         mesh or \p material is not a valid material.
 */
nvarStatus_t NVAR_API
nvarSetMeshMaterial(nvarMesh_t mesh, nvarMaterial_t material);

/**
 * \brief Gets the transform of the mesh
 *
 * Returns the transformation matrix of the specified mesh.
 *
 * \param mesh [this] Valid mesh handle
 * \param pTransform [out] Returned transformation matrix
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p mesh is not a valid
 *         mesh or \p pTransform is NULL.
 */
nvarStatus_t NVAR_API
nvarGetMeshTransform(nvarMesh_t mesh, nvarMatrix4x4_t* pTransform);

/**
 * \brief Sets the transform of the mesh
 *
 * Sets transformation matrix for the specified mesh object.
 *
 * \param mesh [this] Valid mesh handle
 * \param transform [in] The transformation matrix
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p mesh is not a valid
 *         mesh.
 */
nvarStatus_t NVAR_API
nvarSetMeshTransform(nvarMesh_t mesh, nvarMatrix4x4_t transform);

/** @} */ /* END NVAR_MESH */

/**
 * \defgroup NVAR_SOURCE Sound Source Functions
 *
 *
 * This section describes the sound source functions of the NVIDIA Acoustic
 * Raytracer application programming interface.
 *
 * @{
 */

/**
 * \brief Create a sound source
 *
 * Creates a sound source in the scene.  Sound sources are added
 * at the origin and should be fully initialized (for example, moved to their location,
 * all other paramters set) before the next call to ::nvarTraceAudio.
 *
 * \param nvar [this] The NVAR processing context
 * \param effect [in] The effect applied per source
 * \param pSource [out] Returned sound source
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p nvar is not a valid
 *         context or \p pSource is NULL.
 * \retval ::NVAR_STATUS_OUT_OF_RESOURCES The API is unable to
 *         allocate a new sound source.
 */
nvarStatus_t NVAR_API
nvarCreateSource(nvar_t nvar, nvarEffect_t effect, nvarSource_t* pSource);

/**
 * \brief Destroys the specified sound source
 *
 * Destroys the specified sound source and
 * releases any associated resources.
 *
 * \param source [this] The sound source
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p source is not a
 *         valid sound source.
 */
nvarStatus_t NVAR_API 
nvarDestroySource(nvarSource_t source);

/**
 * \brief Gets the sound source location
 *
 * Returns the location of the sound source in the
 * scene.
 *
 * \param source [this] The sound source
 * \param pLocation [out] Returned location of the sound
 *        source
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p source is not a
 *         valid sound source or \p pLocation is NULL.
 */
nvarStatus_t NVAR_API
nvarGetSourceLocation(nvarSource_t source, nvarFloat3_t* pLocation);

/**
 * \brief Sets the sound source location
 *
 * Sets the location of the sound source in the
 * scene.
 *
 * \param source The sound source
 * \param location [in] The location of the sound source
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p source is not a
 *         valid sound source.
 * \retval ::NVAR_STATUS_ERROR A generic error has occurred.
 */
nvarStatus_t NVAR_API
nvarSetSourceLocation(nvarSource_t source, nvarFloat3_t location);

/**
 * \brief Gets the indirect path gain of the sound source
 *
 * Returns the indirect path gain for the specified sound source.
 * If not set earlier with ::nvarSetSourceIndirectPathGain this returns the
 * default indirect path gain.
 *
 * \param source [this] The sound source
 * \param pGain [out] Returned indirect path gain for the sound source
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p source is not a
 *         valid sound source or \p pContribution is NULL.
 */
nvarStatus_t NVAR_API
nvarGetSourceIndirectPathGain(nvarSource_t source, float* pGain);

/**
 * \brief Sets the gain applied to indirect paths 
 *
 * Sets the gain applied to indirect paths between the specified sound source
 * and the listener. An indirect path is a path which has at least one reflection
 * or transmission point between the source and listener.
 *
 * A value greather than 1.0 has will amplify sound along indirect paths. A value
 * of less than 1.0 will attenuate indirect path audio, that is, reverb. A value of 
 * zero has the effect of disabling reverb for the specified source entirely. 
 * Valid range is [0.0, Inf).
 *
 * If this function is not called for a source, the default value 
 * ::NVAR_DEFAULT_INDIRECT_PATH_GAIN is used.
 *
 * \param source [this] The sound source
 * \param gain [in] The indirect path gain for the sound source
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p source is not a
 *         valid sound source or contribution is not in the range [0.0, Inf).
 * \retval ::NVAR_STATUS_ERROR A generic error has occurred.
 */
nvarStatus_t NVAR_API
nvarSetSourceIndirectPathGain(nvarSource_t source, const float gain);

/**
* \brief Gets the source effect preset of the sound source
*
* Returns the source effect preset for the specified sound source.
*
* \param source [this] The sound source
* \param effectPreset [out] Returned effect preset for the sound source
*
* \retval ::NVAR_STATUS_SUCCESS No error has occurred.
* \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
*         not been called.
* \retval ::NVAR_STATUS_INVALID_VALUE \p source is not a
*         valid sound source or \p pContribution is NULL.
*/
nvarStatus_t NVAR_API
nvarGetSourceEffectPreset(nvarSource_t source, nvarEffect_t *effectPreset);

/**
* \brief Sets the source effect preset of the sound source
*
* Sets the source effect preset. This allows the user to select the strength of
* audio effects to the applied to the processed audio.
*
* If this function is not called for a source, the value sent via nvarCreateSource
* is used.
*
* \param source [this] The sound source
* \param gain [in] The effect preset for the sound source
*
* \retval ::NVAR_STATUS_SUCCESS No error has occurred.
* \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
*         not been called.
* \retval ::NVAR_STATUS_INVALID_VALUE \p source is not a
*         valid sound source or contribution is not in the range [0.0, Inf).
* \retval ::NVAR_STATUS_ERROR A generic error has occurred.
*/
nvarStatus_t NVAR_API
nvarSetSourceEffectPreset(nvarSource_t source, nvarEffect_t effectPreset);

/**
 * \brief Gets the gain applied to the direct path sound
 *
 * Returns the direct path gain of the specified sound source.
 *
 * \param source [this] The sound source
 * \param pGain [out] Returned direct path gain
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p source is not a
 *         valid sound source or \p pMix is NULL.
 */
nvarStatus_t NVAR_API
nvarGetSourceDirectPathGain(nvarSource_t source,  float* pGain);

/**
 * \brief Sets the gain applied to the direct path
 *
 * Sets the gain applied to the direct path audio in the output
 * filter for the specified sound source. Direct path audio is audio
 * which follows an unoccluded straight line between the source and 
 * listener.
 
 * A value of 0.0 has the effect 
 * of disabling the direct sound path. A value of 1.0 incorporates 
 * the direct sound path along with the indirect sound paths. A value
 * greater than 1.0 will amplify the sound on the direct path between
 * the source and listener. Valid range is [0.0, Inf).
 *
 * If this function is not called, a default value of 
 * ::NVAR_DEFAULT_DIRECT_PATH_GAIN  is used for the source.
 *
 * \param source [this] The sound source
 * \param contribution [in] Direct path gain
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p source is not a
 *         valid sound source or \p gain is not in the range
 *         [0.0, Inf).
 * \retval ::NVAR_STATUS_ERROR A generic error has occurred.
 */
nvarStatus_t NVAR_API
nvarSetSourceDirectPathGain(nvarSource_t source, const float gain);

/**
 *  \brief Applies the sound source filters to the input data
 *
 * This function applies the filters generated by
 * ::nvarTraceAudio to the audio samples contained in the
 * input data buffer. The input buffer format is a single 
 * audio channel of floating-point PCM data.
 * \p pIn is an array of at least \p numSamples floating point values.
 *  
 * \p pOut is an array of pointers to output buffers, one buffer for
 * each output channel.  The number of pointers should be
 * nvar_t::channels and the buffer for each channel must
 * be at least sizeof(float) * \p numSamples bytes
 * in size.  
 *
 * To prevent internal reallocations, the value of \p numSamples
 * should not be changed from call to call. The function
 * may be called with
 * \p pOut and \p pIn both NULL to allocate buffers internally for
 * \p numSamples. Calling to allocate before using is an optimization
 * that is not required for correct operation.
 *
 * \param source [this] The sound source
 * \param pOut [out] Returned audio data for each channel
 * \param pIn [in] The input audio data buffer to process
 * \param numSamples [in] The number of audio samples to process
 *        from the input buffer to the output buffer. \p numSamples
 *        must be greater than 0.
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p source is not a valid
 *         context, or a buffer pointer in \p pOut is NULL, or
 *         \p InputBuffer is NULL, or \p numSamples is not in
 *         the range (0, INT_MAX].
 * \retval ::NVAR_STATUS_OUT_OF_RESOURCES An internal allocation
 *         has failed.
 * \retval ::NVAR_STATUS_ERROR A generic error has occurred.
 */
nvarStatus_t NVAR_API
nvarApplySourceFilters(nvarSource_t source,
                       float** pOut, const float* pIn,
                       const int numSamples);


/**
 * \brief Gets the filter array size 
 *
 * Returns the size in bytes of the filter array
 * for the ::nvarGetSourceFilters function call.
 *
 * \param nvar [this] The NVAR processing context
 * \param pFilterArraySize [out] Returned filter array size in bytes
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p nvar is not a valid
 *         context or \p pFilterSize is NULL.
 */
nvarStatus_t NVAR_API
nvarGetSourceFilterArraySize(nvar_t nvar, int* pFilterArraySize);


/**
 * \brief Gets the filters for the sound source
 *
 * This function returns an array of filters that were generated
 * by the call to ::nvarTraceAudio.  The filter array must be
 * at least filterArraySize bytes in size.  This size is returned by the
 * function ::nvarGetSourceFilterArraySize.
 *
 * The number of elements in the filter array is as follows:
 * \code{.c}
 * numFilterArrayElements = filterArraySize / sizeof(float);
 * \endcode
 *
 * The number of elements in each filter is as follows:
 * \code{.c}
 * int numElementsPerChannel = numFilterArrayElements /
 *     numChannels;
 * \endcode
 *
 * The pointer to the filter array for each channel is as follows:
 * \code{.c}
 * float* ptr = &filterArray[numFiltersPerChannel * channel];
 * \endcode
 *
 * \param source [this] The sound source
 * \param filterArray [out] Returned array of filters
 *
 * \retval ::NVAR_STATUS_SUCCESS No error has occurred.
 * \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
 *         not been called.
 * \retval ::NVAR_STATUS_INVALID_VALUE \p source is not a valid
 *      context or \p filterArray \p is NULL.
 * \retval ::NVAR_STATUS_NOT_READY The tracer geometry is not
 *         ready or the audio trace is in progress.
 * \retval ::NVAR_STATUS_ERROR A generic error has occurred.
 */
nvarStatus_t NVAR_API
nvarGetSourceFilters(nvarSource_t source, float filterArray[]);

/**
*  \brief Applies the sound source direct path filters to the input data
*
* This function applies the direct path filters generated by
* ::nvarTraceAudio to the audio samples contained in the
* input data buffer. The input buffer format is a single
* audio channel of floating-point PCM data.
* \p pIn is an array of at least \p numSamples floating point values.
*
* \p pOut is an array of pointers to output buffers, one buffer for
* each output channel.  The number of pointers should be
* nvar_t::channels and the buffer for each channel must
* be at least sizeof(float) * \p numSamples bytes
* in size.
*
* To prevent internal reallocations, the value of \p numSamples
* should not be changed from call to call. The function
* may be called with
* \p pOut and \p pIn both NULL to allocate buffers internally for
* \p numSamples. Calling to allocate before using is an optimization
* that is not required for correct operation.
*
* \param source [this] The sound source
* \param pOut [out] Returned audio data for each channel
* \param pIn [in] The input audio data buffer to process
* \param numSamples [in] The number of audio samples to process
*        from the input buffer to the output buffer. \p numSamples
*        must be greater than 0.
*
* \retval ::NVAR_STATUS_SUCCESS No error has occurred.
* \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
*         not been called.
* \retval ::NVAR_STATUS_INVALID_VALUE \p source is not a valid
*         context, or a buffer pointer in \p pOut is NULL, or
*         \p InputBuffer is NULL, or \p numSamples is not in
*         the range (0, INT_MAX].
* \retval ::NVAR_STATUS_OUT_OF_RESOURCES An internal allocation
*         has failed.
* \retval ::NVAR_STATUS_ERROR A generic error has occurred.
*/
nvarStatus_t NVAR_API
nvarApplySourceDirectPathFilter(nvarSource_t source,
float** pOut, const float* pIn,
const int numSamples);

/**
*  \brief Applies the sound source indirect path filters to the input data
*
* This function applies the indirect path filters generated by
* ::nvarTraceAudio to the audio samples contained in the
* input data buffer. The input buffer format is a single
* audio channel of floating-point PCM data.
* \p pIn is an array of at least \p numSamples floating point values.
*
* \p pOut is an array of pointers to output buffers, one buffer for
* each output channel.  The number of pointers should be
* nvar_t::channels and the buffer for each channel must
* be at least sizeof(float) * \p numSamples bytes
* in size.
*
* To prevent internal reallocations, the value of \p numSamples
* should not be changed from call to call. The function
* may be called with
* \p pOut and \p pIn both NULL to allocate buffers internally for
* \p numSamples. Calling to allocate before using is an optimization
* that is not required for correct operation.
*
* \param source [this] The sound source
* \param pOut [out] Returned audio data for each channel
* \param pIn [in] The input audio data buffer to process
* \param numSamples [in] The number of audio samples to process
*        from the input buffer to the output buffer. \p numSamples
*        must be greater than 0.
*
* \retval ::NVAR_STATUS_SUCCESS No error has occurred.
* \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
*         not been called.
* \retval ::NVAR_STATUS_INVALID_VALUE \p source is not a valid
*         context, or a buffer pointer in \p pOut is NULL, or
*         \p InputBuffer is NULL, or \p numSamples is not in
*         the range (0, INT_MAX].
* \retval ::NVAR_STATUS_OUT_OF_RESOURCES An internal allocation
*         has failed.
* \retval ::NVAR_STATUS_ERROR A generic error has occurred.
*/
nvarStatus_t NVAR_API
nvarApplySourceIndirectPathFilter(nvarSource_t source,
float** pOut, const float* pIn,
const int numSamples);

/**
*  \brief Submits source audio buffer indirect path filtering
*
* This function submits the audio buffers for indirect filtering.
* The indirect path filters generated by
* ::nvarTraceAudio to the audio samples contained in the
* input data buffer. The input buffer format is a single
* audio channel of floating-point PCM data.
* \p pIn is an array of at least \p numSamples floating point values.
*
*
* To prevent internal reallocations, the value of \p numSamples
* should not be changed from call to call.
*
* \param source [this] The sound source
* \param pIn [in] The input audio data buffer to process
* \param numSamples [in] The number of audio samples to process
*        from the input buffer to the output buffer. \p numSamples
*        must be greater than 0.
*
* \retval ::NVAR_STATUS_SUCCESS No error has occurred.
* \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
*         not been called.
* \retval ::NVAR_STATUS_INVALID_VALUE \p source is not a valid
*         context, or \p InputBuffer is NULL, or \p numSamples is not in
*         the range (0, INT_MAX].
* \retval ::NVAR_STATUS_OUT_OF_RESOURCES An internal allocation
*         has failed.
* \retval ::NVAR_STATUS_ERROR A generic error has occurred.
*/
nvarStatus_t NVAR_API
nvarSourceSubmitBuffers(nvarSource_t source, const float* pIn, 
const int numSamples);

/**
*  \brief Applies indirect path filtering to submitted source buffers
*
* This function applies  indirect filtering to all the audio source buffers
* submitted using ::nvarSourceSubmitBuffers api and returns the mixed output.
* The \p numSamples must be same as the one provided during ::nvarSourceSubmitBuffers api.

* \param nvar [this] The NVAR processing context
* \param pOut [out] Returned audio data for each channel
* \param numSamples [in] The number of audio samples to process
*        from the input buffer to the output buffer. \p numSamples
*        must be greater than 0.
*
* \retval ::NVAR_STATUS_SUCCESS No error has occurred.
* \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
*         not been called.
* \retval ::NVAR_STATUS_NOT_READY No Buffers are submitted yet via ::nvarSourceSubmitBuffers
* \retval ::NVAR_STATUS_INVALID_VALUE \p nvar is not a valid
*         context, or \p pOut is NULL, or \p numSamples is not in
*         the range (0, INT_MAX].
* \retval ::NVAR_STATUS_OUT_OF_RESOURCES An internal allocation
*         has failed.
* \retval ::NVAR_STATUS_ERROR A generic error has occurred.
*/
nvarStatus_t NVAR_API
nvarApplyIndirectPathFiltersToSubmittedBuffers(nvar_t nvar, float **pOut, const int numSamples);

/**
* \brief Gets the source's direct path occlusion settings
*
* This function returns the source's direct path occlusion 
* attenuation factor and distance attenuation factor.
*
* \param source [this] The sound source
* \param pOcclusionAttenuation [out] Returned occlusion attenuation factor.
* \param pDistanceAttenuation [out] Returned distance attenuation factor.
*
* \retval ::NVAR_STATUS_SUCCESS No error has occurred.
* \retval ::NVAR_STATUS_NOT_INITIALIZED ::nvarInitialize has
*         not been called.
* \retval ::NVAR_STATUS_INVALID_VALUE \p source is not a valid
*         context, or \p pOcclusionAttenuation is NULL, or
*         \p pDistanceAttenuation is NULL.
* \retval ::NVAR_STATUS_OUT_OF_RESOURCES An internal allocation
*         has failed.
*/
nvarStatus_t NVAR_API
nvarGetSourceOcclusionSettings(nvarSource_t source, float* pOcclusionAttenuation, float* pDistanceAttenuation);
/** @} */ /* END NVAR_SOURCE */


#ifdef __cplusplus
}
#endif

#endif /* __NVAR_H__ */
