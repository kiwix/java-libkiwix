
package org.kiwix.test.libkiwix;

import org.kiwix.libkiwix.Book;
import org.kiwix.test.libkiwix.TestIllustration;
import org.kiwix.test.libzim.TestArchive;
import java.util.stream.Stream;

public class TestBook
{
  private Book inner;
  public TestBook() { inner = new Book(); }
  public TestBook(Book _inner) { inner = _inner; }
  public Book inner() { return inner; }

  public void update(TestBook book) { inner.update(book.inner()); }
  public void update(TestArchive archive) { inner.update(archive.inner()); }

  public String getId() { return inner.getId(); }
  public String getPath() { return inner.getPath(); }
  public String getHumanReadableIdFromPath() { return inner.getHumanReadableIdFromPath(); }
  public boolean isPathValid() { return inner.isPathValid(); }
  public String getTitle() { return inner.getTitle(); }
  public String getDescription() { return inner.getDescription(); }
  public String getLanguage() { return inner.getLanguage(); }
  public String getCreator() { return inner.getCreator(); }
  public String getPublisher() { return inner.getPublisher(); }
  public String getDate() { return inner.getDate(); }
  public String getUrl() { return inner.getUrl(); }
  public String getName() { return inner.getName(); }
  public String getFlavour() { return inner.getFlavour(); }
  public String getCategory() { return inner.getCategory(); }
  public String getTags() { return inner.getTags(); }
  public String getTagStr(String tagName) { return inner.getTagStr(tagName); }
  public long getArticleCount() { return inner.getArticleCount(); }
  public long getMediaCount() { return inner.getMediaCount(); }
  public long getSize() { return inner.getSize(); }

  public TestIllustration[] getIllustrations() { return Stream.of(inner.getIllustrations()).map(i -> new TestIllustration(i)).toArray(TestIllustration[]::new); }
  public TestIllustration getIllustration(int size) { return new TestIllustration(inner.getIllustration(size)); }
}
