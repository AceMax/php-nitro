<?php
///////////////// dnsaddrec /////////////////

class dnsaddrec
{
    public function add($hostname, $ip, $ttl)
    {
        global $nitroNSIP;
        global $authToken;

        $nitroUrl    = "http://$nitroNSIP/nitro/v1/config/" . get_called_class();
        $nitroReq    = "POST";
        $nitroData   = '{"' . get_called_class() . '":
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
        echo $result;
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
