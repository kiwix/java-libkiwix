import java.io.*;
import java.util.*;

import org.junit.Test;

import static org.junit.Assert.*;

import org.kiwix.libkiwix.*;
import org.kiwix.libzim.*;
import org.kiwix.test.libzim.*;
import org.kiwix.test.libkiwix.*;

public class test {
    static {
        System.loadLibrary("kiwix");
        System.loadLibrary("zim");
        System.loadLibrary("kiwix_wrapper");
        System.loadLibrary("zim_wrapper");
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

    private void testArchive(TestArchive archive)
        throws IOException {
        // test the zim file main page title
        TestEntry mainPage = archive.getMainEntry();
        assertEquals("mainPage", mainPage.getTitle());
        assertEquals("Test ZIM file", mainPage.getItem(true).getTitle());
        // test zim file main url
        assertEquals("mainPage", mainPage.getPath());
        assertEquals("main.html", mainPage.getItem(true).getPath());

        // test zim file size
        assertEquals(66910, archive.getFilesize()); // The file size is in KiB
        // test zim file content
        byte[] mainData = getFileContent("small_zimfile_data/main.html");
        byte[] inZimMainData = archive.getEntryByPath("main.html").getItem(true).getData().getData();
        assert(Arrays.equals(mainData, inZimMainData));

        // test zim file icon
        assertEquals(true, archive.hasIllustration(48));
        byte[] faviconData = getFileContent("small_zimfile_data/favicon.png");
        TestItem item = archive.getIllustrationItem(48);
        assertEquals(faviconData.length, item.getSize());
        assert(Arrays.equals(faviconData, item.getData().getData()));

        // Checking direct access information
        DirectAccessInfo dai = item.getDirectAccessInformation();
        assertNotEquals("", dai.filename);
        byte[] readData = getFileContentPartial(dai.filename, (int) dai.offset, (int) item.getSize());
        assert(Arrays.equals(faviconData, readData));
   }

    @Test
    public void testArchiveDirect()
            throws JNIKiwixException, IOException, ZimFileFormatException {
        TestArchive archive = new TestArchive("small.zim");
        testArchive(archive);
        archive.dispose();

        // test reader with invalid zim file
        String zimFile = "test.zim";
        try {
            TestArchive archive1 = new TestArchive(zimFile);
            fail("ERROR: Archive created with invalid Zim file!");
        } catch (ZimFileFormatException zimFileFormatException) {
            assertEquals("Cannot open zimfile " + zimFile, zimFileFormatException.getMessage());
        }
    }

    @Test
    public void testArchiveByFd()
            throws JNIKiwixException, IOException, ZimFileFormatException {
        FileInputStream fis = new FileInputStream("small.zim");
        TestArchive archive = new TestArchive(fis.getFD());
        testArchive(archive);
        archive.dispose();
    }

    @Test
    public void testArchiveWithAnEmbeddedArchive()
            throws JNIKiwixException, IOException, ZimFileFormatException {
        File plainArchive = new File("small.zim");
        FileInputStream fis = new FileInputStream("small.zim.embedded");
        TestArchive archive = new TestArchive(fis.getFD(), 8, plainArchive.length());
        testArchive(archive);
        archive.dispose();
    }

    @Test
    public void testLibrary()
            throws IOException {
        TestLibrary lib = new TestLibrary();
        TestManager manager = new TestManager(lib);
        String content = getTextFileContent("catalog.xml");
        manager.readOpds(content, "http://localhost");
        assertEquals(lib.getBookCount(true, true), 1);
        String[] bookIds = lib.getBooksIds();
        assertEquals(bookIds.length, 1);
        lib.filter(new Filter().local(true));

        TestBook book = lib.getBookById(bookIds[0]);
        assertEquals(book.getTitle(), "Test ZIM file");
        assertEquals(book.getTags(), "unit;test");
        assertEquals(book.getIllustration(48).width(), 48);
        assertEquals(book.getIllustration(48).url(), "http://localhost/meta?name=favicon&content=small");
        assertEquals(book.getUrl(), "http://localhost/small.zim");

        // remove book from library by id
        lib.removeBookById(bookIds[0]);
        bookIds = lib.getBooksIds();
        assertEquals(bookIds.length, 0);
    }

    @Test
    public void testServer() throws ZimFileFormatException, JNIKiwixException {
        TestArchive archive = new TestArchive("small.zim");
        TestLibrary lib = new TestLibrary();
        TestBook book = new TestBook();
        book.update(archive);
        lib.addBook(book);
        assertEquals(1, lib.getBookCount(true, true));
        TestServer server = new TestServer(lib);
        server.setPort(8080);
        assertEquals(true, server.start());
    }

    @Test
    public void testBookMark() throws ZimFileFormatException, JNIKiwixException {
        TestArchive archive = new TestArchive("small.zim");
        TestLibrary lib = new TestLibrary();
        TestBook book = new TestBook();
        book.update(archive);
        lib.addBook(book);
        TestBookmark bookmark = new TestBookmark();
        bookmark.setBookId(book.getId());
        bookmark.setTitle(book.getTitle());
        bookmark.setUrl(book.getUrl());
        bookmark.setLanguage(book.getLanguage());
        bookmark.setDate(book.getDate());
        bookmark.setBookTitle(book.getName());
        // add bookmark to library
        lib.addBookmark(bookmark);
        TestBookmark[] bookmarkArray = lib.getBookmarks(true);
        assertEquals(1, bookmarkArray.length);
        bookmark = bookmarkArray[0];
        // test saved bookmark
        assertEquals(bookmark.getBookId(), book.getId());
        assertEquals(bookmark.getTitle(), book.getTitle());
        assertEquals(bookmark.getUrl(), book.getUrl());
        assertEquals(bookmark.getLanguage(), book.getLanguage());
        assertEquals(bookmark.getDate(), book.getDate());
        // remove bookmark from library
        lib.removeBookmark(bookmark.getBookId(), bookmark.getUrl());
        bookmarkArray = lib.getBookmarks(true);
        assertEquals(0, bookmarkArray.length);
    }

    @Test
    public void testSearcher() throws Exception, ZimFileFormatException, JNIKiwixException {
        TestArchive archive = new TestArchive("small.zim");

        TestSearcher searcher = new TestSearcher(archive);
        TestQuery query = new TestQuery("test");
        TestSearch search = searcher.search(query);
        int estimatedMatches = (int) search.getEstimatedMatches();
        assertEquals(1, estimatedMatches);
        TestSearchIterator iterator = search.getResults(0, estimatedMatches);
        assertEquals("Test ZIM file", iterator.getTitle());
        searcher.dispose();

        TestSuggestionSearcher suggestionSearcher = new TestSuggestionSearcher(archive);
        TestSuggestionSearch suggestionSearch = suggestionSearcher.suggest("test");
        int matches = (int) suggestionSearch.getEstimatedMatches();
        assertEquals(1, matches);
        TestSuggestionIterator results = suggestionSearch.getResults(0, matches);
        TestSuggestionItem suggestionItem = results.next();
        assertEquals("Test ZIM file", suggestionItem.getTitle());
        suggestionSearcher.dispose();
    }

    static
    public void main(String[] args) {
        Library lib = new Library();
        lib.getBookCount(true, true);
    }
}
