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
 * Tasks handler.
 * Contains the menus to access tasks registers
 *
 * @author Jonas Gualberto Diel [jonas_diel@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 * Arthur Lehdermann [arthur@solis.coop.br]
 * Fabiano Tomasini [fabiano@solis.coop.br]
 * Jonas Gualberto Diel [jonas_diel@solis.coop.br]
 * Moises Heberle [moises@solis.coop.br]
 * Samuel Koch [samuel@solis.coop.br]
 *
 * @since
 * Class created on 18/03/2011
 */

$MIOLO->trace('file:' . $_SERVER['SCRIPT_NAME']);

$home = 'main:config:tasks';
$module = SAGU::getFileModule(__FILE__);
$navbar->addOption(_M('Pend�ncias', $module), $module, $home);

$MIOLO->getClass('basic', 'access');
access::insert(_M('Pend�ncias', $module), $home, 'timeSheet-16x16.png');
$data->home = $home;

$function = MIOLO::_request('function');

$ui = $MIOLO->getUI();
if ( (strlen($function) == 0) || ($function == 'search') )
{
    $MIOLO->checkAccess('FrmTask', A_ACCESS, true, true);

    $frmTask = $ui->getForm($module, 'FrmTaskSearchServices', $data);
    $frmTask->setClose($MIOLO->getActionURL($module, substr($home, 0, strrpos($home, ':'))));

    $content = $frmTask;
}
else
{
    switch ( $function )
    {
        case 'insert':
            $MIOLO->checkAccess('FrmTask', A_INSERT, true, true);
            break;
        case 'update':
            if ( strlen(MIOLO::_request('event')) > 0 )
            {
                $MIOLO->checkAccess('FrmTask', A_ACCESS, true, true);
            }
            break;
        case 'delete':
            $MIOLO->checkAccess('FrmTask', A_DELETE, true, true);
            break;
    }

    $frmTasks = $ui->getForm($module, 'FrmTaskServices');
    $content = $frmTasks;
}

// Theme receives the contents of the form
if ( $theme->page->generateMethod != 'generateAjax' )
{
    $theme->clearContent();
    $theme->insertContent($content);
}
?>