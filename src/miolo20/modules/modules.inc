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
 * Handler modules
 *
 * @author Leovan Tavares da Silva [leovan] [leovan@solis.coop.br]
 *
 * $version: $Id$
 *
 * \b Maintainers \n
 * Equipe Solis [sagu2@solis.coop.br]
 *
 * @since
 * Class created on 14/06/2006
 */

//
// defines user access right constants, which are used in the
// $MIOLO->CheckAccess() and ThemeMenu->AddUserOption() methods.
//


//caso especial onde a fun��o n�o exista e n�o seja poss�vel instalar o pacote do php
if ( !function_exists('mime_content_type') )
{
    function mime_content_type($filename)
    {
        $mime_types = array(

            'txt' => 'text/plain',
            'htm' => 'text/html',
            'html' => 'text/html',
            'php' => 'text/html',
            'css' => 'text/css',
            'js' => 'application/javascript',
            'json' => 'application/json',
            'xml' => 'application/xml',
            'swf' => 'application/x-shockwave-flash',
            'flv' => 'video/x-flv',

            // images
            'png' => 'image/png',
            'jpe' => 'image/jpeg',
            'jpeg' => 'image/jpeg',
            'jpg' => 'image/jpeg',
            'gif' => 'image/gif',
            'bmp' => 'image/bmp',
            'ico' => 'image/vnd.microsoft.icon',
            'tiff' => 'image/tiff',
            'tif' => 'image/tiff',
            'svg' => 'image/svg+xml',
            'svgz' => 'image/svg+xml',

            // archives
            'zip' => 'application/zip',
            'rar' => 'application/x-rar-compressed',
            'exe' => 'application/x-msdownload',
            'msi' => 'application/x-msdownload',
            'cab' => 'application/vnd.ms-cab-compressed',

            // audio/video
            'mp3' => 'audio/mpeg',
            'qt' => 'video/quicktime',
            'mov' => 'video/quicktime',

            // adobe
            'pdf' => 'application/pdf',
            'psd' => 'image/vnd.adobe.photoshop',
            'ai' => 'application/postscript',
            'eps' => 'application/postscript',
            'ps' => 'application/postscript',

            // ms office
            'doc' => 'application/msword',
            'rtf' => 'application/rtf',
            'xls' => 'application/vnd.ms-excel',
            'ppt' => 'application/vnd.ms-powerpoint',

            // open office
            'odt' => 'application/vnd.oasis.opendocument.text',
            'ods' => 'application/vnd.oasis.opendocument.spreadsheet',
        );

        $ext = strtolower(array_pop(explode('.',$filename)));

        if (array_key_exists($ext, $mime_types))
        {
            return $mime_types[$ext];
        }
        elseif (function_exists('finfo_open'))
        {
            $finfo = finfo_open(FILEINFO_MIME);
            $mimetype = finfo_file($finfo, $filename);
            finfo_close($finfo);
            return $mimetype;
        }
        else
        {
            return 'application/octet-stream';
        }
    }
}


$MIOLO = MIOLO::getInstance();
$module = MIOLO::getCurrentModule();
$action = MIOLO::getCurrentAction();

// Autoload classes
$autoload->setFile('sAutoload', $MIOLO->getModulePath('basic', 'classes/sAutoload.class'));
$sAutoload = new sAutoload();
$sAutoload->definePaths();

// Sistema de autologin utilizado apenas por desenvolvedores para facilitar teste com diferentes logins no sistema
$autoLoginUser = $MIOLO->getConf('login.autoLoginUser');
if ( strlen($autoLoginUser) > 0 )
{
    $MIOLO->getAuth()->setLogin(new MLogin($autoLoginUser));
}

// Check login false quando for acao permitida
if ( SAGU::isAllowedAction() )
{
    $MIOLO->setConf('login.check', 'false');
}

$MIOLO->auth = $MIOLO->getAuth();
$MIOLO->perms = $MIOLO->getPerms();
$MIOLO->persistence = new PersistentManagerFactory();
$MIOLO->persistence->setConfigLoader('XML');

define('A_ACCESS', 1); // 000001
define('A_QUERY',  1); // 000001

define('A_INSERT',   3); // 000011
define('A_DELETE',   5); // 000101
define('A_UPDATE',   9); // 001001
define('A_EXECUTE', 17); // 010001

define('A_SYSTEM', 31); // 011111
define('A_ADMIN',  31); // 011111

define('A_DEVELOP', 32); // 100000

// defines true and false value system
define('DB_TRUE',  't');
define('DB_FALSE', 'f');
define('DB_ALL', 'a');
define('SAGU_VERSION', file_get_contents($MIOLO->getModulePath('basic', 'VERSION')));
define('BASE_ENCODING', 'iso-8859-1');

/**
* Realiza login via Portal
**/
if( strlen($_COOKIE['miolo_username']) > 0 && strlen($_COOKIE['m_password']) > 0 )
{
    $uid = str_replace('\"', '"', $_COOKIE['miolo_username']);
    $uid = str_replace("\'", "'", $uid);
    $pwd = $_COOKIE['m_password'];

    //Descriptografa informa��es
    $uid = base64_decode($uid);
    $pwd = base64_decode($pwd);
    
    $loggedUser = $MIOLO->getLogin()->id; //Obtem usu�rio logado no sistema

    // Faz logout para nao manter sessao aberta do usuario anterior que estava no portal
    if ( ( strlen($uid) > 0 ) && ( strlen($loggedUser) > 0 ) && ( strtolower($loggedUser) != strtolower($uid) ) )
    {
        $MIOLO->getAuth()->logout();
    }
    if( strlen($uid) > 0 && strlen($pwd) > 0  && strlen($loggedUser) == 0 )
    {
        $ok = $MIOLO->auth->Authenticate($uid, $pwd);
    }
}

// Define diretorio de relatorios do cliente
if ( SAGU::isClientReportPathExists() )
{
    $MIOLO->setConf('options.reportsdir', SAGU::getClientReportPath());
}

// Utilizado para sinalizar que esta em uma instalacao SAGU
$MIOLO->setConf('temp.is.from.sagu', true);
?>