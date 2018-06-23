<?php
///////////////// dnsnsrec /////////////////
class dnsnsrec
{
    public function add($domainname, $hostname)
    {
        global $nitroNSIP;
        global $authToken;

        $nitroUrl    = "http://$nitroNSIP/nitro/v1/config/" . get_called_class();
        $nitroReq    = "POST";
        $nitroData   = '{"' . get_called_class() . '":
{
  "domain": "'.$domainname.'",
  "nameserver": "'.$hostname.'",
  "ttl": 3600
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

    public function check($object) {
      $output = do_check(get_called_class(), $object);
      return $output;
    }

    public function rm($domainname, $hostname)
    {
        global $nitroNSIP;
        global $authToken;

        $nitroUrl    = "http://$nitroNSIP/nitro/v1/config/" . get_called_class() . "/$domainname?args=nameServer:$hostname";
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
