
$Id: README.txt 544 2008-05-21 09:48:49Z ericehlers $

This directory contains the files for the website.  The files rely on server side includes.  If you have these pages on your hard drive and want to view them in the browser, add the following lines to your Apache configuration file:

Alias /xlw/ "/path/to/xlw-site/"

<Directory "/path/to/xlw-site/">
    Options Indexes MultiViews FollowSymLinks Includes
    AllowOverride None
    Order allow,deny
    Allow from all
</Directory>

Then (re)start Apache and point your browser at

    http://localhost/xlw/index.shtml

Subdirectory refman is taken from xlw/docs/html, and subdirectory version2 is taken from xlw/docs/xlwplus2/html-singlepage.

