package examples.pubhub.dao;

import java.util.List;
import examples.pubhub.model.Book;
import examples.pubhub.model.BookTag;

public interface TagDAO {
	
	public boolean addTag(String isbn, String tag);
	public boolean removeTag(String isbn, String tag);
	public List<BookTag> getAllTags();
	public List<Book> getAllTaggedBooks(String tag);
	
}
