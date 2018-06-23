<?php
///////////////// dnszone /////////////////

class dnszone
{

    public function add($domainname)
    {
        global $nitroNSIP;
        global $authToken;

        $nitroUrl    = "http://$nitroNSIP/nitro/v1/config/" . get_called_class();
        $nitroReq    = "POST";
        $nitroData   = '{"' . get_called_class() . '":
          {
            "zonename": "'.$domainname.'",
            "proxymode": "NO",
            "dnssecoffload": "DISABLED",
            "nsec": "DISABLED"
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

    public function rm($object) {
      $output = do_rm(get_called_class(), $object);
      return $output;
    }
}
