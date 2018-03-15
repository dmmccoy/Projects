package examples.pubhub.servlets;

import java.io.IOException;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import examples.pubhub.dao.BookDAO;
import examples.pubhub.dao.TagDAO;
import examples.pubhub.model.Book;
import examples.pubhub.model.BookTag;
import examples.pubhub.utilities.DAOUtilities;

/**
 * Servlet implementation class GetTaggedBooks
 */
@WebServlet("/GetTaggedBooks")
public class GetTaggedBooks extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public GetTaggedBooks() {
        super();
        // TODO Auto-generated constructor stub
    }
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

		request.getRequestDispatcher("TagBooks.jsp").forward(request, response);
	}
	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		TagDAO dao = DAOUtilities.getTagDAO();
		String name = request.getParameter("tagName");
		List<Book> books = dao.getAllTaggedBooks(name);
		List<BookTag> tagList = dao.getAllTags();
		

		
		request.setAttribute("books", books);
		request.setAttribute("tags", tagList);
		request.getRequestDispatcher("TagBooks.jsp").forward(request, response);
	}

}
