<%@ page language="java" import = "Uotel.*, java.util.*" %>
<html>
<head>

</head>

<body>
<%
// public static String updateTH(Statement statement, String owner, int hid, String startDate, String endDate, String costPerNight)
String username = (String) session.getAttribute("username");
String hid = request.getParameter("hid");
String startDate = request.getParameter("startDate");
String endDate = request.getParameter("endDate");
String costPerNight = request.getParameter("costPerNight");

if (hid == null) {
%>

	Enter HID you would like to update:
	<form name = "record" method=get action = "updateTH.jsp">
		<input type=hidden name="hidAtt">
		<input type=text name = "hid">
	<BR><BR>
	Enter the beginning of your TH's availability (YYYY-MM-DD):
		<input type=hidden name="startDateAtt">
		<input type=text name = "startDate">
	<BR><BR>
	Enter the end of your TH's availability (YYYY-MM-DD):
		<input type=hidden name="endDateAtt">
		<input type=text name = "endDate">
	<BR><BR>	
	Enter the cost per night of your TH's availability window:
		<input type=hidden name="costPerNightAtt">
		<input type=text name = "costPerNight">	
		<input type=submit>
	</form>
	<BR><BR><BR><BR>
	Add keywords describing your TH:
	<form name = "dates" action = "keywords.jsp">
		<button type = submit>Go</button>
	</form>

<%
} else {
	
	//hid = request.getParameter("hid");
	Connector c = new Connector();	
%> <BR>
	Update Status: <BR><BR>
<%	
String result = TemporaryHome.updateTH(c.statement, username, hid, startDate, endDate, costPerNight);
	if (result.contains("error"))
	{
		out.println("Problem updating TH...");
	}
	else if (result.contains("own")) 
	{
		out.println("You do not own this TH...");
	}
	else 
	{
		out.println(result);
	} 
%>
	<BR><BR><BR>
	Update another TH:
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