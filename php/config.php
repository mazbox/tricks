<?php

	/**
	
	configuration file
	
	**/
	
	// the IP address at where the MySQL database server is running.
	define("MYSQL_HOST",     "localhost");
	
	define("JPEGQUALITY", 50);
	
	define("MAX_UPLOAD_FILE_SIZE", 3000000);
	
	
	error_reporting(E_ALL);
	
	// the username of a mysql account, with privileges to modify content
	// of at least the database in question.
	define("MYSQL_USERNAME", "root");
	
	// the password for the above account
	define("MYSQL_PASSWORD", "password");
	
	// the name of the database running on mysql
	// containing the tables for the microrent system
	define("MYSQL_DATABASE", "DELL");
	
	// the url of the site on the web.
	define("SITE_ROOT", "/");
	
	// where the File class uploads files to
	define("SAVEDIR", "/home/marber82/mazbox.com/swark/files");
	
	// the http location of the files that are located
	define("SAVEURL", "http://www.mazbox.com/swark/files");
	