@echo off
echo WRAS Release Script V2 - EComm Winchester release for [%1] subarea [%2]

md WRAS-%1-%2

echo Making static section... (WRAS-%1-%2\ifdesk)
md WRAS-%1-%2\ifdesk
md WRAS-%1-%2\ifdesk\%1
md WRAS-%1-%2\ifdesk\%1\%2
md WRAS-%1-%2\ifdesk\%1\%2\behaviors
md WRAS-%1-%2\ifdesk\%1\%2\css
md WRAS-%1-%2\ifdesk\%1\%2\images
md WRAS-%1-%2\ifdesk\%1\%2\javascript
md WRAS-%1-%2\ifdesk\%1\%2\sessions
md WRAS-%1-%2\ifdesk\%1\%2\screens
md WRAS-%1-%2\ifdesk\%1\%2\components
md WRAS-%1-%2\ifdesk\%1\%2\components
md WRAS-%1-%2\ifdesk\%1\%2\WebLibrary
md WRAS-%1-%2\ifdesk\%1\%2\extjs
md WRAS-%1-%2\ifdesk\%1\%2\js

xcopy /s webcode\behaviors\*.*     WRAS-%1-%2\ifdesk\%1\%2\behaviors
xcopy /s webcode\css\*.*           WRAS-%1-%2\ifdesk\%1\%2\css
xcopy /s webcode\images\*.*        WRAS-%1-%2\ifdesk\%1\%2\images
xcopy /s webcode\javascript\*.*    WRAS-%1-%2\ifdesk\%1\%2\javascript
xcopy /s webcode\sessions\*.*      WRAS-%1-%2\ifdesk\%1\%2\sessions
xcopy /s webcode\screens\*.htm*    WRAS-%1-%2\ifdesk\%1\%2\screens
xcopy /s webcode\components\*.htm* WRAS-%1-%2\ifdesk\%1\%2\components
xcopy /s webcode\components\*.png  WRAS-%1-%2\ifdesk\%1\%2\components
xcopy /s webcode\components\*.jpg  WRAS-%1-%2\ifdesk\%1\%2\components
xcopy /s webcode\components\*.gif  WRAS-%1-%2\ifdesk\%1\%2\components
xcopy /s webcode\WebLibrary\*.*    WRAS-%1-%2\ifdesk\%1\%2\WebLibrary
xcopy /s webcode\extjs\*.*		   WRAS-%1-%2\ifdesk\%1\%2\extjs
xcopy /s webcode\js\*.*			   WRAS-%1-%2\ifdesk\%1\%2\js

echo (done).
echo.

echo Making dynamic section... (WRAS-%1-%2\ifdesk%1Ear)
md WRAS-%1-%2\ifdesk%1Ear
md WRAS-%1-%2\ifdesk%1Ear\ifdesk%1WebApp
md WRAS-%1-%2\ifdesk%1Ear\ifdesk%1WebApp\ifdesk
md WRAS-%1-%2\ifdesk%1Ear\ifdesk%1WebApp\ifdesk\%1
md WRAS-%1-%2\ifdesk%1Ear\ifdesk%1WebApp\ifdesk\%1\%2
md WRAS-%1-%2\ifdesk%1Ear\ifdesk%1WebApp\ifdesk\%1\%2\jobs
md WRAS-%1-%2\ifdesk%1Ear\ifdesk%1WebApp\ifdesk\%1\%2\components
md WRAS-%1-%2\ifdesk%1Ear\ifdesk%1WebApp\ifdesk\%1\%2\screens
md WRAS-%1-%2\ifdesk%1Ear\ifdesk%1WebApp\ifdesk\%1\%2\sessions
md WRAS-%1-%2\ifdesk%1Ear\ifdesk%1WebApp\ifdesk\%1\%2\xsl
md WRAS-%1-%2\ifdesk%1Ear\ifdesk%1WebApp\ifdesk\%1\%2\smartviews

xcopy /s webcode\jobs\*.xml       WRAS-%1-%2\ifdesk%1Ear\ifdesk%1WebApp\ifdesk\%1\%2\jobs
xcopy /s webcode\components\*.xsl WRAS-%1-%2\ifdesk%1Ear\ifdesk%1WebApp\ifdesk\%1\%2\components
xcopy /s webcode\screens\*.xsl    WRAS-%1-%2\ifdesk%1Ear\ifdesk%1WebApp\ifdesk\%1\%2\screens
xcopy /s webcode\screens\*.xml    WRAS-%1-%2\ifdesk%1Ear\ifdesk%1WebApp\ifdesk\%1\%2\screens
xcopy /s webcode\sessions\*.*     WRAS-%1-%2\ifdesk%1Ear\ifdesk%1WebApp\ifdesk\%1\%2\sessions
xcopy /s webcode\xsl\*.xsl    	  WRAS-%1-%2\ifdesk%1Ear\ifdesk%1WebApp\ifdesk\%1\%2\xsl
xcopy /s webcode\smartviews\*.xsl    	  WRAS-%1-%2\ifdesk%1Ear\ifdesk%1WebApp\ifdesk\%1\%2\smartviews

copy webcode\client.cfg WRAS-%1-%2\ifdesk%1Ear\ifdesk%1WebApp\ifdesk\%1\%2\%2.cfg

echo Processing %1_ns.xml
md WRAS-%1-%2\ifdesk%1Ear
md WRAS-%1-%2\ifdesk%1Ear\ifdesk%1WebApp
md WRAS-%1-%2\ifdesk%1Ear\ifdesk%1WebApp\ifdesk
md WRAS-%1-%2\ifdesk%1Ear\ifdesk%1WebApp\ifdesk\%1
md WRAS-%1-%2\ifdesk%1Ear\ifdesk%1WebApp\ifdesk\%1\config
echo copy config\%1_ns.xml WRAS-%1-%2\ifdesk%1Ear\ifdesk%1WebApp\ifdesk\%1\config\ns.xml
copy config\%1_ns.xml       WRAS-%1-%2\ifdesk%1Ear\ifdesk%1WebApp\ifdesk\%1\config\ns.xml

echo Processing JAR Files
md WRAS-%1-%2\ifdesk%1Ear\APP-INF
md WRAS-%1-%2\ifdesk%1Ear\APP-INF\lib
copy lib\*.jar WRAS-%1-%2\ifdesk%1Ear\APP-INF\lib


echo.
echo done copy.   Zip each folder seperatly and upload to http://170.40.25.215/
echo ifdesk%1Ear.zip is dynamic and ifdesk.zip is static
echo.
echo.
pause




