<%@ page language="java" import = "Uotel.*, java.util.*" %>
<html>
<head>

</head>

<body>
<%
String username = (String) session.getAttribute("username");
String hid = request.getParameter("givenHID");
String from = request.getParameter("start");
String to = request.getParameter("end");

if (hid == null || from == null || to == null) {
%>

	Enter ID of house you stayed at:
	<form name = "record" method=get action = "recordStay.jsp">
		<input type=hidden name="hid">
		<input type=text name = "givenHID">
	<BR><BR>
	Enter Start date of stay (format: YYYY-MM-DD):
		<input type=hidden name="startDate">
		<input type=text name = "start">
	<BR><BR>	
	Enter end date of stay (format: YYYY-MM-DD):
		<input type=hidden name="endDate">
		<input type=text name = "end">
		<input type=submit>
	</form>

<%
} else {
	
	hid = request.getParameter("givenHID");
	from = request.getParameter("start");
	to = request.getParameter("end");
	Connector c = new Connector();	
%> <BR>
	Status: <BR><BR>
	<%String result = TemporaryHome.recordStay(c.statement, username, hid, from, to);
	if (result.charAt(0) == 'E')
	{
		out.println(result);
	}
	else
	{
		ArrayList<String> list = (ArrayList<String>) session.getAttribute("pendingStays");
		list.add(result);
		session.setAttribute("pendingStays", list);
		out.println("Stay recorded Successfully! To confirm this recorded stay, select 'Checkout' from the main page!");	
	}
%>
	<BR>	
	Record Another:
	<form name = "again" action = "recordStay.jsp">
		<button type = submit>Record</button>
	</form>
	
	Back to Main Page:
	<form name = "main" action = "mainPage.jsp">
		<button type = submit>Return</button>
	</form>
<%
} 
%>


</body>
