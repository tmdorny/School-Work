<%@ page language="java" import = "Uotel.*" %>
<html>
<head>
</head>

<body>

<%
String user = (String) session.getAttribute("username");

String hid = request.getParameter("H");
String num = request.getParameter("N");
if (hid == null || num == null)
{
%>
	Enter the ID of the home you'd like to view feedback for: <BR>
	<form name = "home" method = get action = "getFeedback.jsp">
		<input type=hidden name = "H" value="H">
		<input type=text name="id">
	<BR><BR>
	Enter number of comments you'd like to see: <BR>
		<input type=hidden name = "N" value="N">
		<input type=text name="nums">
		<input type = submit>
	</form>
	<BR><BR>
<%
} else {
	hid = request.getParameter("id");
	num = request.getParameter("nums");

	Connector con = new Connector();
%>
	<BR>
	Results: <BR><BR>
	<pre>
	<%String result = TemporaryHome.getFeedback(con.statement, hid, num);
	out.println(result + "\n");%>
	</pre>

	<BR>
	See More:
	<form name = "again" action = "getFeedback.jsp">
	<button type=submit>Continue</button>
	</form>
	
	<BR>
	Rate Feedback:
	<form name = "again" action = "rateFeedback.jsp">
	<button type=submit>Rate</button>
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
