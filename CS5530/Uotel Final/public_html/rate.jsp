<%@ page language="java" import = "Uotel.*, java.util.*" %>
<html>
<head>

</head>

<body>
<%
// public static String rateFeedback(Statement statement, String login, String fid, String rating)
String username = (String) session.getAttribute("username");
String rating = request.getParameter("rating");
String fid = request.getParameter("fid");

if (rating == null || fid == null) {
%>

	Enter FID of feedback you would like to rate:
	<form name = "record" method=get action = "rate.jsp">
		<input type=hidden name="fidAtt">
		<input type=text name = "fid">
	<BR><BR>
	Enter the feedback score (0 - poor; 1 - helpful; 2 - very helpful):
		<input type=hidden name="ratingAtt">
		<input type=text name = "rating">
		<input type=submit>
	</form>
	<BR><BR><BR><BR>
	Return to feedback:
	<form name = "dates" action = "rateFeedback.jsp">
		<button type = submit>Return</button>
	</form>
	Return to main page:
	<form name = "dates" action = "mainPage.jsp">
		<button type = submit>Return</button>
	</form>

<%
} else {
	
	//hid = request.getParameter("hid");
	Connector c = new Connector();	
%> <BR>
	Rating Status: <BR><BR>
<%	
String result = TemporaryHome.rateFeedback(c.statement, username, fid, rating);
out.println(result);
%>
	<BR><BR><BR>
	Return to feedback:
	<form name = "again" action = "rateFeedback.jsp">
		<button type = submit>Return</button>
	</form>
	
	Back to Main Page:
	<form name = "main" action = "mainPage.jsp">
		<button type = submit>Return</button>
	</form>
<%
}
%>