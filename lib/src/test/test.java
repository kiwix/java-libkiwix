import java.io.*;
import java.util.*;

import org.junit.Test;

import static org.junit.Assert.*;

import org.kiwix.libkiwix.*;
import org.kiwix.libzim.*;

public class test {
    static {
        System.loadLibrary("kiwix");
        System.loadLibrary("zim");
        System.loadLibrary("buildkiwix");
    }

    private static byte[] getFileContent(String path)
            throws IOException {
        File file = new File(path);
        DataInputStream in = new DataInputStream(
                new BufferedInputStream(
                        new FileInputStream(file)));
        byte[] data = new byte[(int) file.length()];
        in.read(data);
        return data;
    }

    private static byte[] getFileContentPartial(String path, int offset, int size)
            throws IOException {
        File file = new File(path);
        DataInputStream in = new DataInputStream(
                new BufferedInputStream(
                        new FileInputStream(file)));
        byte[] data = new byte[size];
        in.skipBytes(offset);
        in.read(data, 0, size);
        return data;
    }

    private static String getTextFileContent(String path)
            throws IOException {
        return new String(getFileContent(path));
    }

    @Test
    public void testReader()
            throws JNIKiwixException, IOException, ZimFileFormatException {
        Archive archive = new Archive("small.zim");
        // test the zim file main page title
        assertEquals("Test ZIM file", archive.getMainEntry().getTitle());
        // test zim file size
        assertEquals(3, archive.getFilesize() / 1024); // The file size is in KiB
        // test zim file main url
        assertEquals("A/main.html", archive.getMainEntry().getPath());
        // test zim file content
        String s = getTextFileContent("small_zimfile_data/main.html");
        String c = archive.getEntryByPath("A/main.html").getItem(true).getData().getData();
        assertEquals(s, c);

        // test zim file icon
        byte[] faviconData = getFileContent("small_zimfile_data/favicon.png");
        assertEquals(true, archive.hasIllustration(48));
        Item item = archive.getIllustrationItem(48);
        assertEquals(faviconData.length, item.getSize());

        DirectAccessInfo dai = archive.getEntryByPath("I/favicon.png").getItem(true).getDirectAccessInformation();
        assertNotEquals("", dai.filename);
        c = new String(getFileContentPartial(dai.filename, (int) dai.offset, faviconData.length));
        assertEquals(new String(faviconData), c);

        archive.dispose();
    }

    @Test
    public void testReaderByFd()
            throws JNIKiwixException, IOException, ZimFileFormatException {
        FileInputStream fis = new FileInputStream("small.zim");
        Archive archive = new Archive(fis.getFD());
        // test the zim file main page title
        assertEquals("Test ZIM file", archive.getMainEntry().getTitle());
        // test zim file size
        assertEquals(3, archive.getFilesize() / 1024); // The file size is in KiB
        // test zim file main url
        assertEquals("A/main.html", archive.getMainEntry().getPath());
        // test zim file content
        String s = getTextFileContent("small_zimfile_data/main.html");
        String c = archive.getEntryByPath("A/main.html").getItem(true).getData().getData();
        assertEquals(s, c);

        // test zim file icon
        byte[] faviconData = getFileContent("small_zimfile_data/favicon.png");
        assertEquals(true, archive.hasIllustration(48));
        Item item = archive.getIllustrationItem(48);
        assertEquals(faviconData.length, item.getSize());

        DirectAccessInfo dai = archive.getEntryByPath("I/favicon.png").getItem(true).getDirectAccessInformation();
        assertNotEquals("", dai.filename);
        c = new String(getFileContentPartial(dai.filename, (int) dai.offset, faviconData.length));
        assertEquals(new String(faviconData), c);

        archive.dispose();
    }

    @Test
    public void testReaderWithAnEmbeddedArchive()
            throws JNIKiwixException, IOException, ZimFileFormatException {
        File plainArchive = new File("small.zim");
        FileInputStream fis = new FileInputStream("small.zim.embedded");
        Archive archive = new Archive(fis.getFD(), 8, plainArchive.length());
        // test the zim file main page title
        assertEquals("Test ZIM file", archive.getMainEntry().getTitle());
        // test zim file size
        assertEquals(3, archive.getFilesize() / 1024); // The file size is in KiB
        // test zim file main url
        assertEquals("A/main.html", archive.getMainEntry().getPath());
        // test zim file content
        String s = getTextFileContent("small_zimfile_data/main.html");
        String c = archive.getEntryByPath("A/main.html").getItem(true).getData().getData();
        assertEquals(s, c);

        // test zim file icon
        byte[] faviconData = getFileContent("small_zimfile_data/favicon.png");
        assertEquals(true, archive.hasIllustration(48));
        Item item = archive.getIllustrationItem(48);
        assertEquals(faviconData.length, item.getSize());

        DirectAccessInfo dai = archive.getEntryByPath("I/favicon.png").getItem(true).getDirectAccessInformation();
        assertNotEquals("", dai.filename);
        c = new String(getFileContentPartial(dai.filename, (int) dai.offset, faviconData.length));
        assertEquals(new String(faviconData), c);

        archive.dispose();
    }

    @Test
    public void testLibrary()
            throws IOException {
        Library lib = new Library();
        Manager manager = new Manager(lib);
        String content = getTextFileContent("catalog.xml");
        manager.readOpds(content, "http://localhost");
        assertEquals(lib.getBookCount(true, true), 1);
        String[] bookIds = lib.getBooksIds();
        assertEquals(bookIds.length, 1);
        lib.filter(new Filter().local(true));
    }

    @Test
    public void testServer() throws ZimFileFormatException, JNIKiwixException {
        Archive archive = new Archive("small.zim");
        Library lib = new Library();
        Book book = new Book();
        book.update(archive);
        lib.addBook(book);
        assertEquals(1, lib.getBookCount(true, true));
        Server server = new Server(lib);
        server.setPort(8080);
        assertEquals(true, server.start());
    }

    @Test
    public void testBookMark() throws ZimFileFormatException, JNIKiwixException {
        Archive archive = new Archive("small.zim");
        Library lib = new Library();
        Book book = new Book();
        book.update(archive);
        lib.addBook(book);
        Bookmark bookmark = new Bookmark();
        bookmark.setBookId(book.getId());
        bookmark.setTitle(book.getTitle());
        bookmark.setUrl(book.getUrl());
        bookmark.setLanguage(book.getLanguage());
        bookmark.setDate(book.getDate());
        bookmark.setBookTitle(book.getName());
        // add bookmark to library
        lib.addBookmark(bookmark);
        Bookmark[] bookmarkArray = lib.getBookmarks(true);
        assertEquals(1, bookmarkArray.length);
        bookmark = bookmarkArray[0];
        // test bookmark title
        assertEquals(bookmark.getTitle(), book.getTitle());
        // remove bookmark from library
        lib.removeBookmark(bookmark.getBookId(), bookmark.getUrl());
        bookmarkArray = lib.getBookmarks(true);
        assertEquals(0, bookmarkArray.length);
    }

    @Test
    public void testSearcher() throws Exception, ZimFileFormatException, JNIKiwixException {
        Archive archive = new Archive("small.zim");
        Searcher searcher = new Searcher(archive);
    }

    static
    public void main(String[] args) {
        Library lib = new Library();
        lib.getBookCount(true, true);
    }
}