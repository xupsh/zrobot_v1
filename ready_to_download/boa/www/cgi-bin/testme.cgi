#!/bin/sh
# shell script to test CGI
# Output the header followed by a blank line
echo "Content-type: text/html"
echo
echo "<html><head><title>CGI
Test</title><body>"
echo "<h1>Simple CGI Test</h1>"
echo "<b>"
date
echo "</b></body></html>"
