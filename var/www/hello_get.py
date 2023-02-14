#!/usr/bin/python3

# Import modules for CGI handling
import cgi, cgitb
import time

# Create instance of FieldStorage
form = cgi.FieldStorage()

# Get data from fields
first_name = form.getvalue('first_name')
last_name  = form.getvalue('last_name')

print("Content-type:text/html\r\n\r\n")
print("<html>")
print("<head>")
print("<title>Hello - CGI Program</title>")
print("</head>")
print("<body>")
print("<h2>Hello %s %s</h2>" % (first_name, last_name))
# time.sleep(2)
# print("<h2>stop sleeping</h2>")
print("</body>")
print("</html>")
