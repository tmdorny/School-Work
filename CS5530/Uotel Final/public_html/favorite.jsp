<%@ page language="java" import = "Uotel.*, java.util.*" %>
<html>
<head>

</head>

<body>
<%
//public static void addFavorite(Statement statement, String user, String hid)
String username = (String) session.getAttribute("username");
String hid = request.getParameter("hid");

if (hid == null) {
%>

	Enter HID of home you would like to add as a favorite:
	<form name = "record" method=get action = "favorite.jsp">
		<input type=hidden name="hidAtt">
		<input type=text name = "hid">
		<input type=submit>
	</form>
	<BR><BR><BR><BR>
	Return to main page:
	<form name = "main" action = "mainPage.jsp">
		<button type = submit>Return</button>
	</form>

<%
} else {
	
	//hid = request.getParameter("hid");
	Connector c = new Connector();	
%> <BR>
	Status: <BR><BR>
<%	
String result = User.addFavorite(c.statement, username, hid);
out.println(result);

%>
	Add another favorite:
	<form name = "main" action = "favorite.jsp">
		<button type = submit>Return</button>
	</form>
	Back to Main Page:
	<form name = "main" action = "mainPage.jsp">
		<button type = submit>Return</button>
	</form>
<%
}
%>