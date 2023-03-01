
package org.kiwix;

import java.lang.ref.Cleaner;

public class Wrapper implements AutoCloseable {
    private static final Cleaner cleaner = Cleaner.create();
    protected static class Resource implements Runnable {
        Resource(int classid, long nativeHandle) {
            this.classid = classid;
            this.nativeHandle = nativeHandle;
        }

        public void run() {
            dispose();
        }
        // The pointer (as a long) to the native handle (the shared_ptr)
        private long nativeHandle;

        // The name of the class.
        // We need it to cast our pointer to the right type.
        private int classid;

        // The native method wich will actually delete the cpp resource.
        private native void dispose();
    }


    private final Resource nativeResource;
    private final Cleaner.Cleanable cleanable;

    public Wrapper(Resource resource) {
        this.nativeResource = resource;
        this.cleanable = cleaner.register(this, nativeResource);
    }

    public void close() {
        cleanable.clean();
    }
}
