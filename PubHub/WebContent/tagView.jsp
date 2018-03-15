	<jsp:include page="header.jsp" />
<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<!DOCTYPE html >
	<header>
	  <div class="container">
	
	    <h1>PUBHUB <small>Change Tags</small></h1>
		<hr class="book-primary">
		
		
	    <h4>Use the form below to tag a book</h4>
  			<form method="post"> 
     		ISBN: <input type="text" name="isbn13" />
     		Name: <input type="text" name="tagName" />
     		<input type="submit" value="Add Tag" />
  		</form>
  		<table class="table table-striped table-hover table-responsive pubhub-datatable">
			<thead>
				<tr>
					<td>ISBN-13:</td>
					<td>TAG:</td>
					<td></td>
				</tr>
			</thead>
			<tbody>
               <c:forEach var="BookTag" items="${tags}">
					<tr>
						<td><c:out value="${BookTag.isbn13}" /></td>						
						<td><c:out value="${BookTag.tagName}" /></td>
						<td><form action="DeleteTag" method="post">
								<input type="hidden" name="isbn13" value="${BookTag.isbn13}">
								<input type="hidden" name="tagName" value="${BookTag.tagName}">
								<button class="btn btn-primary">Delete</button>
							</form></td>
					</tr>
				</c:forEach>
			</tbody>
		</table>
  <hr/>

	  </div>
	</header>
	
	
	<!-- Footer -->
	<jsp:include page="footer.jsp" />	