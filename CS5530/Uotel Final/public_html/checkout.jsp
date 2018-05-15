<%@ page language="java" import = "Uotel.*, java.util.*" %>
<html>
<head>

</head>
<body>

<%
String username = (String) session.getAttribute("username");
String conf = request.getParameter("Conf");
ArrayList<String> stays = (ArrayList<String>)session.getAttribute("pendingStays");
ArrayList<String> reservs = (ArrayList<String>)session.getAttribute("pendingReserves");

if (stays == null || reservs == null) 
{
	%>	
	No stays or reservations awaiting confirmation...
	<BR>
	Return to main menu:
	<BR><BR>
	<form action = "mainPage.jsp" name = "toMain">
	<button type="submit">Main Page </button>
	</form>

	<BR><BR>
	Logout:
	<form action = "login.jsp" name = "logout">
	<button type="submit">Logout</button>
	</form>
<%
}
else if (conf == null)
{
%> <pre> <%
	for (String s: reservs) {
		String[] split = s.split("\\s+");

		out.println("Confirm Reservation at Home " + split[5] + " from " + split[0] + " to " + split[1] + "?\n");
	}

	for (String s1: stays) {
		String hid = s1.substring(0,1);
		out.println("Confirm Stay at Home " + hid + "?\n"); 	
	} 


%> </pre>
	<BR><BR>
	Confirm These Reservations/Stays? (y/n) <BR>
	<form action = "checkout.jsp" method=get>
		<input type = hidden name="Conf" value="Conf">
		<input type=text name = "Confirm">
		<input type = "submit">
	</form>
	View suggested homes for a given hid:
	<form name = "main" action = "getSuggestions.jsp">
		<button type = submit>Return</button>
	</form>
<%
} else {
	conf = request.getParameter("Confirm");
	if (conf.equals("y"))
	{
	out.println("Confirming reservations/stays.\n");
	Connector con = new Connector();
		for(String s: reservs)
		{
			out.println(TemporaryHome.finishReserveTH(con.statement, s, username));
			out.println("\n");
		}
		for(String s1: stays)
		{
			out.println(TemporaryHome.finishRecordStay(con.statement, s1));
			out.println("\n");
		}

	reservs.clear();
	stays.clear();
	session.setAttribute("pendingStays", stays);
	session.setAttribute("pendingReserves", reservs);
	}
	else
	{
		out.println("Reservations/Stays Not Confirmed\n");
	}

%>	<BR><BR>
	<form action = "mainPage.jsp" name = "toMain">
	<button type="submit">Main Page </button>
	</form>

	<BR><BR>
	<form action = "login.jsp" name = "logout">
	<button type="submit">Logout</button>
	</form>
<%
} 
%>
</body>
