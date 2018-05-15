<%@ page language="java" import = "Uotel.*, java.util.*" %>
<html>
<head>

</head>

<body>
<%
//public static Map<Integer, String> getFeedbackArray(Statement statement, String user, String hid) {
String username = (String) session.getAttribute("username");
String hid = request.getParameter("hid");

if (hid == null) {
%>

	Enter HID you would like to rate feedback for:
	<form name = "record" method=get action = "rateFeedback.jsp">
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
	Update Status: <BR><BR>
<%	
HashMap<Integer, String> result = TemporaryHome.getFeedbackArray(c.statement, username, hid);
for (int i : result.keySet()){
	
	%>Feedback: <BR><BR> <%
	out.println("FID: " +  i + " " + result.get(i));
	%><BR><BR><BR> <%
}
%>
	Take note of a review's FID and rate feedback:
	<form name = "rate" action = "rate.jsp">
		<button type = submit>Rate</button>
	</form>
	Back to Main Page:
	<form name = "main" action = "mainPage.jsp">
		<button type = submit>Return</button>
	</form>
<%
}
%>