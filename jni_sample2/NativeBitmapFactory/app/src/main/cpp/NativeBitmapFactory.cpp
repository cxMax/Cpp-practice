/**
 * this codes are picked up from https://github.com/Bilibili/NativeBitmapFactory/blob/DFM/jni/NativeBitmapFactory.cpp
 * just for better known of JNI and C++
 * Created by caixi on 17-9-5.
 *
 */
#include <jni.h>
#include <dlfcn.h>
#include <stdint.h>
#include <malloc.h>
#include <android/log.h>
#include "NativeBitmapFactory.h"

#define SUCCESS 0
#define EGENERIC -1
#define ENOMEM -2
#define SIZE_OF_SKBITMAP 256

typedef void (*SkBitmap_ctor)(void *);

typedef void (*SkBitmap_dtor)(void *);

typedef void (*SkBitmap_setConfig)(void *, int, int, int, int);

typedef void (*SkBitmap_setConfig_19later)(void *, int, int, int, size_t, uint8_t);

typedef void (*SkBitmap_setInfo)(void *, int *, int);

typedef void (*SkBitmap_allocPixels)(void *, void *, void *);

typedef void (*SkBitmap_eraseARGB)(void *, size_t, size_t, size_t, size_t);

typedef jobject (*GraphicsJNI_createBitmap)(void *, void *, int, void *, int);

typedef jobject (*GraphicsJNI_createBitmap_19later)(void *, void *, void *, int, void *, void *,
                                                    int);

enum SkAlphaType {

    kIgnore_SkAlphaType,

    kOpaque_SkAlphaType,

    kPremul_SkAlphaType,

    kUnpremul_SkAlphaType,

    kLastEnum_SkAlphaType = kUnpremul_SkAlphaType
};

enum SkColorType {
    kUnknown_SkColorType,
    kAlpha_8_SkColorType,
    kRGB_565_SkColorType,
    kARGB_4444_SkColorType,
    kRGBA_8888_SkColorType,
    kBGRA_8888_SkColorType,
    kIndex_8_SkColorType,

    kLastEnum_SkColorType = kIndex_8_SkColorType,

    kN32_SkColorType = kRGBA_8888_SkColorType,
#ifdef SK_SUPPORT_LEGACY_N32_NAME
    kPMColor_SkColorType = kN32_SkColorType
#endif
};

static int SkBitmapConfigToColorType(int config) {
    static const SkColorType gCT[] = {
            kUnknown_SkColorType,   // kNo_Config
            kAlpha_8_SkColorType,   // kA8_Config
            kIndex_8_SkColorType,   // kIndex8_Config
            kRGB_565_SkColorType,   // kRGB_565_Config
            kARGB_4444_SkColorType, // kARGB_4444_Config
            kN32_SkColorType,   // kARGB_8888_Config
    };
    return gCT[config];
}

struct skbitmap_sys_t {
    void *libskia;
    SkBitmap_ctor sk_ctor;
    SkBitmap_dtor sk_dtor;
    SkBitmap_setConfig sk_setConfig;
    SkBitmap_setConfig_19later sk_setConfig_19later;
    SkBitmap_setInfo sk_setInfo;
    SkBitmap_allocPixels sk_allocPixels;
    SkBitmap_eraseARGB sk_eraseARGB;

    void *libjnigraphics;
    GraphicsJNI_createBitmap gjni_createBitmap;
    GraphicsJNI_createBitmap_19later gjni_createBitmap_19later;
};

struct ndkbitmap_object_t {
    skbitmap_sys_t *sys;
};

static void *InitLibrary(struct skbitmap_sys_t *p_sys) {
    /* DL Open libskia */
    void *p_library;
    p_library = dlopen("libskia.so", RTLD_NOW | RTLD_LOCAL);
    if (!p_library)
        return NULL;

    /* Register symbols */
    p_sys->sk_ctor = (SkBitmap_ctor) (dlsym(p_library, "_ZN8SkBitmapC1Ev"));
    p_sys->sk_dtor = (SkBitmap_dtor) (dlsym(p_library, "_ZN8SkBitmapD1Ev"));
    p_sys->sk_setConfig = (SkBitmap_setConfig) (dlsym(p_library,
                                                      "_ZN8SkBitmap9setConfigENS_6ConfigEiii"));
    if (!p_sys->sk_setConfig) {
        p_sys->sk_setConfig = (SkBitmap_setConfig) (dlsym(p_library,
                                                          "_ZN8SkBitmap9setConfigENS_6ConfigEiij"));
    }
    p_sys->sk_setConfig_19later = (SkBitmap_setConfig_19later) (dlsym(p_library,
                                                                      "_ZN8SkBitmap9setConfigENS_6ConfigEiij11SkAlphaType"));
    if (!p_sys->sk_setConfig && !p_sys->sk_setConfig_19later) {
        p_sys->sk_setInfo = (SkBitmap_setInfo) (dlsym(p_library,
                                                      "_ZN8SkBitmap7setInfoERK11SkImageInfoj"));
    }

    p_sys->sk_allocPixels = (SkBitmap_allocPixels) (dlsym(p_library,
                                                          "_ZN8SkBitmap11allocPixelsEPNS_9AllocatorEP12SkColorTable"));
    if (!p_sys->sk_allocPixels) {    // for Nexus Android M Preview
        p_sys->sk_allocPixels = (SkBitmap_allocPixels) (dlsym(p_library,
                                                              "_ZN8SkBitmap14tryAllocPixelsEPNS_9AllocatorEP12SkColorTable"));
    }
    p_sys->sk_eraseARGB = (SkBitmap_eraseARGB) (dlsym(p_library, "_ZNK8SkBitmap9eraseARGBEjjjj"));

    __android_log_print(ANDROID_LOG_INFO, "NativeBitmapFactory",
                        "[libskia] ctor:%p,dtor:%p,setConfig:%p,setConfig_19later:%p,setInfo:%p,allocPixels:%p,eraseARGB:%p",
                        p_sys->sk_ctor, p_sys->sk_dtor,
                        p_sys->sk_setConfig, p_sys->sk_setConfig_19later, p_sys->sk_setInfo,
                        p_sys->sk_allocPixels, p_sys->sk_eraseARGB);
    // We need all the Symbols
    if (!(p_sys->sk_ctor && p_sys->sk_dtor
          && (p_sys->sk_setConfig || p_sys->sk_setConfig_19later || p_sys->sk_setInfo)
          && p_sys->sk_allocPixels && p_sys->sk_eraseARGB)) {
        __android_log_print(ANDROID_LOG_ERROR, "NativeBitmapFactory", "InitLibrary dlsym failed");
        dlclose(p_library);
        return NULL;
    }
    return p_library;
}

static void *InitLibrary2(struct skbitmap_sys_t *p_sys) {
    /* DL Open libjnigraphics */
    void *p_library;
    p_library = dlopen("libandroid_runtime.so", RTLD_NOW | RTLD_LOCAL);
    if (!p_library)
        return NULL;

    /* Register symbols */
    p_sys->gjni_createBitmap = (GraphicsJNI_createBitmap) (dlsym(p_library,
                                                                 "_ZN11GraphicsJNI12createBitmapEP7_JNIEnvP8SkBitmapbP11_jbyteArrayi"));
    if (!p_sys->gjni_createBitmap) {
        p_sys->gjni_createBitmap = (GraphicsJNI_createBitmap) (dlsym(p_library,
                                                                     "_ZN11GraphicsJNI12createBitmapEP7_JNIEnvP8SkBitmapiP11_jbyteArrayi"));
    }

    p_sys->gjni_createBitmap_19later = (GraphicsJNI_createBitmap_19later) (dlsym(p_library,
                                                                                 "_ZN11GraphicsJNI12createBitmapEP7_JNIEnvP8SkBitmapP11_jbyteArrayiS5_P10_jintArrayi"));
    if (!p_sys->gjni_createBitmap_19later) {
        p_sys->gjni_createBitmap_19later = (GraphicsJNI_createBitmap_19later) (dlsym(p_library,
                                                                                     "_ZN11GraphicsJNI12createBitmapEP7_JNIEnvP8SkBitmapP11_jbyteArrayiS5_P8_jobjecti"));
    }

    __android_log_print(ANDROID_LOG_INFO, "NativeBitmapFactory",
                        "[GraphicsJNI] createBitmap:%p,createBitmap_19later:%p",
                        p_sys->gjni_createBitmap,
                        p_sys->gjni_createBitmap_19later);

    // We need all the Symbols
    if (!p_sys->gjni_createBitmap && !p_sys->gjni_createBitmap_19later) {
        __android_log_print(ANDROID_LOG_ERROR, "NativeBitmapFactory", "InitLibrary2 dlsym failed");
        p_sys->gjni_createBitmap = NULL;
        p_sys->gjni_createBitmap_19later = NULL;
        dlclose(p_library);
        return NULL;
    }
    return p_library;
}

ndkbitmap_object_t *ndkbitmap_obj;


static int Open(ndkbitmap_object_t *obj) {
    skbitmap_sys_t *sys = (skbitmap_sys_t *) malloc(sizeof(*sys));

    if (sys == NULL)
        return ENOMEM;

    sys->libskia = InitLibrary(sys);
    if (sys->libskia == NULL) {
        free(sys);
        return EGENERIC;
    }
    sys->libjnigraphics = InitLibrary2(sys);
    if (sys->libjnigraphics == NULL) {
        free(sys);
        return EGENERIC;
    }

    obj->sys = sys;
    return SUCCESS;
}

static void Close(ndkbitmap_object_t *obj) {
    skbitmap_sys_t *sys = obj->sys;

    if (sys == NULL) {
        return;
    }
    if (sys->libjnigraphics) {
        dlclose(sys->libjnigraphics);
        sys->libjnigraphics = NULL;
    }
    if (sys->libskia) {
        dlclose(sys->libskia);
        sys->libskia = NULL;
    }
    free(sys);
}

static int Start() {
    ndkbitmap_obj = (ndkbitmap_object_t *) malloc(sizeof(*ndkbitmap_obj));
    int r = Open(ndkbitmap_obj);
    if (r != SUCCESS) {
        if (ndkbitmap_obj) {
            free(ndkbitmap_obj);
            ndkbitmap_obj = NULL;
        }
        return ENOMEM;
    }
    return SUCCESS;
}

static int Stop() {
    if (ndkbitmap_obj == NULL) {
        return SUCCESS;
    }
    Close(ndkbitmap_obj);
    free(ndkbitmap_obj);
    ndkbitmap_obj = NULL;
    return SUCCESS;
}

inline void *createSkBitmap(ndkbitmap_object_t *obj, int config, int w, int h) {
    skbitmap_sys_t *p_sys = obj->sys;
    if (p_sys == NULL || p_sys->libskia == NULL) {
        return NULL;
    }
    void *skBitmap = malloc(SIZE_OF_SKBITMAP);
    if (!skBitmap) {
        return NULL;
    }
    *((uint32_t *) ((uint32_t) skBitmap + SIZE_OF_SKBITMAP - 4)) = 0xbaadbaad;
    //ctor
    p_sys->sk_ctor(skBitmap);
    if (p_sys->sk_setConfig) {
        p_sys->sk_setConfig(skBitmap, config, w, h, 0);
    } else if (p_sys->sk_setConfig_19later) {
        p_sys->sk_setConfig_19later(skBitmap, config, w, h, 0, (uint8_t) kPremul_SkAlphaType);
    } else if (p_sys->sk_setInfo) {
        int imageInfo[4] = {w, h, SkBitmapConfigToColorType(config), kPremul_SkAlphaType};
        p_sys->sk_setInfo(skBitmap, imageInfo, 0);
    }
    p_sys->sk_allocPixels(skBitmap, NULL, NULL);
    p_sys->sk_eraseARGB(skBitmap, 0, 0, 0, 0);


    if (!(*((uint32_t *) ((uint32_t) skBitmap + SIZE_OF_SKBITMAP - 4)) == 0xbaadbaad)) {
        free(skBitmap);
        return NULL;
    }

    return skBitmap;
}

jboolean JNICALL
Java_com_cxmax_nativebitmapfactory_NativeBitmapFactory_init(JNIEnv *env) {
#ifdef defined(__arm__)
    __android_log_print(ANDROID_LOG_INFO, "NativeBitmapFactory", "Loaded libndkbitmap.so arch is: ARM");
#elif defined(__i386__)
    __android_log_print(ANDROID_LOG_INFO, "NativeBitmapFactory", "Loaded libndkbitmap.so arch is: x86");
#endif
    int r = Start();
    return r == SUCCESS;
}

jboolean JNICALL
Java_com_cxmax_nativebitmapfactory_NativeBitmapFactory_release(JNIEnv *env) {
    int r = Stop();
    return r == SUCCESS;
}

jobject createBitmap(JNIEnv *env, jobject obj, jint w, jint h, jint config, jboolean hasAlpha,
                     int isMuttable, int api) {
    void *bm = createSkBitmap(ndkbitmap_obj, config, w, h);
    if (bm == NULL) {
        return NULL;
    }
    jobject result = NULL;
    skbitmap_sys_t *p_sys = ndkbitmap_obj->sys;
    if (p_sys->libjnigraphics) {
        if (p_sys->gjni_createBitmap) {
            result = p_sys->gjni_createBitmap(env, bm, isMuttable, NULL, -1);
        } else if (p_sys->gjni_createBitmap_19later) {
            result = p_sys->gjni_createBitmap_19later(env, bm, NULL, isMuttable, NULL, NULL, -1);
        }

    }

    return result;
}

jobject JNICALL
Java_com_cxmax_nativebitmapfactory_NativeBitmapFactory_createBitmap(JNIEnv *env, jobject obj,
                                                                    jint w, jint h, jint config,
                                                                    jboolean hasAlpha) {
    return createBitmap(env, obj, w, h, config, hasAlpha, true, 0);
}

jobject JNICALL
Java_com_cxmax_nativebitmapfactory_NativeBitmapFactory_createBitmap19(JNIEnv *env, jobject obj,
                                                                      jint w, jint h, jint config,
                                                                      jboolean hasAlpha) {
    return createBitmap(env, obj, w, h, config, hasAlpha, 0x3, 19);
}


