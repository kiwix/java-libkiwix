
package org.kiwix;

import java.lang.ref.Cleaner;

public class IterWrapper implements AutoCloseable {
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


    private final Resource nativeResourceBegin;
    private final Cleaner.Cleanable cleanableBegin;

    private final Resource nativeResourceEnd;
    private final Cleaner.Cleanable cleanableEnd;

    public IterWrapper(Resource resourceBegin, Resource resourceEnd) {
        this.nativeResourceBegin = resourceBegin;
        this.cleanableBegin = cleaner.register(this, nativeResourceBegin);
        this.nativeResourceEnd = resourceEnd;
        this.cleanableEnd = cleaner.register(this, nativeResourceEnd);
    }

    public void close() {
        cleanableBegin.clean();
        cleanableEnd.clean();
    }
}
