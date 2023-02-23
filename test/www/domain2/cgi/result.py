#!/usr/bin/python3

# Import modules for CGI handling
import cgi, cgitb
import time

# Create instance of FieldStorage
form = cgi.FieldStorage()

# Get data from fields
postContent = form.getvalue('contentPost')
getContent = form.getvalue('contentGet')

print("Set-Cookie:lastvisit=" + str(time.time()))
print("Content-type:text/html\r\n\r\n")
print("<html>")
print("<head>")
print("<title>Hello - CGI Program</title>")
print("</head>")
print("<body>")
print("<h2>post %s</h2>" % (postContent))
print("<h2>get %s</h2>" % (getContent))
print("</body>")
print("</html>")
