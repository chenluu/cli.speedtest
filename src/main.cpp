#define CURL_STATICLIB

#include "curl/curl.h"

#include <stdio.h>
#include <string>
#include <time.h>
#include <math.h>

using namespace std;

const float 	ver				= 1.01;
const int 		width			= 40;
const 			time_t sTime	= time(NULL);
double 			topSpeed 		= 0;
const string	small			= "http://speedtest-2.internode.on.net/oz-broadband/jetty_600kb.jpg";
const string	medium			= "http://speedtest-2.internode.on.net/oz-broadband/storm_3mb.jpg";
const string	large			= "http://speedtest-2.internode.on.net/oz-broadband/pinball_9mb.jpg";


static size_t WriteCallback(void *ptr, size_t size, size_t nmemb, void *data)
{
  (void)ptr; 
  (void)data;
  return (size_t)(size * nmemb);
}

int progressCallback(void *ptr,   double dltotal,   double dlnow,   double ultotal,   double ulnow)
{
    double progressPercentage = dlnow / dltotal;

    int progressBar = round(progressPercentage * width);
    
	double speed = (dlnow / (time(NULL) - sTime) / 1000);
    
    if(fpclassify(speed) == FP_NORMAL)
    {
    	topSpeed = (speed > topSpeed ? speed : topSpeed );
    }
    
    
    printf("%0.0f%% @ %0.2f KB/s \r", round(progressPercentage * 100), speed);
    
    
    return 0; 
}

void speedtest(string url)
{
  CURL *curl_handle;
  CURLcode res;
  char domain[url.length()];
  
  sscanf(url.c_str(), "http://%[^/]", &domain);
  int prtall = 0, prtsep = 0, prttime = 0;
  
  printf("\ncli.speedtest v%.2f by Chen Luu\n\n", ver);
  printf("Starting speed test on : %s\n", domain);

  curl_global_init(CURL_GLOBAL_ALL);

  curl_handle = curl_easy_init();
  curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteCallback);
  curl_easy_setopt(curl_handle, CURLOPT_PROGRESSFUNCTION, progressCallback);
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "SpeedTest");
  curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, false );
  res = curl_easy_perform(curl_handle);
  
  if(CURLE_OK == res)
   {
    double val;
    
	puts("\n");
	for (int i = 0; i < width; i++) { printf("-"); }
	puts("\n");
	
	res = curl_easy_getinfo(curl_handle, CURLINFO_NAMELOOKUP_TIME, &val);
      printf("Ping: %0.3fs\n", val);
      
    res = curl_easy_getinfo(curl_handle, CURLINFO_CONNECT_TIME, &val);
      printf("Connect Time: %0.3fs\n", val);
      
    res = curl_easy_getinfo(curl_handle, CURLINFO_SIZE_DOWNLOAD, &val);
      printf("Downloaded: %0.3f MB in ", (val / 1000024));

    res = curl_easy_getinfo(curl_handle, CURLINFO_TOTAL_TIME, &val);
      printf("%0.3fs\n", val);

    res = curl_easy_getinfo(curl_handle, CURLINFO_SPEED_DOWNLOAD, &val);
      printf("Average Speed: %0.2f KB/s (%0.2fMb/s)\n", (val / 1024), (val / 100000));

      printf("Top Speed: %0.2lf KB/s (%0.2fMb/s)\n", topSpeed, (topSpeed / 100));
      
   }
   else 
   {
    		printf("Error while fetching '%s'\n", url.c_str());
   }
  
  curl_easy_cleanup(curl_handle);

  curl_global_cleanup();
}

int main(int argc, char** argv) {
	
  	char *appname = argv[0];
  	
  	if (argc > 1) 
	{
	    for (argc--, argv++; *argv; argc--, argv++) 
		{
	      if (strncasecmp(*argv, "-", 1) == 0) 
		  {
	        if (strncasecmp(*argv, "-help", 5) == 0) 
			{
	          	fprintf(stderr, "\rUsage: %s [-size=small|medium|large] [-url=url_to_file] [-pause] [-help]\n", appname);
	          	exit(1);
	        }
	        else if (strncasecmp(*argv, "-size=", 6) == 0)
			 {
	          	  string size = (*argv)+6;
	          	  
	          	  if(size == "small") speedtest(small);
	          	  else if(size == "medium") speedtest(medium);
	          	  else if(size == "large") speedtest(large);
	          	  else
	          	  {
		        		fprintf(stderr, "\r%s: Invalid size parameter: \"%s\", use -help for usage.\n", appname, *argv + 6);
		                exit(1);
		          }
	        }
	        else if(strncasecmp(*argv, "-url=", 5) == 0)
	        {
	        	string url = (*argv)+5;
	        	speedtest(url);
	        }
			else 
			{
	          fprintf(stderr, "\r%s: Invalid or unknown option: \"%s\", use -help for usage\n", appname, *argv);
	          exit(1);
	        }
	      } 
	    }
	}
  	else
  	{
  		speedtest(medium);
  	}
  	
	return 0;
}
