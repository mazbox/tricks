<?php
	require_once "config.php";
/** 
	Marek's PHP Database Framework 
	version 2.01
	
	This framework is designed to make adding dynamic capabilities to
	your site as painlessly as possible. Basically it reduces the number
	of lines of your code, and does the dirty work. It saves you writing
	the same piece of code on every page in a slightly different way.
	
	At the moment it consists of 3 classes.
	
		- DB - a class dealing with the database connection, and executing
		  sql statements.
		  
		- Row - abstracts the concept of a row in the database. 
		
		- Date - represents the date data type with utility methods.
	
	
	
	29.11.05
	--------
	
	Changes:
		v2.01:
			- added escape() function to protect against sql injection.
			
		v1 - v2:
			- You can now give the DB class a sql statement
			  to execute in its contructor.
			- delete() method added to Row class.
			- textBox() and selectBox() added to Row class to make
			  it easier to generate forms.
	
	Licence: LGPL
	         
	Copyright: Marek Bereza, Wikid.co.uk
 **/
 

	class DB {
		var $db;
		var $result;
		
		// in change from v1 to v2, you can give
		// a sql query in the contructor and it will
		// automatically execute.
		function DB($sql) {
			
			$this->db = mysql_connect(MYSQL_HOST, MYSQL_USERNAME, MYSQL_PASSWORD);
			// mysql_select_db("hig10001_HighlifeTreehouses", $this->db);
			mysql_select_db(MYSQL_DATABASE, $this->db);
			
			if(isset($sql)) {
				$this->execute($sql);
			}
		}
		
		function size() {
			return mysql_num_rows($this->result);
		}
		
		function rewind() {
			if($this->size()>0) {
				mysql_data_seek($this->result, 0);
			}
		}
		
		function execute($sql) {
			$this->result = mysql_query($sql, $this->db) or die('Query failed: ' . mysql_error().'\nSQL: '.$sql);
		}
		function lastInsertId() {
			return mysql_insert_id($this->db);
		}
		function next() {
			return mysql_fetch_assoc($this->result);
		}
	}
	

	
	class Date {
		var $date;
		function Date($str = "") {
			
			if($str=="") {
				$this->date = time();
			} else {
				$this->date = strtotime($str);
			}
		}
		
		function copy() {
			$d = new Date($this->toSQL());
			return $d;
		}
		
		/** 
		 * sets the values of the date object to 
		 * a date in the parameter with the names $key.day
		 * $key.month and $key.year
		 */
		function dateFromRequest($key) {
			$day = $_REQUEST[$key.'_day'];
			$month = $_REQUEST[$key.'_month'];
			$year = $_REQUEST[$key.'_year'];
			$time = $year;
			
			if(strlen($month)==1) {
				$time .= "0";
			}
			
			$time .= $month;
			
			if(strlen($day)==1) {
				$time .= "0";
			}
			
			$time .= $day;
			$this->date = strtotime($time);
		}
		
		function writeHiddenInput($key) {
			print '
				<input type="hidden" name="'.$key.'.day" value="'.$this->getDay().'" />
				<input type="hidden" name="'.$key.'.month" value="'.$this->getMonth().'" />
				<input type="hidden" name="'.$key.'.year" value="'.$this->getYear().'" />';
		}
		
		function long() {
			return date("l, jS of F, Y", $this->date);
		}
		function med() {
			return date("jS M, 'y", $this->date);
		}
		function medium() {
			return date("jS of F", $this->date);
		}
		
		function short($separator = "/") {
			return date("d", $this->date).$separator.date("m", $this->date).$separator.date("y", $this->date);
		}
		
		function toSQL() {
			return date("Y-m-d", $this->date);
		}
		function set($d) {
			$this->date = $d;
		}
		function wikid() {
			return date("jS F, Y", $this->date) . " at " . date("g:ia", $this->date);
		}
		
		function getDayOfWeek() {
			return date("l", $this->date);
		}
		function getMonthName() {
			return date("F", $this->date);
		}
		function getYear() {
			return date("Y", $this->date);
		}
		function getDay() {
			return date("j", $this->date);
		}
		function getMonth() {
			return date("n", $this->date);
		}
		function getDaysInMonth() {
			return date("t", $this->date);
		}
		function getTh() {
			return date("S", $this->date);
		}
		
		function compareTo($date) {
			return $this->date - $date;
		}
		
		// time in seconds since 1/1/70
		function getDate() {
			return $this->date;
		}
		
		// returns number of days difference
		function compareDays($date) {
			return ($this->date - $date->getDate())/(60 * 60 * 24);
		}
		
		function addDays($days) {
			$this->date += ($days * 24 * 60 * 60);
		}
	
	}
	
	
	class Row {
		var $data;
		var $table;
		var $id;
		
		function Row($table, $id = 0) {
			if($id==null) {
				$id = 0;
			}
			// this should change to count the parameters
			// because sometimes you will want id=0
			$this->table = $table;
			$this->id = $id;
			if($this->id>0) {
				$this->loadData();
			}
		}
		function loadData() {
			// load the row into $data
			$db = new DB("SELECT * FROM $this->table WHERE id = $this->id;");
			$this->data = $db->next();
		}

		function id() {
			return $this->id;
		}
		
		function set($key, $value) {
			$this->data[$key] = $value;
		}
		
		function setDate($key, $date) {
			$this->data[$key] = $date->toSQL();
		}
		
		function get($key) {
			return mystripslashes($this->data[$key]);
		}
		
		function getDate($key) {
			return new Date($this->data[$key]);
		}
		
		// deletes this row.
		function delete() {
			new DB("DELETE FROM $this->table WHERE id = $this->id;");
		}
		
		// hmm, maybe this will be useful one day.
		function req_set($keys) {
			for($i = 0; $i < count($keys); $i++) {
				$this->set($keys[$i], $_REQUEST[$keys[$i]]);
			}
		}
		
		function json() {
			return json_encode($this->data);
		}
		
		// saves the internal hashmap to the database by creating
		// a sql statement and executing it.
		function save() {
			$sql = "";
			
			if($this->id==0) {
				$keys = "";
				$values = "";
			
				foreach($this->data as $key=>$value) {
					$keys .= "`".$key."`" . ",";
					if($value=="NOW()") {
						$values .= $value . ",";
					} else {
						$values .= "'" . myaddslashes($value) . "',";
					}
					
				}
				$keys = substr($keys, 0, -1);
				$values = substr($values, 0, -1);
				$sql = "INSERT INTO " . $this->table . " (" . $keys .
				") VALUES (" . $values . ");";
				
			} else {
				$keyValuePairs = "";
				foreach($this->data as $key=>$value) {
					if($value=="NOW()") {
						$keyValuePairs .= $keyValuePairs . " $key = $value,";
					} else {
						$keyValuePairs .= $keyValuePairs . " $key = '".myaddslashes($value)."',";	
					}
				}
				
				$keyValuePairs = substr($keyValuePairs, 0, -1);
				$sql = "UPDATE " .$this->table. " SET " .$keyValuePairs . " WHERE id = "
					. $this->id;
			}

			$db = new DB($sql);
			
			
			if($this->id==0) {
				$this->id = $db->lastInsertId();
			}
			$this->loadData();
		}
		
		function textBox($name, $attr) {
			return '<input type="text" name="'.$name.'" value="'.$this->get($name).'" '.$attr.' />';
		}
		
		function selectBox($name, $table, $column, $naText) {
			$db = new DB("SELECT * FROM $table ORDER BY $column");
			$s = "<select name=\"$name\">\n";
			if(isset($naText)) {
				$s .= "<option value=\"0\">$naText</option>\n";
			}
			for($i = 0; $i < $db->size(); $i++) {
				$row = $db->next();
				$s .= '<option value="'.$row['id'].'"';
				if($row['id']==$this->get($name)) {
					$s .= ' selected="selected"';
				}
				$s .= '>'.$row[$column]."</option>\n";
			}
			$s .= "</select>";
			return $s;
		}
	}
	
	function selectBox($name, $table, $column, $selectedId, $naText) {
		$db = new DB("SELECT * FROM $table ORDER BY $column");
		$s = "<select name=\"$name\">\n";
		if(isset($naText)) {
			$s .= "<option value=\"0\">$naText</option>\n";
		}
		for($i = 0; $i < $db->size(); $i++) {
			$row = $db->next();
			$s .= '<option value="'.$row['id'].'"';
			if($row['id']==$selectedId) {
				$s .= ' selected="selected"';
			}
			$s .= '>'.$row[$column]."</option>\n";
		}
		$s .= "</select>";
		return $s;
	}
		
	// returns a parameter called id on the request.
	// or zero if it isn't.
	function id() {
		$id = $_REQUEST['id'];
		if($id==null) {
			return 0;
		} else {
			return $id;
		}
	}
	function action() {
		return $_REQUEST['action'];
	}
	
	function r($name) {
		$r = $_REQUEST($name);
		if(isset($r)) {
			return $r;
		} else {
			return 0;
		}
	}
	// deprecated.
	function req_id() {
		return id();
	}
	
	$rootUrl = "";
	
	// methods to get round the magic quotes shittiness.
	function myaddslashes( $string ) {
		if (get_magic_quotes_gpc()) {
			return $string;
		} else {
			return str_replace ("'", "\'", $string);
		}
	}
	
	function mystripslashes($string) {
		return $string;
	}
	
	function today() {
		$d = new Date();
		return $d;
	}
	
	function redirect($url) {
		header("Location: $url");
	}
	
	// give it s a sql statement with a COUNT() in it and this will
	// return the count. Or -1.
	function DB_count($sql) {
		$db = new DB($sql);
		if($result = $db->next()) {
			foreach($result as $key=>$value) {
				return $value;
			}
		} else {
			return -1;
		}
	}
	$local = true;
	$saveUrl = "http://www.wikid.co.uk/files/";
	if($local) {
		$saveUrl = "http://localhost/files/";
	}
	$saveDir = "/home/iggy/sites/wikid.co.uk/html/files/";
	if($local) {
		$saveDir = "/Library/WebServer/Documents/files/";
	}
	
	
	function get($key) {
		$db = new DB("SELECT * FROM Hash WHERE `key` = '".$key."'");
		if($r = $db->next()) {
			return $r['value'];
		}
		return '';
	}
	
	function put($key, $value) {
		$c = DB_count("SELECT COUNT(*) FROM Hash WHERE `key` = '".$key."'");
		if($c==0) {
			new DB("INSERT INTO Hash (`key`, `value`) VALUES ('".$key."', '".$value."')");
		
		} else {
			new DB("UPDATE Hash SET `value` = '".$value."' WHERE `key` = '".$key."'");
		}
	}

	function escape($inp) { 
		if(is_array($inp)) 
			return array_map(__METHOD__, $inp); 
	
		if(!empty($inp) && is_string($inp)) { 
			return str_replace(array('\\', "\0", "\n", "\r", "'", '"', "\x1a"), array('\\\\', '\\0', '\\n', '\\r', "\\'", '\\"', '\\Z'), $inp); 
		} 
	
		return $inp; 
	} 
	
	