<%@ page language="java" import = "Uotel.*, java.util.*" %>
<html>
<head>

</head>

<body>
<%
String owner = (String) session.getAttribute("username");
String category = request.getParameter("category");
String ThName = request.getParameter("ThName");
String ThAddress = request.getParameter("ThAddress");
String Url = request.getParameter("Url");
String ThPhone = request.getParameter("ThPhone");
String yearBuilt = request.getParameter("yearBuilt");

if (category == null || ThName == null || ThAddress == null || Url == null || ThPhone == null || yearBuilt == null) {
%>

	Enter the Type of Home Your Temporary Home is (house, apartment, etc.):
	<form name = "registerTH" method=get action = "registerTH.jsp">
		<input type=hidden name="categoryAtt">
		<input type=text name = "category">
	<BR><BR>
	Enter the Name of Your Temporary Home:
		<input type=hidden name="ThNameAtt">
		<input type=text name = "ThName">
	<BR><BR>	
	Enter the Address of Your Temporary Home:
		<input type=hidden name="ThAddressAtt">
		<input type=text name = "ThAddress">
	<BR><BR>
	Enter the URL of Your Temporary Home's Website:
		<input type=hidden name="UrlAtt">
		<input type=text name = "Url">
	<BR><BR>	
	Enter the Phone Number of Your Temporary Home:
		<input type=hidden name="ThPhoneAtt">
		<input type=text name = "ThPhone">
	<BR><BR>	
	Enter the Year Your Temporary Home was Built:
		<input type=hidden name="yearBuiltAtt">
		<input type=text name = "yearBuilt">	
		<input type=submit>
	</form>

<%
} else {
	
	category = request.getParameter("category");
	ThName = request.getParameter("ThName");
	ThAddress = request.getParameter("ThAddress");
	Url = request.getParameter("Url");
	ThPhone = request.getParameter("ThPhone");
	yearBuilt = request.getParameter("yearBuilt");
	
	Connector c = new Connector();	
%> <BR>
	Status: <BR><BR>
	<%
		String result = TemporaryHome.newTH(c.statement, owner, category, ThName, ThAddress, Url, ThPhone, yearBuilt);
		out.println(result);
%>
	<BR>	
	Add Another TH?:
	<form name = "again" action = "registerTH.jsp">
		<button type = submit>Add</button>
	</form>
	
	Back to Main Page:
	<form name = "main" action = "mainPage.jsp">
		<button type = submit>Return</button>
	</form>
<%
} 
%>


</body>
