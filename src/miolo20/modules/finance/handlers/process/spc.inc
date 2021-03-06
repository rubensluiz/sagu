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
 * Finance register handler.
 * Contains the menus to access register submenus
 *
 * @author Fabiano Tomasini [fabiano@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Fabiano Tomasini [fabiano@solis.coop.br]
 *
 * @since
 * Class created on 11/12/2005
 *
 **/
$MIOLO = MIOLO::getInstance();
$MIOLO->trace('file:' . $_SERVER['SCRIPT_NAME']);
$MIOLO->checkAccess('finSPC', A_ACCESS, true, true);

$function = MIOLO::_REQUEST('function');

if ( $function == 'resetStack' )
{
    SAGU::resetStack();
}

$module = MIOLO::getCurrentModule();
$home = 'main:process:spc';
$navbar->addOption(_M('SPC', $module), $module, $home, null, array('function' => 'resetStack'));

if ( !$MIOLO->invokeHandler($module, 'process/spc/' . $context->shiftAction()) )
{
    
    $ui = $MIOLO->getUI();
    $btnClose = $MIOLO->getActionURL($module, substr($home, 0, strrpos($home, ':')));
    
    $icon = $ui->getImage($module, 'process-16x16.png');
    $pnlPupilAssistance = new MActionPanel('pnlPupilAssistance', _M('SPC', $module), null, $btnClose, $icon);
    $pnlPupilAssistance->setIconType('small');
    $pnlPupilAssistance->setControlSize(SAGU::getParameter('BASIC', 'MPANEL_DEFAULT_WIDTH'), SAGU::getParameter('BASIC', 'MPANEL_DEFAULT_HEIGHT'));
    
    $menuItem = array(
                        array(_M('Raz�o SPC', $module), 'spcReason-16x16.png', "$home:spcReason"),
                        array(_M('Registrar pessoas no SPC', $module), 'spc-16x16.png', "$home:spc")                        
                     );
    
    $sortMenuItem = SAGU::arraySort($menuItem, 0);
    
    foreach ( $sortMenuItem as $m )
    {
        $pnlPupilAssistance->addAction($m[0], $ui->getImage($module, $m[1]), $module, $m[2]);
    }
    
    $theme->clearContent();
    $theme->insertContent($pnlPupilAssistance);

}

?>

