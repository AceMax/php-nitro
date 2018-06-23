<?php

function do_check($method, $object)
{
    global $nitroNSIP;
    global $authToken;

    $nitroUrl    = "http://$nitroNSIP/nitro/v1/config/$method/$object";
    $nitroReq    = "GET";
    $nitroCookie = "Cookie:NITRO_AUTH_TOKEN=$authToken";
    $nitroHeader = "Content-Type: application/json";

    $ch = curl_init($nitroUrl);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($ch, CURLOPT_HTTPHEADER, array($nitroCookie,$nitroHeader));
    curl_setopt($ch, CURLOPT_CUSTOMREQUEST, $nitroReq);

    $result      = curl_exec($ch);
    curl_close($ch);

    $data = json_decode($result, true);
    $output = ($data["message"] == "Done" ? true : false);
    return($output);
}

function do_rm($method, $object)
{
    global $nitroNSIP;
    global $authToken;

    $nitroUrl    = "http://$nitroNSIP/nitro/v1/config/$method/$object";
    $nitroReq    = "DELETE";
    $nitroCookie = "Cookie:NITRO_AUTH_TOKEN=$authToken";
    $nitroHeader = "Content-Type: application/json";

    $ch = curl_init($nitroUrl);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($ch, CURLOPT_HTTPHEADER, array($nitroCookie,$nitroHeader));
    curl_setopt($ch, CURLOPT_CUSTOMREQUEST, $nitroReq);

    $result      = curl_exec($ch);
    curl_close($ch);

    $data = json_decode($result, true);
    $output = ($data["message"] == "Done" ? true : false);
    return($output);
}

?>
