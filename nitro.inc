<?php

include(__DIR__ . "/nitro_auth.inc");
include(__DIR__ . "/objects/auth.inc");

date_default_timezone_set('UTC');
$timestamp = date('U');

$auth_cache = file_get_contents($tmpPath . "/nitro_authtoken.cache");
$auth_array = explode(",", $auth_cache);

if (($timestamp > ($auth_array[0] + 900))) {
    echo "Generating new auth token\n";
    $authToken = ns::login();
    file_put_contents($tmpPath . "/nitro_authtoken.cache", "$timestamp,$authToken");
} else {
    echo "Using cached auth token\n";
    $authToken = $auth_array[1];
}

include(__DIR__ . "/objects/dnsaddrrec.inc");
include(__DIR__ . "/objects/dnsnsrec.inc");
include(__DIR__ . "/objects/dnssoarec.inc");
include(__DIR__ . "/objects/dnszone.inc");

?>
