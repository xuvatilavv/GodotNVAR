#include <Godot.hpp>
#include <Reference.hpp>
#include "nvar.h"

using namespace godot;

class GodotNVAR : public Reference {
    GODOT_CLASS(GodotNVAR, Reference);
public:
    GodotNVAR() { }

    /** `_init` must exist as it is called by Godot. */
    void _init() { }

    /** Print an error to the console **/
    void printError(nvarStatus_t status) {
        const char* title;
        const char* description;
        const char** pTitle = &title;
        const char** pDescription = &description;
        nvarStatus_t titleStatus;
        nvarStatus_t descStatus;

        titleStatus = nvarGetStatusString(pTitle, status);
        if (titleStatus != NVAR_STATUS_SUCCESS) {
            Godot::print("Unspecified error!");
            return;
        }

        descStatus = nvarGetStatusDescription(pDescription, status);

        godot::String message = "Error: ";
        message += *pTitle;
        message += "\n\t";
        message += *pDescription;
        Godot::print(message);
    }
    
    /** Gets the string representation of a status code enum **/
    Variant getStatusString(nvarStatus_t status) {
        const char** statusString;
        nvarStatus_t nvarStatus = nvarGetStatusString(statusString, status);
        return Variant(*statusString);
    }

    /** Gets the string description of a status code **/
    Variant getStatusDescription(nvarStatus_t status) {
        const char** statusDescription;
        nvarStatus_t nvarStatus = nvarGetStatusDescription(statusDescription, status);
        return Variant(*statusDescription);
    }

    /** Gets the NVAR API version **/
    Variant getVersion() {
        nvarStatus_t nvarStatus;
        int version;
        nvarStatus = nvarGetVersion(&version);
        if (nvarStatus == NVAR_STATUS_SUCCESS) {
            return Variant(version);
        } else {
            printError(nvarStatus);
            return Variant();
        }
    }

    /** Returns the number of audio channels in the specified output format.
     *  Currently unused, as the only exising output format is stereo headphones with 2 channels.
     */
    Variant getOutputFormatChannels(nvarOutputFormat_t outputFormat) {
        nvarStatus_t nvarStatus;
        int channels;

        nvarStatus = nvarGetOutputFormatChannels(outputFormat, &channels);
        if (nvarStatus == NVAR_STATUS_SUCCESS) {
            return Variant(channels);
        } else {
            printError(nvarStatus);
            return Variant();
        }
    }

    /** Initializes the NVAR API. Must be called before any other function that can return 
     * ::NVAR_STATUS_NOT_INITIALIZED.
     */
    void initialize(int flags) {
        nvarStatus_t nvarStatus;
        
        nvarStatus = nvarInitialize(flags);
        if (nvarStatus == NVAR_STATUS_SUCCESS) {
            // Success
        } else {
            printError(nvarStatus);
        }
    }

    /** Resets the NVAR API to the default state. **/
    void finalize(void) {
        nvarStatus_t nvarStatus;
        
        nvarStatus = nvarFinalize();
        if (nvarStatus == NVAR_STATUS_SUCCESS) {
            // Success
        } else {
            printError(nvarStatus);
        }
    }

    /** Returns the flags used to initialize the API. **/
    Variant getInitializeFlags(void) {
        nvarStatus_t nvarStatus;
        int flags;
        
        nvarStatus = nvarGetInitializeFlags(&flags);
        if (nvarStatus == NVAR_STATUS_SUCCESS) {
            return Variant(flags);
        } else {
            printError(nvarStatus);
        }
        return Variant();
    }

    /** Returns the number of devices in the system that NVAR can use. **/
    Variant getDeviceCount(void) {
        nvarStatus_t nvarStatus;
        int deviceCount;
        
        nvarStatus = nvarGetDeviceCount(&deviceCount);
        if (nvarStatus == NVAR_STATUS_SUCCESS) {
            return Variant(deviceCount);
        } else {
            printError(nvarStatus);
        }
        return Variant();
    }

    /** Returns an identifer string for a device **/
    Variant getDeviceName(int deviceNumber) {
        nvarStatus_t nvarStatus;
        char name[32];
        
        nvarStatus = nvarGetDeviceName(deviceNumber, name, 32);
        if (nvarStatus == NVAR_STATUS_SUCCESS) {
            return Variant(name);
        } else {
            printError(nvarStatus);
        }
        return Variant();
    }

    /** Gets the preferred NVAR device index **/
    Variant getPreferredDevice() {
        nvarStatus_t nvarStatus;
        int device;

        /** they spelled this function wrong, it's not my fault! **/
        nvarStatus = nvarGetPreferedDevice(NULL, &device);
        if (nvarStatus == NVAR_STATUS_SUCCESS) {
            return Variant(device);
        } else {
            printError(nvarStatus);
        }
        return Variant();
    }

    /** Creates and inits an NVAR processing context **/
    void create(int preset, int device = 0) {
        nvarStatus_t nvarStatus;

        nvarStatus = nvarCreate(&nvar, contextName, sizeof(contextName), 
            static_cast<nvarPreset_t>(preset), &device);
        if (nvarStatus == NVAR_STATUS_SUCCESS) {
            // Success
        } else {
            printError(nvarStatus);
        }
    }

    /** Destroys an NVAR processing context **/
    void destroy() {
        nvarStatus_t nvarStatus;

        nvarStatus = nvarDestroy(nvar);
        if (nvarStatus == NVAR_STATUS_SUCCESS) {
            // Success
        } else {
            printError(nvarStatus);
        }
    }

    /** Gets the CUDA device number from the NVAR processing context **/
    Variant getDeviceNum() {
        nvarStatus_t nvarStatus;
        int deviceNum;

        nvarStatus = nvarGetDeviceNum(nvar, &deviceNum);
        if (nvarStatus == NVAR_STATUS_SUCCESS) {
            return Variant(deviceNum);
        } else {
            printError(nvarStatus);
        }
        return Variant();
    }

    /** Gets the reverb length in seconds **/
    Variant getReverbLength() {
        nvarStatus_t nvarStatus;
        float reverbLength;

        nvarStatus = nvarGetReverbLength(nvar, &reverbLength);
        if (nvarStatus == NVAR_STATUS_SUCCESS) {
            return Variant(reverbLength);
        } else {
            printError(nvarStatus);
        }
        return Variant();
    }

    /** Sets the reverb length in seconds. Changing this is expensive,
     *  for realtime this should be set before creating any sources. 
     */
    void setReverbLength(float reverbLength) {
        nvarStatus_t nvarStatus;

        nvarStatus = nvarSetReverbLength(nvar, reverbLength);
        if (nvarStatus == NVAR_STATUS_SUCCESS) {
            // Success
        } else {
            printError(nvarStatus);
        }
    }

    /** Returns the sample rate in samples per second. **/
    Variant getSampleRate() {
        nvarStatus_t nvarStatus;
        int sampleRate;

        nvarStatus = nvarGetSampleRate(nvar, &sampleRate);
        if (nvarStatus == NVAR_STATUS_SUCCESS) {
            return Variant(sampleRate);
        } else {
            printError(nvarStatus);
        }
        return Variant();
    }

    /** Sets the sample rate in samples per second. Changings this is expensive,
     *  for realtime this should be set before creating any sources. 
     */
    void setSampleRate(int sampleRate) {
        nvarStatus_t nvarStatus;

        nvarStatus = nvarSetSampleRate(nvar, sampleRate);
        if (nvarStatus == NVAR_STATUS_SUCCESS) {
            //
        } else {
            printError(nvarStatus);
        }
    }

    /** Returns the output format **/
    Variant getOutputFormat() {
        nvarStatus_t nvarStatus;
        nvarOutputFormat_t outputFormat;

        nvarStatus = nvarGetOutputFormat(nvar, &outputFormat);
        if (nvarStatus == NVAR_STATUS_SUCCESS) {
            return Variant(static_cast<int>(outputFormat));
        } else {
            printError(nvarStatus);
        }
        return Variant();
    }

    /** Sets the output format of filters. Changings this is expensive,
     *  for realtime this should be set before creating any sources. 
     */
    void setOutputFormat(int outputFormat) {
        nvarStatus_t nvarStatus;

        nvarStatus = nvarSetSampleRate(nvar, static_cast<nvarOutputFormat_t>(outputFormat));
        if (nvarStatus == NVAR_STATUS_SUCCESS) {
            // Success
        } else {
            printError(nvarStatus);
        }
    }

    /** Returns the reverb decay factor **/
    Variant getDecayFactor() {
        nvarStatus_t nvarStatus;
        float decayFactor;

        nvarStatus = nvarGetDecayFactor(nvar, &decayFactor);
        if (nvarStatus == NVAR_STATUS_SUCCESS) {
            return Variant(decayFactor);
        } else {
            printError(nvarStatus);
        }
        return Variant();
    }

    /** Sets the reverb decay factor **/
    void setDecayFactor(float decayFactor) {
        nvarStatus_t nvarStatus;

        nvarStatus = nvarSetDecayFactor(nvar, decayFactor);
        if (nvarStatus == NVAR_STATUS_SUCCESS) {
            // Success
        } else {
            printError(nvarStatus);
        }
    }

    /** Gets unit length in meters per geometry unit **/
    Variant getUnitLength() {
        nvarStatus_t nvarStatus;
        float ratio;

        nvarStatus = nvarGetUnitLength(nvar, &ratio);
        if (nvarStatus == NVAR_STATUS_SUCCESS) {
            return Variant(ratio);
        } else {
            printError(nvarStatus);
        }
        return Variant();
    }

    /** Sets unit length in meters per geometry unit **/
    void setUnitLength(float ratio) {
        nvarStatus_t nvarStatus;

        nvarStatus = nvarSetUnitLength(nvar, ratio);
        if (nvarStatus == NVAR_STATUS_SUCCESS) {
            // Success
        } else {
            printError(nvarStatus);
        }
    }

    /** Updates the scene's acoustic geometry **/
    void commitGeometry() {
        nvarStatus_t nvarStatus;

        nvarStatus = nvarCommitGeometry(nvar);
        if (nvarStatus == NVAR_STATUS_SUCCESS) {
            // Success
        } else {
            printError(nvarStatus);
        }
    }

    /** Exports NVAR geometry to Wavefront .obj file. **/
    void exportOBJs(String objFileBaseName) {
        nvarStatus_t nvarStatus;
        const char* thing = objFileBaseName.alloc_c_string();

        nvarStatus = nvarExportOBJs(nvar, thing);
        if (nvarStatus == NVAR_STATUS_SUCCESS) {
            // Success
        } else {
            printError(nvarStatus);
        }
    }

    /** Returns the location of the listener in the scene **/
    Variant getListenerLocation() {
        nvarStatus_t nvarStatus;
        nvarFloat3_t location;

        nvarStatus = nvarGetListenerLocation(nvar, &location);
        if (nvarStatus == NVAR_STATUS_SUCCESS) {
            return Variant(Vector3(location.x, location.y, location.z));
        } else {
            printError(nvarStatus);
        }
        return Variant();
    }

    /** Sets the location of the listener in the scene **/
    void setListenerLocation(Vector3 location) {
        nvarStatus_t nvarStatus;
        nvarFloat3_t nLocation;
        nLocation.x = location.x;
        nLocation.y = location.y;
        nLocation.z = location.z;

        nvarStatus = nvarSetListenerLocation(nvar, nLocation);
        if (nvarStatus == NVAR_STATUS_SUCCESS) {
            // Success
        } else {
            printError(nvarStatus);
        }
    }

    /** Returns the forward axis of the listener in the scene **/
    Variant getlistenerForwardAxis() {
        nvarStatus_t nvarStatus;
        nvarFloat3_t forward;
        nvarFloat3_t up;

        nvarStatus = nvarGetListenerOrientation(nvar, &forward, &up);
        if (nvarStatus == NVAR_STATUS_SUCCESS) {
            return Variant(Vector3(forward.x, forward.y, forward.z));
        } else {
            printError(nvarStatus);
        }
        return Variant();
    }

    /** Returns the forward axis of the listener in the scene **/
    Variant getlistenerUpAxis() {
        nvarStatus_t nvarStatus;
        nvarFloat3_t forward;
        nvarFloat3_t up;

        nvarStatus = nvarGetListenerOrientation(nvar, &forward, &up);
        if (nvarStatus == NVAR_STATUS_SUCCESS) {
            return Variant(Vector3(up.x, up.y, up.z));
        } else {
            printError(nvarStatus);
        }
        return Variant();
    }

    /** Sets the location of the listener in the scene **/
    void setListenerOrientation(Vector3 forwardAxis, Vector3 upAxis) {
        nvarStatus_t nvarStatus;
        nvarFloat3_t nForwardAxis;
        nvarFloat3_t nUpAxis;
        nForwardAxis.x = forwardAxis.x;
        nForwardAxis.y = forwardAxis.y;
        nForwardAxis.z = forwardAxis.z;
        nUpAxis.x = upAxis.x;
        nUpAxis.y = upAxis.y;
        nUpAxis.z = upAxis.z;

        nvarStatus = nvarSetListenerOrientation(nvar, nForwardAxis, nUpAxis);
        if (nvarStatus == NVAR_STATUS_SUCCESS) {
            // Success
        } else {
            printError(nvarStatus);
        }
    }

    /** Queue a trace of the audio paths between listener and sound sources **/
    void traceAudio() {
        nvarStatus_t nvarStatus;

        nvarStatus = nvarTraceAudio(nvar, NULL);
        if (nvarStatus == NVAR_STATUS_SUCCESS) {
            // Success
        } else {
            printError(nvarStatus);
        }
    }

    /** Records an event in nvar command queue **/
    void eventRecord(HANDLE hEvent) {
        // Not sure how to implement this, or if it's useful in Godot, so I won't.
        // nvarEventRecord
    }

    /** Blocks calling thread until nvar command stream is idle **/
    void synchronize() {
        nvarStatus_t nvarStatus;

        nvarStatus = nvarSynchronize(nvar);
        if (nvarStatus == NVAR_STATUS_SUCCESS) {
            // Success
        } else {
            printError(nvarStatus);
        }
    }

    /** Register methods, members, and signals to expose them to Godot **/
    static void _register_methods() {
        register_method("get_version", &GodotNVAR::getVersion);
        register_method("initialize", &GodotNVAR::initialize);
        register_method("finalize", &GodotNVAR::finalize);
        register_method("get_initialize_flags", &GodotNVAR::getInitializeFlags);
        register_method("get_device_count", &GodotNVAR::getDeviceCount);
        register_method("get_device_name", &GodotNVAR::getDeviceName);
        register_method("get_preferred_device", &GodotNVAR::getPreferredDevice);
        register_method("create", &GodotNVAR::create);
        register_method("destroy", &GodotNVAR::destroy);
        register_method("get_device_num", &GodotNVAR::getDeviceNum);
        register_method("get_reverb_length", &GodotNVAR::getReverbLength);
        register_method("set_reverb_length", &GodotNVAR::setReverbLength);
        register_method("get_sample_rate", &GodotNVAR::getSampleRate);
        register_method("set_sample_rate", &GodotNVAR::setSampleRate);
        register_method("get_output_format", &GodotNVAR::getOutputFormat);
        register_method("set_output_format", &GodotNVAR::setOutputFormat);
        register_method("get_decay_factor", &GodotNVAR::getDecayFactor);
        register_method("set_decay_factor", &GodotNVAR::setDecayFactor);
        register_method("get_unit_length", &GodotNVAR::getUnitLength);
        register_method("set_unit_length", &GodotNVAR::setUnitLength);
        register_method("commit_geometry", &GodotNVAR::commitGeometry);
        register_method("export_objs", &GodotNVAR::exportOBJs);
        register_method("get_listener_location", &GodotNVAR::getListenerLocation);
        register_method("set_listener_location", &GodotNVAR::setListenerLocation);
        register_method("get_listener_forward_axis", &GodotNVAR::getlistenerForwardAxis);
        register_method("get_listener_up_axis", &GodotNVAR::getlistenerUpAxis);
        register_method("set_listener_orientation", &GodotNVAR::setListenerOrientation);
        register_method("trace_audio", &GodotNVAR::traceAudio);
        register_method("synchronize", &GodotNVAR::synchronize);

        /**
         * The line below is equivalent to the following GDScript export:
         *     export var _name = "GodotNVAR"
         **/
        register_property<GodotNVAR, String>("base/name", &GodotNVAR::_name, String("GodotNVAR"));

        /** Alternatively, with getter and setter methods: */
        register_property<GodotNVAR, int>("base/value", &GodotNVAR::set_value, &GodotNVAR::get_value, 0);

        /** Registering a signal: **/
        // register_signal<GodotNVAR>("signal_name");
        // register_signal<GodotNVAR>("signal_name", "string_argument", GODOT_VARIANT_TYPE_STRING)
    }

    String _name;
    int _value;

    void set_value(int p_value) {
        _value = p_value;
    }

    int get_value() const {
        return _value;
    }

    nvar_t nvar;
    const char* contextName = "GodotNVAR";
};

/** GDNative Initialize **/
extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
    godot::Godot::gdnative_init(o);
}

/** GDNative Terminate **/
extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
    godot::Godot::gdnative_terminate(o);
}

/** NativeScript Initialize **/
extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
    godot::Godot::nativescript_init(handle);

    godot::register_class<GodotNVAR>();
}