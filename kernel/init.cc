#include "init.h"
#include "elf.h"
#include "machine.h"
#include "fs.h"
#include "libk.h"

Init::Init() : Process("init",nullptr) {
}

long Init::run() {
    SimpleQueue<const char*> argv;
    argv.addTail(K::strdup("admin"));

    //argv.addTail(K::strdup("shell"));
    argv.addTail(K::strdup("chuser"));

    //execv("shell",&argv,2);
    execv("chuser", &argv, 2);

    Debug::shutdown("What?");
    return 0;
}
