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
            throws IOException, EntryNotFoundException {
        // test the zim file main page title
        TestEntry mainPage = archive.getMainEntry();
        assertTrue(mainPage.isRedirect());
        assertEquals("mainPage", mainPage.getTitle());
        assertEquals("Test ZIM file", mainPage.getItem(true).getTitle());
        assertEquals("Test ZIM file", mainPage.getRedirectEntry().getTitle());
        assertEquals("Test ZIM file", mainPage.getRedirect().getTitle());
        // test zim file main url
        assertEquals("mainPage", mainPage.getPath());
        assertEquals("main.html", mainPage.getItem(true).getPath());

        // test zim file size
        assertEquals(66937, archive.getFilesize()); // The file size is in KiB
        // test zim file content
        byte[] mainData = getFileContent("small_zimfile_data/main.html");
        byte[] inZimMainData = archive.getEntryByPath("main.html").getItem(true).getData().getData();
        assertTrue(Arrays.equals(mainData, inZimMainData));

        // test zim file icon
        assertTrue(archive.hasIllustration(48));
        byte[] faviconData = getFileContent("small_zimfile_data/favicon.png");
        TestItem item = archive.getIllustrationItem(48);
        assertEquals(faviconData.length, item.getSize());
        assertEquals("image/png", item.getMimetype());
        TestBlob illustrationData = item.getData();
        assertEquals(faviconData.length, illustrationData.size());
        assertTrue(Arrays.equals(faviconData, illustrationData.getData()));

        IllustrationInfo illustrationInfo = new IllustrationInfo();
        illustrationInfo.width = 48;
        illustrationInfo.height = 48;
        illustrationInfo.scale = 1.0f;
        TestItem item1 = archive.getIllustrationItem(illustrationInfo);
        assertEquals(faviconData.length, item1.getSize());
        assertEquals("image/png", item1.getMimetype());
        TestBlob illustrationData1 = item1.getData();
        assertEquals(faviconData.length, illustrationData1.size());
        assertTrue(Arrays.equals(faviconData, illustrationData1.getData()));

        // Checking direct access information
        DirectAccessInfo dai = item.getDirectAccessInformation();
        assertNotEquals("", dai.filename);
        byte[] readData = getFileContentPartial(dai.filename, (int) dai.offset, (int) item.getSize());
        assertTrue(Arrays.equals(faviconData, readData));

        // Checking all metadata
        assertTrue(archive.hasNewNamespaceScheme());
        assertTrue(archive.hasChecksum());
        assertEquals("4a2709fddbee8c27db708c20b4952a06", archive.getChecksum());
        assertTrue(archive.hasFulltextIndex());
        assertTrue(archive.hasMainEntry());
        long[] illuSizes = {48};
        assertTrue(Arrays.equals(illuSizes, archive.getIllustrationSizes()));
        String[] metaKeys = {"Counter", "Creator", "Date", "Description", "Illustration_48x48@1", "Language", "LongDescription", "Name", "Publisher", "Scraper", "Tags", "Title"};
        assertTrue(Arrays.equals(
            metaKeys,
            archive.getMetadataKeys()
        ));
        assertEquals("e34f5109-ed0d-b93e-943d-06f7717c7340", archive.getUuid());
        assertEquals(1, archive.getMediaCount());
        assertEquals(1, archive.getArticleCount());
        assertEquals(2, archive.getEntryCount());
        assertEquals(19, archive.getAllEntryCount());
        assertTrue(archive.hasEntryByTitle("Test ZIM file"));
        assertTrue(archive.hasEntryByPath("main.html"));
        assertEquals("Test ZIM file", archive.getEntryByTitle("Test ZIM file").getTitle());
        assertEquals("main.html", archive.getEntryByPath("main.html").getPath());
        assertEquals("Test ZIM file", archive.getEntryByTitle(0).getTitle());
        assertEquals("main.html", archive.getEntryByPath(1).getPath());
        assertEquals("main.html", archive.getEntryByClusterOrder(0).getPath());


        assertEquals("Test ZIM file", archive.getMetadata("Title"));
        assertEquals("Title", archive.getMetadataItem("Title").getTitle());

        assertFalse(archive.getRandomEntry().getTitle().isEmpty());

        // Test different iterators
        {
            TestEntryIterator iter = archive.iterByPath();
            assertTrue(iter.hasNext());
            assertEquals("favicon.png", iter.next().getPath());
            assertEquals("main.html", iter.next().getPath());
            assertFalse(iter.hasNext());
            try {
                iter.next();
                fail("ERROR: next() should raise a NoSuchElementException.");
            } catch (NoSuchElementException e) {
                // We are good
            } catch(Exception e) {
                fail("ERROR: Must be a NoSuchElementException.");
            }
        }

        {
            TestEntryIterator iter = archive.iterByTitle();
            assertTrue(iter.hasNext());
            assertEquals("main.html", iter.next().getPath());
            // No favicon, because favicon is not a main article (no title)
            assertFalse(iter.hasNext());
            try {
                iter.next();
                fail("ERROR: next() should raise a NoSuchElementException.");
            } catch (NoSuchElementException e) {
                // We are good
            } catch(Exception e) {
                fail("ERROR: Must be a NoSuchElementException.");
            }
        }

        {
            TestEntryIterator iter = archive.iterEfficient();
            assertTrue(iter.hasNext());
            assertEquals("main.html", iter.next().getPath());
            assertEquals("favicon.png", iter.next().getPath());
            assertFalse(iter.hasNext());
            try {
                iter.next();
                fail("ERROR: next() should raise a NoSuchElementException.");
            } catch (NoSuchElementException e) {
                // We are good
            } catch(Exception e) {
                fail("ERROR: Must be a NoSuchElementException.");
            }
        }

        {
            TestEntryIterator iter = archive.findByPath("ma");
            assertTrue(iter.hasNext());
            assertEquals("main.html", iter.next().getPath());
            assertFalse(iter.hasNext());
            try {
                iter.next();
                fail("ERROR: next() should raise a NoSuchElementException.");
            } catch (NoSuchElementException e) {
                // We are good
            } catch(Exception e) {
                fail("ERROR: Must be a NoSuchElementException.");
            }
        }

        {
            TestEntryIterator iter = archive.findByTitle("Test");
            assertTrue(iter.hasNext());
            assertEquals("main.html", iter.next().getPath());
            assertFalse(iter.hasNext());
            try {
                iter.next();
                fail("ERROR: next() should raise a NoSuchElementException.");
            } catch (NoSuchElementException e) {
                // We are good
            } catch(Exception e) {
                fail("ERROR: Must be a NoSuchElementException.");
            }
        }

        // Test invalid path
        try {
            archive.getEntryByTitle("Wrong title");
        } catch(EntryNotFoundException e) {
            assertEquals("Cannot find entry", e.getMessage());
        } catch(Exception e) {
            fail("ERROR: Must be a EntryNotFoundException.");
        }

        try {
            archive.getEntryByPath("wrong_path.html");
        } catch(EntryNotFoundException e) {
            assertEquals("Cannot find entry", e.getMessage());
        } catch(Exception e) {
            fail("ERROR: Must be a EntryNotFoundException.");
        }

        long maxCacheSize = archive.getDirentCacheMaxSize();
        assertEquals(512, maxCacheSize);
        long currentCacheSize = archive.getDirentCacheCurrentSize();
        assertEquals(19, currentCacheSize);
        archive.setDirentCacheMaxSize(19);
        System.gc();
        System.runFinalization();
    }

    @Test
    public void testArchiveDirect()
            throws JNIKiwixException, IOException, ZimFileFormatException, EntryNotFoundException {
        {
            TestArchive archive = new TestArchive("small.zim");
            testArchive(archive);
            assertFalse(archive.isMultiPart());
            assertTrue(archive.hasTitleIndex());
            assertTrue(archive.check());
            assertEquals("small.zim", archive.getFilename());
        }
        System.gc();
        System.runFinalization();
   }

    @Test
    public void testArchiveDirectWithOpenConfig()
            throws JNIKiwixException, IOException, ZimFileFormatException, EntryNotFoundException {
        {
            OpenConfig openConfig = new OpenConfig(true, 0);
            TestArchive archive = new TestArchive("small.zim", openConfig);
            testArchive(archive);
            assertFalse(archive.isMultiPart());
            assertTrue(archive.hasTitleIndex());
            assertTrue(archive.check());
            assertEquals("small.zim", archive.getFilename());
        }
        System.gc();
        System.runFinalization();
    }

   @Test
   public void testNonExistant() {
        // test reader with non existant zim file
        String zimFile = "non_existant.zim";
        try {
            TestArchive archive1 = new TestArchive(zimFile);
            fail("ERROR: Archive created with invalid ZIM file!");
        } catch (Exception e) {
            assertEquals("Error opening ZIM file: " + zimFile, e.getMessage());
        }
    }

    @Test
    public void testNotValid() {
        // test reader with non existant zim file
        String zimFile = "test.java";
        try {
            TestArchive archive1 = new TestArchive(zimFile);
            fail("ERROR: Archive created with invalid Zim file!");
        } catch (ZimFileFormatException e) {
            assertEquals("Invalid magic number", e.getMessage());
        } catch(Exception e) {
            fail("ERROR: Must be a ZimFileFormatException.");
        }
    }

    @Test
    public void testArchiveByFd()
            throws JNIKiwixException, IOException, ZimFileFormatException, EntryNotFoundException {
        {
            FileInputStream fis = new FileInputStream("small.zim");
            TestArchive archive = new TestArchive(fis.getFD());
            testArchive(archive);
            assertFalse(archive.isMultiPart());
            assertTrue(archive.hasTitleIndex());
            assertTrue(archive.check());
            assertEquals("", archive.getFilename());
        }
        System.gc();
        System.runFinalization();
    }

    @Test
    public void testArchiveByFdWithConfig()
            throws JNIKiwixException, IOException, ZimFileFormatException, EntryNotFoundException {
        {
            OpenConfig openConfig = new OpenConfig(true, 0);
            FileInputStream fis = new FileInputStream("small.zim");
            TestArchive archive = new TestArchive(fis.getFD(), openConfig);
            testArchive(archive);
            assertFalse(archive.isMultiPart());
            assertTrue(archive.hasTitleIndex());
            assertTrue(archive.check());
            assertEquals("", archive.getFilename());
        }
        System.gc();
        System.runFinalization();
    }

    @Test
    public void testArchiveByFdInput()
            throws JNIKiwixException, IOException, ZimFileFormatException, EntryNotFoundException {
        {
            File plainArchive = new File("small.zim");
            FileInputStream fis = new FileInputStream("small.zim");
            FdInput fd = new FdInput(fis.getFD(), 0, plainArchive.length());
            TestArchive archive = new TestArchive(fd);
            testArchive(archive);
            assertFalse(archive.isMultiPart());
            assertTrue(archive.hasTitleIndex());
            assertTrue(archive.check());
            assertEquals("", archive.getFilename());
        }
        System.gc();
        System.runFinalization();
    }

    @Test
    public void testArchiveByFdInputWithConfig()
            throws JNIKiwixException, IOException, ZimFileFormatException, EntryNotFoundException {
        {
            OpenConfig openConfig = new OpenConfig(true, 0);
            File plainArchive = new File("small.zim");
            FileInputStream fis = new FileInputStream("small.zim");
            FdInput fd = new FdInput(fis.getFD(), 0, plainArchive.length());
            TestArchive archive = new TestArchive(fd, openConfig);
            testArchive(archive);
            assertFalse(archive.isMultiPart());
            assertTrue(archive.hasTitleIndex());
            assertTrue(archive.check());
            assertEquals("", archive.getFilename());
        }
        System.gc();
        System.runFinalization();
    }

    @Test
    public void testArchiveWithAnEmbeddedArchive()
            throws JNIKiwixException, IOException, ZimFileFormatException, EntryNotFoundException {
        {
            File plainArchive = new File("small.zim");
            FileInputStream fis = new FileInputStream("small.zim.embedded");
            TestArchive archive = new TestArchive(fis.getFD(), 8, plainArchive.length());
            // This fails. See https://github.com/openzim/libzim/issues/812
            //assertTrue(archive.check());
            testArchive(archive);
            assertFalse(archive.isMultiPart());
            assertTrue(archive.hasTitleIndex());
            assertEquals("", archive.getFilename());
        }
        System.gc();
        System.runFinalization();
    }

    @Test
    public void testArchiveWithAnEmbeddedArchiveWithConfig()
            throws JNIKiwixException, IOException, ZimFileFormatException, EntryNotFoundException {
        {
            OpenConfig openConfig = new OpenConfig(true, 0);
            File plainArchive = new File("small.zim");
            FileInputStream fis = new FileInputStream("small.zim.embedded");
            TestArchive archive = new TestArchive(fis.getFD(), 8, plainArchive.length(), openConfig);
            // This fails. See https://github.com/openzim/libzim/issues/812
            //assertTrue(archive.check());
            testArchive(archive);
            assertFalse(archive.isMultiPart());
            assertTrue(archive.hasTitleIndex());
            assertEquals("", archive.getFilename());
        }
        System.gc();
        System.runFinalization();
    }

    @Test
    public void testArchiveWithAnEmbeddedArchiveFdInputNaive()
            throws JNIKiwixException, IOException, ZimFileFormatException, EntryNotFoundException {
        {
            File plainArchive = new File("small.zim");
            FileInputStream fis = new FileInputStream("small.zim.embedded");
            FdInput fd1 = new FdInput(fis.getFD(), 8, plainArchive.length() / 2);
            FdInput fd2 = new FdInput(fis.getFD(), fd1.offset + fd1.size, plainArchive.length() - fd1.size);

            FdInput fds[] = {fd1, fd2};

            TestArchive archive = new TestArchive(fds);
            // This fails. See https://github.com/openzim/libzim/issues/812
            //assertTrue(archive.check());
            testArchive(archive);
            assertTrue(archive.isMultiPart());
            //Naive split cut the title index in the middle. libzim cannot read it.
            assertFalse(archive.hasTitleIndex());
            assertEquals("", archive.getFilename());
        }
        System.gc();
        System.runFinalization();
    }

    @Test
    public void testArchiveWithAnEmbeddedArchiveFdInputNaiveWithConfig()
            throws JNIKiwixException, IOException, ZimFileFormatException, EntryNotFoundException {
        {
            OpenConfig openConfig = new OpenConfig(true, 0);
            File plainArchive = new File("small.zim");
            FileInputStream fis = new FileInputStream("small.zim.embedded");
            FdInput fd1 = new FdInput(fis.getFD(), 8, plainArchive.length() / 2);
            FdInput fd2 = new FdInput(fis.getFD(), fd1.offset + fd1.size, plainArchive.length() - fd1.size);

            FdInput fds[] = {fd1, fd2};

            TestArchive archive = new TestArchive(fds, openConfig);
            // This fails. See https://github.com/openzim/libzim/issues/812
            //assertTrue(archive.check());
            testArchive(archive);
            assertTrue(archive.isMultiPart());
            //Naive split cut the title index in the middle. libzim cannot read it.
            assertFalse(archive.hasTitleIndex());
            assertEquals("", archive.getFilename());
        }
        System.gc();
        System.runFinalization();
    }

    @Test
    public void testArchiveWithAnEmbeddedArchiveFdInput()
            throws JNIKiwixException, IOException, ZimFileFormatException, EntryNotFoundException {
        {
            File plainArchive = new File("small.zim");
            FileInputStream fis = new FileInputStream("small.zim.embedded");
            FdInput fd1 = new FdInput(fis.getFD(), 8, plainArchive.length() / 10);
            FdInput fd2 = new FdInput(fis.getFD(), fd1.offset + fd1.size, plainArchive.length() - fd1.size);

            FdInput fds[] = {fd1, fd2};

            TestArchive archive = new TestArchive(fds);
            // This fails. See https://github.com/openzim/libzim/issues/812
            //assertTrue(archive.check());
            testArchive(archive);
            assertTrue(archive.isMultiPart());
            //If we don't cut in the middle of xapian db, we can read it.
            assertTrue(archive.hasTitleIndex());
            assertEquals("", archive.getFilename());
        }
        System.gc();
        System.runFinalization();
    }

    @Test
    public void testArchiveWithAnEmbeddedArchiveFdInputWithConfig()
            throws JNIKiwixException, IOException, ZimFileFormatException, EntryNotFoundException {
        {
            OpenConfig openConfig = new OpenConfig(true, 0);
            File plainArchive = new File("small.zim");
            FileInputStream fis = new FileInputStream("small.zim.embedded");
            FdInput fd1 = new FdInput(fis.getFD(), 8, plainArchive.length() / 10);
            FdInput fd2 = new FdInput(fis.getFD(), fd1.offset + fd1.size, plainArchive.length() - fd1.size);

            FdInput fds[] = {fd1, fd2};

            TestArchive archive = new TestArchive(fds, openConfig);
            // This fails. See https://github.com/openzim/libzim/issues/812
            //assertTrue(archive.check());
            testArchive(archive);
            assertTrue(archive.isMultiPart());
            //If we don't cut in the middle of xapian db, we can read it.
            assertTrue(archive.hasTitleIndex());
            assertEquals("", archive.getFilename());
        }
        System.gc();
        System.runFinalization();
    }

    private void testLibrary(TestLibrary lib)
            throws IOException {
        assertEquals(lib.getBookCount(true, true), 1);
        String[] bookIds = lib.getBooksIds();
        assertEquals(bookIds.length, 1);
        lib.filter(new Filter().local(true));
        assertTrue(Arrays.equals(lib.getBooksPublishers(), new String[]{"Publisher"}));
        assertTrue(Arrays.equals(lib.getBooksCreators(), new String[]{"Creator"}));
        System.out.println(Arrays.toString(lib.getBooksCategories()));
        assertTrue(Arrays.equals(lib.getBooksCategories(), new String[]{"Category"}));
        assertTrue(Arrays.equals(lib.getBooksLanguages(), new String[]{"eng"}));


        // getArchiveById needs books with valid path. Which is not possible by definition if library is initialized by opds stream.
        //assertEquals("86c91e51-55bf-8882-464e-072aca37a3e8", lib.getArchiveById("86c91e51-55bf-8882-464e-072aca37a3e8").getUuid());

        TestBook book = lib.getBookById(bookIds[0]);
        assertEquals(book.getTitle(), "Test ZIM file");
        assertEquals(book.getTags(), "_category:Category;_ftindex:yes;_ftindex:yes;_pictures:yes;_videos:yes;_details:yes");

        assertEquals(book.getUrl(), "http://localhost/small.zim");
        assertEquals(book.getDescription(), "Description");
        assertEquals(book.getCreator(), "Creator");
        assertEquals(book.getPublisher(), "Publisher");
        assertEquals(book.getFlavour(), "");
        assertEquals(book.getCategory(), "Category");
        assertEquals(book.getArticleCount(), 1);
        assertEquals(book.getMediaCount(), 1);
        assertEquals(book.getSize(), 66560);
        TestIllustration[] illustrations = book.getIllustrations();
        assertEquals(1, illustrations.length);

        assertEquals(book.getTagStr("video"), "");
    }

    @Test
    public void testLibrarySimple() throws IOException {
        {
            TestLibrary lib = new TestLibrary();
            TestManager manager = new TestManager(lib);
            manager.addBookFromPath("small.zim", "small.zim", "http://localhost/small.zim", true);
            testLibrary(lib);
            String[] bookIds = lib.getBooksIds();
            TestBook book = lib.getBookById(bookIds[0]);

            TestIllustration illustration = book.getIllustration(48);
            assertEquals(illustration.width(), 48);
            assertEquals(illustration.height(), 48);
            assertEquals(illustration.mimeType(), "image/png");
            assertEquals(illustration.url(), "");
            byte[] faviconData = getFileContent("small_zimfile_data/favicon.png");
            assertTrue(Arrays.equals(faviconData, illustration.getData()));

            assertEquals(book.getPath(), new File("small.zim").getAbsolutePath());
            assertEquals(book.getHumanReadableIdFromPath(), "small");
            assertTrue(book.isPathValid());

            // remove book from library by id
            lib.removeBookById(bookIds[0]);
            bookIds = lib.getBooksIds();
            assertEquals(bookIds.length, 0);
        }
        System.gc();
        System.runFinalization();
    }

    @Test
    public void testLibraryXml() throws IOException {
        {
            TestLibrary lib = new TestLibrary();
            TestManager manager = new TestManager(lib);
            manager.readFile("library.xml");
            testLibrary(lib);
            String[] bookIds = lib.getBooksIds();
            TestBook book = lib.getBookById(bookIds[0]);

            TestIllustration illustration = book.getIllustration(48);
            assertEquals(illustration.width(), 48);
            assertEquals(illustration.height(), 48);
            assertEquals(illustration.mimeType(), "image/png");
            assertEquals(illustration.url(), "");
            byte[] faviconData = getFileContent("small_zimfile_data/favicon.png");
            assertTrue(Arrays.equals(faviconData, illustration.getData()));

            assertEquals(book.getPath(), new File("small.zim").getAbsolutePath());
            assertEquals(book.getHumanReadableIdFromPath(), "small");
            assertTrue(book.isPathValid());
        }
        System.gc();
        System.runFinalization();
    }

    @Test
    public void testLibraryXmlContent() throws IOException {
        {
            TestLibrary lib = new TestLibrary();
            TestManager manager = new TestManager(lib);
            String content = getTextFileContent("library.xml");
            manager.readXml(content, "library.xml");
            testLibrary(lib);
            String[] bookIds = lib.getBooksIds();
            TestBook book = lib.getBookById(bookIds[0]);

            TestIllustration illustration = book.getIllustration(48);
            assertEquals(illustration.width(), 48);
            assertEquals(illustration.height(), 48);
            assertEquals(illustration.mimeType(), "image/png");
            assertEquals(illustration.url(), "");
            byte[] faviconData = getFileContent("small_zimfile_data/favicon.png");
            assertTrue(Arrays.equals(faviconData, illustration.getData()));

            assertEquals(book.getPath(), new File("small.zim").getAbsolutePath());
            assertEquals(book.getHumanReadableIdFromPath(), "small");
            assertTrue(book.isPathValid());
        }
        System.gc();
        System.runFinalization();
    }

    @Test
    public void testLibraryOPDS() throws IOException {
        {
            TestLibrary lib = new TestLibrary();
            TestManager manager = new TestManager(lib);
            String content = getTextFileContent("catalog.xml");
            manager.readOpds(content, "http://localhost");
            testLibrary(lib);
            String[] bookIds = lib.getBooksIds();
            TestBook book = lib.getBookById(bookIds[0]);

            TestIllustration illustration = book.getIllustration(48);
            assertEquals(illustration.width(), 48);
            assertEquals(illustration.height(), 48);
            assertEquals(illustration.mimeType(), "image/png");
            assertEquals(illustration.url(), "http://localhost/meta?name=favicon&content=small");
            // This will try to downoald to the data, but we have no local server. So return empty array.
            assertTrue(Arrays.equals(illustration.getData(), new byte[0]));

            assertEquals(book.getPath(), "");
            assertEquals(book.getHumanReadableIdFromPath(), "");
            assertFalse(book.isPathValid());
        }
        System.gc();
        System.runFinalization();
    }

    @Test
    public void testServer() throws ZimFileFormatException, JNIKiwixException {
        {
            TestArchive archive = new TestArchive("small.zim");
            TestLibrary lib = new TestLibrary();
            TestBook book = new TestBook();
            book.update(archive);
            lib.addBook(book);
            assertEquals(1, lib.getBookCount(true, true));
            TestServer server = new TestServer(lib);
            server.setPort(8080);
            server.setRoot("FOO");
            server.setAddress("127.0.0.1");
            server.setNbThreads(1);
            server.setBlockExternalLinks(true);
            server.setTaskbar(true, true);
            assertTrue(server.start());
            List<String> urls = Arrays.asList(server.getServerAccessUrls());
            assertNotNull(urls);
            assertFalse(urls.isEmpty());
            assertEquals(urls.get(0), "http://127.0.0.1:8080/FOO");
            server.stop();
        }
        System.gc();
        System.runFinalization();
    }

    @Test
    public void testBookMark() throws ZimFileFormatException, JNIKiwixException {
        {
            TestArchive archive = new TestArchive("small.zim");
            TestLibrary lib = new TestLibrary();
            TestBook book = new TestBook();
            book.update(archive);
            lib.addBook(book);
            TestBookmark bookmark = new TestBookmark();
            bookmark.setBookId(book.getId());
            bookmark.setTitle("A title for an article");
            bookmark.setUrl("foo/bar.html");
            bookmark.setLanguage(book.getLanguage());
            bookmark.setDate(book.getDate());
            bookmark.setBookTitle(book.getTitle());
            bookmark.setBookName(book.getName());
            bookmark.setBookFlavour(book.getFlavour());
            // add bookmark to library
            lib.addBookmark(bookmark);
            TestBookmark[] bookmarkArray = lib.getBookmarks(true);
            assertEquals(1, bookmarkArray.length);
            bookmark = bookmarkArray[0];
            // test saved bookmark
            assertEquals(bookmark.getBookId(), book.getId());
            assertEquals(bookmark.getTitle(), "A title for an article");
            assertEquals(bookmark.getUrl(), "foo/bar.html");
            assertEquals(bookmark.getLanguage(), book.getLanguage());
            assertEquals(bookmark.getDate(), book.getDate());
            assertEquals(bookmark.getBookTitle(), book.getTitle());
            assertEquals(bookmark.getBookName(), book.getName());
            assertEquals(bookmark.getBookFlavour(), book.getFlavour());

            BookmarkMigrationResult result = lib.migrateBookmarks(true);
            assertEquals(result.nbMigratedBookmarks, 0);
            assertEquals(result.nbInvalidBookmarks, 0);

            assertEquals(lib.migrateBookmarks(book.getId(), true), 0);
            assertEquals(lib.migrateBookmarks(book.getId(), "new-id"), 1);

            assertEquals(lib.getBestTargetBookId(bookmark, true), book.getId());
            assertEquals(lib.getBestTargetBookId(book.getName()), book.getId());
            assertEquals(lib.getBestTargetBookId(book.getName(), "someflavour"), book.getId());
            assertEquals(lib.getBestTargetBookId(book.getName(), "someflavour", "20230105"), "");
            assertEquals(lib.getBestTargetBookId(book.getName(), "someflavour", "20190105"), book.getId());
            // remove bookmark from library
            lib.removeBookmark("new-id", bookmark.getUrl());
            bookmarkArray = lib.getBookmarks(true);
            assertEquals(0, bookmarkArray.length);
        }
        System.gc();
        System.runFinalization();
    }

    @Test
    public void testSearcher() throws Exception, ZimFileFormatException, JNIKiwixException {
        {
            TestArchive archive = new TestArchive("small.zim");

            TestSearcher searcher = new TestSearcher(archive);
            searcher.setVerbose(true);
            TestQuery query = new TestQuery("test__");
            query.setQuery("test");

            TestSearch search = searcher.search(query);
            int estimatedMatches = (int) search.getEstimatedMatches();
            assertEquals(1, estimatedMatches);
            TestSearchIterator iterator = search.getResults(0, estimatedMatches);
            assertTrue(iterator.hasNext());
            assertEquals("Test ZIM file", iterator.getTitle());
            assertEquals("main.html", iterator.getPath());
            assertEquals(100, iterator.getScore());
            assertEquals("<b>Test</b> ZIM file", iterator.getSnippet());
            assertEquals(3, iterator.getWordCount());
            assertEquals(0, iterator.getFileIndex());
            assertEquals("e34f5109-ed0d-b93e-943d-06f7717c7340", iterator.getZimId());
            TestEntry entry = iterator.next();
            assertEquals("main.html", entry.getPath());

            query.setGeorange(50,70,50);
            assertEquals(0, searcher.search(query).getEstimatedMatches());

            TestSearcher searcher2 = new TestSearcher(new TestArchive[0]);
            searcher2.addArchive(archive);
            assertEquals(1, searcher2.search(new TestQuery("test")).getEstimatedMatches());

            TestSuggestionSearcher suggestionSearcher = new TestSuggestionSearcher(archive);
            suggestionSearcher.setVerbose(true);
            TestSuggestionSearch suggestionSearch = suggestionSearcher.suggest("test");
            int matches = (int) suggestionSearch.getEstimatedMatches();
            assertEquals(1, matches);
            TestSuggestionIterator results = suggestionSearch.getResults(0, matches);
            assertTrue(results.hasNext());
            TestSuggestionItem suggestionItem = results.next();
            assertFalse(results.hasNext());
            try {
                results.next();
                fail("ERROR: next() should raise a NoSuchElementException.");
            } catch (NoSuchElementException e) {
                // We are good
            } catch(Exception e) {
                fail("ERROR: Must be a NoSuchElementException.");
            }
            assertEquals("Test ZIM file", suggestionItem.getTitle());
            assertEquals("main.html", suggestionItem.getPath());
            assertTrue(suggestionItem.hasSnippet());
            assertEquals("<b>Test</b> ZIM file", suggestionItem.getSnippet());
        }
        System.gc();
        System.runFinalization();
    }

    @Test
    public void testICUInit() {
        TestJNIICU.setDataDirectory(".");
    }

    static
    public void main(String[] args) {
        Library lib = new Library();
        lib.getBookCount(true, true);
    }
}
