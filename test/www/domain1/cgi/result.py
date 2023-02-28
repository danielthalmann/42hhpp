#!/usr/bin/python3

# Import modules for CGI handling
import cgi, os, time, urllib.request

# Create instance of FieldStorage
form = cgi.FieldStorage()

# Get data from fields
postContent = str(form.getvalue('contentPost'))
getContent = str(form.getvalue('contentGet'))
lastvisit = str(time.strftime("%a, %d %b %Y %H:%M:%S +0100"))

print("Set-Cookie: contentPost=" + postContent, end=";\r\n")
print("Set-Cookie: contentGet=" + getContent, end=";\r\n")
print("Set-Cookie: lastvisit=" + lastvisit, end=";\r\n")
print("Content-type:text/html", end="\r\n\r\n")

print("<html>")
print("<head>")
print("<title>Hello - CGI Program</title>")
print("</head>")
print("<body>")
if 'HTTP_COOKIE' in os.environ.keys():
    for cookie in os.environ['HTTP_COOKIE'].split(';'):
        print(urllib.request.unquote(cookie), end="<br>")
print("<h2>post %s</h2>" % (postContent))
print("<h2>get %s</h2>" % (getContent))
print("</body>")
print("</html>")
