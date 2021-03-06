<?php

/**
 * Brief Class Description.
 * Complete Class Description.
 */
class MReport
{
}

/**
 * Brief Class Description.
 * Complete Class Description.
 */
class MCrystalReport extends MReport
{

    /**
     * Attribute Description.
     */
    public $filetype; // pdf doc xls rtf htm rpt

    /**
     * Attribute Description.
     */
    public $dsodbc; // CROR7 CROR8V36

    /**
     * Attribute Description.
     */
    public $fileout;

    /**
     * Attribute Description.
     */
    public $fileexp;

    /**
     * Attribute Description.
     */
    public $objDb;

    /**
     * Attribute Description.
     */
    public $db;

    /**
     * Brief Description.
     * Complete Description.
     *
     * @param $dbcommon' (tipo) desc
     * @param $dsodbc='CROR8V36' (tipo) desc
     *
     * @returns (tipo) desc
     *
     */
    public function __construct($db = 'admin', $dsodbc = 'CROR8V36')
    {
        $MIOLO = MIOLO::getInstance();
        $this->db = $db;
        $this->objDb = $MIOLO->getDatabase($db);
        $this->dsodbc = $dsodbc;
    }

    /**
     * Brief Description.
     * Complete Description.
     *
     * @param $module (tipo) desc
     * @param $name (tipo) desc
     * @param $parameters (tipo) desc
     * @param $rangeparam=null (tipo) desc
     * @param $filetype=pdf' (tipo) desc
     *
     * @returns (tipo) desc
     *
     */
    public function execute($module, $name, $parameters = null, $rangeparam = null, $filetype = 'pdf')
    {
        $MIOLO = MIOLO::getInstance();
        $page = $MIOLO->getPage();

        //var_dump($this->objDb);
        $db = $this->objDb->db;
        $user = $this->objDb->user;
        $pass = $this->objDb->pass;
        $this->filetype = $filetype;
        $filein = $MIOLO->getModulePath($module, 'reports/' . $name . '.rpt');
        $nameo = uniqid(md5(uniqid("")));
        $this->fileexp = $MIOLO->html_home . '/reports/' . $nameo . '.' . $this->filetype;
        $this->fileout = $MIOLO->url_base . $MIOLO->reports_home . '/' . $nameo . '.' . $this->filetype;
        $cmd = $MIOLO->miolo_home . '/crexport.exe ' . '-U' . "\"$user\"" . ' ' . '-P' . "\"$pass\"" . ' ' . '-F'
                   . $filein . ' ' . '-O' . $this->fileexp . ' ' . '-E' . $this->filetype . ' -S' . $this->dsodbc
                   . ' -D' . $db . ' -XFile ';

        if (is_array($parameters))
        {
            $n = count($parameters);
            $cmd .= '-N' . $n . ' ';

            foreach ($parameters as $pn => $pv)
            {
                $cmd .= '-A' . $pn . " -J\"" . $pv . "\" ";
            }
        }

        if (is_array($rangeparam))
        {
            $n = count($rangeparam);
            $cmd .= '-M' . $n . ' ';

            foreach ($rangeparam as $pn => $pv)
            {
                $cmd .= '-B' . $pn . " -V\"" . $pv . "\" ";
            }
        }

        $p_db = $this->db;
        $p_m = $module;
        $p_f = $name . '.rpt';
        $p_o = $nameo . '.' . $this->filetype;
        $p_par = '-E' . $this->filetype . ' -S' . $this->dsodbc . ' -XFile ';

        if (is_array($parameters))
        {
            $n = count($parameters);
            $p_par .= '-N' . $n . ' ';

            foreach ($parameters as $pn => $pv)
            {
                $p_par .= '-A' . $pn . " -J!$pv! ";
            }
        }

        if (is_array($rangeparam))
        {
            $n = count($rangeparam);
            $p_par .= '-M' . $n . ' ';

            foreach ($rangeparam as $pn => $pv)
            {
                $p_par .= '-B' . $pn . " -V!$pv! ";
            }
        }

        //     var_dump($cmd);
        //     exec($cmd, $a, $retcode);
        $this->fileout
            = "http://creta.cpd.ufjf.br:8080/crreport.php?p_db=$p_db&p_m=$p_m&p_f=$p_f&p_o=$p_o&p_par=$p_par";
    //echo $this->fileout;
    //var_dump($this->fileout);
    //     var_dump($a);
    //     var_dump($retcode);

    }
}
?>