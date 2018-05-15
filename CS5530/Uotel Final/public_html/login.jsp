<%@ page language="java" import="Uotel.*, java.util.*" %>
<html>
<head>
<script LANGUAGE="javascript">
function check_all_fields(form_obj){
	//alert(form_obj.username.value+"='"+form_obj.username.value+"'");
	if( form_obj.user.value == ""){
		alert("Please enter username.");
		return false;
	}
	if( form_obj.pass.value == ""){
		alert("Please enter password.");
		return false;
	}	
	return true;
}
</script> 
</head>
<body>

<%
//Values for loging in or registering
String user = request.getParameter("username");
String pass = request.getParameter("password");

String newUser = request.getParameter("newUsername");
String newPass = request.getParameter("newPassword");
String newPassVerif = request.getParameter("newPasswordVerif");
String name = request.getParameter("newName");
String address = request.getParameter("newAddress");
String phone = request.getParameter("newPhone");

//Use forms to input info
if( (user == null || pass == null) && (newUser == null || newPass == null)){
%>
	Username:
	<form name="username" method=get onsubmit="return check_all_fields(this)" action="login.jsp">
		<input type=hidden name="username" value="username">
		<input type=text name="user">
	<BR><BR>
	Password: <BR>
		<input type=hidden name="password" value="password">
		<input type=text name="pass">
		<input type=submit>
	</form>

	<BR><BR><BR>
	Register as new User: <BR>
	Username:
	<form name="register" method=get onsubmit="return check_all_fields(this)" action="login.jsp">
		<input type=hidden name="newUsername">
		<input type=text name="newUser">
	<BR><BR>
	Password: <BR>
		<input type=hidden name="newPassword">
		<input type=text name="newPass">
	<BR><BR>
	Verify Password: <BR>
		<input type=hidden name="newPasswordVerif">
		<input type=text name="newPassVerif">
	<BR><BR>
	Name: <BR>
		<input type=hidden name="newName">
		<input type=text name="name">
	<BR><BR>
	Address: <BR>
		<input type=hidden name="newAddress">
		<input type=text name="address">
	<BR><BR>
	Phone (format: XXX-XXX-XXXX): <BR>
		<input type=hidden name="newPhone">
		<input type=text name="phone">
		<input type=submit>
	</form>	

<%

//If the user is loging in:
} else if (newUser == null || newPass == null) {

	user = request.getParameter("user");
	pass = request.getParameter("pass");

	out.println("Username: ");
	out.println(user + "            ");
	out.println(pass);
	Connector connector = new Connector();
	
%>  <BR>
  Login Status: <BR><BR>
  <%String status = User.login(connector.statement, user, pass);
    out.println(status);%> <BR><BR>
  
<%
	if (status.equals("Login Successful!"))
	{
		ArrayList<String> reserveStrings = new ArrayList<String>();
		ArrayList<String> stayStrings = new ArrayList<String>();
		
		session.setAttribute("pendingReserves", reserveStrings);
		session.setAttribute("pendingStays", stayStrings);
		session.setAttribute("username", user);
		session.setAttribute("con", connector);
		
		response.sendRedirect(response.encodeRedirectUrl("mainPage.jsp"));		
	}

//If the user is registering a new user	
} else if (user == null || pass == null) {
	newUser = request.getParameter("newUser");
	newPass = request.getParameter("newPass");
	newPassVerif = request.getParameter("newPassVerif");
	name = request.getParameter("name");
	address = request.getParameter("address");
	phone = request.getParameter("phone");
	
	Connector connector = new Connector();
%> <BR>
Register Status: <BR><BR>
	<%String regStatus = User.register(connector.statement, newUser, newPass, newPassVerif, name, address, phone);
	out.println(regStatus);%> <BR><BR>

<%
	if (regStatus.equals("Registration Successful!"))
	{
		ArrayList<String> reserveStrings = new ArrayList<String>();
		ArrayList<String> stayStrings = new ArrayList<String>();
		
		session.setAttribute("pendingReserves", reserveStrings);
		session.setAttribute("pendingStays", stayStrings);
		session.setAttribute("username", newUser);
		session.setAttribute("con", connector);

		response.sendRedirect(response.encodeRedirectUrl("mainPage.jsp"));	
	}
}
%>
</body>
