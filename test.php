<?php

include(__DIR__ . "/nitro.inc");

$domain = "domain.local";
$contact = "hostmaster.domain.local";
$ns1name = "ns1.domain.local";
$ns1ip = "192.168.1.10";
$ns2name = "ns2.domain.local";
$ns2ip = "192.168.100.10";
$attl = "3600";

if (isset($argv[1])) {
    if ($argv[1] == "add") {

        // Add a new DNS zone
        dnsaddrrec::add($ns2name, $ns2ip, "3600");
        dnsaddrrec::add($ns1name, $ns1ip, "3600");
        dnsnsrec::add($domain, $ns2name);
        dnsnsrec::add($domain, $ns1name);
        dnssoarec::add($domain, $ns1name, $contact);
        dnszone::add($domain);

        // Add an A record to the new domain
        dnsaddrrec::add("www.domain.local", "192.168.1.200", $attl);

    } elseif ($argv[1] == "rm") {

        // Remove a single A record
        dnsaddrrec::rm("www.domain.local");

        // Remove the comlete DNS zone
        dnszone::rm($domain);
        dnssoarec::rm($domain);
        dnsnsrec::rm($domain, $ns2name);
        dnsnsrec::rm($domain, $ns1name);
        dnsaddrrec::rm($ns2name);
        dnsaddrrec::rm($ns1name);
    }
}

?>
