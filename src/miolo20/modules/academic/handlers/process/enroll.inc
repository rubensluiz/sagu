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
 * Academic enroll handler.
 * Contains the menus to access enroll process
 *
 * @author Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 * Daniel Afonso Heisler [daniel@solis.coop.br]
 * Jamiel Spezia [jamiel@solis.coop.br]
 * Samuel Koch [smauel@solis.coop.br]
 * William Prigol Lopes [william@solis.coop.br]
 *
 * @since
 * Class created on 29/09/2005
 *
 **/
$MIOLO->trace('file:' . $_SERVER['SCRIPT_NAME']);


$home = 'main:process:enroll';

$navbar->addOption(_M('Matr�cula', $module), $module, $home);

$MIOLO->getClass('basic', 'access');

$data->home = $home;

$ui = $MIOLO->getUI();

//testar se a pessoa que est� logada � um funcion�rio
if ( $MIOLO->checkAccess('FrmEnrollContract', A_EXECUTE, false, true) )
{
    $content = $ui->getForm($module, 'FrmEnrollContract', $data);
    access::insert(_M('Matr�cula', $module), $home, 'enroll-16x16.png');
}
//abre um formul�rio para login do aluno (SERVICES)
else
{
    $action     = MIOLO::getCurrentAction();
    $postAction = substr($action,0,strrpos($action,':')) . ':enrollPersonData';
    $content    = $ui->getForm($module, 'FrmLogin', $postAction);
}

$theme->clearContent();
$theme->insertContent($content);

?>
