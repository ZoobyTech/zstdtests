#include <ZoobyTech/ZoobyTech/specs.h>
#include <ZoobyTech/debug.h>
#include <ZoobyTech/io.h>
#include <ZoobyTech/scheduler.h>
#include <ZoobyTech/printf.h>

int main()
{
    info("Resolving specs...");
    zoobyResolveSpecs();
    info("Serializing specs...");
    struct zoobySpecSerialized specs = zoobySerializeSpecs();
    info("\nOutputting specs...");
    putstr(specs.serial,specs.length);
    info("\n\n");

};

#include <ZoobyTech/zoobyBin.h>
