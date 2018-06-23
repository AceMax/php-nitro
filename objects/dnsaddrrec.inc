<?php
///////////////// dnsaddrrec /////////////////
class dnsaddrrec
{
    public function check($hostname)
    {
        global $nitroNSIP;
        global $authToken;

        $nitroUrl    = "http://$nitroNSIP/nitro/v1/config/dnsaddrec/$hostname";
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

    public function add($hostname, $ip, $ttl)
    {
        global $nitroNSIP;
        global $authToken;

        $nitroUrl    = "http://$nitroNSIP/nitro/v1/config/dnsaddrec";
        $nitroReq    = "POST";
        $nitroData   = '{"dnsaddrec":
{
"hostname": "'.$hostname.'",
"ipaddress": "'.$ip.'",
"ttl": '.$ttl.'
}
}
';
        $nitroCookie = "Cookie:NITRO_AUTH_TOKEN=$authToken";
        $nitroHeader = "Content-Type: application/json";

        $ch = curl_init($nitroUrl);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
        curl_setopt($ch, CURLOPT_HTTPHEADER, array($nitroCookie,$nitroHeader));
        curl_setopt($ch, CURLOPT_POSTFIELDS, $nitroData);
        curl_setopt($ch, CURLOPT_CUSTOMREQUEST, $nitroReq);

        $result     = curl_exec($ch);
        curl_close($ch);

        $data = json_decode($result, true);
        $output = ($data["message"] == null ? true : false);
        return($output);
    }

    public function rm($hostname)
    {
        global $nitroNSIP;
        global $authToken;

        $nitroUrl    = "http://$nitroNSIP/nitro/v1/config/dnsaddrec/$hostname";
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
}