<%@ page language="java" import = "Uotel.*, java.util.*" %>
<html>
<head>

</head>

<body>
<%
//public static String getSuggestions(Statement statement, String hid)
String username = (String) session.getAttribute("username");
String hid = request.getParameter("hid");

if (hid == null) {
%>

	Enter HID for suggestions of similar homes:
	<form name = "record" method=get action = "getSuggestions.jsp">
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
	Suggested Homes: <BR><BR>
<pre>
<%	
String result = TemporaryHome.getSuggestions(c.statement, hid);
out.println(result);

%>
</pre>
	Browse Available Dates:
	<form name = "dates" action = "viewDates.jsp">
		<button type = submit>View</button>
	</form>
	Back to Main Page:
	<form name = "main" action = "mainPage.jsp">
		<button type = submit>Return</button>
	</form>
<%
}
%>
