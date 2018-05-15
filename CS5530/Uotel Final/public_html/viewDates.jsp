<%@ page language="java" import = "Uotel.*, java.util.*" %>
<html>
<head>

</head>

<body>
<%
String hid = request.getParameter("hid");

if (hid == null) {
%>

	Enter HID of house to view available dates:
	<form name = "record" method=get action = "viewDates.jsp">
		<input type=hidden name="hidAtt">
		<input type=text name = "hid">
		<input type=submit>
	</form>

<%
} else {
	
	hid = request.getParameter("hid");
	//from = request.getParameter("start");
	//to = request.getParameter("end");
	Connector c = new Connector();	
%> <BR>
	Available Dates for TH <% out.println(hid); %>: <BR><BR>
<%	
String result = TemporaryHome.getAvailableDates(c.statement, hid);
	if (result.charAt(0) == 'E')
	{
		out.println("No available dates for this TH...");
	}
	else {
		out.println(result);
	} 
%>
	<BR><BR><BR>
	Reserve A TH:
	<form name = "again" action = "reserve.jsp">
		<button type = submit>Reserve</button>
	</form>
	
	Back to Main Page:
	<form name = "main" action = "mainPage.jsp">
		<button type = submit>Return</button>
	</form>
<%
}
%>
