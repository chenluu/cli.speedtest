cli.speedtest
====================================

Windows Commandline Speedtest

The drive for this project was my impatience to load up speedtest.net and waiting for the page to load its fancy speedometer, ping test, and server select just to find out my downspeed.

Now you can just download and place the executable in your windows folder and just type "speedtest" in commandline to do a test.

The download discards the data so it does not write to disk.

Commandline Options/Switches
====================================

-size=[small|medium|large] (small = 600KB, medium = 3MB, large = 10MB, default is set to medium)
-url=[url_to_ur_file]


Example Usages:
====================================
speedtest -size=large

speedtest -url=http://www.server.com/somefile.zip

