<?php
/**
 * Created by PhpStorm.
 * User: John Kagga
 * Date: 8/1/2015
 * Time: 12:53 PM
 */
require 'Address.inc';

echo '<h2>Instantiating Address</h2>';
$address = new Address();
//inspecting the object
echo '<h2>Empty object</h2>';
echo '<tt><pre>'.var_export($address).'</pre></tt>';