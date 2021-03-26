--TEST--
Binary type: subtype 0x04 UUID
--DESCRIPTION--
Generated by scripts/convert-bson-corpus-tests.php

DO NOT EDIT THIS FILE
--FILE--
<?php

require_once __DIR__ . '/../utils/basic.inc';

$canonicalBson = hex2bin('1D000000057800100000000473FFD26444B34C6990E8E7D1DFC035D400');
$canonicalExtJson = '{"x" : { "$binary" : {"base64" : "c//SZESzTGmQ6OfR38A11A==", "subType" : "04"}}}';
$degenerateExtJson = '{"x" : { "$uuid" : "73ffd264-44b3-4c69-90e8-e7d1dfc035d4"}}';

// Canonical BSON -> Native -> Canonical BSON
echo bin2hex(fromPHP(toPHP($canonicalBson))), "\n";

// Canonical BSON -> Canonical extJSON
echo json_canonicalize(toCanonicalExtendedJSON($canonicalBson)), "\n";

// Canonical extJSON -> Canonical BSON
echo bin2hex(fromJSON($canonicalExtJson)), "\n";

// Degenerate extJSON -> Canonical BSON
echo bin2hex(fromJSON($degenerateExtJson)), "\n";

?>
===DONE===
<?php exit(0); ?>
--EXPECT--
1d000000057800100000000473ffd26444b34c6990e8e7d1dfc035d400
{"x":{"$binary":{"base64":"c\/\/SZESzTGmQ6OfR38A11A==","subType":"04"}}}
1d000000057800100000000473ffd26444b34c6990e8e7d1dfc035d400
1d000000057800100000000473ffd26444b34c6990e8e7d1dfc035d400
===DONE===