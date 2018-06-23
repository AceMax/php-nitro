<?php
class ns
{
    ///////////////// authentication /////////////////
    public function login()
    {
        global $nitroNSIP;
        global $nitroUser;
        global $nitroPass;

        $nitroUrl    = "http://$nitroNSIP/nitro/v1/config/login/";
        $nitroReq    = "POST";
        $nitroData   = '{"login":{"username":"'.$nitroUser.'","password":"'.$nitroPass.'"}}';
        $nitroHeader = "Content-Type: application/vnd.com.citrix.netscaler.login+json";

        $ch = curl_init($nitroUrl);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
        curl_setopt($ch, CURLOPT_HEADER, 1);
        curl_setopt($ch, CURLINFO_HEADER_OUT, true);
        curl_setopt($ch, CURLOPT_HTTPHEADER, array($nitroHeader));
        curl_setopt($ch, CURLOPT_POSTFIELDS, $nitroData);
        curl_setopt($ch, CURLOPT_CUSTOMREQUEST, $nitroReq);

        $result = curl_exec($ch);

        preg_match_all('/^Set-Cookie:\s*([^\r\n]*)/mi', $result, $ms);
        $cookies     = array();
        foreach ($ms[1] as $m) {
            list($name, $value) = explode('=', $m, 2);
            $cookies[$name]     = $value;
        }

        $authToken   = $cookies["NITRO_AUTH_TOKEN"];

        curl_close($ch);

        return $authToken;
    }


    public function logout($authToken)
    {
        // Set variables
        global $nitroNSIP;
        $nitroUrl    = "http://$nitroNSIP/nitro/v1/config/logout/";
        $nitroReq    = "POST";
        $nitroData   = '{"logout":{}}';
        $nitroCookie = "Cookie:NITRO_AUTH_TOKEN=$authToken";
        $nitroHeader = "Content-Type: application/vnd.com.citrix.netscaler.logout+json";

        // Initialize and set cURL options
        $ch = curl_init($nitroUrl);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
        curl_setopt($ch, CURLOPT_HTTPHEADER, array($nitroCookie,$nitroHeader));
        curl_setopt($ch, CURLOPT_POSTFIELDS, $nitroData);
        curl_setopt($ch, CURLOPT_CUSTOMREQUEST, $nitroReq);

        // Execute the cURL command and close the connection afterwards
        curl_exec($ch);
        curl_close($ch);

        // Unset the Nitro Auth Token
        unset($authToken);
    }
}
