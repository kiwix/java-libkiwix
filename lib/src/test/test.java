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
            throws IOException
    {
        File file = new File(path);
        DataInputStream in = new DataInputStream(
                new BufferedInputStream(
                        new FileInputStream(file)));
        byte[] data = new byte[(int)file.length()];
        in.read(data);
        return data;
    }

    private static byte[] getFileContentPartial(String path, int offset, int size)
            throws IOException
    {
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
            throws IOException
    {
        return new String(getFileContent(path));
    }

    @Test
    public void testReader()
            throws JNIKiwixException, IOException, ZimFileFormatException {
        Archive archive = new Archive("small.zim");
        assertEquals("Test ZIM file", archive.getMainEntry().getTitle());
        assertEquals(3, archive.getFilesize() / 1024); // The file size is in KiB
        assertEquals("A/main.html", archive.getMainEntry().getPath());
        String s = getTextFileContent("small_zimfile_data/main.html");
        String c = archive.getEntryByPath("A/main.html").getItem(true).getData().getData();
        //assertEquals(s, c);

        byte[] faviconData = getFileContent("small_zimfile_data/favicon.png");
        assertEquals(faviconData.length, archive.getEntryByPath("I/favicon.png").getItem(true).getSize());
        c = archive.getEntryByPath("I/favicon.png").getItem(true).getData().getData();
        assertEquals(new String(faviconData), c);

        DirectAccessInfo dai = archive.getEntryByPath("I/favicon.png").getItem(true).getDirectAccessInformation();
        assertNotEquals("", dai.filename);
        c = new String(getFileContentPartial(dai.filename, (int) dai.offset, faviconData.length));
        assertEquals(new String(faviconData), c);
    }

    @Test
    public void testReaderByFd()
            throws JNIKiwixException, IOException, ZimFileFormatException {
        FileInputStream fis = new FileInputStream("small.zim");
        Archive archive = new Archive(fis.getFD());
        assertEquals("Test ZIM file", archive.getMainEntry().getTitle());
        assertEquals(3, archive.getFilesize() / 1024); // The file size is in KiB
        assertEquals("A/main.html", archive.getMainEntry().getPath());
        String s = getTextFileContent("small_zimfile_data/main.html");
        String c = archive.getEntryByPath("A/main.html").getItem(true).getData().getData();
        assertEquals(s, c);

        byte[] faviconData = getFileContent("small_zimfile_data/favicon.png");
        assertEquals(faviconData.length, archive.getEntryByPath("I/favicon.png").getItem(true).getSize());
        c = archive.getEntryByPath("I/favicon.png").getItem(true).getData().getData();
        assertEquals(new String(faviconData), c);

        DirectAccessInfo dai = archive.getEntryByPath("I/favicon.png").getItem(true).getDirectAccessInformation();
        assertNotEquals("", dai.filename);
        c = new String(getFileContentPartial(dai.filename, (int) dai.offset, faviconData.length));
        assertEquals(new String(faviconData), c);
    }

    @Test
    public void testReaderWithAnEmbeddedArchive()
            throws JNIKiwixException, IOException, ZimFileFormatException {
        File plainArchive = new File("small.zim");
        FileInputStream fis = new FileInputStream("small.zim.embedded");
        Archive archive = new Archive(fis.getFD(), 8, plainArchive.length());
        assertEquals("Test ZIM file", archive.getMainEntry().getTitle());
        assertEquals(3, archive.getFilesize() / 1024); // The file size is in KiB
        assertEquals("A/main.html", archive.getMainEntry().getPath());
        String s = getTextFileContent("small_zimfile_data/main.html");
        String c = archive.getEntryByPath("A/main.html").getItem(true).getData().getData();
        assertEquals(s, c);

        byte[] faviconData = getFileContent("small_zimfile_data/favicon.png");
        assertEquals(faviconData.length, archive.getEntryByPath("I/favicon.png").getItem(true).getSize());
        c = archive.getEntryByPath("I/favicon.png").getItem(true).getData().getData();
        assertEquals(new String(faviconData), c);

        DirectAccessInfo dai = archive.getEntryByPath("I/favicon.png").getItem(true).getDirectAccessInformation();
        assertNotEquals("", dai.filename);
        c = new String(getFileContentPartial(dai.filename, (int) dai.offset, faviconData.length));
        assertEquals(new String(faviconData), c);
    }

    @Test
    public void testLibrary()
            throws IOException
    {
        Library lib = new Library();
        Manager manager = new Manager(lib);
        String content = getTextFileContent("catalog.xml");
        manager.readOpds(content, "http://localhost");
        assertEquals(lib.getBookCount(true, true), 1);
        String[] bookIds = lib.getBooksIds();
        assertEquals(bookIds.length, 1);
        Book book = lib.getBookById(bookIds[0]);
        assertEquals(book.getTitle(), "Test ZIM file");
        assertEquals(book.getTags(), "unit;test");
        assertEquals(book.getIllustration(48).url(), "http://localhost/meta?name=favicon&content=small");
        assertEquals(book.getUrl(), "http://localhost/small.zim");
    }

    static
    public void main(String[] args) {
        Library lib = new Library();
        lib.getBookCount(true, true);
    }
}