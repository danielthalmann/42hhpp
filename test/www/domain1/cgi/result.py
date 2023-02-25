#!/usr/bin/python3

# Import modules for CGI handling
import cgi, cgitb, time, os

# Create instance of FieldStorage
form = cgi.FieldStorage()

# Get data from fields
postContent = form.getvalue('contentPost')
getContent = form.getvalue('contentGet')
lastvisite = time.time()

print("Set-Cookie:lastvisit=%s;\n\r" % (lastvisite))
print("Set-Cookie:get=%s;\n\r" % (getContent))
print("Set-Cookie:post=%s;\n\r" % (postContent))
print("Content-type:text/html\r\n\r\n")
print("<html>")
print("<head>")
print("<title>Hello - CGI Program</title>")
print("</head>")
print("<body>")
if 'HTTP_COOKIE' in os.environ.keys():
    for cookie in os.environ['HTTP_COOKIE'].split(';'):
        (key, value) = cookie.split('=')
        print("%s=%s" % (key, value), end='<br>')
print("<h2>post %s</h2>" % (postContent))
print("<h2>get %s</h2>" % (getContent))
print("</body>")
print("</html>")
