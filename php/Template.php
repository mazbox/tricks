<?php
class Template {
	var $page;

	function Template($template = "template.html") {
		if (file_exists($template))
			$this->page = join("", file($template));
		else
			die("Template file $template not found.");
	}

	function parse($file) {
		ob_start();
		include($file);
		$buffer = ob_get_contents();
		ob_end_clean();
		return $buffer;
	}

	function replace_tags($tags = array()) {
		if (sizeof($tags) > 0)
			foreach ($tags as $tag => $data) {
				$data = (file_exists($data)) ? $this->parse($data) : $data;
				$this->page = eregi_replace("{" . $tag . "}", $data, $this->page);
			}
		else
			die("No tags designated for replacement.");
	}
	
	function setContent($content) {
		$this->replace_tags(array("!content!" => $content));
	}
	function setContentFromFile($filename) {
		$content = $this->parse($filename);
		$this->setContent($content);
	}
	function output() {
		echo $this->page;
	}
}
?>