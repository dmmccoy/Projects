package examples.pubhub.servlets;

import java.io.IOException;
import java.util.ArrayList;
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
 * Servlet implementation class TagServlet
 */
@WebServlet("/AddTag")
public class TagServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
    /**
     * @see HttpServlet#HttpServlet()
     */
    public TagServlet() {
        super();
		TagDAO dao = DAOUtilities.getTagDAO();
		List<BookTag> tagList = dao.getAllTags();
        
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		TagDAO dao = DAOUtilities.getTagDAO();
		List<BookTag> tagList = dao.getAllTags();
		request.setAttribute("tags", tagList);
		request.getRequestDispatcher("tagView.jsp").forward(request, response);
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String isbn = request.getParameter("isbn13");
		String name = request.getParameter("tagName");
		
		TagDAO dao = DAOUtilities.getTagDAO();
		List<BookTag> tagList = dao.getAllTags();
		

		dao.addTag(isbn, name);
		
		request.setAttribute("tags", tagList);
		response.setHeader("Refresh", "0; URL=" + request.getContextPath() + "/AddTag");
		request.getRequestDispatcher("tagView.jsp").forward(request, response);
	}

}
