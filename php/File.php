<?php
/*
	Deals with uploading files
	and scaling images (using GD)
*/
require_once "config.php";

class File {
	var $path;
	
	/**
	 * Creates a File object from an
	 * absolute path to the file.
	 */
	function File($path) {
		$this->path = $path;
		/*if($this->path==null) {
			die("Tried to initialize a File object with no path.");
		}
		if(!file_exists($this->path)) {
			die("The file, \"$this->path\" does not exist.");
		}*/
	}
	/**
	 * Returns true if the file exists.
	 */
	function exists() {
		return file_exists($this->path);
	}
	
	/**
	 * Returns a list of File objects in the directory.
	 */
	function ls() {
		$out = array();
		$i = 0;
		if(!$this->isDir()) {
			die("This is not a directory");
		}
		if($dh = opendir($this->path)) {
			while(($file = readdir($dh)) !== false) {
				if($file!='.' && $file!='..') {
					$out[$i++] = new File($this->path.$file);
				}
			}
		} else {
			die("There was a problem reading the directory");
		}
		return $out;
	}
	
	/**
	 * Deletes the file.
	 */
	function delete() {
		
		if(isDir()) {
			die("Can't delete a directory yet!");
		}
		$success = unlink($this->path);
		if(!$success) {
			die("Can't delete the file");
		}
	}
	
	/**
	 * Returns true if this file is a directory.
	 */
	function isDir() {
		return is_dir($this->path);
	}
	
	/**
	 * Returns the size of the file in bytes.
	 */
	function getSize() {
		return filesize($this->path);
	}
	
	/**
	 * Returns the absolute path to the file.
	 */
	function getPath() {
		return $this->path;
	}
	
	/**
	 * Returns just the name of the file minus
	 * the directory.
	 */
	function getFileName() {
		return basename($this->path);
	}
	
	/**
	 * Returns the file object for the subdirectory
	 */
	function createSubDir($dirname) {
		if(!isset($dirname)) {
			die("You must give the subdirectory a name");
		}
		if(!isDir) {
			die("Cannot create a subdirectory of a file");
		}
		if(!mkdir($this->path, $dirname)) {
			die("Could not create the directory");
		}
	}
	
	/**
	 * If a file is posted in a multipart form
	 * give this function the name of the input element
	 * it came from and this will put it in SAVEDIR.
	 * This file object then points to that file.
	 * Returns true if it was successful.
	 */
	function upload($name, $destinationName = '') {
		if($destinationName=='') {
			$destinationName = basename($_FILES[$name]['name']);
		}
		
		$this->path = SAVEDIR . '/' . $destinationName;

		if($this->exists()) {
			$this->path = $this->nextUniqueFileName();
		}
		if(move_uploaded_file($_FILES[$name]['tmp_name'], $this->path)) {
			return true;
		} else {
			return false;
		}
	}
	
	function getParentDir() {
		return new File(dirname($this->path));
	}
	
	/**
	 * Gets a unique file name.
	 */
	function nextUniqueFileName() {
		
		$dir = dirname($this->path);
		$parts = explode(".", $this->getFileName());
		$ext = end($parts);
		$name = $parts[0];
		$i = 0;
		$done = false;
		$f = new File();
		
		if(strlen($name)>14) {
			$name = substr($name, 0, 14);
		}
		
		while($done==false) {
			$f = new File($dir . "/" . $name . $i . "." . $ext);
			if(!$f->exists()) {
				$done = true;
			}
			$i++;
		}
		
		
		return $f->getPath();
	}
}

class Image {
	
	var $path;
	var $img;
	var $type;
	var $height;
	var $width;
	function Image($path) {
		if(!isSet($path)) {
			die ("File does not exist ($path)");
		} else {
			$this->path = $path;
			$this->type = strtolower(end(explode('.', $this->path)));
			if($this->type=='jpg') {
				$this->type = 'jpeg';
			}
		}
		
		if ($this->type=='jpeg') {
			$this->img = imagecreatefromjpeg($this->path);
		} else if ($img == 'png') {
			$this->img = imagecreatefrompng($this->path);
			// Only if your version of GD includes GIF support
		} else if ($img == 'gif') {
			$this->img = imagecreatefromgif($this->path);
		}
		
		if(!$this->img) {
			die("Image did not load. Perhaps it is not an image?");
		}
		
		// Get image size and scale ratio
		$this->width = imagesx($this->img);
		$this->height = imagesy($this->img);
	}
	
			
	function scale($path, $newWidth) {
		$newHeight = round(($this->height*$newWidth)/$this->width);
		
		// Create a new temporary image
		$tmp_img = imagecreatetruecolor($newWidth, $newHeight);

		// Copy and resize old image into new image
		imagecopyresampled($tmp_img, $this->img, 0, 0, 0, 0,
				 $newWidth, $newHeight, $this->width, $this->height);
		// imagedestroy($img);
		imagejpeg($tmp_img, $path, JPEGQUALITY);
	}
	
	/**
	 * Does the same as scale() but creates a
	 * unique file name for the picture, and
	 * returns the name.
	 */
	function scaleToUniqueFile($newWidth) {
		$file = new File($this->path);
		$newPath = $file->nextUniqueFileName();
	//	echo $newPath;
		$this->scale($newPath, $newWidth);
		return new File($newPath);
	}
}


function dirSelect($dirname = '') {
	if($dirname =='') {
		$dirname = $saveDir;
		echo $saveDir;
	}
	echo $dirname;
}

function ls($dirname) {
	
	$file = new File($dirname);
	$files = $file->ls();
	
	echo "<ul>";
	foreach($files as $f) {
		echo "<li>";
		if($f->isDir()) {
			echo "<strong>" . $f->getFileName() . "</strong>";
			ls($f->getPath() . '/');
		} else {
			echo $f->getFileName();
		}
		echo "</li>";
	}
	echo "</ul>";
}
	
	
 /* --test code here
<html>
<body>
<-?
	if(isSet($_REQUEST['upload'])) {
		$file = new File();
		if($file->upload("file")) {	
			$img = new Image($file->getPath());
			$imgFile = $img->scaleToUniqueFile($_REQUEST['width']);
			echo "<br /><img src=\"".SAVEURL."/".$imgFile->getFileName()."\" /><br />";
		}
	}
?->
<form method="POST" enctype="multipart/form-data" action="?upload">
	<input type="hidden" name="MAX_FILE_SIZE" value="1000000" />
	<input type="file" name="file" />
	width: <input type="text" size="4" name="width" value="120" />
	<input type="submit" />
</form>
</body>
</html>*/
