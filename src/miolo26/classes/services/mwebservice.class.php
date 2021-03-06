<?php
/**
 * WebService auxiliary class
 *
 * @author Daniel Hartmann [daniel@solis.coop.br]
 *
 * @version $id$
 *
 * \b Maintainers: \n
 * Armando Taffarel Neto [taffarel@solis.coop.br]
 * Daniel Hartmann [daniel@solis.coop.br]
 *
 * @since
 * Creation date 2010/12/09
 *
 * \b Organization: \n
 * SOLIS - Cooperativa de Soluções Livres \n
 *
 * \b CopyRight: \n
 * Copyright (c) 2010 SOLIS - Cooperativa de Soluções Livres \n
 *
 * \b License: \n
 * Licensed under GPLv2 (for further details read the COPYING file or http://www.gnu.org/licenses/gpl.html)
 *
 * \b History: \n
 * See history in CVS repository: http://www.miolo.org.br
 */

class MWebService
{
    /**
     * Athentication method
     *
     * @param string $user
     * @param string $password
     * @return bool Return true if can authenticate with the given user and password
     */
    protected function checkPermission($user, $password)
    {
        $MIOLO = MIOLO::getInstance();
        return $MIOLO->auth->authenticate($user, $password);
    }

    /**
     * @return bool Return true if the connection is local
     */
    protected function requestIsLocal()
    {
        return $_SERVER['REMOTE_ADDR'] == $_SERVER['SERVER_ADDR'];
    }

    /**
     * Throw Soap error with an access denied message
     */
    protected function accessError()
    {
        $this->error('Server', _M('Access denied'));
    }

    /**
     * Throw Soap error with the given message
     *
     * @param string $code Error code http://www.w3.org/TR/soap12-part1/#faultcodes
     * @param string $message Error message
     */
    protected function error($code, $message)
    {
        throw new SoapFault($code, $message);
    }

    /**
     * Check if the client is on the same subnet of the server
     * WARNING: Linux-only method
     *
     * @return bool Return true whether the request comes from the same subnet
     */
    protected function requestIsFromSubnet()
    {
        $binaryClient = sprintf("%032b",ip2long($_SERVER['REMOTE_ADDR']));
        $binaryServer = sprintf("%032b",ip2long($_SERVER['SERVER_ADDR']));
        $netMask = $this->netmask();

        return (substr_compare($binaryClient, $binaryServer, 0, $netMask) === 0);
    }

    /**
     * @return integer Server netmask in CIDR notation
     */
    private function netmask()
    {
        if ( !($p = popen('ifconfig', 'r')) )
        {
            $this->error('Could not get network information');
        }

        $out = "";
        while ( !feof($p) )
        {
            $out .= fread($p,1024);
        }
        fclose($p);

        $match  = "/^.*Bcast:\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}.*Mask:(\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})$/im";

        if ( !preg_match($match,$out,$regs) )
        {
            $this->error('Could not detemine the network mask');
        }

        $base = ip2long('255.255.255.255');
        $mask = ip2long($regs[1]);

        return 32 - log(($mask ^ $base) + 1, 2);
    }
}
?>
