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

    /** Register methods, members, and signals to expose them to Godot **/
    static void _register_methods() {
        register_method("get_version", &GodotNVAR::getVersion);
        register_method("initialize", &GodotNVAR::initialize);
        register_method("finalize", &GodotNVAR::finalize);
        register_method("get_initialize_flags", &GodotNVAR::getInitializeFlags);
        register_method("get_device_count", &GodotNVAR::getDeviceCount);
        register_method("get_device_name", &GodotNVAR::getDeviceName);
        register_method("get_preferred_device", &GodotNVAR::getPreferredDevice);

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