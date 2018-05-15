<%@ page language="java" import = "Uotel.*, java.util.*" %>
<html>
<head>

</head>

<body>
<%
// public static String addKeyword (Statement statement, String hid, String keyword, String language)
//String username = (String) session.getAttribute("username");
String hid = request.getParameter("hid");
String keyword = request.getParameter("keyword");
String language = request.getParameter("language");

if (hid == null || keyword == null || language == null) {
%>

	Enter HID you would like to add a keyword to:
	<form name = "record" method=get action = "keywords.jsp">
		<input type=hidden name="hidAtt">
		<input type=text name = "hid">
	<BR><BR>
	Enter the keyword to be added:
		<input type=hidden name="startDateAtt">
		<input type=text name = "keyword">
	<BR><BR>
	Enter language the keyword is in:
		<input type=hidden name="costPerNightAtt">
		<input type=text name = "language">	
		<input type=submit>
	</form>
	<BR><BR><BR><BR>
	Return to main page:
	<form name = "dates" action = "mainPage.jsp">
		<button type = submit>Return</button>
	</form>

<%
} else {
	
	//hid = request.getParameter("hid");
	Connector c = new Connector();	
%> <BR>
	Update Status: <BR><BR>
<%	
String result = TemporaryHome.addKeyword(c.statement, hid, keyword, language);
	if (result.contains("error"))
	{
		out.println("Problem adding keyword...");
	}
	else 
	{
		out.println(result);
	} 
%>
	<BR><BR><BR>
	Update a TH:
	<form name = "again" action = "updateTH.jsp">
		<button type = submit>Update</button>
	</form>
	
	Back to Main Page:
	<form name = "main" action = "mainPage.jsp">
		<button type = submit>Return</button>
	</form>
<%
}
%>
