package org.kiwix.libkiwix;

import org.kiwix.libzim.Archive;

public class SpellingsDB {
    public SpellingsDB(Archive archive, String cacheDirPath) {
        setNativeSpellingsDB(archive, cacheDirPath);
    }

    private native void setNativeSpellingsDB(Archive archive, String cacheDirPath);
    public native String[] getSpellingCorrections(String word, int maxCount);

    @Override
    protected void finalize() { dispose(); }

    ///--------- The wrapper thing
    // To delete our native wrapper
    public native void dispose();
    // A pointer (as a long) to a native Handle
    private long nativeHandle;
}
