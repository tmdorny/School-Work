<%@ page language="java" import="Uotel.*" %>
<html>
<head>
</head>

<body>
Welcome to Uotel, 
<%= session.getAttribute("username") %>
!
<BR><BR><BR>

To Reserve a Temporary Home:
<form name = "toReserve" action = "reserve.jsp">
<button type="submit">Reserve</button>
</form>
<BR><BR>

To Register a new Temporay Home:
<form name = "toRegister" action = "registerTH.jsp">
<button type="submit">Register</button>
</form>
<BR><BR>

To Update Information of a Temporay Home:
<form name = "toRegister" action = "updateTH.jsp">
<button type="submit">Register</button>
</form>
<BR><BR>

To Record a Stay:
<form name = "toRecord" action = "recordStay.jsp">
<button type="submit">Record</button>
</form>
<BR><BR>

Declare a Favorite:
<form name = "toFavorite" action = "favorite.jsp">
<button type="submit">Favorite</button>
</form>
<BR><BR>

Leave Feedback:
<form name = "toLeaveFeedback" action = "leaveFeedback.jsp">
<button type="submit">Review</button>
</form>
<BR><BR>

Rate Feedback by Usefulness:
<form name = "toRate" action = "rateFeedback.jsp">
<button type="submit">Rate</button>
</form>
<BR><BR>

Rate Users "trusted" or "not-trusted":
<form name = "toRateUser" action = "rateUser.jsp">
<button type="submit">Rate</button>
</form>
<BR><BR>

Browse Temporary Homes:
<form name = "toBrowse" action = "browse.jsp">
<button type="submit">Browse</button>
</form>
<BR><BR>

Get Most Useful Feedback:
<form name = "toGetFeedback" action = "getFeedback.jsp">
<button type="submit">Get Feedback</button>
</form>
<BR><BR>

Get Temporary Home Suggestions:
<form name = "toSuggestions" action = "getSuggestions.jsp">
<button type="submit">Suggestions</button>
</form>
<BR><BR>

Get Statistics of Temporary Homes:
<form name = "toStatistics" action = "getStatistics.jsp">
<button type="submit">Stats</button>
</form>
<BR><BR>

Checkout and Confirm Reservations and Stays:
<form name = "checkout" action = "checkout.jsp">
<button type="submit">Checkout</button>
</form>
<BR><BR>

Logout:
<form name = "logout" action = "login.jsp">
<button type = "submit">Logout</button>
</form>
</body>
