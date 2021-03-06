<?php

/**
 * Unit test class
 *
 * @author Armando Taffarel Neto [taffarel@solis.coop.br]
 * @author Daniel Hartmann [daniel@solis.coop.br]
 *
 * \b Maintainers: \n
 * Armando Taffarel Neto [taffarel@solis.coop.br]
 * Daniel Hartmann [daniel@solis.coop.br]
 *
 * @since
 * Creation date 2011/03/14
 *
 * \b Organization: \n
 * SOLIS - Cooperativa de Soluções Livres \n
 *
 * \b Copyright: \n
 * Copyright (c) 2011 SOLIS - Cooperativa de Soluções Livres \n
 *
 * \b License: \n
 * Licensed under GPLv2 (for further details read the COPYING file or http://www.gnu.org/licenses/gpl.html)
 */

/*
 * Configuration to have MIOLO working on command line
 */

// Get module name by directory
$dir = explode('/', getcwd());
$module = $dir[6];

// Change directory to the one where the script is located, so it can be called anywhere you are
chdir('../../../');
require_once 'classes/miolo.class.php';

$path = getcwd();
$classPath = "$path/classes/";

/**
 * MIOLOConsole class
 */
class MIOLOConsole
{
    /**
     * @var object MIOLO instance
     */
    private $MIOLO;

    /**
     * @var string Module name
     */
    private $module;

    /**
     * Create a MIOLO instance
     *
     * @param string $pathMiolo MIOLO direcotry path
     * @param string $module Module
     * @return object MIOLO instance
     */
    public function getMIOLOInstance($pathMiolo, $module)
    {
        ob_start();
        echo "MIOLO console\n\n";

        $this->module = $module;

        /*
         * Simulates apache variables which are required by MIOLO
         */
        $_SERVER['DOCUMENT_ROOT'] = "$pathMiolo/html";
        $_SERVER['SCRIPT_FILENAME'] = "$pathMiolo/html";
        $_SERVER['HTTP_HOST'] = 'miolo2.5';
        $_SERVER['SCRIPT_NAME'] = '/index.php';
        $_SERVER['QUERY_STRING'] = strlen($_SERVER['QUERY_STRING']) ? $_SERVER['QUERY_STRING'] : 'module=' . $this->module . '&action=main';
        $_SERVER['REQUEST_URI'] = "http://{$_SERVER['HTTP_HOST']}/{$_SERVER['SCRIPT_NAME']}?{$_SERVER['QUERY_STRING']}";

        /*
         * Instantiates MIOLO
         */
        $this->MIOLO = MIOLO::getInstance();
        ob_end_clean();

        return $this->MIOLO;
    }

    /**
     * Load MIOLO configuration
     */
    public function loadMIOLO()
    {
        ob_start();
        $this->MIOLO->handlerRequest();
        $this->MIOLO->conf->loadConf($this->module);
        ob_end_clean();
    }

}

$MIOLOConsole = new MIOLOConsole();
$GLOBALS['MIOLO'] = $MIOLO = $MIOLOConsole->getMIOLOInstance($path, $module);
$MIOLOConsole->loadMIOLO();

/**
 * MUnitTest class
 */
class MUnitTest extends PHPUnit_Framework_TestCase
{
    /**
     * @var array Global vars phpunit can't use
     */
    protected $backupGlobalsBlacklist = array('MIOLO', 'autoload', 'MIOLOConsole');

    /**
     * @var array Objects to test
     */
    protected $business;

    /**
     * @var array Table's primary keys
     */
    protected $pkeys = array('id');

    /**
     * Test business objects in business attribute
     */
    public function testBusiness()
    {
        if ( !is_array($this->business) )
        {
            return;
        }

        foreach ( $this->business as $key => $obj )
        {
            echo "Business $key:\n";

            // TODO: BEGIN

            try
            {
                echo "Testing insert\t";
                $ret = $obj->insert();
                $this->assertTrue($ret);
                echo "OK\n";

                echo "Testing search\t";
                $ret = $obj->search($obj);
                $this->assertTrue(count($ret) > 0);
                echo "OK\n";

                // define primary keys if they are not defined
                // FIXME: only works if there is only one primary key
                if ( count($this->pkeys) == 1 )
                {
                    foreach ( $this->pkeys as $pk )
                    {
                        $method = 'get' . $pk;
                        if ( !$obj->$method() )
                        {
                            $method = 'set' . $pk;
                            // first column, last row
                            $obj->$method(current(end($ret)));
                        }
                    }
                }

                echo "Testing update\t";
                $ret = $obj->update();
                $this->assertTrue($ret > 0);
                echo "OK\n";

                echo "Testing delete\t";
                $ret = $obj->delete();
                $this->assertTrue($ret);
                echo "OK\n";
            }
            catch ( MDatabaseException $e )
            {
                echo "\n\n";
                echo $e;
                throw new Exception;
            }

            echo "\n";

            // TODO: ROLLBACK
        }
    }

    /**
     * Add a MBusiness inherited object instance representing a table
     *
     * @param object $business MBusiness instance representing a table
     */
    public function addBusiness($business)
    {
        $this->business[] = $business;
    }
}

?>
