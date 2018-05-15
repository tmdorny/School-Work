<%@ page language="java" import = "Uotel.*" %>
<html>
<head>
</head>

<body>

<%
String user = (String) session.getAttribute("username");

String userToJudge = request.getParameter("U");
String rating = request.getParameter("R");
if (userToJudge == null || rating == null)
{
%>
	Enter username of user you'd like to rate: <BR>
	<form name = "home" method = get action = "rateUser.jsp">
		<input type=hidden name = "U" value="U">
		<input type=text name="usr">
	<BR><BR>
	Enter rating (0-not trusted, 1-trusted): <BR>
		<input type=hidden name = "R" value="R">
		<input type=text name="rate">
		<input type = submit>
	</form>
	<BR><BR>
<%
} else {
	userToJudge = request.getParameter("usr");
	rating = request.getParameter("rate");

	Connector con = new Connector();
%>
	<BR>
	Status: <BR><BR>
	<%String result = User.declareTrust(con.statement, user, userToJudge, rating);
	out.println(result + "\n");%>

	<BR>
	Record Another:
	<form name = "again" action = "rateUser.jsp">
	<button type=submit>Record</button>
	</form>

	<BR>
	Back to Main Page:
	<form name = "main" action = "mainPage.jsp">
	<button type=submit>Return</button>
	</form>

<%
}
%>
</body>
