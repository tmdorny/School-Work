1. Compile the java code in WEB-INF/classes: javac cs5530/*.java

2. Edit the web.xml in WEB-INF; replace Your Name with your first name
and last name.

3. Access your homepage via http://georgia.eng.utah.edu:8080/~5530ux
(replace x with your user id, e.g., 5530u01).

4. You can search by login using `user1' or 'user2', or search by director
name using 'Kubrick'. 

4. To work on your own database, you need to modify the credentials in Connector.java (so that it connects to your own database, rather than the class-wide database cs5530db). Note that the sample JSP code then will not work, since the "orders" table does not exist in your own database. You can always use the distributed script orders.sql (use "source orders.sql;" in mysql client) to re-produce that table in your own database, so that the sample JSP code will work with your own database. (be careful when doing this if your database already has a "orders" table from your phase 1; that table will be overwritten. To avoid that, change the orders.sql script to have a different table name, and also change the Orders.java code to query the new table instead).

5. Place any of your JSP pages directly under the public_html folder, and your java code
with the necessary package folder structure under the WEB-INF/classes folder.
You can then access your abc.jsp page from http://georgia.eng.utah.edu:8080/~5530ux/abc.jsp. And inside your abc.jsp page, you can import your java class (see orders.jsp for an example).

PHASE 3 TEAM 5530u28 README:::::::

Notes:

-Keyword addition is found by browsing to updateTH.jsp and clicking the keyword button there.

-rate.jsp is a "helper" page used by rateFeedback to store feedback scores in the database.

-viewDates.jsp displays available dates for the provided hid and is accessable from reserve.jsp
so a user can see what dates are available for a given TH, does not modify database.

- Leaving all fields blank in the browse function returns all THs with available dates.

TESTING INSTRUCTIOns

-User ttest with password t can utilize all browse functionalilty.

-User ttest has temporary homes hid 4 and 5

-TH id of 6 is available for reservation from 2017-06-06 to 2017-06-30 for 100/night and has info: 
(type: Apartment, name: Test Zone, address: 1234 Test Road, URL: realtest.com, phone: 801-111-1111, yearbuilt: 2011)

-hid 6 has keywords 'nice' and 'comfy' in language 'English'

-once a reservation is made, change in available dates can be found by navigating to 'Reserve a Temporary Home:' and clicking the view dates button

-User ttest has 1 stay recorded in TH 6 from 2017-06-03 to 2017-06-06

-ttest added TH 6 to their favorites.

-ttest submitted a review for TH 6

-ttest trusts reviews from user Alex and doesn't trust reviews from user tim

-user 'tim' is the owner of TH 6

-ttest rated feedback on TH 5 with a score of 0

-suggestions can be found within the checkout page

-user ttest gets suggested TH 0 and TH 1 based on similar visits from user Alex to TH 6, 1, and 0

-all other functionalilty is usable by user ttest, feel free to make new users and add as much content as needed.

