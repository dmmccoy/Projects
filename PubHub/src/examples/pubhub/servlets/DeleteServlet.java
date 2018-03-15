package examples.pubhub.servlets;

import java.io.IOException;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import examples.pubhub.dao.TagDAO;
import examples.pubhub.model.BookTag;
import examples.pubhub.utilities.DAOUtilities;

/**
 * Servlet implementation class DeleteServlet
 */
@WebServlet("/DeleteTag")
public class DeleteServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public DeleteServlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String isbn = request.getParameter("isbn13");
		String name = request.getParameter("tagName");
		TagDAO dao = DAOUtilities.getTagDAO();
		List<BookTag> tagList = dao.getAllTags();
		dao.removeTag(isbn, name);
		request.setAttribute("tags", tagList);
		response.setHeader("Refresh", "0; URL=" + request.getContextPath() + "/AddTag");
		request.getRequestDispatcher("tagView.jsp").forward(request, response);
	}

}
