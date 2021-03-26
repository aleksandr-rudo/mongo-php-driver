--TEST--
Decimal128: [basx056] strings without E cannot generate E in result
--DESCRIPTION--
Generated by scripts/convert-bson-corpus-tests.php

DO NOT EDIT THIS FILE
--FILE--
<?php

require_once __DIR__ . '/../utils/basic.inc';

$canonicalBson = hex2bin('180000001364006AB9C8733A0B0000000000000000343000');
$canonicalExtJson = '{"d" : {"$numberDecimal" : "12345678.543210"}}';

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
180000001364006ab9c8733a0b0000000000000000343000
{"d":{"$numberDecimal":"12345678.543210"}}
180000001364006ab9c8733a0b0000000000000000343000
===DONE===