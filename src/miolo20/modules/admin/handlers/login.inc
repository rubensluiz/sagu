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
 *
 * This file login
 *
 * @author Leovan Tavares da Silva [leovan] [leovan@solis.coop.br]
 *
 * $version: $Id$
 *
 * \b Maintainers \n
 * Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 * Arthur Lehdermann [arthur@solis.coop.br]
 * Daniel Afonso Heisler [daniel@solis.coop.br]
 * Jamiel Spezia [jamiel@solis.coop.br]
 * Leovan Tavares da Silva [leovan@solis.coop.br]
 * Samuel Koch [samuel@solis.coop.br]
 * William Prigol Lopes [william@solis.coop.br]
 * 
 * @since
 * Class created on 14/06/2006
 *
 **/

//BLoqueia o logins para uma URL. Foi criado para os casos onde o cliente que disponibilizar o portal mas n�o disponibilizar o sistema para o administrativo
if ($_SERVER['HTTP_HOST'] == $MIOLO->GetConf('login.denyURL'))
{
    die();
}
 
$MIOLO->LogMessage('[LOGIN] file:'.$_SERVER['SCRIPT_NAME']);
$MIOLO->LogMessage('[LOGIN] Using login prompt');

$MIOLO->page->addScript(SAGU::ABSOLUTE_URL_JS_FILES . 'sagu.js');

$module = 'admin';
$ui = $MIOLO->GetUI();
$theme->ClearContent();
$navbar->AddOption('Login', $module, 'login');
$login = $auth->GetLogin();

// If the user is logged in, send to the start up module
if ($login && !SAGU::userIsFromServices() )
{
   //$form = $ui->GetForm($module,'frmAccess',$login);
   $MIOLO->invokeHandler($MIOLO->getConf('options.common'), 'main');
}
elseif ($MIOLO->GetConf('options.authmd5'))
{
   $form = $ui->GetForm($module,'frmLoginMD5');
}
else
{
   $form = $ui->GetForm($module,'frmLogin');
}
if ($theme->GetContent()  == '')
{
   $theme->InsertContent($form);
}
?>
