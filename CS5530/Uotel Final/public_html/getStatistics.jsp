<%@ page language="java" import = "Uotel.*" %>
<html>
<head>
</head>

<body>

<%
String num = request.getParameter("N");
if (num == null || request.getParameter("nums") == "")
{
%>
	Enter number of statistics you'd like to see: <BR>
	<form name = "home" method = get action = "getStatistics.jsp">
		<input type=hidden name = "N" value="N">
		<input type=text name="nums">
		<input type = submit>
	</form>
	<BR><BR>
<%
} else {
	num = request.getParameter("nums");

	Connector con = new Connector();
%>
	<BR>
	Results: <BR><BR>
	<pre>
	<%String result = TemporaryHome.statistics(con.statement,  num);
	out.println(result + "\n");%>
	</pre>
	<BR>
	See More:
	<form name = "again" action = "getStatistics.jsp">
	<button type=submit>Continue</button>
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
