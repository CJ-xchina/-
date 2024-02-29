typedef void* VoidPtr;
int a = 1;

void *vp1 = &a;
VoidPtr vp2 = &a;

void *foo() {
    int *ip = &a;
    if (static_cast<void*>(ip) != nullptr) {
        return static_cast<VoidPtr>(ip);
    }
    return nullptr;
}