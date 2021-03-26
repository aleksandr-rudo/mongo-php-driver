--TEST--
DBPointer type (deprecated): DBpointer
--DESCRIPTION--
Generated by scripts/convert-bson-corpus-tests.php

DO NOT EDIT THIS FILE
--FILE--
<?php

require_once __DIR__ . '/../utils/basic.inc';

$canonicalBson = hex2bin('1A0000000C610002000000620056E1FC72E0C917E9C471416100');
$convertedBson = hex2bin('2a00000003610022000000022472656600020000006200072469640056e1fc72e0c917e9c47141610000');
$canonicalExtJson = '{"a": {"$dbPointer": {"$ref": "b", "$id": {"$oid": "56e1fc72e0c917e9c4714161"}}}}';
$convertedExtJson = '{"a": {"$ref": "b", "$id": {"$oid": "56e1fc72e0c917e9c4714161"}}}';

// Canonical BSON -> Native -> Canonical BSON
echo bin2hex(fromPHP(toPHP($canonicalBson))), "\n";

// Canonical BSON -> Canonical extJSON
echo json_canonicalize(toCanonicalExtendedJSON($canonicalBson)), "\n";

// Canonical extJSON -> Canonical BSON
echo bin2hex(fromJSON($canonicalExtJson)), "\n";

?>
===DONE===
<?php exit(0); ?>
--EXPECT--
1a0000000c610002000000620056e1fc72e0c917e9c471416100
{"a":{"$dbPointer":{"$ref":"b","$id":{"$oid":"56e1fc72e0c917e9c4714161"}}}}
1a0000000c610002000000620056e1fc72e0c917e9c471416100
===DONE===