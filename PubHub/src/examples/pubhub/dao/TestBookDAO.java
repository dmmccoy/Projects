package examples.pubhub.dao;

import java.util.List;

import examples.pubhub.model.Book;

public class TestBookDAO {

	  public static void main(String[] args){
		    BookDAO dao = new BookDAOImpl();
		    
		    List<Book> list = dao.getAllBooks();

		    for (int i = 0; i < list.size(); i++){
		      Book t = list.get(i);
		      System.out.println(t.getAuthor());
		    }
		  }	
}
