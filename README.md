cli.speedtest
====================================

Standalone Windows Commandline Speedtest writtin in C++

<p>The drive for this project was my impatience to load up speedtest.net and waiting for the page to load
its fancy speedometer, ping test, and server select just to find out my downspeed.</p>

<p>Now you can just download and place the executable in your windows folder and just type "speedtest"
in commandline to do a test.</p>

<p>It uses libcurl compiled statically to perform the speedtest.</p>

<p>The download discards the data so it does not write to disk.</p>

3 test sizes are available<br>
small = 600KB<br>
medium = 3MB (this is default)<br>
large = 10MB

Commandline Options/Switches
====================================

-size=(small|medium|large)
<br>
-url=(urlToFile)


Example Usages:
====================================
speedtest -size=large

speedtest -url=http://www.server.com/somefile.zip

