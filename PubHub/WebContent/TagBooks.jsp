	<!-- Header -->
	<jsp:include page="header.jsp" />
	
	<!-- JSTL includes -->
	<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
	<%@ taglib uri="http://java.sun.com/jsp/jstl/fmt" prefix="fmt"%>
	<%@ taglib uri="http://java.sun.com/jsp/jstl/functions" prefix="fn"%>
<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<header>
   <div class="container">
   
	 <h1>PUBHUB <small>Find Books</small></h1>
	 <hr class="book-primary">
			
	   <h4>Search for your book using a tag</h4>
	  <form action="GetTaggedBooks" method="post">
	     Name: <input type="text" name="tagName" />
	     <input type="submit" value="Tagged Books" />
	  </form>
		<table class="table table-striped table-hover table-responsive pubhub-datatable">
			<thead>
				<tr>
					<td>ISBN-13:</td>
					<td>Title:</td>
					<td>Author:</td>
					<td>Publish Date:</td>
					<td>Price:</td>
					<td></td>
					<td></td>
				</tr>
			</thead>
			<tbody>
				<c:forEach var="book" items="${books}">
					<tr>
						<td><c:out value="${book.isbn13}" /></td>
						
						<td><c:out value="${book.title}" /></td>
						<td><c:out value="${book.author}" /></td>
						<td><c:out value="${book.publishDate}" /></td>
						<td><fmt:formatNumber value="${book.price }" type="CURRENCY"/></td>
						<td><form action="DownloadBook" method="get">
								<input type="hidden" name="isbn13" value="${book.isbn13}">
								<button class="btn btn-success">Download</button>
							</form></td>
						<td><form action="ViewBookDetails?isbn=${book.isbn13}" method="get">
								<input type="hidden" name="isbn13" value="${book.isbn13}">
								<button class="btn btn-primary">Details</button>
							</form></td>
					</tr>
				</c:forEach>
			</tbody>
		</table>
  </div>
</header>
  
	<jsp:include page="footer.jsp" />	