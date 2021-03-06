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
 * Finacne process handler.
 * Contains the menus to access process submenus
 *
 * @author William Prigol Lopes [william@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 * Daniel Afonso Heisler [daniel@solis.coop.br]
 * Jamiel Spezia [jamiel@solis.coop.br]
 * Samuel Koch [samuel@solis.coop.br]
 * William Prigol Lopes [william@solis.coop.br]
 *
 * @since
 * Class created on 07/12/2005
 *
 **/

$MIOLO->trace('file:' . $_SERVER['SCRIPT_NAME']);
$MIOLO->checkAccess('finRemittanceReturn', A_ACCESS, true, true);

$function = MIOLO::_request('function');
if ( $function == 'resetStack' )
{
    SAGU::resetStack();
}

$home = 'main:process:remittanceReturn';
$navbar->addOption(_M('Remessa e retorno', $module), $module, $home, null, array('function'=>'resetStack'));

if ( !$MIOLO->invokeHandler($module,'process/'.$context->shiftAction()) )
{
    $ui       = $MIOLO->getUI();
    $btnClose = $MIOLO->getActionURL($module, substr($home, 0, strrpos($home, ':')));

    $icon       = $ui->getImage($module, 'process-16x16.png');
    $pnlInvoice = new MActionPanel('pnlInvoice', _M('T�tulo', $module), null, $btnClose, $icon);
    $pnlInvoice->setIconType('small');
    $pnlInvoice->setControlSize(SAGU::getParameter('BASIC', 'MPANEL_DEFAULT_WIDTH'), SAGU::getParameter('BASIC', 'MPANEL_DEFAULT_HEIGHT'));

    $menuItem1 = array( 
        array(_M('Remessa', $module), 'folder-16x16.png', "$home:remittanceInvoice"),
        array(_M('Retorno de t�tulos', $module), 'defaulter-16x16.png', "$home:bankReturn"),
    );
    $sortMenuItem1 = SAGU::arraySort($menuItem1, 0);
    
    foreach ( $sortMenuItem1 as $m )
    {
        $pnlInvoice->addAction($m[0], $ui->getImage($module, $m[1]), $module, $m[2]);
    }

                  
    $pnlAutomaticDebit = new MActionPanel('pnlAutomaticDebit', _M('D�bito autom�tico', $module), null, $btnClose, $icon);
    $pnlAutomaticDebit->setIconType('small');
    $pnlAutomaticDebit->setControlSize(SAGU::getParameter('BASIC', 'MPANEL_DEFAULT_WIDTH'), SAGU::getParameter('BASIC', 'MPANEL_DEFAULT_HEIGHT'));
   
    $menuItem2 = array(
       array(_M('Remessa', $module), 'folder-16x16.png', "$home:remittanceAutomaticDebit"),
       array(_M('Retorno', $module), 'folder-16x16.png', "$home:returnAutomaticDebit"),
    );
    $sortMenuItem2 = SAGU::arraySort($menuItem2, 0);
    
    foreach ( $sortMenuItem2 as $m )
    {
        $pnlAutomaticDebit->addAction($m[0], $ui->getImage($module, $m[1]), $module, $m[2]);
    }

    $menu = array($pnlInvoice, $pnlAutomaticDebit);
    $theme->clearContent();
    $theme->insertContent($menu);
}

?>
