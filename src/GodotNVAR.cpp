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

    Variant method(Variant arg) {
        Variant ret;
        ret = arg;
        Godot::print("It loads!");
        return ret;
    }

    static void _register_methods() {
        register_method("method", &GodotNVAR::method);

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