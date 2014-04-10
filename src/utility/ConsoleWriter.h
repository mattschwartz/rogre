#ifndef _CONSOLEWRITER_H_
#define _CONSOLEWRITER_H_

/**
 * Included files
 */
#include <iostream>
#include <string>

/**
 * Defines
 */
#define V_NONE 0
#define V_ERROR_ONLY 1
#define V_ALL 2

/**
 * Data
 */
using namespace std;

namespace ConsoleWriter {
    int verbosity = V_ALL;

    static void writeLine(string s) {
        if (verbosity >= V_ALL) {
            cout << " [INFO] " << s << endl;
        } // if
    } // writeLine

    static void writeError(string s) {
        if (verbosity >= V_ERROR_ONLY) {
            cout << " [ERROR] " << s << endl;
        } // if
    } // writeError
};

#endif
