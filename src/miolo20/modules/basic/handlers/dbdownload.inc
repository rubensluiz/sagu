<?php
 /**
 * <--- Copyright 2005-2010 de Solis - Cooperativa de Solu��es Livres Ltda.
 * 
 * Este arquivo � parte do programa Sagu.
 * 
 * O Sagu � um software livre; voc� pode redistribu�-lo e/ou modific�-lo
 * dentro dos termos da Licen�a P�blica Geral GNU como publicada pela Funda��o
 * do Software Livre (FSF); na vers�o 2 da Licen�a.
 * 
 * Este programa � distribu�do na esperan�a que possa ser �til, mas SEM
 * NENHUMA GARANTIA; sem uma garantia impl�cita de ADEQUA��O a qualquer MERCADO
 * ou APLICA��O EM PARTICULAR. Veja a Licen�a P�blica Geral GNU/GPL em
 * portugu�s para maiores detalhes.
 * 
 * Voc� deve ter recebido uma c�pia da Licen�a P�blica Geral GNU, sob o t�tulo
 * "LICENCA.txt", junto com este programa, se n�o, acesse o Portal do Software
 * P�blico Brasileiro no endere�o www.softwarepublico.gov.br ou escreva para a
 * Funda��o do Software Livre (FSF) Inc., 51 Franklin St, Fifth Floor, Boston,
 * MA 02110-1301, USA --->
 * 
 * dbdownload handler.
 * Contains the menus to access turn registers
 *
 * @author Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 * Samuel Koch [samuel@solis.coop.br]
 *
 * @since
 * Class created on 30/08/2007
 *
 **/

$MIOLO->checkAccess('BASIC', A_ADMIN, true, true);

$dbName = $MIOLO->getConf('db.basic.name');
$dbUser = $MIOLO->getConf('db.basic.user');
$dbHost = $MIOLO->getConf('db.basic.host');
$dbPort = $MIOLO->getConf('db.basic.port');
$dbPass = $MIOLO->getConf('db.basic.password');

$bin = SAGU::getParameter('BASIC', 'POSTGRESQL_BASE_PATH') . '/bin/pg_dump';
// Older versions of PHP doesn't have sys_get_temp_dir, so
// this check is necessary here.
if ( function_exists('sys_get_temp_dir') )
{
    $tmpDir = sys_get_temp_dir();
}
else
{
    $tmpDir = '/tmp';
}
$tmpFile = 'dump-' . date('YmdHis') . '.sql.gz';
putenv("PGPASSWORD=$dbPass");
$pg_dump = "$bin $dbName -h $dbHost -p $dbPort -U$dbUser -f $tmpDir/$tmpFile -Z 9 -E UTF-8";
exec($pg_dump, $retData, $retVal);
if ( $retVal != 0 )
{
    $MIOLO->error($pg_dump . ': ' . $retVal);
}
else
{
    header('Content-Type: application/x-compressed-tar');
    header('Content-Length: ' . filesize("$tmpDir/$tmpFile"));
    header('Content-disposition: inline; filename="db' . $tmpFile . '"');
    //passthru("cat $tmpDir/$tmpFile");    
    //exec("rm $tmpDir/$tmpFile", $retData, $retVal);
    readfile("$tmpDir/$tmpFile");
    unlink("$tmpDir/$tmpFile");
}

exit;

?>
