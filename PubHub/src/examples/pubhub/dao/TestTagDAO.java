package examples.pubhub.dao;

import java.util.List;

import examples.pubhub.model.Book;
import examples.pubhub.model.BookTag;

public class TestTagDAO {

	  public static void main(String[] args){
		    TagDAO dao = new TagDAOImpl();
		    String isbn = "1111111111111";
		    String tag = "nimmy";
		    if(dao.addTag(isbn, tag) == false) return;
		    List<BookTag> list = dao.getAllTags();

		    for (int i = 0; i < list.size(); i++){
		      BookTag t = list.get(i);
		      System.out.println(t.getIsbn13() + " " + t.getTagName());
		    }
		    System.out.println("trying to get all tagged books");
		    List<Book> list2 = dao.getAllTaggedBooks("nimmy");
		    for (int i = 0; i < list2.size(); i++){
		      Book b = list2.get(i);
		      System.out.println(b.getIsbn13() + " " + b.getAuthor());
		    }
		    if(dao.removeTag(isbn, tag) == false) return;
	     list = dao.getAllTags();

	    for (int i = 0; i < list.size(); i++){
	      BookTag t = list.get(i);
	      System.out.println(t.getIsbn13() + " " + t.getTagName());
	    }
	  }
}
