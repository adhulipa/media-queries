//
// Created by Aditya Dhulipala on 5/17/15.
//

#ifndef MEDIAQUERIES_RESOURCE_H
#define MEDIAQUERIES_RESOURCE_H

#include <string>

using namespace std;

enum Type {Sample, Query};

/* Resource defines a single resource
 * such as Video or Frame. It should define:
 * 1. Name
 * 2. Width and Height
 * 3. Folder Location
 */

class Resource {

private:
    string Name;
    string FolderLoc;
    Type type;

public:
    //
};


#endif //MEDIAQUERIES_RESOURCE_H
