package org.kiwix.libzim;

public class OpenConfig {
    public boolean preloadXapianDb;
    public int preloadDirentRanges;

    public OpenConfig(boolean preloadXapianDb, int preloadDirentRanges) {
        this.preloadXapianDb = preloadXapianDb;
        this.preloadDirentRanges = preloadDirentRanges;
    }
}
