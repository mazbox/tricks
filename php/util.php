<?php

function urlorize($s) {
	$s = strtolower($s);
	$s = str_replace(" ", "_", $s);
	$s = str_replace("'", "", $s);
	$s = str_replace("\"", "", $s);
	$s = str_replace("/", "", $s);
	$s = str_replace("-", "", $s);
	return $s;
}
?>