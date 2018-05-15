<%@ page language="java" import = "Uotel.*, java.util.*" %>
<html>
<head>

</head>

<body>
<%
//public static ArrayList<String> browse(Statement statement, String login, String lowerBound, String upperBound, String locationConstraint, String keyword, String category, String sort) {
String username = (String) session.getAttribute("username");
String lowerBound = request.getParameter("lowerBound");
String upperBound = request.getParameter("upperBound");
String locationConstraint = request.getParameter("locationConstraint");
String keyword = request.getParameter("keyword");
String category = request.getParameter("category");
String sort = request.getParameter("sort");

if (((lowerBound == null || upperBound == null) && locationConstraint == null && keyword == null && category == null) || sort == null) {
%>

	Enter lower bound for price range constraint:
	<form name = "record" method=get action = "browse.jsp">
		<input type=hidden name="lowerBoundAtt">
		<input type=text name = "lowerBound">
	<BR><BR>
	Enter upper bound for price range constraint:
		<input type=hidden name="upperBoundAtt">
		<input type=text name = "upperBound">
	<BR><BR>
	Enter the desired TH location (city, state, etc):
		<input type=hidden name="locationConstraintAtt">
		<input type=text name = "locationConstraint">
	<BR><BR>	
	Enter keyword to match:
		<input type=hidden name="keywordAtt">
		<input type=text name = "keyword">	
	<BR><BR>
	Enter TH category to match:
		<input type=hidden name="categoryAtt">
		<input type=text name = "category">
	<BR><BR>
	Enter sort filter (1 - price; 2 - Overall Feedback; 3- Trusted Feedback):
		<input type=hidden name="sortAtt">
		<input type=text name = "sort">
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
	Matching Homes: <BR><BR>
<pre>
<%
//public static ArrayList<String> browse(Statement statement, String login, String lowerBound, String upperBound, String locationConstraint, String keyword, String category, String sort) {

String result = TemporaryHome.browse(c.statement, username, lowerBound, upperBound, locationConstraint, keyword, category, sort);	
out.println(result);
%>
</pre>
	Browse more homes:
	<form name = "browse" action = "browse.jsp">
		<button type = submit>Browse</button>
	</form>
	Back to Main Page:
	<form name = "main" action = "mainPage.jsp">
		<button type = submit>Return</button>
	</form>
<%
}
%>
