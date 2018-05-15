<%@ page language="java" import = "Uotel.*" %>
<html>
<head>
</head>

<body>

<%
String user = (String) session.getAttribute("username");

String hid = request.getParameter("HID");
String score = request.getParameter("S");
String text = request.getParameter("T");
if (hid == null || score == null || text == null)
{
%>
	Enter HID of house you'd like to leave feedback for: <BR>
	<form name = "home" method = get action = "leaveFeedback.jsp">
		<input type=hidden name = "HID" value="HID">
		<input type=text name="hid">
	<BR><BR>
	Enter score for house (1-10 with 10 being the best): <BR>
	<form name = "home" method = get action = "leaveFeedback.jsp">
		<input type=hidden name = "S" value="S">
		<input type=text name="scr">
	<BR><BR>
	Enter some text describing your experience: <BR>
	<form name = "home" method = get action = "leaveFeedback.jsp">
		<input type=hidden name = "T" value="T">
		<input type=text name="review">
		<input type=submit>
	<BR><BR>
<%
} else {
	hid = request.getParameter("hid");
	score = request.getParameter("scr");
	text = request.getParameter("review");
	
	Connector con = new Connector();
%>
	<BR>
	Status: <BR><BR>
	<%String result = TemporaryHome.recordFeedback(con.statement, user, hid, score, text);
	out.println(result + "\n");%>

	<BR>
	Record Another:
	<form name = "again" action = "leaveFeedback.jsp">
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
