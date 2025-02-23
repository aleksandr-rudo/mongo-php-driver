--TEST--
MongoDB\BSON\Symbol serialization (Serializable interface)
--SKIPIF--
<?php require __DIR__ . "/../utils/basic-skipif.inc"; ?>
<?php skip_if_php_version('>=', '7.4.0'); ?>
--FILE--
<?php

$test = MongoDB\BSON\toPHP(MongoDB\BSON\fromJSON('{ "symbol": {"$symbol": "symbolValue"} }'))->symbol;

var_dump($symbol = $test);
var_dump($s = serialize($symbol));
var_dump(unserialize($s));

?>
===DONE===
<?php exit(0); ?>
--EXPECTF--
object(MongoDB\BSON\Symbol)#%d (%d) {
  ["symbol"]=>
  string(11) "symbolValue"
}
string(70) "C:19:"MongoDB\BSON\Symbol":38:{a:1:{s:6:"symbol";s:11:"symbolValue";}}"
object(MongoDB\BSON\Symbol)#%d (%d) {
  ["symbol"]=>
  string(11) "symbolValue"
}
===DONE===
