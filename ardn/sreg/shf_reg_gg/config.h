
// use #undef FASTDEMO for a more relaxed display of messages
#define FASTDEMO -1
#undef  FASTDEMO

// use #undef BASIC_POV_TECHNIQUE_DEMO to run without expsing POV techniques
#define BASIC_POV_TECHNIQUE_DEMO -1
#undef  BASIC_POV_TECHNIQUE_DEMO


//  ////////////////////////////////////////////////////////////////////////

#ifdef BASIC_POV_TECHNIQUE_DEMO
    #define EXPOSE_DIGIT_PAINTING -1
    // duration will be doubled in terms of iteration of message:
    #define DURATION 2
    #define REPETITIONS 1
#else
    #define EXPOSE_DIGIT_PAINTING  0
    #ifndef FASTDEMO
        #define DURATION 255
    #else
        #define DURATION 77
    #endif
    #define REPETITIONS 2
#endif

