<%@ page language="java" import = "Uotel.*, java.util.*" %>
<html>
<head>

</head>

<body>
<%

String username = (String) session.getAttribute("username");
String hid = request.getParameter("hid");
String nights = request.getParameter("nights");
String startDate = request.getParameter("startDate");
String endDate = request.getParameter("endDate");
int dates = 0;

if (hid == null) {
%>

	Enter HID of house you would like to reserve:
	<form name = "record" method=get action = "reserve.jsp">
		<input type=hidden name="hidAtt">
		<input type=text name = "hid">
	<BR><BR>
	Enter the number of nights you would like to stay:
		<input type=hidden name="nightsAtt">
		<input type=text name = "nights">
	<BR><BR>
	Enter your desired check-in date (YYYY-MM-DD):
		<input type=hidden name="startDateAtt">
		<input type=text name = "startDate">
	<BR><BR>	
	Enter your desired check-out date (YYYY-MM-DD):
		<input type=hidden name="endDateAtt">
		<input type=text name = "endDate">	
		<input type=submit>
	</form>
	<BR><BR><BR><BR>
	Browse Available Dates:
	<form name = "dates" action = "viewDates.jsp">
		<button type = submit>View</button>
	</form>

<%
} else {
	
	hid = request.getParameter("hid");
	Connector c = new Connector();	
%> <BR>
	Reservation Status: <BR><BR>
	<%String result = TemporaryHome.startReserveTH(c.statement, hid, username, nights, startDate, endDate);
	if (result.charAt(0) == 'E')
	{
		out.println("There was a problem reserving the specified dates.");
	}
	else
	{
		ArrayList<String> list = (ArrayList<String>) session.getAttribute("pendingReserves");
		if (list != null) {
			list.add(result);
		}
		//out.println(result);
		session.setAttribute("pendingReserves", list);
		out.println("Reservation recorded Successfully! To confirm your reservation, select 'Checkout' on the main page!");	
	}
	%>
	<BR>	
	Reserve Another:
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
</body>
